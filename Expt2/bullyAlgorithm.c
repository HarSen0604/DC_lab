#include <sys/socket.h>
#include <netinet.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#define MSG_CONFIRM 0
#define TRUE 1
#define FALSE 0
#define ML 1024
#define MPROC 32

/*
	Function to create a new connection to port `connect_to`
 	1. Creates the socket
  	2. Binds to port
   	3. Returns socket id
*/

int connect_to_port (int connect_to) {
	int sock_id;
	int opt = 1;
	struct sockaddr_in server;
	sock_id = socket(AF_INET, SOCK_DGRAM, 0);
	if ((sock_id < 0)) {
		perror("unable to create a socket");
		exit(EXIT_FAILURE);
	}
	setsockopt(sock_id, SOL_SOCKET, SO_RESUSEADDR, (const void *)&opt, sizeof(int));
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(connect_to);

	if (bind(sock_id, (const struct sockaddr *)&server, sizeof(server)) < 0) {
		perror("unable to bind to port");
		exit (EXIT_FAILURE);
	}
	return sock_id;
}
