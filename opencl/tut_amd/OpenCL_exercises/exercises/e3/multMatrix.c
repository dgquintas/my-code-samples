
// ------ multMatrix.c ----------

#include <stdio.h>
#include <stdlib.h>
#include "CL/cl.h"

#define ROWS 1024 
#define COLS 1024 

#define BLOCK_SIZE 8
int main()
{
	
	cl_float *inputMatrix1;
	cl_float *inputMatrix2;
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
	cl_mem input_buffer1,input_buffer2, output_buffer;
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
	int data=0;

	inputMatrix1 = malloc(sizeof(cl_float)*width*height);
	inputMatrix2 = malloc(sizeof(cl_float)*width*height);
	results = malloc(sizeof(cl_float)*width*height);

	for(y=0;y<height;y++)
	{
		for(x=0;x<width;x++)
		{
		   inputMatrix1[y*height+x]= data;
		   inputMatrix2[y*height+x]= data;
		   results[y*height+x]=0;
                   data++;

		}
	}

	// read the kernel
	fp = fopen("multMatrix_kernel.cl","r");
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


// OpenCL host source starts here ----

	// get a platform id
	err = clGetPlatformIDs(1,&platform_id,&num_platforms_returned); 

	if (err != CL_SUCCESS)
	{	
		printf("Unable to get Platform ID. Error Code=%d\n",err);
		exit(1);
	}
	
	err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &num_devs_returned);
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
	 
	// create program object from source. kernel_src contains 
	// source read from file earlier
	program = clCreateProgramWithSource(context, 1 ,(const char **) &kernel_src, NULL, &err);
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
		char buffer[4096];
		// get the build log
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		printf("--- Build Log -- \n %s\n",buffer);
		exit(1);
	}

	//kernel = clCreateKernel(program, "multMatrix", &err);
	kernel = clCreateKernel(program, "multMatrixSimple", &err);
	if (err != CL_SUCCESS)
	{	
		printf("Unable to create kernel object. Error Code=%d\n",err);
		exit(1);
	}

	// create buffer objects to input and output args of kernel function
	input_buffer1 = clCreateBuffer(context,CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(cl_float) * ROWS*COLS, inputMatrix1, NULL);
	input_buffer2 = clCreateBuffer(context,CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(cl_float) * ROWS*COLS, inputMatrix2, NULL);
	output_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(cl_float) * ROWS*COLS, NULL ,NULL);
	// set the kernel arguments
	if ( clSetKernelArg(kernel, 0, sizeof(cl_mem), &output_buffer) ||
         clSetKernelArg(kernel, 1, sizeof(cl_mem), &input_buffer1) ||
         clSetKernelArg(kernel, 2, sizeof(cl_mem), &input_buffer2) ||
         clSetKernelArg(kernel, 3, sizeof(cl_uint), &width) ||
         clSetKernelArg(kernel, 4, sizeof(cl_uint), &width) != CL_SUCCESS) 
	{
		printf("Unable to set kernel arguments. Error Code=%d\n",err);
		exit(1);
	}

	// set the global & local work size
	global[0]= width;
	global[1]= height;

	local[0]=BLOCK_SIZE;
	local[1]=BLOCK_SIZE;

	// Enqueue the kernel object with 
	// Dimension size = 2, 
	// global worksize = global, 
	// local worksize = local
	// No event wait list
	err = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, global,local, 0, NULL, &profEvent);
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

  printf("Elapsed time: %lu ns (%.3f ms)\n", elapsedTime, elapsedTime/10e6);

	// read the output back to host memory
	err = clEnqueueReadBuffer(command_queue, output_buffer, CL_TRUE, 0, sizeof(cl_float)*width*height, results, 0, NULL, NULL);
	if (err != CL_SUCCESS)
	{	
		printf("Error enqueuing read buffer command. Error Code=%d\n",err);
		exit(1);
	}

	// clean up
	clReleaseMemObject(input_buffer1);
	clReleaseMemObject(input_buffer2);
	clReleaseMemObject(output_buffer);
	clReleaseProgram(program);
	clReleaseKernel(kernel);
	clReleaseCommandQueue(command_queue);
	clReleaseContext(context);

// ---- End of OpenCL host portion 

	
//  uncoment this block to print out matrix results
/*
	printf("\nMatrix A\n");
	for(y=0;y<height;y++)
	{
	   for(x=0;x<width;x++)
	   {
	      printf("%.2f , ",inputMatrix1[y*height+x]);
	   }
	   printf("\n");
	}
	  
	printf("\nMatrix B\n");
	for(y=0;y<height;y++)
	{
	    for(x=0;x<width;x++)
	   {
	      printf("%.2f , ",inputMatrix2[y*height+x]);
	   }
	   printf("\n");
	}
	// print out the transposed matrix 
	printf("\n Matrix A + Matrix B \n");
	for(y=0;y<height;y++)
	{
	   for(x=0;x<width;x++)
	   {
	      printf("%.2f , ",results[y*height+x]);
	   }
	   printf("\n");
	}
*/	  
	free(kernel_src);
	free(inputMatrix1);
	free(inputMatrix2);
	free(results);
	return 0;
}

