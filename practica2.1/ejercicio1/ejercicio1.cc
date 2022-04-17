#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <cstring>

int main(int argc, char** argv){
addrinfo hints;
addrinfo* result;
int rc;
char host[NI_MAXHOST];
char serv[NI_MAXSERV];
memset(&result,0,sizeof(addrinfo));
memset(&hints,0,sizeof(addrinfo));

hints.ai_flags    = AI_PASSIVE; //Devolver 0.0.0.0
hints.ai_family   = AF_INET; // IPv4
hints.ai_socktype = SOCK_STREAM;

rc = getaddrinfo(argv[1], argv[2], &hints, &result);
getnameinfo(result->ai_addr, result->ai_addrlen, host, NI_MAXHOST,serv,NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
printf("IP: %s",host);
printf(" Family: %d",result->ai_family);
printf(" Sock Type: %d\n",result->ai_socktype);

hints.ai_socktype = SOCK_DGRAM;

rc = getaddrinfo(argv[1], argv[2], &hints, &result);
getnameinfo(result->ai_addr, result->ai_addrlen, host, NI_MAXHOST,serv,NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
printf("IP: %s",host);
printf(" Family: %d",result->ai_family);
printf(" Sock Type: %d\n",result->ai_socktype);

hints.ai_socktype = SOCK_RAW;

rc = getaddrinfo(argv[1], argv[2], &hints, &result);
getnameinfo(result->ai_addr, result->ai_addrlen, host, NI_MAXHOST,serv,NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
printf("IP: %s",host);
printf(" Family: %d",result->ai_family);
printf(" Sock Type: %d\n",result->ai_socktype);


hints.ai_family   = AF_INET6; // IPv6
hints.ai_socktype = SOCK_STREAM;

rc = getaddrinfo(argv[1], argv[2], &hints, &result);
getnameinfo(result->ai_addr, result->ai_addrlen, host, NI_MAXHOST,serv,NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
printf("IP6: %s",host);
printf(" Family: %d",result->ai_family);
printf(" Sock Type: %d\n",result->ai_socktype);

hints.ai_socktype = SOCK_DGRAM;

rc = getaddrinfo(argv[1], argv[2], &hints, &result);
getnameinfo(result->ai_addr, result->ai_addrlen, host, NI_MAXHOST,serv,NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
printf("IP6: %s",host);
printf(" Family: %d",result->ai_family);
printf(" Sock Type: %d\n",result->ai_socktype);

hints.ai_socktype = SOCK_RAW;

rc = getaddrinfo(argv[1], argv[2], &hints, &result);
getnameinfo(result->ai_addr, result->ai_addrlen, host, NI_MAXHOST,serv,NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
printf("IP6: %s",host);
printf(" Family: %d",result->ai_family);
printf(" Sock Type: %d\n",result->ai_socktype);

return 0;
}
