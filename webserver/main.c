#include "socket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <wait.h>
int main (/*int argc, char **argv*/void)
{
	/* Arnold Robbins in the LJ of February ’95 , describing RCS */
	/*if (argc>1 && strcmp (argv[1], "-advice") == 0) {
		printf ("Don’t Panic !\n");
		return 42;
	}
	printf ("Need an advice ?\n");*/
	int socket_serveur = creer_serveur(8080);
	initialiser_signaux();
	while(1){
		int socket_client ;
		socket_client = accept (socket_serveur,NULL,0);
		if (socket_client == -1)
		{
			perror ("accept");
			/* traitement d ’ erreur */
			return -1;
		}
		FILE* truc = fdopen(socket_client,"w+");
		pid_t pid = 0;
		if ((pid=fork())==0){
			/* On peut maintenant dialoguer avec le client */
			const char * message_bienvenue = "Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément !\n" ;
			sleep(1);
			
			write ( socket_client , message_bienvenue , strlen(message_bienvenue));
	
			while(1){
				char b [50]="";
	
				/*char buf[100]="";
		
				int size = read(socket_client,buf,sizeof(buf));
		
				write(socket_client,buf,size);*/
				int cb=0;
				//cb = recv(socket_client,b,sizeof(b),0);
				char tmp[60]="";
				fprintf(truc,"<mustached_server>");
				if(fgets(tmp,60,truc)!=NULL){
					fprintf(truc,"%s",tmp);
				}
				if( cb <= 0 )
		   		{
		   			printf("client deconnecté\n");
		   			fflush(stdout);
		   			close(socket_client);
					return -1;
				}else{
					write(socket_client,b,cb);
				}
			}
			
		}else{

					
				
		}	
	}
	close(socket_serveur);
	return 0; 
}

