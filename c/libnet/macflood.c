#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <libnet.h>

#define DEFAULT_IFACE "eth0"
#define DEFAULT_N 1

void usage();
void get_random_mac(uint8_t* mac);
uint32_t get_random_ip();
char* mac_to_str(uint8_t* mac);
void print_info(uint8_t* src_mac, uint8_t* dst_mac, uint32_t src_ip, uint32_t dst_ip);
void fail(const char* msg, libnet_t* l);

int main(int argc, char** argv){
    // cmd line option parsing stuff
    int ch;
    char iface[8] = DEFAULT_IFACE, src[18], dst[18];
    int n = DEFAULT_N;
    int src_given = 0, dst_given = 0; 

    uint8_t src_mac[6], dst_mac[6];
    int len;
    uint8_t* tmp;
    char errbuf[LIBNET_ERRBUF_SIZE];

    while( (ch = getopt(argc, argv, "i:s:d:n:h")) != -1 ){
        switch(ch) {
            case 'i':
                strncpy(iface, optarg, 7); 
                iface[7] = '\0';
                break;
            case 's':
                strncpy(src, optarg, 17);
                src[17] = '\0';
                tmp = libnet_hex_aton(src, &len);
                if(len < 6){
                    fprintf(stderr, "Invalid source MAC address\n");
                    usage();
                }
                src_mac[0] = tmp[0]; src_mac[1] = tmp[1]; src_mac[2] = tmp[2]; 
                src_mac[3] = tmp[3]; src_mac[4] = tmp[4]; src_mac[5] = tmp[5]; 
                free(tmp);
                src_given = 1;
                break;
            case 'd':
                strncpy(dst, optarg, 17);
                dst[17] = '\0';
                tmp = libnet_hex_aton(dst, &len);
                if(len < 6){
                    fprintf(stderr, "Invalid destination MAC address\n");
                    usage();
                }
                dst_mac[0] = tmp[0]; dst_mac[1] = tmp[1]; dst_mac[2] = tmp[2]; 
                dst_mac[3] = tmp[3]; dst_mac[4] = tmp[4]; dst_mac[5] = tmp[5]; 
                free(tmp);
                dst_given = 1;
                break;
            case 'n':
                n = atoi(optarg);
                break;
            case '?':
            case 'h':
            default:
                usage();
        }
    }
    argc -= optind;
    argv += optind;

    libnet_t *l; //libnet context

    l = libnet_init(LIBNET_LINK, iface, errbuf);
    if( l == NULL ){
        fprintf(stderr, "libnet_init() failed: %s\n", errbuf);
        exit(EXIT_FAILURE);
    }
    libnet_seed_prand(l);

    int i;
    for(i=0; i < n; i++){

        //build ICMP packet
        int id = libnet_get_prand(LIBNET_PR16);
        int seq = 1;
        if( libnet_build_icmpv4_echo( ICMP_ECHO, 0, 0, id, seq, NULL, 0, l, 0) == -1 ){
            fail("Error building ICMP packet", l);
        }

        //build IP packet
        uint32_t src_ip, dst_ip;
        src_ip = get_random_ip();
        dst_ip = get_random_ip();
        id = libnet_get_prand(LIBNET_PR16);
        if( libnet_build_ipv4(LIBNET_IPV4_H + LIBNET_ICMPV4_ECHO_H, 0, id, 0, 1, 
                    IPPROTO_ICMP, 0, src_ip, dst_ip, NULL, 0, l, 0) == -1 ){
            fail("Error building IP packet", l);
        }

        //build ethernet packet
        if( !src_given ) get_random_mac(src_mac);
        if( !dst_given ) get_random_mac(dst_mac);
        if( libnet_build_ethernet( dst_mac, src_mac, ETHERTYPE_IP, 
                    NULL, 0, l, 0) == -1 ){
            fail("Error building Ethernet packet",l);
        }

        // and write it
        int bytes_written = libnet_write(l);
        if( bytes_written == -1 ){
            fail("Error writing the packet", l);
        }
        print_info(src_mac, dst_mac, src_ip, dst_ip);
        printf("%d bytes written\n", bytes_written);

        //reset context for next iteration
        libnet_clear_packet(l);
    }
    
    libnet_destroy(l);
    return 0;
}


void usage(){
    fprintf(stderr, "Usage: [-i interface (=%s)] [-s src_mac] [-d dst_mac] [-n # packets (=%d)] \n", DEFAULT_IFACE, DEFAULT_N);
    exit(EXIT_FAILURE);
}

void get_random_mac(uint8_t* mac){
    int i;
    for(i=0; i<6; i++){
        mac[i] = (uint8_t)libnet_get_prand(LIBNET_PR8);
    }
}
uint32_t get_random_ip(){
    return libnet_get_prand(LIBNET_PR32);
}

char* mac_to_str(uint8_t* mac){
    char* str = (char*)malloc( 18 );
    snprintf(str, 18, "%02X:%02X:%02X:%02X:%02X:%02X", 
            mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    return str;
}


void print_info(uint8_t* src_mac, uint8_t* dst_mac, uint32_t src_ip, uint32_t dst_ip){
    char *smac, *dmac;
    smac = mac_to_str(src_mac);
    dmac = mac_to_str(dst_mac);
    printf("%s\t(%s)  >  %s\t(%s). ", 
            libnet_addr2name4(src_ip, LIBNET_DONT_RESOLVE),
            smac,
            libnet_addr2name4(dst_ip, LIBNET_DONT_RESOLVE),
            dmac );
    free(smac);
    free(dmac);
}

void fail(const char* msg, libnet_t* l){
    fprintf(stderr, "%s: %s\n",msg, libnet_geterror(l));
    libnet_destroy(l);
    exit(EXIT_FAILURE);
}
