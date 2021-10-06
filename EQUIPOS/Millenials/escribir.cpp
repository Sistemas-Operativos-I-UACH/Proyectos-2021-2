#include<iostream>
using namespace std;

int main(){
    FILE *archivo = fopen("archivo.txt","a");
    char texto[50];

    cout<<"Ingresa un texto"<<endl;
    cin.getline(texto,50,'\n');

    fprintf(archivo,"%s\n", texto);

    return 0;
}