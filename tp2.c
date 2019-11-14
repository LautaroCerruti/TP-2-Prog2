#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct {
  char Nombre[40], Apellido[40], Edad[3];
  int Codigo_localidad, Genero, Genero_Interes;
}Persona;

int comparaInt(const void *i, const void *j){
  int *a = (int *) i, *b = (int *)j;
  return *a - *b;
}

void swapint(int* numeros,int posicion1,int posicion2){
  int buffer = numeros[posicion1];
  numeros[posicion1] = numeros[posicion2];
  numeros[posicion2] = buffer;
}

void GeneradorNnumerosRandoms(int lineasArchivo, int cantdidatos, int* resultado){
  int *Randoms = (int*) malloc(sizeof(int)*lineasArchivo), i, aleatorio;

  for( i = 0;i<lineasArchivo;i++){
    Randoms[i] = i;
  }
  for(i = 0 ; i < cantdidatos; i++){
    aleatorio = rand() % (lineasArchivo  - i) ;
    resultado[i] = Randoms[aleatorio];
    swapint(Randoms, aleatorio, (lineasArchivo-i-1));
  }
  free(Randoms);
}

int ContadorDeLineas(FILE* Entrada){
  char linea[1024];
  int lineasArchivoPersonas = 0;
  while(fgets(linea, 1024, (FILE*) Entrada)) {
    lineasArchivoPersonas++;
  }
  rewind(Entrada);
  return lineasArchivoPersonas;
}

void obtencion_de_personas (int cantdidatos, FILE* Entrada, int lineasArchivoPersonas, Persona *personas){
  int *NumerosDePersonas = (int*) malloc(sizeof(int)*cantdidatos), iterador, PersonaBuscada = 0, iteradorArchivo = 0, codigoLocalidad, genero, generoInteres;
  char** personasAsStrings = (char**) malloc(sizeof(char*)*cantdidatos);
  char nombre[40], apellido[40], edad[3];
  char linea[1024];
  GeneradorNnumerosRandoms(lineasArchivoPersonas, cantdidatos, NumerosDePersonas);
  qsort(NumerosDePersonas, cantdidatos, sizeof(int), comparaInt);
  for(iterador = 0; iterador < cantdidatos; ++iterador){
    personasAsStrings[iterador] = (char*) malloc(sizeof(char)*1024);
  }
  for(iterador = 0; iterador < cantdidatos; ++iterador){
    PersonaBuscada = NumerosDePersonas[iterador];
    for(iteradorArchivo; fscanf(Entrada, "%[^,],%[^,],%i,%[^,],%i,%i", nombre, apellido, &codigoLocalidad, edad, &genero, &generoInteres) && iteradorArchivo != PersonaBuscada; ++iteradorArchivo);
    ++iteradorArchivo;
    strcpy(personas[iterador].Nombre, nombre);
    strcpy(personas[iterador].Apellido, apellido);
    strcpy(personas[iterador].Edad, edad);
    personas[iterador].Codigo_localidad = codigoLocalidad;
    personas[iterador].Genero = genero;
    personas[iterador].Genero_Interes = generoInteres;
  }
}

int main(){
  int cantdidatos, lineasArchivoPersonas;
  FILE *Entrada;
  Persona *personas;
  Entrada = fopen("personas2.txt","r");
  srand (time(NULL));
  lineasArchivoPersonas = ContadorDeLineas(Entrada);
  do{
    scanf("%d",&cantdidatos);
  }while(cantdidatos > lineasArchivoPersonas);
  personas = (Persona*) malloc(sizeof(Persona)*cantdidatos);
  obtencion_de_personas(cantdidatos, Entrada, lineasArchivoPersonas, personas);
  for(int iterador = 0; iterador < cantdidatos; ++iterador){
    printf("%s,%s,%d,%s,%d,%d",personas[iterador].Nombre, personas[iterador].Apellido, personas[iterador].Codigo_localidad, personas[iterador].Edad, personas[iterador].Genero, personas[iterador].Genero_Interes);
  }
  return 0;
}

