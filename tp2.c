#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

  typedef struct {
  char Nombre[40];
  char Apellido[40];
  int Codigo_localidad;
  int Edad;
  int Genero;
  int Genero_Interes;
}Persona;


void swapint(int* numeros,int posicion1,int posicion2){
  int buffer;
  
  buffer = numeros[posicion1];
  numeros[posicion1] = numeros[posicion2];
  numeros[posicion2] = buffer;

}

void GeneradorNnumerosRandoms(int lineas,int cantdidatos,int* resultado){
   int *Randoms = (int*) malloc(sizeof(int)*lineas), i, aleatorio;

  for( i = 0;i<lineas;i++){
    Randoms[i] = i;
  }
  for(i = 0 ; i < cantdidatos; i++){
    aleatorio = rand() % (lineas  - i) ;
    resultado[i] = Randoms[aleatorio];
    puts(" ");
    printf("%d",aleatorio);
    swapint(Randoms,aleatorio,(lineas  - i));
  }
 
}

void MoveInFile(FILE* Entrada,int linea){

}

int ContadorDeLineas(FILE* Entrada){
 char linea[1024];
 int lineas = 0;
  while(fgets(linea, 1024, (FILE*) Entrada)) {
     lineas++;
  }
  return lineas;
}

void obtencion_de_personas (int cantdidatos, FILE* Entrada, int lineas){
  int *resultado = (int*) malloc(sizeof(sizeof(int)*cantdidatos));

GeneradorNnumerosRandoms(lineas,cantdidatos,resultado);
 char** People = (char**) malloc(sizeof(char));

//  return candidatos;
}


int main(){
  int cantdidatos, lineas;
  FILE *Entrada;
  Entrada = fopen("personas.txt","r");
  srand (time(NULL));
  lineas = ContadorDeLineas(Entrada);
  do{
    scanf("%d",&cantdidatos);
  }while(cantdidatos > lineas);
  obtencion_de_personas(cantdidatos, Entrada, lineas);

}

