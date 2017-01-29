/*Cliente UDP*/
/*Authors*/
/*Erick Ivan Altamirano Montalvan*/
/*Jerson Antonio Martinez Moreno*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

void error(char *);

int main(int argc, char *argv[]) {
	int sock, longitud, n;
	
	struct sockaddr_in server, from;
	struct hostent *hp;
	
	char buffer[1024], recibir[1024];

	if (argc != 3) {
		printf("Hace falta: Puerto del servidor\n");
		exit(1);
	}

	/*AF_INET = Para usar los protocolos ARPA de Internet + Tipo = SOCK_DGRAM + Protocolo = 0*/
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	if (sock < 0)
		error("socket");

	server.sin_family = AF_INET;

	hp = gethostbyname(argv[1]);

	if (hp == 0)
		error("Host desconocido");

	/*Copia n bytes de src a dest.*/
	bcopy((char *) hp->h_addr, (char *) &server.sin_addr, hp->h_length);
	
	/*Se captura el puerto que se recibe por argumentos y se asigna a sin_port*/
	server.sin_port = htons(atoi(argv[2])); /*htons = Nodo a variable corta de Red*/
	longitud = sizeof(struct sockaddr_in);  

	while (1) {
		printf("\n");
		printf("Por favor, ingrese el mensaje: ");
		
		/*Se inicializa a 0 la estructura.*/
		bzero(buffer, sizeof(buffer));
		
		fgets(buffer, sizeof(buffer), stdin);
		printf("------------------------------------------------------\n");
		fflush(stdin);

		if (strcmp(buffer, "\n") == 0)
			break;

		n = sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *) &server, longitud);
		
		if (n < 0)
			error("Enviar a");

		bzero(recibir, sizeof(recibir));
		n = recvfrom(sock, recibir, sizeof(recibir), 0, (struct sockaddr *) &from, &longitud);

		if (n < 0)
			error("Recibido desde");

		write(1, "Servidor: ",10);
		write(1, recibir, n);
	}
}

void error(char *msg) {
	perror(msg);
	exit(0);
}