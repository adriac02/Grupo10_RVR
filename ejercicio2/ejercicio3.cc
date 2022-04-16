#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <cstring>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char** argv){
    //Para ayudar a los get infos
    addrinfo hints;
    //El resultado
    addrinfo* result;
    int rc;
    int sd;
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];
    //Para el input creo (?)
    char buffer[128];
    //No estoy muy seguro
    struct sockaddr_in server_address;
    socklen_t server_len = sizeof(struct sockaddr);

    memset(&hints, 0, sizeof(addrinfo));

    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_DGRAM;

    //Para evitar errores
    rc = getaddrinfo(argv[1], argv[2], &hints, &result);
    //El socket
    sd = socket(result->ai_family, result->ai_socktype, 0);

    //Si no es 0 es que ha dado un error
    if (rc != 0) {
        return -1;
    }

    //Creo que esto es como un delete, para que deje de consumir memoria
    freeaddrinfo(result);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(atoi(argv[2]));
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    sendto(sd, argv[3], 2, 0, (struct sockaddr*)&server_address, server_len);

    ssize_t bytes = recvfrom(sd, buffer, 80, 0, (struct sockaddr*)&server_address,
            &server_len);

    printf("%s\n", buffer);


    close(sd);

return 0;
}
