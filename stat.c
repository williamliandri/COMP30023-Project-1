#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	
	FILE *fp;
	//char filename[15], root_dir;
	size_t pngDataLength;

	//strcpy(filename, "index.html");
	
	//root_dir = (char *) malloc(strlen(argv[1]) * sizeof(char));
	//strcpy(root_dir, argv[1]);
	//strcat(root_dir, filename);
	//printf("%s\n", root_dir);
	
	fp = fopen("test/index.html", "rb");
	fseek(fp, 0, SEEK_END);
	int filelen = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	printf("%d\n", filelen);

	if (fp) {
    	// get file size from file info
    	struct stat finfo;
    	fstat(fileno(fp), &finfo);
    	pngDataLength = finfo.st_size;
    
    	printf("Data length: %d\n", (int)pngDataLength);
    }
    
    else if (fp == NULL) {
    	printf("File not found\n");	
    }
    
	return 0;
	
	
}










