#ifndef FIXTURE_H_INCLUDED
#define FIXTURE_H_INCLUDED


/// estructuras de valentin y gonzalo
typedef struct{/**Estructura para leer las selecciones que estan en un Archivo**/
    char dato[20];
}Palabras;


typedef struct{
    int dia;
    int mes;
    char Equipo1[40];
    char Equipo2[40];
    char grupo;

}registroFecha;


typedef struct {
       char nomEquipo[40];
       int mp; ///partidos jugados
       int gf;   ///goles a favor
       int ga;  ///goles en contra
       int win;  ///partidos ganados
       int loss;  ///partidos perdidos
       int pts;  ///puntos totales
}Equipo;


typedef struct nodoEquipo{
    Equipo equipo;
    struct nodoEquipo* siguiente;
}nodoEquipo;


typedef struct{
    char letra; ///'A','B'....
    struct nodoGrupoEquipo* equipos; ///siempre va a haber 4
}Grupo;


typedef struct nodoGrupoEquipo{
    Equipo* equipo;
    struct nodoGrupoEquipo* siguiente;
}nodoGrupoEquipo;


typedef struct{
    int dia;
    int mes; ///eligen ustedes el criterio, el tipo tambien
    Equipo* equipo1;
    Equipo* equipo2;
    int golesEq1;
    int golesEq2;
    int penales1; ///en la fase de grupos no hay penales
    int penales2; ///pueden setearlo en 1 y 0 (como un boolean)
}Partido;


typedef struct nodoPartido
{
   Partido partido;
   struct nodoPartido* siguiente;
}nodoPartido;


typedef struct{
   char letra;
   nodoPartido* partidos;
}GrupoPartido;


typedef struct
{
    int id; ///opcional
    int fecha; ///eligen ustedes el criterio, el tipo tambien
    Equipo* equipo1;
    Equipo* equipo2;
    int golesEq1;
    int golesEq2;
    int penales1; ///en la fase de grupos no hay penales
    int penales2; ///pueden setearlo en 1 y 0 (como un boolean)

}PartidoFase;


/// lista partidos
typedef struct nodoPartidoFase
{
   PartidoFase partido;
   struct nodoPartidoFase* siguiente;

}nodoPartidoFase;


/// lista de todos los que clasificaron primero en fase de grupo
typedef struct primeroFaseGrupos
{
    char grupo;
    Equipo* equipo;
    struct primeroFaseGrupos* sig;
}primeroFaseGrupos;


/// lista de todos los que clasificaron segundo en fase grupo
typedef struct segundoFaseGrupos
{
    char grupo;
    Equipo* equipo;
    struct segundoFaseGrupos* sig;
}segundoFaseGrupos;


/// para arreglo de lista de partidos 8tavos,4tos,semi etc...
typedef struct
{
    int idFase;
    nodoPartidoFase* partidos;
}fase;


/// FUNCIONES EQUIPOS Y GRUPOS /// FUNCIONES EQUIPOS Y GRUPOS /// FUNCIONES EQUIPOS Y GRUPOS /// FUNCIONES EQUIPOS Y GRUPOS /// FUNCIONES EQUIPOS Y GRUPOS /// FUNCIONES EQUIPOS Y GRUPOS ///
/// FUNCIONES EQUIPOS Y GRUPOS /// FUNCIONES EQUIPOS Y GRUPOS /// FUNCIONES EQUIPOS Y GRUPOS /// FUNCIONES EQUIPOS Y GRUPOS /// FUNCIONES EQUIPOS Y GRUPOS /// FUNCIONES EQUIPOS Y GRUPOS ///
/// FUNCIONES EQUIPOS Y GRUPOS /// FUNCIONES EQUIPOS Y GRUPOS /// FUNCIONES EQUIPOS Y GRUPOS /// FUNCIONES EQUIPOS Y GRUPOS /// FUNCIONES EQUIPOS Y GRUPOS /// FUNCIONES EQUIPOS Y GRUPOS ///
/// FUNCIONES EQUIPOS Y GRUPOS /// FUNCIONES EQUIPOS Y GRUPOS /// FUNCIONES EQUIPOS Y GRUPOS /// FUNCIONES EQUIPOS Y GRUPOS /// FUNCIONES EQUIPOS Y GRUPOS /// FUNCIONES EQUIPOS Y GRUPOS ///



