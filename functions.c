/* * * * * * * * *
 * List of helper functions that are used by the main program.
 *
 * Author: William Liandri
 * Student ID: 728710
 * Project 1 - Computer System
 * 
 */
 
#include "functions.h"
 
/**************************** ACCEPT CONNECTION ****************************/
/* Helper function to begin acccepting the connection */ 
void accept_connection(int sockfd, char *root_directory) {
	struct sockaddr_in cli_addr;
	socklen_t clilen = sizeof(cli_addr);
	int newsockfd, n;
	char buffer[SIZE_REQUEST], *tempBuffer, *filepath, *filetype;
	response_header_t header_response;
	 	
	/* Accept a connection */
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		
	if (newsockfd < 0) {
		perror("ERROR on accept");
		exit(1);
	}
		
	bzero(buffer, SIZE_REQUEST);
	
	/* Read the data from the connections then process */
	n = read(newsockfd, buffer, SIZE_REQUEST);
	
	if (n < 0) {
		perror("ERROR reading from socket");
		exit(1);
	}
		
	printf("%s\n", buffer);
		
	fflush(stdout);
		
	/** RESPONSE MESSAGE **/
		
	if (!isspace(buffer[INDEX])) { 
			
		/* Get the file path */
		filepath = get_file_path(buffer);
			
		/* Get the file type */
		char copy_filepath[strlen(filepath)];
		strcpy(copy_filepath, filepath);
		filetype = strtok(copy_filepath, ".");
		filetype = strtok(NULL, " ");
		
		/* Concatenates the file path with the web root directory */
		char *web_root_dir;
		web_root_dir = (char *) malloc((strlen(filepath) + 
			strlen(root_directory))*sizeof(char));
		strcpy(web_root_dir, root_directory);
		strcat(web_root_dir, filepath);
		strcpy(filepath, web_root_dir);
		
		/* Remove the "/" at the beginning of the file path to be able
		to open the file */
		if (filepath[0] == '/') {
			memmove(filepath, filepath+1, strlen(filepath));
		}
	
		header_response = get_http_header(filepath, filetype, 
			&tempBuffer);
					
		/* Write it to the socket. */
		n = write(newsockfd, tempBuffer, 
			header_response.total_char);
		
		if (n < 0) {
			perror("ERROR writing to socket\n");
			exit(1);
		}
		
		/* Free the memory. */
		free(tempBuffer);
	}
		
	/* Close the socket. */
	close(newsockfd);
	
}

/****************************** GET FILE PATH ******************************/
/* Helper function to get the file path */
char* get_file_path(char buffer[SIZE_REQUEST]) {
	char *filepath;
	filepath = strtok(buffer, " ");
	filepath = strtok(NULL, " ");

	return filepath;
}

/**************************** CREATE HTTP HEADER ***************************/
/* Helper function to create the http header */
void create_http_header(response_header_t *header_response,
	char *filetype) {
	int num_chars = 0;
	
	/* Begin to create the header response */
	num_chars = sprintf(header_response->header, "HTTP/1.0 %d %s\r\n",
		header_response->response_number, 
		header_response->response_status);
	header_response->header += num_chars;
			
	// It detects jpeg file.
	if ((strcmp(filetype, JPG) == 0)) {
		num_chars = sprintf(header_response->header, 
		"Content-Type: image/jpeg\r\n\r\n");
		header_response->header += num_chars;	
	}
		
	// It detects either HTML or CSS file.
	else if ((strcmp(filetype, HTML) == 0) || 
		(strcmp(filetype, CSS) == 0)) {
		num_chars = sprintf(header_response->header, 
		"Content-Type: text/%s\r\n\r\n", filetype);
		header_response->header += num_chars;
	}
	
	// It detects JS file.
	else if ((strcmp(filetype, JS) == 0)) {
		num_chars = sprintf(header_response->header, 
		"Content-Type: text/javascript\r\n\r\n");
		header_response->header += num_chars;
	}
}

/**************************** GET HTTP RESPONSE ****************************/
/* Helper function to get the HTTP response */
response_header_t get_http_header(char *filepath, char *filetype,
	char **tempBuffer) {
	response_header_t header_response;
	int num_chars = 0, c;
	FILE *fd;
	struct stat finfo;
	int filesize = 0;
	
	/* Open the file */
	fd = fopen(filepath, "rb");
	
	/* Get the file size */
	if (fd) {
		fstat(fileno(fd), &finfo);
		filesize = (int) finfo.st_size;
	}
	
	/* Allocate the memory for the buffer */
	*tempBuffer = (char *) malloc((INIT_SIZE + filesize) * sizeof(char));

	header_response.header = *tempBuffer;
	header_response.total_char = 0;

	/* Determine the response number and the response status. */
	if (fd == NULL) {
		header_response.response_number = PAGE_NOT_FOUND;
		header_response.response_status = (char *) malloc(
			strlen(NOT_FOUND) * sizeof(char));
			
		strcpy(header_response.response_status, NOT_FOUND);
	}
	
	else {
		header_response.response_number = REQUEST_SUCCEEDED;
		header_response.response_status = (char *) malloc (
			strlen(OK) * sizeof(char));
			
		strcpy(header_response.response_status, OK);
	}
	
	/* Begin to create the header response */
	create_http_header(&header_response, filetype);

	/* Write the body */
	if (fd) {
		while((c = fgetc(fd)) != EOF) {
			num_chars = sprintf(header_response.header, "%c", c);
			header_response.header += num_chars;
		}
		
		/* Close the file */
		fclose(fd);
	}
	
	header_response.total_char = header_response.header - *tempBuffer;
	
	/* Free the memory */
	free(header_response.response_status);
	
	return header_response;

}

 
 
