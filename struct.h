/* * * * * * * * *
 * Struct to store information about the response header that are going to 
 * be sent to the client.
 * 
 * Author: William Liandri
 * Student ID: 728710
 * Project 1 - Computer System
 */

#ifndef RESPONSE_HEADER_H
#define RESPONSE_HEADER_H

typedef struct Response_header {
	char* header;
	int total_char;
	int response_number;
	char* response_status;
} response_header_t;


#endif