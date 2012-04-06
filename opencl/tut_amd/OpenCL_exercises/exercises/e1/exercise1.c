#include <stdio.h>
#include "CL/cl.h"

#define DATA_SIZE 10

const char *ProgramSource = 
"__kernel void swap(__global float *array1, __global float *array2)\n"\
"{\n"\
"  size_t id = get_global_id(0);\n"\
"  float tmp = array2[id];\n"\
"  array2[id] = array1[id];\n"\
"  array1[id] = tmp;\n"\
"}\n";


int main(void)
{

	float inputData1[DATA_SIZE]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	float inputData2[DATA_SIZE]={11,12,13,14,15, 16, 17, 18, 19, 20};

	int i;

// ==== OpenCL code start

// Update the OpenCL host code and kernel function to swap inputData1 and inputData2 arrays
  
  cl_context context;
  cl_context_properties properties[3];
  cl_kernel kernel;
  cl_command_queue command_queue;
  cl_program program;
  cl_int err;

  cl_uint num_of_platforms=0;
  cl_platform_id platform_id;

  cl_device_id device_id;
  cl_uint num_of_devices=0;

  cl_mem a1, a2;
  size_t global;

// retreive a list of platforms avaible
  if( clGetPlatformIDs(1, &platform_id, &num_of_platforms) != CL_SUCCESS ){
    printf("Unable to get platform_id\n");
    return 1;
  }
  
// retreive OpenCL device CPU or GPU
  if( clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &num_of_devices)
      != CL_SUCCESS ){
    printf("Unable to get device_id\n");
    return 1;
  }

// create context
  properties[0] = CL_CONTEXT_PLATFORM ;
  properties[1] = (cl_context_properties) platform_id;
  properties[2] = 0;
  context = clCreateContext(properties, 1, &device_id, NULL, NULL, &err);


// create command queue
  command_queue = clCreateCommandQueue(context, device_id, 0, &err);

// create program object
  program = clCreateProgramWithSource(context, 1, (const char**)&ProgramSource, NULL, &err);
  if( clBuildProgram(program, 0, NULL, NULL, NULL, NULL) != CL_SUCCESS ){
    printf("Error building program\n");
    return 1;
  }

// create kernel object
  kernel = clCreateKernel(program, "swap", &err);


// create memory objects 
  a1 = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float)*DATA_SIZE, NULL, NULL);
  a2 = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float)*DATA_SIZE, NULL, NULL);

// copy data to memory objects
  clEnqueueWriteBuffer(command_queue, a1, CL_TRUE, 0, sizeof(float)*DATA_SIZE, 
    inputData1, 0, NULL, NULL);  
  clEnqueueWriteBuffer(command_queue, a2, CL_TRUE, 0, sizeof(float)*DATA_SIZE, 
    inputData2, 0, NULL, NULL);  

// set kernel arguments
  clSetKernelArg(kernel, 0, sizeof(cl_mem), &a1);
  clSetKernelArg(kernel, 1, sizeof(cl_mem), &a2);
  global = DATA_SIZE;

// enqueue kernel in command queue
  clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global, NULL, 
      0,NULL,NULL);
  clFinish(command_queue);

// read data back from device
  clEnqueueReadBuffer(command_queue, a1, CL_TRUE, 0, sizeof(float)*DATA_SIZE, 
      inputData1, 0, NULL, NULL);
  clEnqueueReadBuffer(command_queue, a2, CL_TRUE, 0, sizeof(float)*DATA_SIZE, 
      inputData2, 0, NULL, NULL);

// clean up
  clReleaseMemObject(a1);
  clReleaseMemObject(a2);
  clReleaseProgram(program);
  clReleaseKernel(kernel);
  clReleaseCommandQueue(command_queue);
  clReleaseContext(context);

// ==== OpenCL code end

	// print the results
	printf("output: \na1: ");
	for(i=0;i<DATA_SIZE; i++)
	{
		 printf("%f ",inputData1[i]);
	}

	printf("\na2: ");
	for(i=0;i<DATA_SIZE; i++)
	{
		 printf("%f ",inputData2[i]);
	}
	printf("\n");

	return 0;
}



