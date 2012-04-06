/* ============================================================

Copyright (c) 2010 Advanced Micro Devices, Inc.  All rights reserved.

Redistribution and use of this material is permitted under the following 
conditions:

Redistributions must retain the above copyright notice and all terms of this 
license.

In no event shall anyone redistributing or accessing or using this material 
commence or participate in any arbitration or legal action relating to this 
material against Advanced Micro Devices, Inc. or any copyright holders or 
contributors. The foregoing shall survive any expiration or termination of 
this license or any agreement or access or use related to this material. 

ANY BREACH OF ANY TERM OF THIS LICENSE SHALL RESULT IN THE IMMEDIATE REVOCATION 
OF ALL RIGHTS TO REDISTRIBUTE, ACCESS OR USE THIS MATERIAL.

THIS MATERIAL IS PROVIDED BY ADVANCED MICRO DEVICES, INC. AND ANY COPYRIGHT 
HOLDERS AND CONTRIBUTORS "AS IS" IN ITS CURRENT CONDITION AND WITHOUT ANY 
REPRESENTATIONS, GUARANTEE, OR WARRANTY OF ANY KIND OR IN ANY WAY RELATED TO 
SUPPORT, INDEMNITY, ERROR FREE OR UNINTERRUPTED OPERA TION, OR THAT IT IS FREE 
FROM DEFECTS OR VIRUSES.  ALL OBLIGATIONS ARE HEREBY DISCLAIMED - WHETHER 
EXPRESS, IMPLIED, OR STATUTORY - INCLUDING, BUT NOT LIMITED TO, ANY IMPLIED 
WARRANTIES OF TITLE, MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, 
ACCURACY, COMPLETENESS, OPERABILITY, QUALITY OF SERVICE, OR NON-INFRINGEMENT. 
IN NO EVENT SHALL ADVANCED MICRO DEVICES, INC. OR ANY COPYRIGHT HOLDERS OR 
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, PUNITIVE,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, REVENUE, DATA, OR PROFITS; OR 
BUSINESS INTERRUPTION) HOWEVER CAUSED OR BASED ON ANY THEORY OF LIABILITY 
ARISING IN ANY WAY RELATED TO THIS MATERIAL, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE. THE ENTIRE AND AGGREGATE LIABILITY OF ADVANCED MICRO DEVICES, 
INC. AND ANY COPYRIGHT HOLDERS AND CONTRIBUTORS SHALL NOT EXCEED TEN DOLLARS 
(US $10.00). ANYONE REDISTRIBUTING OR ACCESSING OR USING THIS MATERIAL ACCEPTS 
THIS ALLOCATION OF RISK AND AGREES TO RELEASE ADVANCED MICRO DEVICES, INC. AND 
ANY COPYRIGHT HOLDERS AND CONTRIBUTORS FROM ANY AND ALL LIABILITIES, 
OBLIGATIONS, CLAIMS, OR DEMANDS IN EXCESS OF TEN DOLLARS (US $10.00). THE 
FOREGOING ARE ESSENTIAL TERMS OF THIS LICENSE AND, IF ANY OF THESE TERMS ARE 
CONSTRUED AS UNENFORCEABLE, FAIL IN ESSENTIAL PURPOSE, OR BECOME VOID OR 
DETRIMENTAL TO ADVANCED MICRO DEVICES, INC. OR ANY COPYRIGHT HOLDERS OR 
CONTRIBUTORS FOR ANY REASON, THEN ALL RIGHTS TO REDISTRIBUTE, ACCESS OR USE 
THIS MATERIAL SHALL TERMINATE IMMEDIATELY. MOREOVER, THE FOREGOING SHALL 
SURVIVE ANY EXPIRATION OR TERMINATION OF THIS LICENSE OR ANY AGREEMENT OR 
ACCESS OR USE RELATED TO THIS MATERIAL.

NOTICE IS HEREBY PROVIDED, AND BY REDISTRIBUTING OR ACCESSING OR USING THIS 
MATERIAL SUCH NOTICE IS ACKNOWLEDGED, THAT THIS MATERIAL MAY BE SUBJECT TO 
RESTRICTIONS UNDER THE LAWS AND REGULATIONS OF THE UNITED STATES OR OTHER 
COUNTRIES, WHICH INCLUDE BUT ARE NOT LIMITED TO, U.S. EXPORT CONTROL LAWS SUCH 
AS THE EXPORT ADMINISTRATION REGULATIONS AND NATIONAL SECURITY CONTROLS AS 
DEFINED THEREUNDER, AS WELL AS STATE DEPARTMENT CONTROLS UNDER THE U.S. 
MUNITIONS LIST. THIS MATERIAL MAY NOT BE USED, RELEASED, TRANSFERRED, IMPORTED,
EXPORTED AND/OR RE-EXPORTED IN ANY MANNER PROHIBITED UNDER ANY APPLICABLE LAWS, 
INCLUDING U.S. EXPORT CONTROL LAWS REGARDING SPECIFICALLY DESIGNATED PERSONS, 
COUNTRIES AND NATIONALS OF COUNTRIES SUBJECT TO NATIONAL SECURITY CONTROLS. 
MOREOVER, THE FOREGOING SHALL SURVIVE ANY EXPIRATION OR TERMINATION OF ANY 
LICENSE OR AGREEMENT OR ACCESS OR USE RELATED TO THIS MATERIAL.

NOTICE REGARDING THE U.S. GOVERNMENT AND DOD AGENCIES: This material is 
provided with "RESTRICTED RIGHTS" and/or "LIMITED RIGHTS" as applicable to 
computer software and technical data, respectively. Use, duplication, 
distribution or disclosure by the U.S. Government and/or DOD agencies is 
subject to the full extent of restrictions in all applicable regulations, 
including those found at FAR52.227 and DFARS252.227 et seq. and any successor 
regulations thereof. Use of this material by the U.S. Government and/or DOD 
agencies is acknowledgment of the proprietary rights of any copyright holders 
and contributors, including those of Advanced Micro Devices, Inc., as well as 
the provisions of FAR52.227-14 through 23 regarding privately developed and/or 
commercial computer software.

This license forms the entire agreement regarding the subject matter hereof and 
supersedes all proposals and prior discussions and writings between the parties 
with respect thereto. This license does not affect any ownership, rights, title,
or interest in, or relating to, this material. No terms of this license can be 
modified or waived, and no breach of this license can be excused, unless done 
so in a writing signed by all affected parties. Each term of this license is 
separately enforceable. If any term of this license is determined to be or 
becomes unenforceable or illegal, such term shall be reformed to the minimum 
extent necessary in order for this license to remain in effect in accordance 
with its terms as modified by such reformation. This license shall be governed 
by and construed in accordance with the laws of the State of Texas without 
regard to rules on conflicts of law of any state or jurisdiction or the United 
Nations Convention on the International Sale of Goods. All disputes arising out 
of this license shall be subject to the jurisdiction of the federal and state 
courts in Austin, Texas, and all defenses are hereby waived concerning personal 
jurisdiction and venue of these courts.

============================================================ */

// ------ multMatrix.c ----------

#include <stdio.h>
#include <stdlib.h>
#include "CL/cl.h"

#define ROWS 2048
#define COLS 2048

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
	
	err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 1, &device_id, &num_devs_returned);
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
	command_queue = clCreateCommandQueue(context,device_id, 0, &err);
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
	err = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, global,local, 0, NULL, NULL);
	if (err != CL_SUCCESS)
	{	
		printf("Unable to enqueue kernel command. Error Code=%d\n",err);
		exit(1);
	}

	// wait for the command to finish
	clFinish(command_queue);

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

