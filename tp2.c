#include <stdio.h>
#include <string.h>
#include <time.h>

  typedef struct {
  char Nombre[40];
  char Apellido[40];
  int Codigo_localidad;
  int Edad;
  int Genero;
  int Genero_Interes;
}Persona;

void obtencion_de_personas (int cantdidatos){
int lineas = 0;
Persona candidatos[30];
char linea[1024];
FILE *Entrada;
Entrada = fopen("personas.txt","r");
while(fgets(linea, 1024, (FILE*) Entrada)) {
    lineas++;
}
printf("%d",lineas);
rewind(Entrada);
int Randoms[cantdidatos], i ;
for( i = 0;i<cantdidatos;i++){
  Randoms[i] = srand (time(NULL)) % (lineas+1);

}
//  return candidatos;
}

int main(){
  int cantdidatos;

  scanf("%d",&cantdidatos);
  obtencion_de_personas(cantdidato);

}
