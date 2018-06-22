/* * * * * * * * *
 * List of helper functions that are used by the main program.
 
 * Author: William Liandri
 * Student ID: 728710
 * Project 1 - Computer System
 * 
 */
 
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "libraries.h" 
#include "struct.h"

/******************************** CONSTANTS ********************************/
#define REQUEST_SUCCEEDED 200 /* Response is success */
#define PAGE_NOT_FOUND 404 /* File not found */
#define OK "OK" /* Response status for 200 */
#define NOT_FOUND "NOT FOUND" /* Response status for 404 */
#define INDEX 5 /* The start index of the file directory in the buffer */
#define INIT_SIZE 512 /* The initial size for the send buffer */
#define SIZE_REQUEST 8192 /* The size of the request buffer */
#define HTML "html" 
#define CSS "css"
#define JS "js"
#define JPG "jpg"

/*************************** FUNCTION PROTOTYPES ***************************/
/* Helper function to begin acccepting the connection */ 
void accept_connection(int sockfd, char *root_directory);

/* Helper function to get the file path */
char* get_file_path(char buffer[SIZE_REQUEST]);

/* Helper function to create the http header */
void create_http_header(response_header_t *header_response,
	char *filetype);

/* Helper function to get the HTTP response */
response_header_t get_http_header(char *filepath, char *filetype,
	char **tempBuffer);



#endif
