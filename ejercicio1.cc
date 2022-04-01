#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>

//struct sockaddr_in {
//      sa_family_t    sin_family; // fijar a AF_INET
//      in_port_t      sin_port;   // puerto
//      struct in_addr sin_addr;   // dirección IP
//    };

//struct in_addr {
//	uint32_t       s_addr;     // 32 bits dirección IP
//};


//struct addrinfo {
//   int              ai_flags;    // Opciones para filtrado (hints)
//   int              ai_family;   // Familia ej. AF_INET
//   int              ai_socktype; // ej. SOCK_STREAM
//   int              ai_protocol; // Protocolo, igual que socket(2)
//   socklen_t        ai_addrlen;
//   struct sockaddr *ai_addr;      //Resultado, NULL o 0 en hints
//   char            *ai_canonname; //addr, depende de ai_family
//   struct addrinfo *ai_next;
//};

int getaddrinfo(const char *node,
                const char *service,
		const struct addrinfo *hints,
		struct addrinfo **res);

int main(int argc, char** argv){
addrinfo hints;
addrinfo host;
addrinfo* result;
int rc;
int sd;
int cliente_sd;
int cliente;
char* serv;
socklen_t cliente_len;
ssize_t c;

hints.ai_flags    = AI_PASSIVE; //Devolver 0.0.0.0
hints.ai_family   = AF_INET; // IPv4
hints.ai_socktype = SOCK_STREAM;

rc = getaddrinfo(argv[1], argv[2], &hints, &result);
sd = socket(result->ai_family, result->ai_socktype, 0);

bind(sd, (struct sockaddr *) result->ai_addr, result->ai_addrlen);
listen(sd, 5);

int i = 0;
while (1) {
  cliente_sd = accept(sd, (struct sockaddr *) &cliente, &cliente_len);
  
  getnameinfo((struct sockaddr *) &cliente, cliente_len, argv[1], 
      NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
  printf("Conexión desde Host:%s Puerto:%s\n",host, serv);

  //Ejemplo: recepción en buffer de aplicación (no leer de byte en byte)
  do {
        c = recv(cliente_sd, &(setbuffer[i]), 1, 0);
  } while ( c >= 0 && i < 79 && setbuffer[i++] != '\n');
  
  send(cliente_sd, setbuffer, i, 0);
}


}
