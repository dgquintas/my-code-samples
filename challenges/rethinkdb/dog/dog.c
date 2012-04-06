#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <aio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

#define BUFSIZE (1048576*4)

#define MAX_NUM_OUTFILES 128
#ifndef PATH_MAX
    #define PATH_MAX 256
#endif


/* From glibc's manual.
 *
 * Subtract the `struct timeval' values X and Y,
   storing the result in RESULT.
   Return 1 if the difference is negative, otherwise 0.  */
int timeval_subtract (result, x, y)
     struct timeval *result, *x, *y;
{
    /* Perform the carry for the later subtraction by updating y. */
    if (x->tv_usec < y->tv_usec) {
        int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
        y->tv_usec -= 1000000 * nsec;
        y->tv_sec += nsec;
    }
    if (x->tv_usec - y->tv_usec > 1000000) {
        int nsec = (x->tv_usec - y->tv_usec) / 1000000;
        y->tv_usec += 1000000 * nsec;
        y->tv_sec -= nsec;
    }

    /* Compute the time remaining to wait.
       tv_usec is certainly positive. */
    result->tv_sec = x->tv_sec - y->tv_sec;
    result->tv_usec = x->tv_usec - y->tv_usec;

    /* Return 1 if result is negative. */
    return x->tv_sec < y->tv_sec;
}

/////////////////////////////////////////////

typedef struct aiocb aiocb;

aiocb* create_aiocb(const char* outfile, char* srcbuf){
    int fd = open( outfile, 
            O_WRONLY | O_APPEND | O_CREAT | O_TRUNC , 
            S_IRUSR | S_IWUSR );
    if( fd < 0 ){ perror("open"); }
    aiocb* aio_req = (aiocb*)calloc(1, sizeof(aiocb)); //XXX: free it
    if( !aio_req ){ perror("malloc aiocb"); }
    aio_req->aio_fildes = fd; //XXX: close it!
    aio_req->aio_buf = srcbuf; 

    return aio_req;
}

// could have been a macro... but well, this isn't gonna be
// cpu-bound anyway
int min(int a, int b){
    return a < b ? a : b;
}

// submit a write request over "req" of "n" bytes
void request_write(aiocb* req, int n){
    req->aio_nbytes = min(n,BUFSIZE);
    if( aio_write(req) ){ perror("aio_write"); }
}

int main(int argc, char** argv){
    int i;
    if( argc <= 1 || argc > MAX_NUM_OUTFILES ){
        fprintf(stderr, "Usage: %s FILE ... (up to %d)\n", 
                argv[0], MAX_NUM_OUTFILES);
        return 1;
    }
    const int num_out_files = argc-1;
    char** outfiles = (char**)malloc( sizeof(char*)*num_out_files );
    if( !outfiles ){ perror("malloc outfiles"); }
    for(i=0; i < num_out_files; i++){
        outfiles[i] = (char*)malloc(PATH_MAX);
        if( !outfiles[i] ){ perror("malloc outfiles") }
    }

    aiocb** aio_reqs = (aiocb**)malloc(sizeof(aiocb*)*num_out_files);
    if( !aio_reqs ){ perror("malloc aiocbs"); }

    char* buf = (char*)malloc(BUFSIZE);
    if( !buf ){ perror("malloc stdin buffer"); }

    for(i=0; i < num_out_files; i++){
        strncpy(outfiles[i], argv[i+1], PATH_MAX);
        outfiles[i][PATH_MAX] = '\0'; // just in case. strncpy
        // doesn't terminate the dst string if src is longer than n
        aio_reqs[i] = create_aiocb(outfiles[i], buf);
    }
    
    int br, totalr = 0;
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    while( (br=fread(buf, 1, BUFSIZE, stdin) ) ){
        totalr += br;
        // we've got some fresh data in "buf". Request writing it
        // to all the aiocb's
        //
        // We issue one requests for each outfile. Once all these have
        // finished, read next chunk of data from stdin
        int remaining_reqs = num_out_files;
        for(i=0; i < num_out_files; i++){
            request_write( aio_reqs[i], br );
        }
        int ret;
        while( remaining_reqs && 
                !(ret= aio_suspend( (const struct aiocb **const)aio_reqs, 
                        num_out_files, NULL ) ) ) {
            int written;
            for(i=0; i < num_out_files; i++){
                if (aio_error(aio_reqs[i])== 0) {
                    if ((written = aio_return( aio_reqs[i] )) > 0) {
                        --remaining_reqs ;
                        break;
                    }
                }
            }
        }
        if( remaining_reqs > 0 || ret ){
            perror("aio_suspend");
        }
    }

    // cleanup
    for(i=0; i < num_out_files; i++){
        aiocb* req = aio_reqs[i];
        close(req->aio_fildes);
        free(req);
    }
    free(aio_reqs);
    free(buf);

    for(i=0; i < num_out_files; i++){
        free(outfiles[i]);
    }
    free(outfiles);
    fclose(stdin);

    // stats
    float mb_read = totalr/(1024*1024.0);
    float mb_written = mb_read * num_out_files;
    gettimeofday(&tv2, NULL);
    struct timeval diff;
    timeval_subtract(&diff, &tv2, &tv1);
    float secs = diff.tv_sec + diff.tv_usec/1e6;
    fprintf(stderr, "Elapsed: %f secs\n", secs);
    fprintf(stderr, "%f MB read (%f MB/s)\n", mb_read, mb_read/secs);
    fprintf(stderr, "%f MB written (%f MB/s)\n", mb_written, mb_written/secs);

    return 0;
}



