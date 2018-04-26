#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
	
	if(argc<2){
		printf("<path> <host-name>");
		exit(1);
	}

	char *address = argv[1];
	char ip[100];

	struct hostent *he;
	struct in_addr **addr_list;
	he = gethostbyname(address);
	if(he == NULL){
		printf("Wrong hostname");
		exit(1);
	}
	addr_list = (struct in_addr**)he->h_addr_list ;
	strcpy(ip, inet_ntoa(*addr_list[0]));
	
	int client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(80);
	inet_aton(ip, &server_address.sin_addr.s_addr);

	int connectStatus = connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));
	if(connectStatus == -1){
		printf("Connect Fail\n");
		exit(1);
	}

	char fnGet[] = "GET / HTTP/1.1\r\n\r\n";
        char response[4096];

	send(client_socket, fnGet, sizeof(fnGet), 0);
	recv(client_socket, &response, sizeof(response), 0);
	
	printf("response : \n%s", response);

	close(client_socket);


	return 0 ;
}
