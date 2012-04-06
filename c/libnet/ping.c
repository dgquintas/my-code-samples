#include <stdio.h>
#include <stdlib.h>
#include <libnet.h>
#include <stdint.h>

void fail(libnet_t *l){
    libnet_destroy(l);
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv){

    libnet_t *l;
    char errbuf[LIBNET_ERRBUF_SIZE], ip_addr_str[16];
    u_int32_t ip_addr;
    u_int16_t id, seq;
    char payload[] = "libnet :D";
    int bytes_written;
 
    if( argc <= 1 ){
        fprintf(stderr, "Usage: %s <iface>\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    l = libnet_init(LIBNET_RAW4, argv[1], errbuf);
    if( l == NULL ){
        fprintf( stderr, "libnet_init() failed: %s\n", errbuf);
        exit(EXIT_FAILURE);
    }

    libnet_seed_prand(l);
    id = (u_int16_t)libnet_get_prand(LIBNET_PR16);

    printf("Destination ip: ");
    scanf("%15s", ip_addr_str);

    ip_addr = libnet_name2addr4(l, ip_addr_str, LIBNET_RESOLVE);
    if( ip_addr == -1 ){
        fprintf(stderr, "Error converting ip addr.\n");
        fail(l);
    }


    //build icmp 
    seq = 1;
    if( libnet_build_icmpv4_echo(ICMP_ECHO, //type
                0, //code
                0, //checksum
                id, // id #
                seq, // seq #
                (u_int8_t*)payload, 
                sizeof(payload),
                l,
                0)   //ptag. 0 => build a new one
            == -1 ){
        fprintf(stderr, "error building icmp header: %s\n", libnet_geterror(l));
        fail(l);
    }

    //build ip
    if( libnet_autobuild_ipv4(LIBNET_IPV4_H + LIBNET_ICMPV4_ECHO_H + sizeof(payload), //len
                IPPROTO_ICMP, //upper layer proto
                ip_addr,  // dst addr
                l) == -1 ){ 
        fprintf(stderr, "error building ip header: %s\n", libnet_geterror(l));
        fail(l);
    }

    //write packet
    bytes_written = libnet_write(l);
    if( bytes_written != -1 ){
        printf("%d bytes written.\n", bytes_written);
    }
    else{
        fprintf(stderr, "error writing packet: %s\n", libnet_geterror(l));
    }

    libnet_destroy(l);
    return 0;
}
