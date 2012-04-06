#include <stdint.h>

struct ethernetHeader{
#define ETHER_ADDR_LEN 6
#define ETHER_HDR_LEN  14  /* 6+6+2 */
    uint8_t dst[ETHER_ADDR_LEN];
    uint8_t src[ETHER_ADDR_LEN];
    uint16_t type;
};

struct ipHeader {
    /* switch order if big endian */
    unsigned ihl :4;
    unsigned version :4;
    uint8_t diff_services;
    uint16_t length;

    uint16_t id;
    unsigned offset :13;
    unsigned flags  :3;

    uint8_t ttl;
    uint8_t protocol;
    uint16_t checksum;

    uint32_t src;

    uint32_t dst;
}; /* total: 20 bytes */


struct tcpHeader {
    uint16_t srcPort;
    uint16_t dstPort;

    uint32_t seq;

    uint32_t ack;

    unsigned control :6;
    unsigned ECN :3;
    unsigned reserved :3;
    unsigned offset :4; /* number of 32-bit words in the header */
    uint16_t window;

    uint16_t checksum;
    uint16_t urgentPtr;
}; /* total: variable. Calculate from offset*4 bytes */



