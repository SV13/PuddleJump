/* PuddleJump.h */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <dlfcn.h>

#define PROXY        "127.0.0.1"
#define PROXYPORT    9050
#define USERNAME     "Puddlejumper"
#define reqsize sizeof(struct proxy_Request)
#define ressize sizeof(struct proxy_Response)

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;


struct proxy_Request {
    int8 vn;
    int8 cd;
    int16 dstport;
    int32 dstip;
    unsigned char userid[13];
} __attribute__((packed)); // <--- Tell GCC to make this exactly 21 bytes
typedef struct proxy_Request Req;


struct proxy_Response {
    int8 vn;
    int8 cd;
    int16 _;
    int32 __;
};
typedef struct proxy_Response Res;

Req *request(struct sockaddr_in *);
int connect(int,const struct sockaddr*,socklen_t);
