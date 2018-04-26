#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {

	int client_socket;
	int socketStatus = client_socket = socket(AF_INET, SOCK_STREAM, 0);

	if(socketStatus == -1){
		printf("Fail to create socket");
		exit(1);
	}else{
		printf("Is create client socket");
	}

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
       	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	int connectStatus = connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));

	if(connectStatus == -1){
		printf("Connect Fail\n");
		exit(1);
	}

	char response[256];
	recv(client_socket, &response, sizeof(response), 0);

	printf("recv : %s\n", response);

	close(client_socket);
		
	return 0;
}
