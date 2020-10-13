#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "hashmap.c"
#include "treemap.h"
#include "treemap.c"
#include "list.h"
#include "list.c"
#include "lectura_csv.c"
#include "menu.c"

typedef struct // Se define la estructura para el guardado de datos de pokémones
{
  char* nombre;
  int id;
  int pc;
  int ps;
  char* sexo;
  char* tipo;
  char* evoPrevia;
  char* evoPosterior;
  int numPokedex;
  char* region; 
} Pokemon;

Pokemon * crearPokemon() //Funcion para inicializar un dato de tipo Pokemon
{
  Pokemon* input = (Pokemon *) calloc (1, sizeof(Pokemon));
  input->nombre = (char *) calloc (50, sizeof(char));
  input->tipo = (char *) calloc (50, sizeof(char));
  input->sexo = (char *) calloc (50, sizeof(char));
  input->evoPrevia = (char *) calloc (50, sizeof(char));
  input->evoPosterior = (char *) calloc (50, sizeof(char));
  input->region = (char *) calloc (50, sizeof(char));
  return input;
}

int main(){
  HashMap* map = createMap(250); //Mapa informacion Pokemones
  FILE* Pokemons = fopen("pokemonArchivo1.csv", "r");
  char line[100];
  while(fgets(line, 99, Pokemons) != NULL) //Agregar datos de archivo al mapa
  {
    //Se llena el mapa con datos
    Pokemon * datos = crearPokemon();
    datos->id = atoi(get_csv_field(line,0));
    datos->nombre = (char *) get_csv_field(line,1);
    datos->tipo = (char *) get_csv_field(line,2);
    datos->pc = atoi(get_csv_field(line,3));
    datos->ps = atoi(get_csv_field(line,4));
    datos->sexo = (char *) get_csv_field(line,5);
    datos->evoPrevia = (char *) get_csv_field(line,6);
    datos->evoPosterior = (char *) get_csv_field(line,7);
    datos->numPokedex = atoi(get_csv_field(line,8));
    datos->region = (char *) get_csv_field(line,9);
    insertMap(map, &datos->id, datos);    
  }
  //Llenar almacenamiento

  fclose(Pokemons);
  free(Pokemons);
  menu(map);
  free(map);
  return 0;
}

/*   FUNCIONES   */

int filtro(HashMap* map, Pokemon * datos) //Filtro para insertar en funcion importar y agregarPokemon (retorna 0 en caso de que ID no exista y 1 en el contrario)
{
  int flag = 0; // Bandera para determinar si el dato está repetido o no
  Pokemon* aux = (Pokemon *) calloc(1, sizeof(Pokemon)); // Creación del puntero para buscar el dato en el mapa
  aux = firstMap(map);
  while(aux != NULL) // Se recorre el mapa
  {
    if(aux->id == datos->id) // Se devuelve la bandera en caso de encontrar la id
    {
      flag = 1;
      return flag;
    }
    else aux = nextMap(map);
  }
  return flag; // Se retorna la bandera en caso de no encontrar el id
}

void Importar(char * nombre, HashMap * map) //Esta funcion importa pokemons desde un archivo ingresado por el usuario
{
  FILE* input;
  char nombre_archivo[20]; // Se crea un archivo para copiar el contenido del original
  snprintf(nombre_archivo, sizeof(nombre_archivo), "%s%s", nombre, ".csv");
  input = fopen(nombre_archivo, "r");
  int cont = 0;
  if(input == NULL)
  {
    printf("No existe el archivo\n");
    return;
  }

  char line[100];
  while(fgets(line, 99, input) != NULL) //Agregar datos de archivo al mapa
  {
    Pokemon * datos = crearPokemon();
    datos->id = atoi(get_csv_field(line,0));
    datos->nombre = (char *) get_csv_field(line,1);
    datos->tipo = (char *) get_csv_field(line,2);
    datos->pc = atoi(get_csv_field(line,3));
    datos->ps = atoi(get_csv_field(line,4));
    datos->sexo = (char *) get_csv_field(line,5);
    datos->evoPrevia = (char *) get_csv_field(line,6);
    datos->evoPosterior = (char *) get_csv_field(line,7);
    datos->numPokedex = atoi(get_csv_field(line,8));
    datos->region = (char *) get_csv_field(line,9);

    if(filtro(map, datos) == 0)
    {
      insertMap(map, &datos->id, datos);
      cont++;
    }
  }

  fclose(input);
  free(input);
  printf("Fueron agregados exitosamente %i Pokemons\n", cont);
}

void Exportar(char *nombre, HashMap* map) //Esta funcion exporta todos los pokemons en posesion en un archivo nuevo
{
  FILE* output;
  char nombreArchivo[20]; // Se crea un archivo para copiar el contenido del original
  snprintf(nombreArchivo ,sizeof(nombreArchivo),"%s%s", nombre,".csv");
  output = fopen(nombreArchivo, "w");
  // Se crea un dato tipo pokémon para copiar los datos al mapa
  Pokemon* p = (Pokemon *) calloc (1,sizeof(Pokemon));
  p = firstMap(map);
  char line[100];
  while(p != NULL) // Se recorre el archivo
  {
    snprintf(line, sizeof(line), "%i, %s, %s, %i, %i, %s, %s, %s, %i, %s\n", p->id, p->nombre , p->tipo, p->pc, p->ps, p->sexo, p->evoPrevia, p->evoPosterior, p->numPokedex, p->region);
    fputs(line, output);
    p = nextMap(map);
  }
  fclose(output);
  free(output);
  free(p);
}


