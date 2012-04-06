#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <OpenCL/opencl.h>

#define DATA_SIZE 100

const char *KernelSource = 
"__kernel void hello(__global float *input, __global float *output)\n"\
"{\n"\
  "  size_t id = get_global_id(0);\n"\
"  output[id] = input[id] * input[id];\n"\
"}\n"\
"\n";


int main(int argc, char** argv){

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
  cl_mem input, output;
  size_t global;

  int i;
  float inputData[DATA_SIZE];
  float results[DATA_SIZE] = {0};
  for(i = 0; i < DATA_SIZE; i++){
    inputData[i] = rand() / (float)RAND_MAX;
  }
  
  if( clGetPlatformIDs(3, &platform_id, &num_of_platforms) != CL_SUCCESS ){
    printf("Unable to get platform_id\n");
    return 1;
  }

  if( clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 3, 
        &device_id, &num_of_devices) != CL_SUCCESS ){
    printf("Unable to get device_id\n");
    return 1;
  }

  char deviceName[128];
  size_t charsWritten;
  clGetDeviceInfo( device_id, CL_DEVICE_NAME, 128, deviceName, &charsWritten);
  deviceName[charsWritten] = '\0';

  cl_uint max_compute_units;
  clGetDeviceInfo( device_id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint),
      &max_compute_units, NULL);

  printf("Using device %s (%d units)\n", deviceName, max_compute_units);

  properties[0] = CL_CONTEXT_PLATFORM;
  properties[1] = (cl_context_properties) platform_id;
  properties[2] = 0;
      
  context = clCreateContext(properties, 1, &device_id, NULL, NULL, &err);
  command_queue = clCreateCommandQueue(context, device_id, 0, &err);
  program = clCreateProgramWithSource(context, 1, (const char**)&KernelSource,
      NULL, &err);
  if( clBuildProgram( program, 0, NULL, NULL, NULL, NULL ) != CL_SUCCESS){
    printf("Error building program\n");
    return 1;
  }

  char* src[1024]; size_t srcRetSize;
  clGetProgramInfo(program, CL_PROGRAM_SOURCE, 1024, src, &srcRetSize);
  src[srcRetSize] = '\0';
  printf("Source: \n%s\n", src);

  kernel = clCreateKernel(program, "hello", &err);



  input = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(float) * DATA_SIZE, NULL, NULL);
  output = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * DATA_SIZE, NULL, NULL);

  clEnqueueWriteBuffer(command_queue, input, CL_TRUE, 0, sizeof(float) * DATA_SIZE, inputData,
      0, NULL, NULL); 

  clSetKernelArg(kernel, 0, sizeof(cl_mem), &input);
  clSetKernelArg(kernel, 1, sizeof(cl_mem), &output);
  global = DATA_SIZE;

  clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global, NULL, 0, NULL,NULL);
  clFinish(command_queue);


  clEnqueueReadBuffer(command_queue, output, CL_TRUE, 0, sizeof(float) * DATA_SIZE, results, 
      0, NULL, NULL);

  printf("output: \n");
  for(i=0; i < DATA_SIZE; i++){
    printf("%f -> %f\n", inputData[i], results[i]);
    assert( inputData[i] * inputData[i] == results[i]) ;
  }
  printf("\n");

  clReleaseMemObject(input);
  clReleaseMemObject(output);
  clReleaseProgram(program);
  clReleaseKernel(kernel);
  clReleaseCommandQueue(command_queue);
  clReleaseContext(context);

  return 0;
}

