#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SIZE 1024

int main(){
	int N, serverPort, len;
	int client_socket;
	struct sockaddr_in clientAdd;
	char s[SIZE], name[4];
	char serverAdd[16];
	
	printf("Enter the number you want\n1. TCP\n2. UDP\n");
	scanf("%d", &N);
	scanf("%s", serverAdd);
	scanf("%d", &serverPort);
	getchar();
	scanf("%s", name);
	getchar();
	
	if(N == 1){
	
	
		client_socket = socket(AF_INET,SOCK_STREAM,0);
		
		clientAdd.sin_family = AF_INET;
		clientAdd.sin_addr.s_addr = inet_addr(serverAdd);
		
		clientAdd.sin_port = htons(serverPort);
		
		
		if(-1==connect(client_socket, (struct sockaddr*)&clientAdd ,sizeof(clientAdd))){
			printf("connect fail\n");
		}else{
			printf("채팅을 입력하세요. 나가기(q or quit)\n");
		}
		
	
		write(client_socket, name, 4);
		
		while(1){
			fgets(s, SIZE, stdin);
			
			write(client_socket, s, SIZE);
			if(strlen(s)==2 || strlen(s)==5){
				if(strncmp(s,"q",1) == 0 || strncmp(s,"quit",4) == 0){
					break;
				}
			}
			read(client_socket, s, SIZE);
			
			
			if(strlen(s)==2 || strlen(s)==5){
				if(strncmp(s,"q",1) == 0 || strncmp(s,"quit",4) == 0){
					break;
				}
			}
			
			printf("[server]: %s\n", s);
		}
		
		close(client_socket);
		
		
	}else if(N == 2){
		client_socket = socket(AF_INET,SOCK_DGRAM,0);
		
		clientAdd.sin_family = AF_INET;
		clientAdd.sin_addr.s_addr = inet_addr(serverAdd);
		
		clientAdd.sin_port = htons(serverPort);
		
		if(-1==sendto(client_socket, name, 4, 0, (struct sockaddr*)&clientAdd, sizeof(clientAdd))){
			printf("sendto fail\n");
		}else{
			printf("채팅을 입력하세요. 나가기(q or quit)\n");
		}
		
		while(1){
			fgets(s, SIZE, stdin);
			sendto(client_socket, s, SIZE, 0, (struct sockaddr*)&clientAdd, sizeof(clientAdd));
			
			if(strlen(s)==2 || strlen(s)==5){
				if(strncmp(s,"q",1) == 0 || strncmp(s,"quit",4) == 0){
					break;
				}
			}
			
			len = sizeof(clientAdd);
			recvfrom(client_socket, s,SIZE, 0, (struct sockaddr*)&clientAdd, &len);
			
			if(strlen(s)==2 || strlen(s)==5){
				if(strncmp(s,"q",1) == 0 || strncmp(s,"quit",4) == 0){
					break;
				}
			}
			
			printf("[server]: %s\n", s);
			
		}
		close(client_socket);
	}
	
	return 0;
}