void agregarPokemon(HashMap* map ,char* name, int id, char* tipo, int pc, int ps, char* sexo, char* evoPrevia, char* evoPosterior, char* region, int numPokedex) //Esta funcion agrega un pokemon a su pokedex
{
  // Se crea un dato tipo pokémon insertar los datos del pokémon
  Pokemon * datos = crearPokemon();
  datos->id = id;
  datos->nombre = name;
  datos->tipo = tipo;
  datos->pc = pc;
  datos->ps = ps;
  datos->sexo = sexo;
  datos->evoPrevia = evoPrevia;
  datos->evoPosterior = evoPosterior;
  datos->region = region;
  datos->numPokedex = numPokedex;
  //Se usa un filtro para verificar si el pokémon existe en el mapa
  if(filtro(map, datos) == 0) 
  {
    insertMap(map, &datos->id, datos); // En caso de no existir se ingresa en el mapa
    printf("Pokemon agregado exitosamente!\n"); 
  }else printf("Ya existe un pokemon con este ID\n"); // En caso de existir no se ingresa en el mapa
}

void buscaxnombre_almacenamiento(HashMap* map, char* nombre) //Esta funcion muestra la información de la pokedex del pokémon
{
  // Se imprime una pequeña interfaz para orientar los datos
  printf("TIPOS | EVOLCION PREVIA | EVOLUCION POSTERIOR | NUMERO POKEDEX | REGION\n");
  int flag = 0;
  // Se crea un dato tipo pokémon para recorrer el mapa
  Pokemon* p = (Pokemon *) calloc (1, sizeof(Pokemon));
  crearPokemon(*p);
  p = firstMap(map);
  while(p != NULL) // Se recorre el mapa
  {
    if(strcmp(nombre, p->nombre) == 0) // Si se encuentra el pokémon, se imprime
    {
      flag = 1;
      printf("%s | %s | %s | %i | %s\n", p->tipo, p->evoPrevia, p->evoPosterior, p->numPokedex, p->region);
      return;
    } 
    p = nextMap(map);
  }

  // Sino se encuentra, se indica por pantalla
  printf("No existe el pokémon en los datos de la pokédex\n");
}

void buscaxnombre(HashMap* map, char* nombre) //Esta funcion muestra todos los pokemones almacenados con el mismo nombre
{
  // Se imprime una pequeña interfaz para orientar los datos
  printf("ID | TIPOS | PC | PS | SEXO | EVOLCION PREVIA | EVOLUCION POSTERIOR | NUMERO POKEDEX | REGION\n");
  int flag = 0;
  // Se crea un dato tipo pokémon para recorrer el mapa
  Pokemon* p = (Pokemon *) calloc (1, sizeof(Pokemon));
  crearPokemon(*p);
  p = firstMap(map);
  while(p != NULL) // Se recorre el mapa
  {
    if(strcmp(nombre, p->nombre) == 0) // Se imprime los nombres de los pokémones guardados
    {
      flag = 1;
      printf("%i | %s | %i | %i | %s | %s | %s | %i | %s\n", p->id, p->tipo, p->pc, p->ps, p->sexo, p->evoPrevia, p->evoPosterior, p->numPokedex, p->region);
    } 
    p = nextMap(map);
  }

  if(flag = 0) printf("No existen pokemons en su almacenamiento con este nombre\n"); // De no existir el nombre, lo indica
  free(p);
}

void Mostrar_Pokemones(HashMap* map) //Esta funcion muestra todos los pokemons almacenados
{
  // Se imprime una pequeña interfaz para orientar los datos
  printf("NOMBRE | ID | TIPOS | PC | PS | SEXO | EVOLCION PREVIA | EVOLUCION POSTERIOR | NUMERO POKEDEX | REGION\n");
  Pokemon* p = firstMap(map); // Se crea un dato tipo pokémon para recorrer el mapa
  while(p != NULL) // Se recorre todo el mapa imprimiendo los datos de los pokémones en el mapa
  {
    printf("%s | %i | %s | %i | %i | %s | %s | %s | %i | %s\n", p->nombre, p->id, p->tipo, p->pc, p->ps, p->sexo, p->evoPrevia, p->evoPosterior, p->numPokedex, p->region);
    p = nextMap(map);
  }
}

