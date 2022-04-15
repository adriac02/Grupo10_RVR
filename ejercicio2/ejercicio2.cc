#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <cstring>

int main(int argc, char** argv){
    time_t time;
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
    //Longitud de la respuesta (?)
    char response[25];
    //No estoy muy seguro
    struct sockaddr client_address;
    socklen_t client_len = sizeof(struct sockaddr);

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

    //Bind del socket
    bind(sd, (struct sockaddr*)result->ai_addr, result->ai_addrlen);

    //Creo que esto es como un delete, para que deje de consumir memoria
    freeaddrinfo(res);

    bool end = false;

    while (!end) {
        ssize_t bytes = recvfrom(sd, buffer, 80, 0, (struct sockaddr*)&client_address,
            &client_len);


        if (buffer[0] == 't') {
            time = localtime();
            bytes = strftime(response, 25, "%H:%M:%S %p", time);
            sendto(sd, response, bytes, 0, &client_address, client_len);
        }
        else if (buffer[0] == 'd') {
            time = localtime();
            bytes = strftime(response, MAX_RESPONSE_LEN, "%Y-%m-%d", tm_);
            sendto(sd, response, bytes, 0, &client_addr, client_len);
        }
        else if (buffer[0] == 'q') end = true;

        getnameinfo((struct sockaddr*)&cliente, cliente_len, host, NI_MAXHOST,
            serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

        printf("Conexión desde Host:%s Puerto:%s\n", host, serv);
        printf("\tMensaje(%i): %s\n", bytes, buffer);
    }


    close(sd);

return 0;
}
