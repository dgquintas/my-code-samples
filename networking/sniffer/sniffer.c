#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "protos.h"

void die(const char* errmsg){
    fprintf(stderr, "Faaail: %s\n", errmsg);
    exit(EXIT_FAILURE);
}

void usage(char* progName){
    fprintf(stderr, "Usage: %s [-i interface]\n", progName);
    exit(EXIT_SUCCESS);
}

typedef struct {
    char iface[8];
} options_t;

int parseOptions(int argc, char** argv, options_t* opts){
    char ch;
    memset(opts, 0, sizeof(options_t));

    while( (ch = getopt(argc, argv, "i:h")) != -1 ){
        switch(ch) {
            case 'i':
                strncpy(opts->iface, optarg, 7); 
                opts->iface[7] = '\0';
                break;
            case '?':
            case 'h':
            default:
                usage(argv[0]);
        }   
    }   
    return optind;
}

char* ipToHost(uint32_t ip, char* host, size_t n){
    int rv;
    struct in_addr sin_addr;
    sin_addr.s_addr = ip;

    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = 0;
    sa.sin_addr = sin_addr;
    
    if( getnameinfo( (const struct sockaddr*)&sa, sizeof sa, host, n, NULL, 0, 0 ) ){
        const char* errmsg = gai_strerror(rv);
        die(errmsg);
    }

    return host;
}
    



int main(int argc, char** argv){
    int i;
    char errbuf[PCAP_ERRBUF_SIZE];
    char *dev;
    options_t opts; 
    pcap_t *handle;

    int nopts = parseOptions(argc, argv, &opts);
    argc -= nopts;
    argv += nopts;

    if( opts.iface[0] == '\0' ){
        dev = pcap_lookupdev(errbuf);
        if( dev == NULL){
            die(errbuf);
        }
    }
    else{
        dev = opts.iface;
    }

    handle = pcap_open_live(dev, BUFSIZ, 1 /*promisc*/, 1000 /*ms. timeout*/, errbuf);
    if( handle == NULL ){
        die(errbuf);
    }
    printf("Using interface '%s'\n", dev );

    const u_char* pkt;
    struct pcap_pkthdr pkthdr;
    while( !(pkt = pcap_next(handle, &pkthdr)) );

    const struct ethernetHeader* ether;
    ether = (const struct ethernetHeader*)pkt;
    printf("Ethernet src: %02X", ether->src[0]);
    for(i=1; i<ETHER_ADDR_LEN; i++){
        printf(":%02X", ether->src[i]);
    }
    printf("\n");
    printf("Ethernet dst: %02X", ether->dst[0]);
    for(i=1; i<ETHER_ADDR_LEN; i++){
        printf(":%02X", ether->dst[i]);
    }
    printf("\n");
    printf("Ethernet type: %d\n", ether->type);


    const struct ipHeader* ip;
    ip = (const struct ipHeader*)(pkt+ETHER_HDR_LEN);
    char ipStr[16], host[NI_MAXHOST];
    printf("IP src: %s (%s)\n", 
            inet_ntop(AF_INET, &(ip->src), ipStr, 16), 
            ipToHost(ip->src, host, NI_MAXHOST)
          );
    printf("IP dst: %s (%s)\n", 
            inet_ntop(AF_INET, &(ip->dst), ipStr, 16),
            ipToHost(ip->dst, host, NI_MAXHOST)
          );
    

    const struct tcpHeader* tcp;
    tcp = (const struct tcpHeader*)(pkt+ETHER_ADDR_LEN+sizeof(struct ipHeader));
    printf("TCP src port: %d\n", ntohs(tcp->srcPort));
    printf("TCP dst port: %d\n", ntohs(tcp->dstPort));

    pcap_close(handle);
    return 0;
}



