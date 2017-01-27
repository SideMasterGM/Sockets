/*TCP Cliente*/
/*Authors*/
/*Erick Ivan Altamirano Montalvan*/
/*Jerson Antonio Martinez Moreno*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(char *);

int main(int argc, char *argv[]) {
    int sock, puerto, n;
    struct sockaddr_in serv_addr;
    struct hostent *servidor;

    char buffer[256];
        
    while (1){

        if (argc < 3) {
           fprintf(stderr,"Usado %s, escriba un puerto\n", argv[0]);
           exit(0);
        }

        puerto = atoi(argv[2]);
        sock = socket(AF_INET, SOCK_STREAM, 0);
        
        if (sock < 0) 
            error("ERROR, no ha establecido la conexion");
        
        servidor = gethostbyname(argv[1]);
        
        if (servidor == NULL) {
            fprintf(stderr,"ERROR, host desconocido\n");
            exit(0);
        }

        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)servidor->h_addr, (char *) &serv_addr.sin_addr.s_addr, servidor->h_length);
        serv_addr.sin_port = htons(puerto);
        
        if (connect(sock,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
            error("ERROR, no hay conexion...");
        
        printf("Por favor, ingrese el mensaje: ");
        bzero(buffer, sizeof(buffer));
        fgets(buffer, sizeof(buffer), stdin);
        printf("------------------------------------------------------\n");
        fflush(stdin);

        if (strcmp(buffer, "\n") == 0)
            break;

        n = write(sock, buffer, strlen(buffer));
        
        if (n < 0) 
             error("ERROR, no hay comunicacion");
        
        bzero(buffer, sizeof(buffer));
        
        n = read(sock, buffer, sizeof(buffer));
        
        if (n < 0) 
             error("ERROR, no se ha podido leer el dato");
        
        printf("%s\n", buffer);  
    }

    close(sock);

    return 0;
}

void error(char *msg) {
    perror(msg);
    exit(0);
}