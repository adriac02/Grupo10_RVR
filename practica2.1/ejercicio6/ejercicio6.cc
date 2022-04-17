#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <cstring>
#include <unistd.h>
#include <ctime>
#include <string.h>
#include <thread>
#include <iostream>
#include <string>

class MessageThread{
public:
    MessageThread(int sk) : socket(sk){}

    void do_message(){
        time_t time_aux;
        struct tm* time_;
        char host[NI_MAXHOST];
        char serv[NI_MAXSERV];
        //Para el input creo (?)
        char buffer[128];
        //Longitud de la respuesta (?)
        char response[25];
        //No estoy muy seguro
        struct sockaddr client_address;
        socklen_t client_len = sizeof(struct sockaddr);

        bool end = false;

        while (!end) {
            ssize_t bytes = recvfrom(socket, buffer, 80, 0, (struct sockaddr*)&client_address,
                &client_len);

            sleep(2);

            if (buffer[0] == 't') {
                time(&time_aux);
                time_ = localtime(&time_aux);
                bytes = strftime(response, 25, "%H:%M:%S %p", time_);
                sendto(socket, response, bytes, 0, &client_address, client_len);
            }
            else if (buffer[0] == 'd') {
                time(&time_aux);
                time_ = localtime(&time_aux);
                bytes = strftime(response, 25, "%Y-%m-%d", time_);
                sendto(socket, response, bytes, 0, &client_address, client_len);
            }
            else if (buffer[0] == 'q') end = true;

            getnameinfo(&client_address, client_len, host, NI_MAXHOST,
                serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);


            printf("Conexion desde Host:%s Puerto:%s\n", host, serv);
            printf("\tMensaje(%li): %s\n", bytes, buffer);
        }

    }

private:
    int socket;

};

int main(int argc, char** argv){
    //Para ayudar a los get infos
        addrinfo hints;
        //El resultado
        addrinfo* result;
        int rc;
        int sd;
        int threads;

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
        freeaddrinfo(result);

        threads = atoi(argv[3]);
        for(int i = 0;i<threads;++i){
            MessageThread* m = new MessageThread(sd);
            std::thread([m](){
                m->do_message();
                delete m;
            }).detach();
        }

        std::string st;
        std::cin >> st;
        while(st!="q"){
            std::cin >> st;
        }
        close(sd);
        return 0;
}