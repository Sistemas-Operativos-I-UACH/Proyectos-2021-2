#include <stdio.h>
#include <dirent.h>
#include <string.h>

void open_file(char *pf)
{
    FILE *file;
    char cmdline_file[255];

    file = fopen(pf, "r");

    if (file == NULL)
    {
        printf("Este proceso no contiene cmdline");
    }
    else
    {
        while (!feof(file))
        {
            fgets(cmdline_file, 255, file);
            printf("Contenido:\t%s\n\n", cmdline_file);
        }
    }
    fclose(file);
}

int main(int argc, char **argv)
{
    struct dirent *de;
    DIR *dr = opendir("/proc/");

    char fname[255];
    int i = 0;

    if (dr == NULL)
    {
        printf("Error, /proc fallo al abrir.");
        return 1;
    }

    while ((de = readdir(dr)) != NULL)
        if (strchr(de->d_name, '0') || strchr(de->d_name, '1') || strchr(de->d_name, '2') || strchr(de->d_name, '3') ||
            strchr(de->d_name, '4') || strchr(de->d_name, '5') || strchr(de->d_name, '6') ||
            strchr(de->d_name, '7') || strchr(de->d_name, '8') || strchr(de->d_name, '9'))
        {
            strcpy(fname, "/proc/");
            strcat(fname, de->d_name);
            strcat(fname, "/cmdline");
            printf("Abriendo:\t%s\n", fname);
            open_file(fname);
            i++;
        }
    printf("CANTIDAD DE PROCESOS: %d", i);
    closedir(dr);
    return 0;
}