#include <aio.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define BUFSIZE 4096

int done = 0;

void aio_completion_handler(int signo, siginfo_t *info, void* context){
    struct aiocb *req;
    int ret;

    if( info->si_signo == SIGIO ){
        req = (struct aiocb *)info->si_value.sival_ptr;

        if (aio_error(req)== 0) {
            if ((ret = aio_return( req )) > 0) {
    //            printf("Read %d bytes\n", ret);

                req->aio_offset += ret;

                aio_read( req );
            }
        }
        if( ret == 0 ){
            done = 1;
        }
    }
}



int main(){
    int fd, ret;
    struct aiocb my_aiocb;

    fd = open( "file.txt", O_RDONLY );
    if (fd < 0) perror("open");

    struct sigaction sig_act;

    sigemptyset(&sig_act.sa_mask);
    sig_act.sa_flags = SA_SIGINFO;
    sig_act.sa_sigaction = aio_completion_handler;


    /* Zero out the aiocb structure (recommended) */
    bzero( (char *)&my_aiocb, sizeof(struct aiocb) );

    /* Allocate a data buffer for the aiocb request */
    my_aiocb.aio_buf = malloc(BUFSIZE+1);
    if (!my_aiocb.aio_buf) perror("malloc");

    /* Initialize the necessary fields in the aiocb */
    my_aiocb.aio_fildes = fd;
    my_aiocb.aio_nbytes = BUFSIZE;
    my_aiocb.aio_offset = 0;

    my_aiocb.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    my_aiocb.aio_sigevent.sigev_signo = SIGIO;
    my_aiocb.aio_sigevent.sigev_value.sival_ptr = &my_aiocb;
 
    ret = sigaction( SIGIO, &sig_act, NULL );
    if( ret ){
        perror("sigaction");
    }

    aio_read( &my_aiocb );

//    if( ret == 0 ){
//        printf("EOF\n");
//        printf("Total read %zd bytes\n", total);
//    }
//    else{
//        perror("aio_read2");
//    }

   const struct aiocb *const cblist[1] = { &my_aiocb };



    while(1){
        aio_suspend( cblist, 1, NULL );
        if( done ){
            break;
        }
    }
    return 0;
}



