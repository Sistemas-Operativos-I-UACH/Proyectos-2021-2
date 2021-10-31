#include <stdio.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>

void open_proc(char *pf)
{
    FILE *file;
    char proc_file[255];

    file = fopen(pf, "r");

    if (file == NULL)
    {
        printf("Este proceso no contiene dicho archivo.");
    }
    else
    {
        while (!feof(file))
        {
            fgets(proc_file, 255, file);
            printf("%s", proc_file);
            fclose(file);
        }
    }
}

int open_mem(char *pf)
{
    FILE *file;
    int size_rss;
    int total;
    char dummy[255];
    char proc_file[255];

    file = fopen(pf, "r");

    if (file == NULL)
    {
        printf("Este proceso no contiene dicho archivo.");
    }
    else
    {
        while (!feof(file))
        {
            fgets(proc_file, 255, file);
            if (strchr(proc_file, 'R') && strchr(proc_file, 's'))
            {
                sscanf(proc_file, "%s %d %s", dummy, &size_rss, dummy);
                total += size_rss;
            }
        }
        fclose(file);
        return total;
    }
}

void open_nice(char *pf)
{
    FILE *file;
    char proc_file[255];
    long int nice, priority;
    char dummy[255];

    file = fopen(pf, "r");

    if (file == NULL)
    {
        printf("Este proceso no contiene dicho archivo.");
    }
    else
    {
        while (fgets(proc_file, 255, file) != NULL)
        {
            sscanf(proc_file, "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld",
                   &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy,
                   &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &priority, &nice);
            printf("\nPriority:\t%ld", priority);
            printf("\nNiceness:\t%ld", nice);
            fclose(file);
        }
    }
}

void open_uid(char *pf)
{
    FILE *file;
    char proc_file[255], usr[255];
    file = fopen(pf, "r");

    if (file == NULL)
    {
        printf("Este proceso no contiene dicho archivo.");
    }
    else
    {
        while (!feof(file))
        {
            fgets(proc_file, 255, file);
            if (strchr(proc_file, '1'))
            {
                printf("UID:\t\t%s\n", proc_file);
                printf("User:\t\tFlick\n");
            }
            else
                printf("User:\t\tKernel\n");
            fclose(file);
        }
    }
}

void open_memtotal(char *pf)
{
    FILE *file;
    char proc_file[255];

    file = fopen(pf, "r");

    if (file == NULL)
    {
        printf("Este proceso no contiene dicho archivo.");
    }
    else
    {
        while (!feof(file))
        {
            fgets(proc_file, 255, file);
            printf("%s", proc_file);
            fclose(file);
        }
    }
}

int main(int argc, char **argv)
{
    struct dirent *de;
    DIR *dr = opendir("/proc/");

    char fname[255];
    int i = 0;
    int total;

    if (dr == NULL)
    {
        printf("Error, /proc fallo al abrir.");
        return 1;
    }

    while ((de = readdir(dr)) != NULL)
        if (isdigit(de->d_name[0]) != 0)
        {
            printf("ID:\t\t%s\n", de->d_name);

            strcpy(fname, "/proc/");
            strcat(fname, de->d_name);
            strcat(fname, "/comm");
            printf("Nombre: \t");
            open_proc(fname);

            strcpy(fname, "/proc/");
            strcat(fname, de->d_name);
            strcat(fname, "/cmdline");
            printf("cmdline:\t");
            open_proc(fname);

            strcpy(fname, "/proc/");
            strcat(fname, de->d_name);
            strcat(fname, "/smaps");
            total = open_mem(fname);
            if (total != 0)
                printf("\nMemoria:\t%d MB", total / 1024);
            else
                printf("\nMemoria:\t%d kiB", total);

            strcpy(fname, "/proc/");
            strcat(fname, de->d_name);
            strcat(fname, "/stat");
            open_nice(fname);
            printf("\n");

            strcpy(fname, "/proc/");
            strcat(fname, de->d_name);
            strcat(fname, "/loginuid");
            open_uid(fname);
            printf("\n- - - - - - - - - - - - - - - - - - - - -\n");
            i++;
        }
    strcpy(fname, "/proc/meminfo");
    open_memtotal(fname);
    printf("# de Procesos: \t%d\n", i);
    closedir(dr);
    return 0;
}