nodoEquipo* CrearNodoEquipo (Equipo dato);

nodoGrupoEquipo* CrearNodoGrupo (Equipo* Equipo);

void insertarAlFinal(nodoEquipo** Lista, nodoEquipo* nuevo);

void CargarSelecciones (nodoEquipo** Selecciones);

void mostrarunEquipo (Equipo Seleccion);

void MostrarEquipos (nodoEquipo* Selecciones);

void insertarAlFinalGrupos (nodoGrupoEquipo** Grupo,nodoGrupoEquipo* Nuevo);

void CargarGrupos (Grupo* Grupos,int validos, nodoEquipo* Selecciones);

void MostrarGrupos (Grupo FasedeGrupos [],int validos);




/// FUNCIONES PARTIDO Y GRUPOPARTIDO /// FUNCIONES PARTIDO Y GRUPOPARTIDO /// FUNCIONES PARTIDO Y GRUPOPARTIDO /// FUNCIONES PARTIDO Y GRUPOPARTIDO /// FUNCIONES PARTIDO Y GRUPOPARTIDO ///
/// FUNCIONES PARTIDO Y GRUPOPARTIDO /// FUNCIONES PARTIDO Y GRUPOPARTIDO /// FUNCIONES PARTIDO Y GRUPOPARTIDO /// FUNCIONES PARTIDO Y GRUPOPARTIDO /// FUNCIONES PARTIDO Y GRUPOPARTIDO ///
/// FUNCIONES PARTIDO Y GRUPOPARTIDO /// FUNCIONES PARTIDO Y GRUPOPARTIDO /// FUNCIONES PARTIDO Y GRUPOPARTIDO /// FUNCIONES PARTIDO Y GRUPOPARTIDO /// FUNCIONES PARTIDO Y GRUPOPARTIDO ///
/// FUNCIONES PARTIDO Y GRUPOPARTIDO /// FUNCIONES PARTIDO Y GRUPOPARTIDO /// FUNCIONES PARTIDO Y GRUPOPARTIDO /// FUNCIONES PARTIDO Y GRUPOPARTIDO /// FUNCIONES PARTIDO Y GRUPOPARTIDO ///



/// crear nodo partido
nodoPartido* CrearNodoPartido(Partido dato);


/// insertar al final un partido en lista de partidos
void insertarAlFinalPartido(nodoPartido** lista,Partido datoPartido);


/// buscar un grupo en el arreglo
int buscarGrupoEnArregloPartido(GrupoPartido arrPartido[],char grupo,int validos);


/// funcion principal lee archivo carga arreglo
int leerArchivoCargarArreglo(GrupoPartido arrPartido[],int validos,nodoEquipo* listaEquipos,char equipoSeleccionado[]);


/// cargar arreglo de partido crear partidos cargar equipo
int cargarArregloGrupoPartido(GrupoPartido arrPartido[],registroFecha datoReg,int validos,nodoEquipo* listaEquipos,char equipoSeleccionado[]);


/// crear partido cargar resultados en equipos
Partido crearPartido(nodoEquipo* listaEquipos,registroFecha datoReg,char equipoSeleccionado[]);


/// buscar equipo en lista
Equipo* buscarEquipoEnLista(nodoEquipo* listaEquipos,char nombre[]);


/// cargar partido y arreglo
int cargarPartidoYarreglo(GrupoPartido arrPartido[],int validos,Partido datoPartido,char grupo);


void cargarDatosEquipo(int golesAfavor,int golesEncontra,Equipo* seleccion);


void mostrarUnPartido(Partido datoPartido);


void mostrarEquipoRefencia(Equipo* Seleccion);


void mostrarListaPartidos(nodoPartido* lista);


void mostrarArrPartidoGrupo(GrupoPartido arrGrupoPartido[],int validos);




///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///
///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///
///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///
///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///FUNCIONES DE FASES ///






/// buscar 1er lugar en fase de grupos por grupo
Equipo* buscarPrimeroClasificadoEnLista(nodoGrupoEquipo* lista);


/// buscar un segundo clasicado en fase de grupos por grupo
Equipo* buscarSegundoClasificadoEnLista(nodoGrupoEquipo* lista);


