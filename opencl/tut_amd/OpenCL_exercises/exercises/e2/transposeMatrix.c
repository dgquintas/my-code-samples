
// tranposeMatrix.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "OpenCL/opencl.h"

#define ROWS 2048
#define COLS 1024

#define BLOCK_ROWS 16
#define BLOCK_COLS 16

int main()
{
	
	cl_float *inputMatrix;
	cl_float *results;
	cl_uint width = COLS;
	cl_uint height = ROWS;
	
	// OpenCL host variables
	cl_uint num_devs_returned;
	cl_context_properties properties[3];
	cl_device_id device_id;
	cl_int err;
	cl_platform_id platform_id;
	cl_uint num_platforms_returned;
	cl_context context;
	cl_command_queue command_queue;
	cl_program program;
	cl_kernel kernel;
	cl_mem input_buffer, output_buffer;
	size_t global[2];
	size_t local[2];

  cl_event profEvent;
	
	// variables used to read kernel source file
      FILE *fp;
      long filelen;
      long readlen;
      char *kernel_src;  // char string to hold kernel source


	// initialize inputMatrix with some data and print it
	int x,y;
	int data=1;

	inputMatrix = malloc(sizeof(cl_float)*width*height);
	results = malloc(sizeof(cl_float)*width*height);
	printf("Input Matrix\n");
	for(x=0 ; x < height; x++)
	{
		for(y=0; y < width; y++)
		{
		   inputMatrix[x*width + y]= data;
		   results[x*width+y]=0;

       data++;

		   //printf("%.2f, ",inputMatrix[y*height+x]);
		}
		//printf("\n");
	}

	// read the kernel
    fp = fopen("transposeMatrix_kernel2.cl","r");
    fseek(fp,0L, SEEK_END);
    filelen = ftell(fp);
    rewind(fp);

    kernel_src = malloc(sizeof(char)*(filelen+1));
    readlen = fread(kernel_src,1,filelen,fp);
    if(readlen!= filelen)
    {
           printf("error reading file\n");
           exit(1);
    }
	
    // ensure the string is NULL terminated
    kernel_src[filelen+1]='\0';


// Insert OpenCL host source here ----

	// get a platform id
	err = clGetPlatformIDs(1,&platform_id,&num_platforms_returned); 

	if (err != CL_SUCCESS)
	{	
		printf("Unable to get Platform ID. Error Code=%d\n",err);
		exit(1);
	}
	
	err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, 
                           &device_id, &num_devs_returned);
	if (err != CL_SUCCESS)
	{	
		printf("Unable to get Device ID. Error Code=%d\n",err);
		exit(1);
	}
	
	// context properties list - must be terminated with 0
	properties[0]= CL_CONTEXT_PLATFORM;
	properties[1]= (cl_context_properties) platform_id;
	properties[2]= 0;
	
	// create context
	context = clCreateContext(properties, 1, &device_id, NULL, NULL, &err);
	if (err != CL_SUCCESS)
	{	
		printf("Unable to create context. Error Code=%d\n",err);
		exit(1);
	}

	// create command queue 
	command_queue = clCreateCommandQueue(context,device_id, CL_QUEUE_PROFILING_ENABLE, &err);
	if (err != CL_SUCCESS)
	{	
		printf("Unable to create command queue. Error Code=%d\n",err);
		exit(1);
	}
	 
	// create program object from source. 
      // kernel_src contains source read from file earlier
	program = clCreateProgramWithSource(context, 1 ,(const char **)
                                          &kernel_src, NULL, &err);
	if (err != CL_SUCCESS)
	{	
		printf("Unable to create program object. Error Code=%d\n",err);
		exit(1);
	}       
	
	err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if (err != CL_SUCCESS)
	{
        printf("Build failed. Error Code=%d\n", err);

		size_t len;
		char buffer[2048];
		// get the build log
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG,
                                  sizeof(buffer), buffer, &len);
		printf("--- Build Log -- \n %s\n",buffer);
		exit(1);
	}

	kernel = clCreateKernel(program, "matrixTranspose", &err);
	if (err != CL_SUCCESS)
	{	
		printf("Unable to create kernel object. Error Code=%d\n",err);
		exit(1);
	}
  size_t kernelWorkGroupSize;
  clGetKernelWorkGroupInfo(kernel, device_id, CL_KERNEL_WORK_GROUP_SIZE, 
      sizeof(size_t), &kernelWorkGroupSize, NULL);
  printf("Kernel work group size: %d\n", kernelWorkGroupSize);

	// create buffer objects to input and output args of kernel function
	input_buffer =
             clCreateBuffer(context,CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR,
                        sizeof(cl_float) * ROWS*COLS, inputMatrix, NULL);
	output_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 
                        sizeof(cl_float) * ROWS*COLS, NULL ,NULL);


  cl_uint DLx = BLOCK_ROWS;
  cl_uint DLy = BLOCK_COLS;
	// set the kernel arguments
	if ( clSetKernelArg(kernel, 0, sizeof(cl_mem), &output_buffer) ||
       clSetKernelArg(kernel, 1, sizeof(cl_mem), &input_buffer)  
       ||  
       clSetKernelArg(kernel, 2, (DLx*DLy)*sizeof(cl_float), NULL)     ||
       clSetKernelArg(kernel, 3, sizeof(cl_uint), &DLx )     ||
       clSetKernelArg(kernel, 4, sizeof(cl_uint), &DLy )  
    ){
		printf("Unable to set kernel arguments. Error Code=%d\n",err);
		exit(1);
	}

	// set the global work dimension size
	global[0]= height;
	global[1]= width;

  local[0] = BLOCK_ROWS;
  local[1] = BLOCK_COLS;

	// Enqueue the kernel object with 
	// Dimension size = 2, 
	// global worksize = global, 
	// local worksize = NULL - let OpenCL runtime determine
	// No event wait list
	err = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, 
                                   global, local, 0, NULL, &profEvent);
	if (err != CL_SUCCESS)
	{	
		printf("Unable to enqueue kernel command. Error Code=%d\n",err);
		exit(1);
	}

	// wait for the command to finish
	clFinish(command_queue);

  cl_ulong startTime, endTime;
  clGetEventProfilingInfo(profEvent, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &startTime, NULL);
  clGetEventProfilingInfo(profEvent, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &endTime, NULL);

  cl_ulong elapsedTime = endTime - startTime;

  printf("Elapsed time: %d ns (%.3f ms)\n", elapsedTime, elapsedTime/10e6);

	// read the output back to host memory
	err = clEnqueueReadBuffer(command_queue, output_buffer, CL_TRUE, 0,
                   sizeof(cl_float)*width*height, results, 0, NULL, NULL);
	if (err != CL_SUCCESS)
	{	
		printf("Error enqueuing read buffer command. Error Code=%d\n",err);
		exit(1);
	}


//  for(x = 0; x < height; x++) {
//    for(y=0; y < width; y++) {
//      printf("%.1f ", inputMatrix[x * width + y]);
//    }
//    printf("\n");
//  }
//  printf("\n");
//  for(x = 0; x < width; x++) {
//    for(y=0; y < height; y++) {
//      printf("%.1f ", results[x * height + y]);
//    }
//    printf("\n");
//  }

  for(x = 0; x < height; x++) {
    for(y=0; y < width; y++) {
      if(inputMatrix[x * width + y] != results[ y * height + x]){
        printf("%.1f vs %.1f\n", inputMatrix[x * width + y], results[ y * height + x]);
      }
    }
  }




	// clean up
	clReleaseMemObject(input_buffer);
	clReleaseMemObject(output_buffer);
	clReleaseProgram(program);
	clReleaseKernel(kernel);
	clReleaseCommandQueue(command_queue);
	clReleaseContext(context);
	free(kernel_src);
	free(inputMatrix);
	free(results);
	return 0;
}

