#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define ERROR -1
#define BUFSIZE 12

int goodfunc(const char *str); /* funcptr starts out as this */


/**
 * Le programme vulnérable.
 * 
 * le but de l'attaque est d'écraser le pointeur de fonction "funcptr"
 * pour qu'il ne contienne non plus l'adresse de la fonction, mais
 * l'adresse de la fonction C "system()".
 * 
 * 
 * 
 */
int main(int argc, char **argv)
{
	static char buf[BUFSIZE];
	static int (*funcptr)(const char *str);
	char functionArgs[100];
	u_long sysaddr;

	// buffer pour la socket
	char buffer[100];
	int sockfd, newsockfd, portno, clilen;
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	
	
	if (argc < 2) {
		fprintf(stderr,"Usage : %s <port>\n", argv[0]);
		exit(-1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("ERROR opening socket");
		exit(-1);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
		sizeof(serv_addr)) < 0) {
		perror("ERROR on binding");
		exit(-1);
	}
	
	printf("server :: (for 1st exploit) system() = %p\n", system);
	
	while(1) {
		listen(sockfd,5);
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, 
			(struct sockaddr *) &cli_addr, 
			&clilen);
		if (newsockfd < 0) {
			perror("ERROR on accept");
			exit(-1);
		}
		
		/*******************************************************/
		/* on envoie l'adresse de la fonction "system()"...
		 * (completement top niveau sécurité..)
		 */
		sysaddr = (u_long)&system;
		
		/* conversion en string */
		char tmp[100];//récepteur assez large
		sprintf(tmp, "%lu", sysaddr);//et tmp contient le texte
		//printf("server :: %s\n",tmp);
		
		n = write(newsockfd,tmp,sizeof(tmp));
		if (n < 0) {
			perror("ERROR writing to socket");
			exit(-1);
		}
		
		/*******************************************************/
		/* on récupere l'argument de la fonction
		 */

		bzero(buffer,100);
		n = read(newsockfd,buffer,sizeof(buffer));
		if (n < 0) {
			perror("ERROR reading from socket");
			exit(-1);
		}
		bzero(functionArgs,sizeof(functionArgs));
		strncpy(functionArgs, buffer, strlen(buffer));
		printf("server :: functionargs: %s\n", functionArgs);
		
		
		printf("server :: flush\n");
		/* juste pour flusher.. */
		n = write(newsockfd,"flush",5);
		if (n < 0) {
			perror("ERROR writing to socket");
			exit(-1);
		}
		
		/*******************************************************/
		/* puis on recupere le contenu du buffer
		 */

		bzero(buffer,sizeof(buffer));
		n = read(newsockfd,buffer,sizeof(buffer));
		if (n < 0) {
			perror("ERROR reading from socket");
			exit(-1);
		}
		printf("server :: buffer: %s\n", buffer);
		
		
		funcptr = (int (*)(const char *str))goodfunc;
		printf("server :: before overflow: funcptr points to %p\n", funcptr);
		
		memset(buf, 0, sizeof(buf));
		strncpy(buf, buffer, strlen(buffer));

		printf("server :: after overflow: funcptr points to %p\n", funcptr);
		
		//(void)(*funcptr)(functionArgs);
		(void)(*funcptr)(functionArgs);
	}
	
	
	
	
	
	
	
	
	
	
	
	
	

	
	/*
	printf("enter the function arguments: (going to be displayed) ");
	scanf("%s", functionArgs);
	
	printf("enter the buffer content: ");
	//scanf("%s", inputBuffer);
	//printf("\n");
	
	funcptr = (int (*)(const char *str))goodfunc;
	printf("before overflow: funcptr points to %p\n", funcptr);
	
	memset(buf, 0, sizeof(buf));
	strncpy(buf, inputBuffer, strlen(inputBuffer));
	printf("after overflow: funcptr points to %p\n", funcptr);
	
	//(void)(*funcptr)(functionArgs);
	(void)(*funcptr)("/bin/sh");
	*/
	return 0;
}

/* ---------------------------------------------- */

/* This is what funcptr would point to if we didn't overflow it */
int goodfunc(const char *str)
{
	printf("\nHi, I'm a good function.  I was passed: %s\n\n", str);
	return 0;
}

