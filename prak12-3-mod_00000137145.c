#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>


void err_quit(char *msg)
{
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[]){
	int fdin;
	char *src;
	struct stat statbuf;
	off_t len;

	if(argc != 2){
		fprintf(stderr, "usage: %s <text file>\n", argv[0]);
		exit(0);
	}

	if((fdin = open(argv[1], O_RDONLY)) < 0) err_quit("open");
	if((fstat(fdin, &statbuf)) < 0) err_quit("fstat");
	len = statbuf.st_size;

    // check if the file is empty
    if(len == 0){
        printf("File is empty\n");
        close(fdin);
        return 0;
    }

	if((src=mmap(0, len, PROT_READ | PROT_WRITE, MAP_SHARED, fdin, 0)) == (void *)-1) 
    err_quit("mmap");
	
    for (off_t i = 0; i < len / 2; i++) {
        char temp = src[i];
        src[i] = src[len - 1 - i];
        src[len - 1 - i] = temp;
 }

    printf("File contents have been successfully reversed!\n");
	close(fdin);
	munmap(src,len);

    return 0;
}