/// buscar los clasificados en el arreglo de listas por grupo y posicion de clasificado -> 1 primero - 2 segundo
Equipo* buscarClasificadosEnArregloGrupos(Grupo arrGrupo[],char grupo,int pos);


/// cargar lista de partidos
void cargarListaPartidos(nodoPartidoFase** listaPartido,Grupo arrGrupos[]);


/// insertar partido al final las id que se envian tienen id creciente ordenado
void insertarPartidoAlFinal(nodoPartidoFase** lista,PartidoFase dato);


/// crear nodo partido
nodoPartidoFase* crearNodoPartidoFase(PartidoFase nuevoPartido);


/// cargar lista de partidos octavos de final en arreglo de fases
int cargarListaPartidosEnFaseOctavos(fase arrFase[],int validos,Grupo arrGrupos[]);


/// buscar ganador de partido por id En lista de partidos
Equipo* buscarEquipoGanadorListaPartidos(nodoPartidoFase* lista,int idPartido);


/// buscar ganador de partido por id En lista de partidos
Equipo* buscarPerdedorListaPartido(nodoPartidoFase* lista,int idPartido);


/// cargar fase de cuartos semifinal tercer puesto y final
int cuartosSemiFinalTerceros(fase arrFase[],int validos);


/// retorna cuantos partidos se disputaron en una lista
int cantidadPartidosLista(nodoPartidoFase* lista);


/// crear un partido y retornarlo
PartidoFase crearPartidoFases(Equipo* equipo1,Equipo* equipo2,int id);


/// mostrar un arreglo de fases
void mostrarArrPartidoFase(fase arrPartidofase[],int validos);


/// mostrar lista de partido fases
void mostrarListaPartidoFase(nodoPartidoFase* lista);


/// void mostrar un partido de la fase
void mostrarUnPartidoFase(PartidoFase datoPartido);


/// mostrar fases
void mostrarFases(int fase);


/// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR ///
/// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR ///
/// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR ///
/// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR ///

void color(int background,int text);

void recuadro(int xs,int ys,int xi,int yi);

void recuadroDif33(int xs,int ys,int xi,int yi);

void recuadroDif(int xs,int ys,int xi,int yi);

void gotoxy(int x,int y);

void tituloRecuadro();

void centrarTexto(char texto[],int y);

void lineaHorizontal(int xi,int y,int xf);

void lineaVertical(int x,int ys,int yi);

void aMayus(char palabra[]);

void aMinus(char palabra[]);

void banderaArg(int xs,int ys);


void mostrarArregloGruposGrilla(Grupo arrGrupos[],char equipoSeleccionado[]);


void MostrarEquiposGrilla(nodoGrupoEquipo* listaGrupo,int x,int y,char grupo,char equipoSeleccionado[]);

void mostrarunEquipoParaGrilla(Equipo* equipos,int x,int y,char grupo,char equipoSeleccionado[]);

void mostrarArrGrupoPartidosRecuadro(GrupoPartido arrGrupoPartido[],char equipoSeleccionado[]);

void mostrarListaPartidosGrupoRecuadro(nodoPartido* lista,int x,int y,int col,char letra,char equipoSeleccionado[]);

void mostrarUnPartidoGrupoRecuadro(Partido datoPartido,int x,int y,int col,char equipoSeleccionado[]);

void mostrarArgentinaCampeon(char equipo1[],char equipo2[],char equipo3[]);

void mostrarArrPartidoFaseArbol(fase arrPartidoFase[],char equipoSeleccionado[]);

void mostrarListaPartidoFaseArbol(nodoPartidoFase* lista,int x,int y,int color,char equipoSeleccionado[]);

void mostrarUnPartidoFaseArbol(PartidoFase datoPartido,int x,int y,int col,char equipoSeleccionado[]);


/// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES ///
/// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES ///
/// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES ///
/// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES ///



void verificarEquipoSeleccionado(char nombre[],nodoEquipo* equipos);


/// modificar un registro
registroFecha modificarEstructura(registroFecha dato);


/// buscar dato en archivo y modificarlo
void modificarRegistro(int posRegistro);


int cantidadDatosArchivo();


void mostrarDatoReg(registroFecha dato);



#endif // FIXTURE_H_INCLUDED
