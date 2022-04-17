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
    
    
    //No estoy muy seguro
    struct sockaddr_in server_address;
    socklen_t server_len = sizeof(struct sockaddr);

    memset(&hints, 0, sizeof(addrinfo));

    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM;

    //Para evitar errores
    rc = getaddrinfo(argv[1], argv[2], &hints, &result);
    //El socket
    sd = socket(result->ai_family, result->ai_socktype, 0);

    //Si no es 0 es que ha dado un error
    if (rc != 0) {
        return -1;
    }

    
    

    connect(sd, result->ai_addr, result->ai_addrlen);

    //Creo que esto es como un delete, para que deje de consumir memoria
    freeaddrinfo(result);

    while(true){

        char buffer[128];
        fgets(buffer,128,stdin);
        
        if(buffer[0]=='Q') break;

        size_t len = strlen(buffer);
        send(sd, buffer, len, 0);

        char response[128];
        ssize_t recv_bytes = recv(sd, response, 128, 0);

        printf("%s\n", response);



    }

    


    close(sd);

return 0;
}
