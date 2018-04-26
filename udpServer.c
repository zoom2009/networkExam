#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>

int main() {
	
	int server_socket;
	server_socket = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in server_address, client_address;
	memset(&server_address, '\0', sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

	char response[1024];
	socklen_t addr_size = sizeof(client_address);
	recvfrom(server_socket, response, sizeof(response), 0, (struct sockaddr*)&client_address, &addr_size);

	printf("response from client : %s\n", response);
	
	char message[256] = "This is udp Server";
	sendto(server_socket, message, sizeof(message), 0, (struct sockaddr*)&client_address, addr_size);

	
	return 0;	
}