void Buscarxtipo(HashMap* map, char *tipo) //Esta funcion muestra por pantalla todos los pokemones del tipo buscado
{
  // Se imprime una pequeña interfaz para orientar los datos
  printf("NOMBRE | PS | PC\n");
  int flag = -1;
  // Se crea un dato tipo pokémon para los tipos de los pokemones del tipo ingresado
  Pokemon* p = (Pokemon *) calloc (1, sizeof(Pokemon));
  crearPokemon(*p);
  p = firstMap(map);

  while(p != NULL) // Se recorre el mapa
  {
    if(strcmp(tipo, p->tipo) == 0) // Si se encuentra un pokémon con el tipo indicado, lo imprime
    {
      flag = 1;
      printf("%s | %i | %i\n", p->nombre, p->ps, p->pc);
    }
    p = nextMap(map); // Se pasa al siguiente dato
  }

  if(flag == -1) printf("No existen pokemons en tu almacenamiento con este tipo\n"); // En caso de no encontrar el tipo, se indica por pantalla
  free(p);
}

void LiberarPokemon(HashMap* map, int id) //Esta funcion libera un pokemon en base a su ID
{
  // Se crea un dato tipo pokémon para buscar el pokémon ingresado
  Pokemon* p = (Pokemon *) calloc (1, sizeof(Pokemon));
  crearPokemon(*p);
  p = firstMap(map);

  while(p != NULL) // Se busca el pokémon a eliminar a traves del id
  { 
    if(p->id == id){ // En caso de encontrarse el pokémon lo elimina
      eraseMap(map, &p->id);
      printf("Pokemon liberado exitosamente!\n");
      return;
    }
    else{
      p = nextMap(map); // Sino pasa al siguiente pokémon
    }
  }

  // En caso de no existir el pokémon imprime que no existe en el mapa
  printf("El pokémon no existe\n");
}

int lower_than_int(void* key1, void* key2){ //Funcion utilizada para crear arbol binario
    int k1 = *((int*) (key1));
    int k2 = *((int*) (key2));
    return k1<k2;
}

void MostrarxPC(HashMap * map) //Esta funcion muestra todos los pokemons almacenados ordenados de forma descendente por sus PC
{
  printf("NOMBRE | PC\n");
  // Se crea un dato tipo pokémon para poder mover los datos
  Pokemon* p = (Pokemon *) calloc (1, sizeof(Pokemon));
  crearPokemon(*p);
  p = firstMap(map);
  TreeMap* pc = createTreeMap(lower_than_int); //Mapa para ordenar de menor a mayor por PC
  while(p != NULL) //Se llena el mapa ordenado
  {
    insertTreeMap(pc, &p->pc, p);
    p = nextMap(map);
  }

  List* list = create_list(); //Lista para posteriormente imprimir ordenado
  p = firstTreeMap(pc);
  while(p != NULL) //Se llena la lista
  {
    push_front(list, p);
    p = nextTreeMap(pc);
  }
  
  p = first(list);
  while(p != NULL) //Se imprime la lista ordenada
  {
    printf("%s | %d\n", p->nombre , p->pc);
    p = next(list);
  }
}

void MostrarxPS(HashMap * map) //Esta funcion imprime por pantalla todos los pokemons ordenados de forma descendente por sus PS
{
  printf("NOMBRE | PS\n");
  // Se crea un dato tipo pokémon para poder mover los datos
  Pokemon* p = (Pokemon *) calloc (1, sizeof(Pokemon));
  crearPokemon(*p);
  p = firstMap(map);
  TreeMap* ps = createTreeMap(lower_than_int); //Mapa para ordenar de menor a mayor por PS
  while(p != NULL) //Se llena el mapa ordenado
  {
    insertTreeMap(ps, &p->ps, p);
    p = nextMap(map);
  }

  List* list = create_list(); //Lista para posteriormente imprimir ordenado
  p = firstTreeMap(ps);
  while(p != NULL) //Se llena la lista
  {
    push_front(list, p);
    p = nextTreeMap(ps);
  }
  
  p = first(list);
  while(p != NULL) //Se imprime la lista ordenada
  {
    printf("%s | %d\n", p->nombre , p->ps);
    p = next(list);
  }
}

void mostrar_Pokemon_Region(char* region,HashMap* map){ //Esta funcion muestra todos los pokemons de una misma region

  // Se crea un dato tipo pokémon para poder comparar
  Pokemon* datos = (Pokemon *) calloc(1,sizeof(Pokemon));
  crearPokemon(datos);
  datos = firstMap(map);

  int cont = 0;
  int caso = 0;

  // Se imprime una pequeña interfaz para orientar los datos
  printf("Nombre | Tipo | PC | PS | Sexo | EvoPrevia | EvoPosterior | Pokedex\n");

  while(datos != NULL){ // Se recorre el mapa imprimiendo los datos de los pokémones pertenecientes a la región
    if(strcmp(region,datos->region) == 0){
      caso = 1;
      cont++;
      printf("%s | %s | %d | %d | %s | %s | %s | %d\n",datos->nombre,datos->tipo,datos->pc,datos->ps,datos->sexo,datos->evoPrevia,datos->evoPosterior,datos->numPokedex);
    }
    datos = nextMap(map);
  }

  if(caso == 0){ // Se imprime la cantidad de pokémones pertenecientes a la región
    printf("Region no valida\n");
  }
  else{
    printf("Tienes %d pokemones de la region %s\n",cont,region);
  }
}
