#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <cstring>
#include <unistd.h>
#include <ctime>
#include <string.h>

int main(int argc, char** argv){
    time_t time_aux;
    struct tm* time_;
    //Para ayudar a los get infos
    addrinfo hints;
    //El resultado
    addrinfo* result;
    int rc;
    int sd;
    int sd_c;
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];
    //Para el input creo (?)
    char buffer[128];
    //No estoy muy seguro
    struct sockaddr client_address;
    socklen_t client_len = sizeof(struct sockaddr);

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

    //Bind del socket
    bind(sd, (struct sockaddr*)result->ai_addr, result->ai_addrlen);

    //Creo que esto es como un delete, para que deje de consumir memoria
    freeaddrinfo(result);

    listen(sd, 5);

    sd_c = accept(sd,&client_address,&client_len);

    getnameinfo(&client_address, client_len, host, NI_MAXHOST,
            serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);


        printf("Conexion desde Host:%s Puerto:%s\n", host, serv);

    while (true) {
        ssize_t bytes = recv(sd_c, buffer, 80, 0);
        

        if(bytes < 1 || send(sd_c, buffer, bytes, 0) == -1){
            break;
        }
    }

    printf("Conexion desconectada.\n");

    close(sd);

return 0;
}
