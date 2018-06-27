#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define pswdfile "./secret"
#define datasize 32

int main(int argc, char **argv){
	char uinp[datasize];
	uinp[32]="\0";
	char filedata[datasize] ;
	FILE *fd;
	char cmd[40];
	if(argc != 2){
		printf("%s [password]\n",argv[0]);
		exit(EXIT_FAILURE);
		}

	strncpy(uinp,argv[1],sizeof(uinp)-1);

	if(!(fd = fopen(pswdfile,"r"))){
		perror("fopen()");
		exit(EXIT_FAILURE);
		}

	fcntl(3,FD_CLOEXEC);
	fgets(filedata,sizeof(filedata),fd);
	filedata[sizeof(filedata)-1]="\0";
	printf("Your Access is ..\n");

	if(strcmp(uinp,filedata) != 0){
		setreuid(getuid(),getuid());
		fflush(stdout);
		fprintf(stderr,"Denied bye.\n");
		execve("/bin/sh",NULL,NULL);
		return EXIT_FAILURE;
		}


	fprintf(stdout,"Garanted ^^ Welcome\n");
	execve("/bin/sh",NULL,NULL);
	return EXIT_SUCCESS;
}
