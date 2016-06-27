#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_ipv4(const char *host, int port_num, struct sockaddr_storage *addr,
                size_t *len) {
  struct sockaddr_in *in = (struct sockaddr_in *)addr;
  memset(in, 0, sizeof(*in));
  *len = sizeof(*in);
  in->sin_family = AF_INET;
  if (inet_pton(AF_INET, host, &in->sin_addr) == 0) {
    fprintf(stderr, "invalid ipv4 address: '%s'", host);
    abort();
  }
  in->sin_port = htons((uint16_t)port_num);
}

void parse_ipv6(const char *host, int port_num, struct sockaddr_storage *addr,
                size_t *len) {
  struct sockaddr_in6 *in6 = (struct sockaddr_in6 *)addr;
  memset(in6, 0, sizeof(*in6));
  *len = sizeof(*in6);
  in6->sin6_family = AF_INET6;
  if (inet_pton(AF_INET6, host, &in6->sin6_addr) == 0) {
    fprintf(stderr, "invalid ipv6 address: '%s'", host);
    abort();
  }
  in6->sin6_port = htons((uint16_t)port_num);
}

int main() {
  struct sockaddr_storage addr4, addr6;
  size_t addr_len4, addr_len6;
  parse_ipv4("127.0.0.1", 1234, &addr4, &addr_len4);
  parse_ipv6("::2", 4321, &addr6, &addr_len6);

  assert(((struct sockaddr*)&addr4)->sa_family == AF_INET);
  assert(((struct sockaddr*)&addr6)->sa_family == AF_INET6);

  char buffer4[INET_ADDRSTRLEN] = {0};
  char buffer6[INET6_ADDRSTRLEN] = {0};
  char port[6] = {0};
  int err;

  err = getnameinfo((struct sockaddr *)&addr4, addr_len6, buffer4,
                    sizeof(buffer4), port, 6, NI_NUMERICHOST | NI_NUMERICSERV);
  if (err != 0) {
    fprintf(stderr, "failed to convert address to string (code=%d)", err);
    abort();
  }
  printf("Remote address: %s:%s\n", buffer4, port);

  err = getnameinfo((struct sockaddr *)&addr6, addr_len6, buffer6,
                    sizeof(buffer6), port, 6, NI_NUMERICHOST | NI_NUMERICSERV);
  if (err != 0) {
    fprintf(stderr, "failed to convert address to string (code=%d)", err);
    abort();
  }
  printf("Remote address: %s:%s\n", buffer6, port);
  return 0;
}
