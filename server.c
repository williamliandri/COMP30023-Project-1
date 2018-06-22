/* * * * * * * * *
 * Main Program: Create a simple HTTP server that only serves limited ranges
 * of contents (html, css, js, jpg) and gives response to each GET requests.
 * Additionally, this simple HTTP server also support concurrent connections
 * using fork technique.
 * 
 * Author: William Liandri
 * Student ID: 728710
 * Project 1 - Computer System
 * 
 */

#include "libraries.h"
#include "functions.h"

/******************************** CONSTANTS ********************************/
#define LIMIT 10 /* Maximum number of concurrent connections */
#define TRUE 1

/****************************** MAIN FUNCTION ******************************/
int main (int argc, char **argv) {
	int sockfd, portno;
	struct sockaddr_in serv_addr;
	int children = 0;	
	
	if (argc < 3) {
		fprintf(stderr, "./server [port number] [path to web root]\n");
		exit(1);
	}
	
	/* Create the socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd < 0) {
		perror("ERROR opening socket");
		exit(1);
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	portno = atoi(argv[1]);
	
	/* Create the address that we are going to listen on the given port 
	number, converted to network byte order and any IP address for this 
	machine. */ 
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno); 
	
	/* Bind address to the socket */
	if (bind(sockfd, (struct sockaddr *) &serv_addr, 
		sizeof(serv_addr)) < 0) {
	
		perror("Error on binding\n");
		exit(1);
	}

	/* Listen on socket, which indicates we are ready to accept 
	connections */
	listen(sockfd, 10);
	
	while (TRUE) {
	
		pid_t pid = 0;
		
		if (children <= LIMIT) {
			pid = fork();
			children += 1;
		}
		
		if (pid == -1) {
			printf("Error on fork\n");
			exit(1);
		}		
		
		accept_connection(sockfd, argv[2]);	
	}
	
	/* Close socket */
	close(sockfd);
	
	return 0;
}
