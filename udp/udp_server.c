/*Server UDP*/
/*Author*/
/*Jerson Antonio Martinez Moreno (Side Master)*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char * invertir_str(char *); 
void error(char *);

int main(int argc, char *argv[]){
	int sock, longitud, long_cliente, n, lenbuf;

	struct sockaddr_in servidor;
	struct sockaddr_in cliente;
	
	char buf[2048];

	if (argc < 2) {
		fprintf(stderr, "ERROR, no ha proporcionado un puerto\n");
		exit(0);
	}

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	
	if (sock < 0)
		error("Abriendo socket");

	// longitud = sizeof(servidor);
	bzero(&servidor, longitud);
	servidor.sin_family = AF_INET;
	servidor.sin_addr.s_addr = INADDR_ANY;
	servidor.sin_port = htons(atoi(argv[1]));

	if (bind(sock, (struct sockaddr *) &servidor, sizeof(servidor)) < 0)
		error("Conectando...");

	long_cliente = sizeof(struct sockaddr_in);

	while (1){
		bzero(buf, sizeof(buf));
		n = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *) &cliente, &long_cliente);
		
		if (n < 0)
			error("Recibido desde");

		write(0, "Mensaje UDP recibido: ", 22);
		write(0, buf, n);

		lenbuf = strlen(buf) - 1;

		printf("Logitud: %d Bytes\n", lenbuf);

		n = sendto(sock, ("%s", invertir_str(buf)), strlen(buf), 0,(struct sockaddr *) &cliente, long_cliente);
		
		if (n < 0)
			error("Enviar a");
	}
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
	
	invstr[len + 10] = '\0';
	
	return invstr;
}