#include <stdio.h>
//Lee un archivo
int main()
{
    FILE *file;
    char lectura[255]; 
    file = fopen("myarchivo.txt","r");
    if (file==NULL)
    {
       printf ("Crea el archivo primero"); 
       return 1;
    }  
    while(!feof(file))
    {       
        fgets(lectura,255,file);
        printf("%s",lectura);    
    }
    fclose(file);
    return 0;
}