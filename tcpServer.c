#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {

	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	if(server_socket == -1){
		printf("Fail to create socket\n");
		exit(1);
	}else{
		printf("Is create socket\n");
	}


	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	int bindStatus = bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

	if(bindStatus == -1){
		printf("Can not bind server\n");
		exit(1);
	}else{
		printf("Server is binding");
	}


	listen(server_socket, 5);
	
	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);

	char message[100] = "This is server message" ;
	send(client_socket, message, sizeof(message), 0);

	close(server_socket);

	return 0;
}
