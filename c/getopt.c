#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
char *optarg; //points to an option argument
int optind;   //index of the next argv argument for a subseq call to getopt
int optopt;   //the last known option char returned by getopt
int opterr;   //whether to return '?' when an unknown option or a missing arg. if opterr == 0, no '?'. 1 by def
int optreset; //set to 1 before batches of calls to getopt

int getopt(int argc, char * const argv[], const char *optstring);

The option string optstring may contain the following elements: individual
characters, and characters followed by a colon to indicate an option argument
is to follow.  For example, an option string "x" recognizes an option ``-x'',
and an option string "x:" recognizes an option and argument ``-x argument''.
It does not matter to getopt() if a following argument has leading white space.
     
 * 
 */

void usage(){
    fprintf(stderr, "%s\n", "Usage: [-b] [-f file]\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv){
    int ch;

    while ((ch = getopt(argc, argv, "bf:")) != -1) {
            switch (ch) {
            case 'b':
                    printf("-b flag activated\n");
                    break;
            case 'f':
                    printf("-f %s activated\n", optarg);
                    break;
            case '?':
            default:
                    usage();
            }
    }
    argc -= optind;
    argv += optind;

    return 0;

}

