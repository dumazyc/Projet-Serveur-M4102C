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
		if(truc==NULL){
			perror("Error opening socket");
      		return(-1);
		}
		pid_t pid = 0;
		if ((pid=fork())==0){
		fprintf(truc,"Hello\n");
			int requeteValable=0;
			while(requeteValable==0){
				char tmp[500]="";
				int tmp2=0;
				int indiceDeuxiemeMot=0;
				int indiceTroisiemeMot=0;
				fprintf(truc,"passe par la 2\n");
				if(fgets(tmp,500,truc)!=NULL){
					if(tmp[0]=='G'&&tmp[1]=='E'&&tmp[2]=='T'){
						fprintf(truc,"GET VALIDE\n");
						int i =0;
						int tmp3 = strlen(tmp);
						for(i = 0; i < tmp3;i++){
							if(tmp[i]==' '){
								if(indiceDeuxiemeMot==0&&indiceTroisiemeMot==0){
									indiceDeuxiemeMot=i+1;
								}else{
									indiceTroisiemeMot=i+1;
								}
								tmp2++;
							}
						}
						if (tmp2==2){
							fprintf(truc,"Contient 3 mots\n");
							if(tmp[indiceTroisiemeMot]=='H'&&tmp[indiceTroisiemeMot+1]=='T'&&tmp[indiceTroisiemeMot+2]=='T'&&tmp[indiceTroisiemeMot+3]=='P'&&tmp[indiceTroisiemeMot+4]=='/'&&tmp[indiceTroisiemeMot+5]=='1'&&tmp[indiceTroisiemeMot+6]=='.'&&(tmp[indiceTroisiemeMot+7]=='0'||tmp[indiceTroisiemeMot+7]=='1')){
								fprintf(truc,"HTTP/M.m Valide\n");
								requeteValable=1;
							}
						}
					}
				}
					
					
					
					/*strncpy(tmp,tmp2,3);
					printf("%s",tmp2);
					if(strcmp(tmp2,"GET")==0){
						printf("GET VALIDE");
					}*/
					
				}
			
			/* On peut maintenant dialoguer avec le client */
			const char * message_bienvenue = "Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément !\n" ;
			sleep(1);
			fprintf(truc,"%s",message_bienvenue);
			//write ( socket_client , message_bienvenue , strlen(message_bienvenue));
			
				
			while(1){
				char tmp[500]="";
				fprintf(truc,"<me> ");
				//char b [50]="";
	
				/*char buf[100]="";
		
				int size = read(socket_client,buf,sizeof(buf));
		
				write(socket_client,buf,size);*/
				//int cb=0;
				//cb = recv(socket_client,b,sizeof(b),0);
				
				if(fgets(tmp,500,truc)!=NULL){
					printf(tmp);
					//fprintf(truc,"<mustached_server> %s",tmp);
				}
				/*if( cb <= 0 )
		   		{
		   			printf("client deconnecté\n");
		   			fflush(stdout);
		   			close(socket_client);
					return -1;
				}else{
					write(socket_client,b,cb);
				}*/
			}
			
		}else{
			
					
				
		}
	}
	close(socket_serveur);
	return 0; 
}

