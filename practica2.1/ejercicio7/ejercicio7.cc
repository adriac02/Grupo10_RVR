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
    MessageThread(int sk) : socket_c(sk){}

    void do_message(){
        char buffer[128];
        while (true) {
            ssize_t bytes = recv(socket_c, buffer, 80, 0);


            if(bytes < 1 || send(socket_c, buffer, bytes, 0) == -1){
                break;
            }
        }
    }

private:
    int socket_c;

};

int main(int argc, char** argv){
    //Para ayudar a los get infos
        addrinfo hints;
        //El resultado
        addrinfo* result;
        int rc;
        int sd;
        int threads;
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

        listen(sd,5);

        while(true){
            int sd_c = accept(sd,&client_address,&client_len);
            MessageThread* m = new MessageThread(sd_c);
            std::thread([m](){
                m->do_message();
                delete m;
            }).detach();
        }
        close(sd);
        return 0;
}