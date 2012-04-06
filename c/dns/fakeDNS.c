#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include <inttypes.h>

#define PORT 53


enum { HDR_ID=0, HDR_FLAGS, HDR_NQUERIES, HDR_NREPLIES, HDR_NSS, HDR_NADDRES };
typedef struct {
  uint16_t fields[6];
} Header_t ;

typedef struct {
  void* data;
  uint16_t qtype;
  uint16_t qclass;
  char qname[64];
} Question_t;

typedef struct {
  Header_t header;
  Question_t question;
  uint8_t* original_data[1024];
  size_t original_data_size;
} Query_t ;

typedef struct {
  uint16_t name;
  uint16_t type;
  uint16_t class;
  uint32_t ttl;
  uint16_t rdlength;
  uint8_t rdata[512];
} Response_t;

//////////////////////////////////////////////////////////////
void hdr_new(Header_t* header, uint8_t* data){
  uint16_t* data_as_shorts = (uint16_t*) data;
  int i=0;
  for(i=0; i < 6; i++){
    header->fields[i] = ntohs(data_as_shorts[i]);
  }
}
int hdr_check_QR_flag(const Header_t* header){
  return header->fields[HDR_FLAGS] & (1<<15);
}
int hdr_check_OPCODE_flag(const Header_t* header){
  return header->fields[HDR_FLAGS] & (0xf<<10);
}
int hdr_check_RCODE_flag(const Header_t* header){
  return header->fields[HDR_FLAGS] & (0xf);
}
//////////////////////////////////////////////////////////////
void qst_new(Question_t* question, uint8_t* data){
  //skip the first 12 bytes (header) 
  data += 12;

  uint8_t length;
  int i=0;
  while( (length = data[0]) ){
    strncpy( question->qname+i, data+1, length );
    question->qname[i+length] = '.';
    i += (length+1);
    data += (length+1);
  }; 
  question->qname[i-1] = '\0';
  data++; 

  question->qtype = ntohs(((uint16_t*)data)[0]);
  question->qclass= ntohs(((uint16_t*)data)[1]);

}
//////////////////////////////////////////////////////////////
uint8_t* get_response(const Query_t* query){

  const char* res_txt = "testing 123";

  // size == 12 bytes
  Header_t res_header;
  res_header.fields[HDR_ID] = htons(query->header.fields[HDR_ID]);
  res_header.fields[HDR_FLAGS] = htons(0x8000);
  res_header.fields[HDR_NQUERIES] = htons(1);
  res_header.fields[HDR_NREPLIES] = htons(1);
  res_header.fields[HDR_NSS] = 0;
  res_header.fields[HDR_NADDRES] = 0;

  // size <= 2+2+2+4+2+n = 12+n (n <= 500) => size <= 512
  Response_t response;
  response.name = htons(0xc00c);
  response.type = htons(16);
  response.class = htons(1);
  response.ttl = 0;
  response.rdlength = htons((strlen(res_txt)+1));
  snprintf(response.rdata, 500, "%d%s", htons(strlen(res_txt)), res_txt);
  
  // response == header + original query + response body
  uint8_t res_data[12+1024+512];
  uint8_t* res_data_ptr = &res_data;
  memcpy(res_data_ptr, &res_header, sizeof(Header_t));
  res_data_ptr += sizeof(Header_t);
  memcpy(res_data_ptr, &(query.original_data), query.original_data_size);
  res_data_ptr += query.original_data_size;
  memcpy(res_data_ptr, &response, 12 + response.rdlength);
  
  return &res_data;
}


int main(){
  int sock;
  int addr_len, bytes_read;

  char in_data[1024];
  struct sockaddr_in server_addr, client_addr;

  if( (sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("Socket");
    exit(1);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;
  bzero( &(server_addr.sin_zero), 8 );

  if( bind(sock, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) == -1 ){
    perror("Bind");
    exit(1);
  }

  addr_len = sizeof(struct sockaddr);
  printf("All good, waitin' for stuff on port %d\n", PORT);
  fflush(stdout);

  while(0xDEADBABE){
    bytes_read = recvfrom(sock, in_data, 1024, 0, (struct sockaddr*)&client_addr, &addr_len);
    in_data[bytes_read] = '\0';

    Query_t query;
    strncpy(query.original_data, in_data, 1024);
    query.original_data_size = bytes_read;
    hdr_new( &(query.header), in_data );
    qst_new( &(query.question), in_data );   

  }

  return 0;
}




