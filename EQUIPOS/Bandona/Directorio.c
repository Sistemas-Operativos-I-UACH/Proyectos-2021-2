#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<dirent.h>

void read_file(char *f){

	FILE *file= fopen(f,"r");
	char line[255];
	if(file==NULL){
		printf("Sin archivo cmdline");
	}else{
		while(feof(file)==0){
		printf("Archivo cmdline: ");
		fgets(line,255,file);
		puts(line);
		printf("\n");
		}
	}
	fclose(file);
	
}

int main(int argc, char *argv[])
{
	DIR *dir;
	struct dirent *sd;
	char dirName[255];
	dir = opendir("/proc");
	
	if(dir==NULL)
	{
		printf("Error, no se pudo abrir el directorio.\n");
		exit(1);
	}
	while((sd=readdir(dir)) !=NULL)
	{
		if((*sd->d_name>'0') && (*sd->d_name<='9')){
			printf(">> %s\n", sd->d_name);
			strcpy(dirName, "/proc/");
			strcat(dirName, sd->d_name);
			strcat(dirName, "/cmdline");
			read_file(dirName);
			
		}
	}
	closedir(dir);

	return 0;
	
}