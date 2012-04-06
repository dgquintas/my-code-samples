#include <stdio.h>
#include <stdlib.h>
#include <libnet.h>
#include <stdint.h>

// sends an ARP request for the IP address read from stdin

int main(int argc, char** argv) {

        libnet_t *l;    /* the libnet context */
        char errbuf[LIBNET_ERRBUF_SIZE], target_ip_addr_str[16];
        u_int32_t target_ip_addr, src_ip_addr;
        u_int8_t mac_broadcast_addr[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
                 mac_zero_addr[6] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
        struct libnet_ether_addr *src_mac_addr;
        int bytes_written;

        if( argc <= 1 ){
            fprintf(stderr, "Usage: %s <iface>\n", argv[0]);
            exit(EXIT_FAILURE);
        }

        l = libnet_init(LIBNET_LINK, argv[1], errbuf);
        if ( l == NULL ) {
                fprintf(stderr, "libnet_init() failed: %s\n", errbuf);
                exit(EXIT_FAILURE);
        }

        /* Getting our own MAC and IP addresses */

        src_ip_addr = libnet_get_ipaddr4(l);
        if ( src_ip_addr == -1 ) {
                fprintf(stderr, "Couldn't get own IP address: %s\n", libnet_geterror(l));
                libnet_destroy(l);
                exit(EXIT_FAILURE);
        }

        src_mac_addr = libnet_get_hwaddr(l);
        if ( src_mac_addr == NULL ) {
                fprintf(stderr, "Couldn't get own IP address: %s\n", libnet_geterror(l));
                libnet_destroy(l);
                exit(EXIT_FAILURE);
        }

        /* Getting target IP address */

        printf("Target IP address: ");
        scanf("%15s",target_ip_addr_str);

        target_ip_addr = libnet_name2addr4(l, target_ip_addr_str,\
                        LIBNET_DONT_RESOLVE);

        if ( target_ip_addr == -1 ) {
                fprintf(stderr, "Error converting IP address.\n");
                libnet_destroy(l);
                exit(EXIT_FAILURE);
        }

        /* Building ARP header */

        if ( libnet_autobuild_arp (ARPOP_REQUEST, //ARP operation type
                        src_mac_addr->ether_addr_octet, // sender's HW addres
                        (u_int8_t*)(&src_ip_addr), //sender's proto address
                        mac_zero_addr, // dst HW addr
                        (u_int8_t*)(&target_ip_addr),  // dst proto addr
                        l) == -1) 
        {
                fprintf(stderr, "Error building ARP header: %s\n",\
                                libnet_geterror(l));
                libnet_destroy(l);
                exit(EXIT_FAILURE);
        }
        
        /* Building Ethernet header */
        
        if ( libnet_autobuild_ethernet (mac_broadcast_addr, // dst ether addr
                    ETHERTYPE_ARP, // upper layer proto type
                    l) == -1 )
        {
                fprintf(stderr, "Error building Ethernet header: %s\n",\
                                libnet_geterror(l));
                libnet_destroy(l);
                exit(EXIT_FAILURE);
        }

        /* Writing packet */

        bytes_written = libnet_write(l);
        if ( bytes_written != -1 )
                printf("%d bytes written.\n", bytes_written);
        else
                fprintf(stderr, "Error writing packet: %s\n",\
                                libnet_geterror(l));

        libnet_destroy(l);
        return 0;
}

