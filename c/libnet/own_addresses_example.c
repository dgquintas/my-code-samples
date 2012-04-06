#include <stdio.h>
#include <stdlib.h>
#include <libnet.h>


int main(int argc, char** argv){

    libnet_t *l; //libnet context

    char errbuf[LIBNET_ERRBUF_SIZE];
    char ip_addr_str[16], mac_addr_str[18];
    u_int32_t ip_addr;
    u_int8_t *ip_addr_p, *mac_addr;
    int i, length; //for libnet_hex_aton

    if( argc <= 1 ){
        fprintf(stderr, "Usage: %s <iface>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    l = libnet_init(LIBNET_RAW4 /*inj. type*/, argv[1] /* iface */, errbuf);
    if( l == NULL ){
        fprintf(stderr, "libnet_init() failed: %s\n", errbuf);
        exit(EXIT_FAILURE);
    }

    //IP addr

    printf("IP addr: ");
    ip_addr = libnet_get_ipaddr4(l);

    if( ip_addr != -1 ){ //no error
        //libnet always deals with stuff in network order
       /* Check your system's endianess: */
       ip_addr_p = (u_int8_t*)(&ip_addr);
       printf("ip_addr:   %08X\n", ip_addr);
       printf("ip_addr_p: %02X %02X %02X %02X\n", ip_addr_p[0],\
                     ip_addr_p[1], ip_addr_p[2], ip_addr_p[3]);
        printf("Address as per addr2name4: %s\n", \
                libnet_addr2name4(ip_addr, LIBNET_DONT_RESOLVE));
    }
    else{
        fprintf(stderr, "Error converting IP\n");
    }


    // MAC addr
    printf("MAC address: ");
    struct libnet_ether_addr* mac_addr_struct;
    mac_addr_struct = libnet_get_hwaddr(l);
    mac_addr = (u_int8_t*)&(mac_addr_struct->ether_addr_octet);
    length = 6;

    if( mac_addr != NULL) {

        printf("Address read: ");
        for ( i=0; i < length; i++) {
            printf("%02X", mac_addr[i]);
            if ( i < length-1 )
                printf(":");
        }
        printf("\n");

    }
    else{
        fprintf(stderr, "Error converting MAC address.\n");
    }

    libnet_destroy(l);
    return 0;
}


