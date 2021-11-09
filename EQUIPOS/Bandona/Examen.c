#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>

void meminfo_file(char*f){
	FILE *fd= fopen(f,"r");
	char n[20];
	long tammem;
	float t;
	fscanf(fd,"%s""%ld",n,&tammem);
	t=tammem;
	printf("\n\nTamaño de memoria del sistema: %f Gb\n",(t/1024)/1024);


}

void info_proceso(char *f){

	FILE *fd= fopen(f,"r");
	
	char name[30],state;
	float t;
	int pid,ppid,pgrp,session,tty_nr,tpgid,i=0;
	unsigned long flags,minflt,cminflt,majflt,cmajflt,utime,stime,starttime,vsize;
	long cutime,cstime,priority,nice,numthreads,itrealvalue;
	
	if(fd==NULL){
		printf("Sin archivo stat");
	}else{
		fscanf(fd,    "%d "    // pid
			      "%s "    // nombre cmd
			      "%c" "%d" "%d" "%d" "%d" "%d" "%lu" "%lu" 
			      "%lu" "%lu" "%lu" "%lu" "%lu" "%ld" "%ld" 
			      "%ld"    //18 prioridad
			      "%ld"    //19 nice
			      "%ld" "%ld" "%lu"
			      "%lu"    //23  tamaño
			      
			      ,&pid     // pid
			      ,name     // nombre cmd
			      ,&state, &ppid, &pgrp, &session, &tty_nr, &tpgid, &flags,  &minflt 				      ,&cminflt, &majflt, &cmajflt, &utime, &stime, &cutime, &cstime
			      ,&priority // prioridad
			      ,&nice     // nice
			      ,&numthreads, &itrealvalue, &starttime
			      ,&vsize);  // tamaño
			      
                printf("%s\n" "\t\t\t %d\t " "\t%ld \t" "%ld\t",name,pid,priority,nice);
                   
                if(vsize==0){
                	printf("%lu B\n",vsize);
                }else{
                	vsize=vsize/1024;
                	printf("%lu Kb\n",vsize);
                }
                 fclose(fd);
	}
}

void proc_kernel(char *f){
	FILE *fd=fopen(f,"r");
	char n;
	
	if(fd==NULL){
		printf("archivo cmdline faltante");
	}else{
		if((n=fgetc(fd))==EOF){
			printf("Proceso de Kernel\n");
		}else{
			printf("Proceso de Usuario\n");
		}
	}
	fclose(fd);
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
	
	// memoria del sistema
	strcpy(dirName, "/proc/meminfo");
	meminfo_file(dirName);
	
	printf("\n\t\t\tInformacion Procesos\n");
	printf ("\tNombre\t" "\tPID\t" "Prioridad\t" "Nice\t " "Tamaño\n ");
	
	while((sd=readdir(dir)) !=NULL)
	{
		if((*sd->d_name>'0') && (*sd->d_name<='9')){
			strcpy(dirName, "/proc/");
			strcat(dirName, sd->d_name);
			strcat(dirName, "/cmdline");
			proc_kernel(dirName);
			
			strcpy(dirName, "/proc/");
			strcat(dirName, sd->d_name);
			strcat(dirName, "/stat");
			info_proceso(dirName);
			
		}
		
	}
	closedir(dir);

	return 0;
	
}
