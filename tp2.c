#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*
  En el programa tomaremos a las personas a escribir en el archivo resultante como una estructura 
  en la cual se alamcenaran los datos de la persona tomados del archivo de entrada
*/
typedef struct {
  char Nombre[40], Apellido[40], Edad[3];
  int Codigo_localidad, Genero, Genero_Interes;
}Persona;
/*
  ComparaInt 
*/
int comparaInt(const void *i, const void *j){
  int *a = (int *) i, *b = (int *)j;
  return *a - *b;
}
/*
  swapint Toma un array de enteros, una posicion1 y otra posicion e intercambia de lugar el numero en la 
primera posicion con el de la segunda
*/
void swapint(int* numeros,int posicion1,int posicion2){
  int buffer = numeros[posicion1];
  numeros[posicion1] = numeros[posicion2];
  numeros[posicion2] = buffer;
}
/*
  Genenra una lista de n numeros randoms no repetidos, siendo n un numero que se ingreso como parametro de la funcion
*/
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
/*
Dado un archivo cuenta la cantidad de lineas que tiene el archivo dado
ContadorDeLineas: File -> Int
*/
int ContadorDeLineas(FILE* Entrada){
  char linea[1024];
  int lineasArchivoPersonas = 0;
  while(fgets(linea, 1024, (FILE*) Entrada)) {
    lineasArchivoPersonas++;
  }
  rewind(Entrada);
  return lineasArchivoPersonas;
}
/*
  Dado un archivo con personas, la cantidad de lineas del archivo, un array de la estructura antes descripta y un numero n
  guarda en el array de la estructura, n personas random no repetidas del archivo.
*/
void obtencion_de_personas (int cantdidatos, FILE* Entrada, int lineasArchivoPersonas, Persona *personas){
  int *NumerosDePersonas = (int*) malloc(sizeof(int)*cantdidatos), iterador, PersonaBuscada = 0, iteradorArchivo = -1, codigoLocalidad, genero, generoInteres;
  char nombre[40], apellido[40], edad[3];
  GeneradorNnumerosRandoms(lineasArchivoPersonas, cantdidatos, NumerosDePersonas);
  qsort(NumerosDePersonas, cantdidatos, sizeof(int), comparaInt);
  for(iterador = 0; iterador < cantdidatos; ++iterador){
    PersonaBuscada = NumerosDePersonas[iterador];
    for(; iteradorArchivo != PersonaBuscada; iteradorArchivo++){
      fscanf(Entrada, "%[^,],%[^,],%d,%[^,],%d,%d", nombre, apellido, &codigoLocalidad, edad, &genero, &generoInteres);
      fgetc(Entrada);
    }
    strcpy(personas[iterador].Nombre, nombre);
    strcpy(personas[iterador].Apellido, apellido);
    strcpy(personas[iterador].Edad, edad);
    personas[iterador].Codigo_localidad = codigoLocalidad;
    personas[iterador].Genero = genero;
    personas[iterador].Genero_Interes = generoInteres;
  }
}
/*
  Dado un string, regularisa el strings, es decir quita los espacios de mas del string
*/
void formateo(char* string){
  int iterador, bandera = 1;
  for(iterador = 0; string[iterador] != '\0' && bandera; ++iterador){
    if(string[iterador] == ' ' && string[iterador + 1] == ' '){
      bandera=0;
      string[iterador]='\0';
    }
  }
}
/*
  Toma un archivo de entrada con las localidades,la cantidad de lineas del archivo y un array de strings
  y guarda en el array todas las localidades de forma tal que el codigo de la ciudad corresponde con el indice del array
*/
void CargaDeLocalidades (FILE* Ciudades, int lineasArchivoLocalidades, char** localidades){
  int iteradorArchivo = 1, iterador, index = 0;
  char localidad[150];
  for(iterador = 1; iterador <= lineasArchivoLocalidades; ++iterador){
    localidades[iterador] = (char*) malloc(sizeof(char)*200);
    fscanf(Ciudades,"%i,%[^\n]", &index, localidad);
    fgetc(Ciudades);
    formateo(localidad);
    strcpy(localidades[index], localidad);
  }
}
/*
recive un archivo de salida, la cantidad de personas a imprimir, un array con la estructura que representa a las personas, las localidades
un array con los posibles generos y otro array con los posibles generos de interes, luego toma los datos de las personas y los imprime en 
el archivo de salida
*/
void ImprimePersonas(FILE* Salida, int cantdidatos, Persona *personas, char** localidades, char *genero, char *generointeres){
  int i = 0;
  for(i = 0; i < cantdidatos; ++i){
    fprintf(Salida, "%s,%s,%s,%s,%c,%c\n", personas[i].Nombre, personas[i].Apellido, localidades[personas[i].Codigo_localidad], personas[i].Edad, genero[personas[i].Genero-1], generointeres[personas[i].Genero_Interes-1]);
  }
}

int main(){
  int cantdidatos, lineasArchivoPersonas, lineasArchivoLocalidades, iterador;
  FILE *Entrada, *Ciudades, *Salida;
  Persona *personas;
  char **localidades, *genero="MF", *generointeres="FMAN";
  Entrada = fopen("personas.txt","r");
  Ciudades = fopen("codigoLocalidades.txt","r");
  srand(time(NULL));
  lineasArchivoPersonas = ContadorDeLineas(Entrada);
  lineasArchivoLocalidades = ContadorDeLineas(Ciudades);
  localidades = (char**) malloc(sizeof(char*)*lineasArchivoLocalidades);

  do{
    scanf("%d",&cantdidatos);
  } while(cantdidatos > lineasArchivoPersonas);
  personas = (Persona*) malloc(sizeof(Persona)*cantdidatos);
  obtencion_de_personas(cantdidatos, Entrada, lineasArchivoPersonas, personas);
  fclose(Entrada);
  CargaDeLocalidades(Ciudades, lineasArchivoLocalidades, localidades);
  fclose(Ciudades);
  Salida = fopen("salida.txt","w+");
  ImprimePersonas(Salida, cantdidatos, personas, localidades, genero, generointeres);
  free(localidades);
  free(personas);
  return 0;
}
