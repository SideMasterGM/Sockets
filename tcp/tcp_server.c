/*--------------- TCP Server -----------------*/
/*----------------  Author -------------------*/
/*Jerson Antonio Martinez Moreno (Side Master)*/

/*Channel YouTube: https://www.youtube.com/channel/UCwk5llU9cIYbPRMAp0Z8jxg/ */
/*Channel YouTube 2: https://www.youtube.com/sidemaster */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

char * invertir_str(char *); 
void error(char *);

int main(int argc, char *argv[]) {
    int sock, newsock, puerto, long_message;
    socklen_t long_cliente;

    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
     
    if (argc < 2) {
        fprintf(stderr,"ERROR, no ha proporcionado un puerto\n");
        exit(1);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
     
    if (sock < 0) 
        error("ERROR, no se ha podido abrir establecer la conexion");
     
    bzero((char *) &serv_addr, sizeof(serv_addr));
    puerto = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(puerto);
     
    if (bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR No hay conexion");
     
    listen(sock, 5);
    
    while (1){

        long_cliente = sizeof(cli_addr);

        newsock = accept(sock, (struct sockaddr *) &cli_addr, &long_cliente);
        
        if (newsock < 0) 
            error("ERROR, no ha sido aceptado.");

        bzero(buffer,256);
         
        n = read(newsock,buffer,255);
        
        if (n < 0) error("ERROR, lectura del socket");
         
        long_message = strlen(buffer) - 1;

        if (long_message < 0){
            printf("\nEl cliente se ha desconectado\n");
        } else {
            printf("Mensaje recibido: %s Longitud del mensaje: %d Bytes\n",buffer, long_message);
         
            n = write(newsock,("Cadena invertida: %s", invertir_str(buffer)), long_message + 18);
         
            if (n < 0) error("ERROR, escribiendo en el socket");         
        }
        
    }

    close(newsock);
    close(sock);
     
    return 0; 
}

void error(char *msg) {
    perror(msg);
    exit(0);
}

char * invertir_str(char * str) {
    int len, i;
    char *invstr = "";

    len = strlen(str);
    invstr = (char *) malloc((len + 1) * sizeof(char));
    fflush(stdin);

    for (i=0; i<len; i++)
        invstr[i] = str[len-1 - i];
    
    invstr[len] = '\0';
    
    return invstr;
}