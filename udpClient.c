#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){

	int client_socket;
	client_socket = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in server_address;
	memset(&server_address, '\0', sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	char message[256] = "I am client";
	sendto(client_socket, message, sizeof(message), 0, (struct sockaddr*)&server_address, sizeof(server_address));

	char response[256];
	socklen_t addr_size = sizeof(server_address);

	recvfrom(client_socket, response, sizeof(response), 0, (struct sockaddr*)&server_address, &addr_size);

	printf("Response : %s\n", response);


	return 0;
}
