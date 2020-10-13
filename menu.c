#include <stdio.h>

void Importar(char *nombre, HashMap * map);
void Exportar(char *nombre, HashMap * map);
void agregarPokemon(HashMap * map ,char* name, int id, char* tipo, int pc, int ps, char* sexo, char* evoPrevia, char* evoPosterior, char* region, int numPokedex);
void buscaxnombre(HashMap* map, char* nombre);
void buscaxnombre_almacenamiento(HashMap* map, char *nombre);
void Buscarxtipo(HashMap * map, char *tipo);
void Mostrar_Pokemones(HashMap * map);
void LiberarPokemon(HashMap * map, int id);
void MostrarxPC(HashMap * map);
void MostrarxPS(HashMap * map);
void mostrar_Pokemon_Region(char* ,HashMap*);

int menu (HashMap* map) // Interfaz del programa
{
  char opcionMenu;
  int flag = -1;
  printf("Bienvenid@ a la Pokedex! \n");
  
  while(flag != 0)
  {
    printf("\n");
    // Se imprime las opciones del programa
    printf("¿Que deseas hacer?\n a)Importar tus Pokemons \n b)Exportar tus Pokemons \n c)Atrapar un Pokemon y añadirlo a tu almacenamiento \n d)Buscar un Pokemon por su tipo en la Pokedex \n e)Buscar un Pokemon por su nombre (Mostrará informacion general de este Pokemon) \n f)Buscar un Pokemon por su nombre en la Pokedex (Mostrará todos los Pokemons con este nombre) \n g)Mostrar todos los Pokemon de la Pokedex \n h)Mostrar los Pokemon de tu almacenamiento ordenados de mayor a menor por sus PC \n i)Mostrar los Pokemon de tu almacenamiento ordenados de mayor a menor por sus PS \n j)Liberar un Pokemon de tu almacenamiento \n k)Mostrar los Pokemon por región que tienes \n \n Si no quieres hacer nada presiona la tecla Enter \n");
    fflush(stdin);
    scanf("%c", &opcionMenu);
    switch (opcionMenu) // Dependiendo de lo que se ingrese se ejecuta la función determinada
    {
        case 'a': // Llama a función Importar
        {
            char archivo[20];
            printf("Ingresa el nombre del archivo a importar (Sin formato)\n");
            fflush(stdin);
            scanf("%s", archivo);
            Importar(archivo, map);
            break;
        }
        case 'b': // Llama a función Exportar
        {
            char nombre[20];
            printf("Ingrese el nombre que desea que tenga el archivo a exportar (Sin formato)\n");
            fflush(stdin);
            scanf("%s", nombre);
            Exportar(nombre, map);
            printf("Se exportaron los Pokemon al archivo %s.csv\n", nombre);
            break;
        }
        case 'c': // Llama a función agregarPokemon
        {
            fflush(stdin);
            char* nombre = (char *) calloc (50, sizeof(char));
            int id;
            int pc;
            int ps;
            char* sexo = (char *) calloc (50, sizeof(char));
            char* evoPrevia = (char *) calloc (50, sizeof(char));
            char* evoPosterior = (char *) calloc (50, sizeof(char)); 
            char* region = (char *) calloc (50, sizeof(char));
            int numPokedex;
            char* tipo = (char *) calloc (50, sizeof(char));

      
            printf("Ingresa el nombre del pokemon\n");
            fflush(stdin);
            scanf("%s", nombre);
            printf("Ingresa su ID\n");
            fflush(stdin);
            scanf("%i", &id);
            printf("Ingrese su(s) tipo(s)\n");
            fflush(stdin);
            scanf("%s", tipo);
            printf("Ingresa sus puntos de combate\n");
            fflush(stdin);
            scanf("%i", &pc);
            printf("Ingresa sus puntos de salud\n");
            fflush(stdin);
            scanf("%i", &ps);
            printf("Ingresa su sexo (Macho o Hembra)\n");
            fflush(stdin);
            scanf("%s", sexo);
            printf("Ingresa su evolucion previa (en caso de no tener ingrese 'No tiene')\n");
            fflush(stdin);
            scanf("%s", evoPrevia);
            printf("Ingresa su evolucion posterior (en caso de no tener ingrese 'No tiene')\n");
            fflush(stdin);
            scanf("%s", evoPosterior);
            printf("Ingrese su region\n");
            fflush(stdin);
            scanf("%s", region);
            printf("Ingrese su numero de pokedex\n");
            fflush(stdin);
            scanf("%d", &numPokedex);
            
            agregarPokemon(map, nombre, id, tipo, pc, ps, sexo, evoPrevia, evoPosterior, region, numPokedex);
            break;
        }
        case 'd': // Llama a función Buscarxtipo
        {
            char* tipo = (char *) calloc (50, sizeof(char));
            printf("Ingrese el tipo de pokemon que desea buscar en el siguiente formato (tipo1, tipo2) OJO QUE DEBE INGRESAR PRIMERA LETRA MAYUSCULA!\n");
            fflush(stdin);
            scanf("%[^\n]",tipo);
            Buscarxtipo(map ,tipo);
            break;
        }
        case 'e': // Llama a función buscaxnombre_almacenamiento
        {
            char* nombre = (char *) calloc (50, sizeof(char));
            printf("Ingrese nombre del pokemon a buscado\n");
            fflush(stdin);
            scanf("%s", nombre);
            buscaxnombre_almacenamiento(map, nombre);
            break;
        }
        case 'f': // Llama a función buscaxnombre
        {
            char* name = (char*) calloc(100,sizeof(char));
            printf("Ingrese nombre del pokemon a filtrar\n");
            fflush(stdin);
            scanf("%s",name);
            buscaxnombre(map,name);
            break;
        }
        case 'g': // Llama a función Mostrar_Pokemones
        {
            Mostrar_Pokemones(map);
            break;
        }
        case 'h': // Llama a función MostrarxPC
        {
            MostrarxPC(map);
            break;
        }
        case 'i': // Llama a función MostrarxPS
        {
            MostrarxPS(map);
            break;
        }
        case 'j': // Llama a función LiberarPokemon
        {
            int id;
            printf("Ingrese ID de pokemon a liberar\n");
            fflush(stdin);
            scanf("%i", &id);
            LiberarPokemon(map,id);
            break;
        }
        case 'k': // Llama a función mostrar_Pokemon_Region
        {
            char region[20];
            printf("Ingrese region\n");
            fflush(stdin);
            scanf("%s", region);
            mostrar_Pokemon_Region(region,map);
            break;
        }
        case '\n':
        {
            flag = 0;
            break;
        }
        default: // En caso de que ingresen una clave no válida
        {
          printf("Entrada no valida\n");
          printf("\n");
          break;
        }
    }

  }
  
  return 0;
}