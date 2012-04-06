#include <aio.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE 4096

int main(){
    int fd, ret;
    struct aiocb my_aiocb;

    fd = open( "file.txt", O_RDONLY );
    if (fd < 0) perror("open");

    /* Zero out the aiocb structure (recommended) */
    bzero( (char *)&my_aiocb, sizeof(struct aiocb) );

    /* Allocate a data buffer for the aiocb request */
    my_aiocb.aio_buf = malloc(BUFSIZE+1);
    if (!my_aiocb.aio_buf) perror("malloc");

    /* Initialize the necessary fields in the aiocb */
    my_aiocb.aio_fildes = fd;
    my_aiocb.aio_nbytes = BUFSIZE;
    my_aiocb.aio_offset = 0;

    size_t total = 0;

    do {
        ret = aio_read( &my_aiocb );
        if (ret < 0) perror("aio_read");

        //    while ( aio_error( &my_aiocb ) == EINPROGRESS ){
        //        printf("Working...\n");
        //    }
        const struct aiocb *const cblist[1] = { &my_aiocb };
        aio_suspend( cblist, 1, NULL );

        if ((ret = aio_return( &my_aiocb )) > 0) {
            //printf("Read %d bytes\n", ret);
            total += ret;

            my_aiocb.aio_offset += ret;
        }
    } while( ret > 0);
    if( ret == 0 ){
        printf("EOF\n");
        printf("Total read %zd bytes\n", total);
    }
    else{
        perror("aio_read2");
    }

    return 0;
}



