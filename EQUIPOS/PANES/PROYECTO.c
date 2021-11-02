#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <sys/sysinfo.h> //J

void printmemsize(char *str, unsigned long ramsize) { 
        printf("%s: %ld KB\n",str, ramsize/1024); 
}  


void ciclo(char *comando){

	char state, name[32];
    int pid, ppid, pgrp, session, tty, tpgid, nlwp;
    unsigned long flags, min_flt, cmin_flt, maj_flt, cmaj_flt, vsize;
    unsigned long long utime, stime, cutime, cstime, start_time;
    long priority, nice, alarm, rss;

	FILE *fd;
	fd = fopen(comando, "r");
	char linea[255];

	if (fd==NULL){
		printf ("No existe el archivo a dicho proceso...");
	}else{
		while (fgets(linea,255,fd)!=NULL){
			printf ("-------------------------\n");
			sscanf(linea, "%d %s " "%c " "%d %d %d %d %d " "%lu %lu %lu %lu %lu " "%Lu %Lu %Lu %Lu "
			"%ld %ld " "%d " "%ld " "%Lu " "%lu " "%ld", &pid, name, &state, &ppid, &pgrp, &session, &tty, &tpgid,
			&flags, &min_flt, &cmin_flt, &maj_flt, &cmaj_flt, &utime, &stime, &cutime, &cstime, &priority, &nice,
			&nlwp, &alarm, &start_time, &vsize, &rss);
			printf ("PID: %d\n" "CMD: %s\n" "Estado: %c\n" "PPID: %d\n" "Prioridad (nice): %ld\n" "Tama�o: %lu\n" "RAM (rss): %ld KiB\n",
			pid, name, state, ppid, nice, vsize, rss);
		}
		fclose(fd);
	}
}
		
int main(){
    DIR *folder;	
    struct dirent *entry;
    char comando[295];
    folder = opendir("/proc/");       
    struct sysinfo info;
    sysinfo(&info);
	
    while((entry=readdir(folder))!=NULL){
        if (isdigit (entry->d_name[0]) != 0){
        	strcpy (comando,"/proc/");
        	strcat (comando,entry->d_name);
        	strcat (comando,"/stat");
        	ciclo(comando);
			sprintf(comando, "/proc/%s/status", entry->d_name);
			FILE *fdu = fopen(comando, "r");
			if ( fdu != NULL ){
				char linea[256];
				int count = 0;
				while (fgets(linea, sizeof linea, fdu) != NULL){
					if (count == 8){
						printf("(Pertenencia) %.30s", linea);
						break;
					}else{
						count++;
					}
				}
				fclose(fdu);
			}
        }
    }
    printf ("=============================\n");
    printmemsize("RAM total del sistema", info.totalram);
    printf ("=============================\n");
    closedir(folder);
    return 0;
}
