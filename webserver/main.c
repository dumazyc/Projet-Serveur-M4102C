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
int main (void)
{
	const char * message_bienvenue = "Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément ! Bienvenue sur le serveur de Ludovic et Clément !\r\n" ;
	int socket_serveur = creer_serveur(8080);
	initialiser_signaux();	
	while(1){
		int socket_client ;
		socket_client = accept (socket_serveur,NULL,0);
		if (socket_client == -1)
		{
			perror ("accept");
			return -1;
		}
		FILE* truc = fdopen(socket_client,"w+");
		if(truc==NULL){
			perror("Error opening socket");
      		return(-1);
		}
		pid_t pid = 0;
		if ((pid=fork())==0){
			int requeteValable=0;
			while(requeteValable==0){
				char tmp[500]="";
				int tmp2=0;
				int indiceDeuxiemeMot=0;
				int indiceTroisiemeMot=0;
				if(fgets_or_exit(tmp,500,truc)!=NULL){
					char buf[256];
					while(strncmp("\r\n", fgets_or_exit(buf, sizeof(buf), truc), 2) != 0)
						;
					
					if(tmp[0]=='G'&&tmp[1]=='E'&&tmp[2]=='T'){
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
							if(tmp[indiceTroisiemeMot]=='H'&&tmp[indiceTroisiemeMot+1]=='T'&&tmp[indiceTroisiemeMot+2]=='T'&&tmp[indiceTroisiemeMot+3]=='P'&&tmp[indiceTroisiemeMot+4]=='/'&&tmp[indiceTroisiemeMot+5]=='1'&&tmp[indiceTroisiemeMot+6]=='.'&&(tmp[indiceTroisiemeMot+7]=='0'||tmp[indiceTroisiemeMot+7]=='1')){
								
								if(tmp[indiceDeuxiemeMot]=='/'&&tmp[indiceDeuxiemeMot+1]==' '){
									requeteValable=1;
									fprintf(truc,"HTTP/1.1 200 OK\r\n");
									fprintf(truc,"Connection: close\r\n");
									fprintf(truc,"Content-Length: 1000 \r\n");
									fprintf(truc,"\r\n");
								}else{
									
									fprintf(truc,"HTTP/1.1 400 Bad Request\r\n");
									fprintf(truc,"Connection: close\r\n");
									fprintf(truc,"Content-Length: 17\r\n");
									fprintf(truc,"\r\n");
									fprintf(truc,"400 Bad Request\r\n");
								}
							}
						}else{
							fprintf(truc,"HTTP/1.1 400 Bad Request\r\n");
							fprintf(truc,"Connection: close\r\n");
							fprintf(truc,"Content-Length: 17\r\n");
							fprintf(truc,"\r\n");
							fprintf(truc,"400 Bad Request\r\n");
							
						}
					}else{
						fprintf(truc,"HTTP/1.1 400 Bad Request\r\n");
						fprintf(truc,"Connection: close\r\n");
						fprintf(truc,"Content-Length: 17\r\n");
						fprintf(truc,"\r\n");
						fprintf(truc,"400 Bad Request\r\n");
					}
				}		
			}	
			
			sleep(1);
			fprintf(truc,"%s",message_bienvenue);
			
				
			while(1){
				char tmp[500]="";
				fprintf(truc,"<me> ");
	
				
				
				if(fgets_or_exit(tmp,500,truc)!=NULL){
					printf("%s",tmp);
				}
				
			}
			
		}else{
			
					
				
		}
	}
	close(socket_serveur);
	return 0; 
}



