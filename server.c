#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SIZE 1024

int main(){
	int N,serverPort, len;
	int server_socket, connect_socket;
	struct sockaddr_in serverAdd;
	struct sockaddr_in connectAdd;
	char s[SIZE], name[4];
	
	printf("Enter the number you want\n1. TCP\n2. UDP\n");
	scanf("%d", &N);
	scanf("%d", &serverPort);
	getchar();
	
	if(N == 1){
		
		server_socket = socket(AF_INET, SOCK_STREAM,0);//socket making
		if(server_socket == -1){
			printf("Socket Fail");
		}else{
			printf("Server: create TCP socket done\n");
		}
			
		serverAdd.sin_family = AF_INET;
		serverAdd.sin_addr.s_addr=htonl(INADDR_ANY);
		serverAdd.sin_port = htons(serverPort);
			
		
			
		if(-1==bind(server_socket, (struct sockaddr*)&serverAdd, sizeof(serverAdd))){
			printf("bind error\n");
		}
		
		
		
		if(listen(server_socket, 1)==-1){
			printf("listening error\n");
		}else{
			printf("Server: waiting connection request\n");
		}
		
		len = sizeof(connectAdd);
		connect_socket = accept(server_socket,(struct sockaddr*)&connectAdd, &len);
		
		
		
		if(connect_socket == -1){
			printf("connect fail\n");
		}else{
			read(connect_socket, name, 4);
			printf("%s님이 입장하셨습니다. 나가기(q or quit)", name);
		}
		
		printf("\n");
		
		
		
		while(1){
			
			
			
			read(connect_socket, s, SIZE);
			
			
			if(strlen(s)==2 || strlen(s)==5){
				if(strncmp(s,"q",1) == 0 || strncmp(s,"quit",4) == 0){
					
					break;
				}
			}
			printf("[%s]: %s\n", name, s);
			
			
			fgets(s, SIZE, stdin);
			write(connect_socket, s, SIZE);
			
			
			if(strlen(s)==2 || strlen(s)==5){
				if(strncmp(s,"q",1) == 0 || strncmp(s,"quit",4) == 0){
					
					break;
				}
			}
			
		}
		close(connect_socket);
		close(server_socket);
		
		
	
	}else if(N == 2){
		server_socket = socket(AF_INET, SOCK_DGRAM,0);
		if(server_socket == -1){
			printf("Socket Fail");
		}else{
			printf("Server: create UDP socket done\n");
		}
		
		serverAdd.sin_family = AF_INET;
		serverAdd.sin_addr.s_addr=htonl(INADDR_ANY);
		serverAdd.sin_port = htons(serverPort);
		
		if(-1==bind(server_socket, (struct sockaddr*)&serverAdd, sizeof(serverAdd))){
			
			printf("bind error\n");
		}
		len = sizeof(connectAdd);
		if(-1==recvfrom(server_socket, name,4, 0, (struct sockaddr*)&connectAdd, &len)){
			printf("recvfrom error");
		}else{
			printf("%s님이 입장하셨습니다. 나가기(q or quit)\n", name);
		}
		
		while(1){
			
			len = sizeof(connectAdd);
			if(-1 == recvfrom(server_socket, s,SIZE, 0, (struct sockaddr*)&connectAdd, &len)){
				printf("recvfrom error");
			}
			
			if(strlen(s)==2 || strlen(s)==5){
				if(strncmp(s,"q",1) == 0 || strncmp(s,"quit",4) == 0){
					break;
				}
			}
			
			printf("[%s]: %s\n",name, s);
			
			fgets(s, SIZE, stdin);
			
			sendto(server_socket, s,SIZE,0,(struct sockaddr*)&connectAdd, sizeof(connectAdd));
			
			if(strlen(s)==2 || strlen(s)==5){
				if(strncmp(s,"q",1) == 0 || strncmp(s,"quit",4) == 0){
					break;
				}
			}
		}
		
		close(server_socket);
	}
	
	
	
	return 0;
}
