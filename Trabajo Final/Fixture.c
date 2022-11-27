#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include "Fixture.h"


/// FUNCIONES DE EQUIPO Y GRUPOS /// FUNCIONES DE EQUIPO Y GRUPOS /// FUNCIONES DE EQUIPO Y GRUPOS /// FUNCIONES DE EQUIPO Y GRUPOS /// FUNCIONES DE EQUIPO Y GRUPOS /// FUNCIONES DE EQUIPO Y GRUPOS ///
/// FUNCIONES DE EQUIPO Y GRUPOS /// FUNCIONES DE EQUIPO Y GRUPOS /// FUNCIONES DE EQUIPO Y GRUPOS /// FUNCIONES DE EQUIPO Y GRUPOS /// FUNCIONES DE EQUIPO Y GRUPOS /// FUNCIONES DE EQUIPO Y GRUPOS ///
/// FUNCIONES DE EQUIPO Y GRUPOS /// FUNCIONES DE EQUIPO Y GRUPOS /// FUNCIONES DE EQUIPO Y GRUPOS /// FUNCIONES DE EQUIPO Y GRUPOS /// FUNCIONES DE EQUIPO Y GRUPOS /// FUNCIONES DE EQUIPO Y GRUPOS ///
/// FUNCIONES DE EQUIPO Y GRUPOS /// FUNCIONES DE EQUIPO Y GRUPOS /// FUNCIONES DE EQUIPO Y GRUPOS /// FUNCIONES DE EQUIPO Y GRUPOS /// FUNCIONES DE EQUIPO Y GRUPOS /// FUNCIONES DE EQUIPO Y GRUPOS ///

nodoEquipo* CrearNodoEquipo (Equipo dato)/**Creacion de una seleccion con 0 stacs**/
{
    nodoEquipo* nuevo=(nodoEquipo*)malloc(sizeof(nodoEquipo));
    nuevo->siguiente=NULL;
    nuevo->equipo=dato;
    nuevo->equipo.ga=0;
    nuevo->equipo.gf=0;
    nuevo->equipo.loss=0;
    nuevo->equipo.mp=0;
    nuevo->equipo.pts=0;
    nuevo->equipo.win=0;
    return nuevo;
}

nodoGrupoEquipo* CrearNodoGrupo (Equipo* Equipo)/**Creacion de un lugar del grupo**/
{
    nodoGrupoEquipo* nuevo=(nodoGrupoEquipo*)malloc(sizeof(nodoGrupoEquipo));
    nuevo->equipo=Equipo;
    nuevo->siguiente=NULL;

    return nuevo;
}

void insertarAlFinal(nodoEquipo** Lista, nodoEquipo* nuevo)
{
    nodoEquipo* seg=(*Lista);
    if (*Lista!=NULL)
    {
        while(seg->siguiente!=NULL)
        {
            seg=seg->siguiente;
        }
        seg->siguiente=nuevo;
    }
    else
    {
        (*Lista)=nuevo;
    }
}

void CargarSelecciones (nodoEquipo** Selecciones)/**Funcion que carga la lista de selecciones desde un Archivo con todos los nombres de las mismas**/
{
    FILE* buff;
    Palabras A;
    Equipo X;
    buff=fopen("Selecciones del mundial.bin","rb");

    if (buff!=NULL)
    {
        while(fread(&A,sizeof(Palabras),1,buff)>0)
        {
            fflush(stdin);
            strcpy(X.nomEquipo,A.dato);
            insertarAlFinal(Selecciones,CrearNodoEquipo(X));
        }
    }
    fclose(buff);
}

void mostrarunEquipo (Equipo Seleccion)///Funcion que muestra las estadisticas de un Equipo
{
    printf("\n----------%s----------\n",Seleccion.nomEquipo);
    printf("\n|Puntos: %i            |",Seleccion.pts);
    printf("\n|Partidos Jugados: %i  |",Seleccion.mp);
    printf("\n|Goles a favor: %i     |",Seleccion.gf);
    printf("\n|Goles en contra: %i   |",Seleccion.ga);
    printf("\n|Partidos ganados: %i  |",Seleccion.win);
    printf("\n|Partidos perdidos: %i |",Seleccion.loss);
    printf("\n--------------------\n");
}

void MostrarEquipos (nodoEquipo* Selecciones)///Funcion que muestra todos los equipos y sus estadisticas
{
    while (Selecciones!=NULL)
    {
        mostrarunEquipo(Selecciones->equipo);
        Selecciones=Selecciones->siguiente;
    }
}



void insertarAlFinalGrupos (nodoGrupoEquipo** Grupo,nodoGrupoEquipo* Nuevo)
{
    nodoGrupoEquipo*seg=(*Grupo);
    if (seg!=NULL)
    {
        while(seg->siguiente!=NULL)
        {
            seg=seg->siguiente;
        }
        seg->siguiente=Nuevo;
    }
    else
    {
        (*Grupo)=Nuevo;
    }
}

void CargarGrupos (Grupo* Grupos ,int validos, nodoEquipo* Selecciones)
{
    int n=0, contador=0;
    char Letra='A';
    nodoGrupoEquipo* Lista=NULL;


    while(validos>n)
    {
        Grupos[n].letra=Letra;
        Letra++;

        contador=0;
        Lista=NULL;
        while (contador<4)
        {
           insertarAlFinalGrupos(&Lista,CrearNodoGrupo(&Selecciones->equipo));
           Selecciones=Selecciones->siguiente;
           contador++;
        }
        Grupos[n].equipos=Lista;
        n++;
    }
}

void MostrarunGrupo (nodoGrupoEquipo* Lista)
{
    while (Lista!=NULL)
    {
      mostrarunEquipo(*Lista->equipo);
      Lista=Lista->siguiente;
    }

}

void MostrarGrupos(Grupo FasedeGrupos[], int validos)
{
    int i=0;
    while (validos>i)
    {
        printf("\n--------------------------------------------Grupo %c--------------------------------------------\n",FasedeGrupos[i].letra);
        MostrarunGrupo(FasedeGrupos[i].equipos);
        i++;
        system("pause");
    }
}


/// FUNCIONES DE PARTIDOS Y GRUPO.PARTIDOS /// FUNCIONES DE PARTIDOS Y GRUPO.PARTIDOS /// FUNCIONES DE PARTIDOS Y GRUPO.PARTIDOS /// FUNCIONES DE PARTIDOS Y GRUPO.PARTIDOS /// FUNCIONES DE PARTIDOS Y GRUPO.PARTIDOS ///
/// FUNCIONES DE PARTIDOS Y GRUPO.PARTIDOS /// FUNCIONES DE PARTIDOS Y GRUPO.PARTIDOS /// FUNCIONES DE PARTIDOS Y GRUPO.PARTIDOS /// FUNCIONES DE PARTIDOS Y GRUPO.PARTIDOS /// FUNCIONES DE PARTIDOS Y GRUPO.PARTIDOS ///
/// FUNCIONES DE PARTIDOS Y GRUPO.PARTIDOS /// FUNCIONES DE PARTIDOS Y GRUPO.PARTIDOS /// FUNCIONES DE PARTIDOS Y GRUPO.PARTIDOS /// FUNCIONES DE PARTIDOS Y GRUPO.PARTIDOS /// FUNCIONES DE PARTIDOS Y GRUPO.PARTIDOS ///
/// FUNCIONES DE PARTIDOS Y GRUPO.PARTIDOS /// FUNCIONES DE PARTIDOS Y GRUPO.PARTIDOS /// FUNCIONES DE PARTIDOS Y GRUPO.PARTIDOS /// FUNCIONES DE PARTIDOS Y GRUPO.PARTIDOS /// FUNCIONES DE PARTIDOS Y GRUPO.PARTIDOS ///




/// funcion principal lee archivo carga arreglo
int leerArchivoCargarArreglo(GrupoPartido arrPartido[],int validos,nodoEquipo* listaEquipos,char equipoSeleccionado[])
{
    FILE* arch=fopen("fechas.dat","rb");
    registroFecha datoReg;

    if(arch)
    {
        while((fread(&datoReg,sizeof(datoReg),1,arch))>0)
        {
            //printf("\n %s \t %s  -> grupo %c\n\n",datoReg.Equipo1,datoReg.Equipo2,datoReg.grupo);

            validos=cargarArregloGrupoPartido(arrPartido,datoReg,validos,listaEquipos,equipoSeleccionado);


        }

        fclose(arch);
    }

    return validos;
}

/// cargar arreglo de partido crear partidos cargar equipo
int cargarArregloGrupoPartido(GrupoPartido arrPartido[],registroFecha datoReg,int validos,nodoEquipo* listaEquipos,char equipoSeleccionado[])
{

    int indice=buscarGrupoEnArregloPartido(arrPartido,datoReg.grupo,validos);

    Partido nuevoPartido=crearPartido(listaEquipos,datoReg,equipoSeleccionado);


    if(indice!=-1)
    {

        insertarAlFinalPartido(&arrPartido[indice].partidos,nuevoPartido);
    }
    else
    {

        validos=cargarPartidoYarreglo(arrPartido,validos,nuevoPartido,datoReg.grupo);
    }

    return validos;
}

/// crear partido cargar resultados en equipos
Partido crearPartido(nodoEquipo* listaEquipos,registroFecha datoReg,char equipoSeleccionado[])
{

    int goles1=rand()%5;
    int goles2=rand()%5;
    Partido nuevo;
    nuevo.equipo1=buscarEquipoEnLista(listaEquipos,datoReg.Equipo1);
    nuevo.equipo2=buscarEquipoEnLista(listaEquipos,datoReg.Equipo2);


    if(equipoSeleccionado[0]!='\0' && strcmpi((*nuevo.equipo1).nomEquipo,equipoSeleccionado)==0)
    {

        while(goles1<goles2)
        {
            goles1=rand()%5+1;goles2=rand()%4;
        }

    }
    else if( equipoSeleccionado[0]!='\0' && strcmpi((*nuevo.equipo2).nomEquipo,equipoSeleccionado)==0 && equipoSeleccionado!='\0')
    {

        while(goles2<goles1)
        {
            goles2=rand()%5+1;goles1=rand()%4;
        }
    }

    nuevo.dia=datoReg.dia;
    nuevo.mes=datoReg.mes;
    nuevo.golesEq1=goles1;
    nuevo.golesEq2=goles2;
    nuevo.penales1=0;
    nuevo.penales2=0;

    cargarDatosEquipo(goles1,goles2,nuevo.equipo1);
    cargarDatosEquipo(goles2,goles1,nuevo.equipo2);

    return nuevo;
}

void cargarDatosEquipo(int golesAfavor,int golesEncontra,Equipo* seleccion)
{
   (*seleccion).gf+=golesAfavor;
   (*seleccion).ga+=golesEncontra;
   (*seleccion).mp+=1;

   if(golesAfavor > golesEncontra)
   {
        (*seleccion).win+=1;
        (*seleccion).pts+=3;
   }
   else if(golesAfavor < golesEncontra)
   {

       (*seleccion).loss+=1;
   }
   else if(golesAfavor==golesEncontra)
   {

       (*seleccion).pts+=1;
   }
}

/// buscar equipo en lista
Equipo* buscarEquipoEnLista(nodoEquipo* listaEquipos,char nombre[])
{
    Equipo* buscado=NULL;
    while(listaEquipos)
    {
        if(strcmpi(listaEquipos->equipo.nomEquipo,nombre)==0)
        {

            buscado= &(listaEquipos->equipo);
        }

        listaEquipos=listaEquipos->siguiente;
    }

    return buscado;
}

/// cargar partido y arreglo
int cargarPartidoYarreglo(GrupoPartido arrPartido[],int validos,Partido datoPartido,char grupo)
{

    int i=validos-1;

    while(i>=0 && arrPartido[i].letra > grupo)
    {
        arrPartido[i+1]=arrPartido[i];
        i--;
    }

    arrPartido[i+1].partidos=NULL;
    arrPartido[i+1].letra=grupo;
    insertarAlFinalPartido(&(arrPartido[i+1]).partidos,datoPartido);

    validos++;


    return validos;
}



/// buscar un grupo en el arreglo
int buscarGrupoEnArregloPartido(GrupoPartido arrPartido[],char grupo,int validos)
{
    int i=0,flag=0,pos=-1;
    while(i<validos && flag!=1)
    {

        if(arrPartido[i].letra==grupo)
        {
            pos=i;
            flag=1;
        }
        i++;
    }


    return pos;
}

nodoPartido* CrearNodoPartido(Partido dato)
{
    nodoPartido*nuevo=(nodoPartido*)malloc(sizeof(nodoPartido));
    nuevo->partido=dato;
    nuevo->siguiente=NULL;

    return nuevo;
}


void insertarAlFinalPartido(nodoPartido** lista,Partido datoPartido)
{
    nodoPartido* nuevo=CrearNodoPartido(datoPartido);

    nodoPartido* seg;
    if ((*lista) == NULL)
   {

            (*lista) = nuevo;

   }
    else
   {
        seg = (*lista);
        while (seg->siguiente != NULL)
        {
            seg=seg->siguiente;
        }
            seg->siguiente=nuevo;
    }
}

void mostrarArrPartidoGrupo(GrupoPartido arrGrupoPartido[],int validos)
{
    int i=0;

    while(i<validos)
    {
        mostrarListaPartidos(arrGrupoPartido[i].partidos);
        i++;
    }
}

/// mostrar un partido
void mostrarUnPartido(Partido datoPartido)
{
    printf("\nFECHA PARTIDO : \t%i/%i\n\n",datoPartido.dia,datoPartido.mes);

    printf("\n\t**%s**\t\n",(*datoPartido.equipo1).nomEquipo);
    printf("\nGoles equ1:\t%i\n",datoPartido.golesEq1);
    printf("\nPenales:\t%i\n",datoPartido.penales1);
   printf("\n\t**%s**\t\n",(*datoPartido.equipo2).nomEquipo);
    printf("\nGoles equ2:\t%i\n",datoPartido.golesEq2);
    printf("\nPenales equ2\t%i\n\n",datoPartido.penales2);
    printf("\nINFORMACION EQUIPOS\n\n");
    mostrarEquipoRefencia(datoPartido.equipo1);
    mostrarEquipoRefencia(datoPartido.equipo2);

    printf("\n-------------------------------------------------\n");
}

void mostrarEquipoRefencia(Equipo* Seleccion)
{
    printf("\t\t");puts((*Seleccion).nomEquipo);
    printf("\n\t\tPuntos: %i",(*Seleccion).pts);
    printf("\n\t\tPartidos Jugados: %i",(*Seleccion).mp);
    printf("\n\t\tGoles a favor: %i",(*Seleccion).gf);
    printf("\n\t\tGoles en contra: %i",(*Seleccion).ga);
    printf("\n\t\tPartidos ganados: %i",(*Seleccion).win);
    printf("\n\t\tPartidos perdidos: %i",(*Seleccion).loss);
    printf("\n\t\t--------------------\n");
}

void mostrarListaPartidos(nodoPartido* lista)
{
    while(lista)
    {
        mostrarUnPartido(lista->partido);

        lista=lista->siguiente;
    }
}







/// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES ///
/// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES ///
/// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES ///
/// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES /// FUNCIONES DE FASES ///




/// buscar 1er lugar en fase lista de equipos
Equipo* buscarPrimeroClasificadoEnLista(nodoGrupoEquipo* lista)
{
    Equipo* primero=lista->equipo;/// equipo que se clasifica como 1ero del grupo/// equipo que se clasifica como 1ero del grupo
    lista=lista->siguiente;/// se comprará con el siguiente

    while(lista)
    {
        if((*lista->equipo).pts > (*primero).pts )
        {

            primero=lista->equipo;

        }
        else if((*lista->equipo).pts == (*primero).pts)
        {

            if( ( ((*lista->equipo).gf ) - ((*lista->equipo).ga) ) > (( (*primero).gf) - ((*primero).ga)) )
            {

                primero=lista->equipo;

            }
            else if( ((*lista->equipo).gf - (*lista->equipo).ga ) == ( ((*primero).gf) - ((*primero).ga)) )
            {

                if((*lista->equipo).gf > (*primero).gf)
                {

                    primero=lista->equipo;

                }
            }
        }

        lista=lista->siguiente;
    }
    return primero;
}

/// buscar un segundo clasicado en lista de equipos
Equipo* buscarSegundoClasificadoEnLista(nodoGrupoEquipo* lista)
{
    Equipo* primero=buscarPrimeroClasificadoEnLista(lista);

    if(strcmpi((*lista->equipo).nomEquipo,(*primero).nomEquipo)==0)
    {
        lista=lista->siguiente;
    }

    Equipo* segundo=lista->equipo;

    lista=lista->siguiente;

    while(lista)
    {
        /// valida que no estemos a punto de comparar el segundo lugar con el que esta primero
        if(strcmpi((*lista->equipo).nomEquipo,(*primero).nomEquipo)!=0 )
        {

            /// comienzo evaluacion de puntajes para determinar el segundo equipo con mas puntos que clasifica

            ///evaluacion por puntos
            if((*lista->equipo).pts > (*segundo).pts )
            {

                segundo=lista->equipo;

            }
            else if((*lista->equipo).pts == (*segundo).pts) /// si tienen mismo puntaje
            {

                if( ( ((*lista->equipo).gf ) - ((*lista->equipo).ga) ) > (( (*segundo).gf) - ((*segundo).ga)) )/// define por diferencia de goles
                {

                    segundo=lista->equipo;

                }
                else if( ((*lista->equipo).gf - (*lista->equipo).ga ) == ( ((*segundo).gf) - ((*segundo).ga)) ) /// si tienen misma goal diference
                {

                    if((*lista->equipo).gf > (*segundo).gf)/// define por el que realizo mas goles
                    {

                        segundo=lista->equipo;

                    }
                }
            }
        }

        /// avanzamos hacia el equipo siguiente para seguir comparando
        lista=lista->siguiente;
    }

    /// retornamos la direccion del segundo mejor equipo que clasifica a octavos
    return segundo;
}


/// buscar los clasificados en el arreglo de listas por grupo y posicion de clasificado -> 1 primero - 2 segundo
Equipo* buscarClasificadosEnArregloGrupos(Grupo arrGrupo[],char grupo,int pos)
{
    Equipo* equipoBuscado;
    //printf("\nbuscar clasificado en arreglo  %c   %i\n",grupo,pos);
    int i=0;

    while(i<8)
    {
        if(arrGrupo[i].letra == grupo)
        {
            if(pos==1)
            {
                equipoBuscado=buscarPrimeroClasificadoEnLista(arrGrupo[i].equipos);
            }
            else if(pos==2)
            {
                equipoBuscado=buscarSegundoClasificadoEnLista(arrGrupo[i].equipos);
            }
        }

        i++;
    }

    return equipoBuscado;
}

/// crear un partido y retornarlo
PartidoFase crearPartidoFases(Equipo* equipo1,Equipo* equipo2,int id)
{

    int goles1=rand()%5;
    int goles2=rand()%5;
    PartidoFase datoPartido;
    datoPartido.id=id;
    datoPartido.equipo1=equipo1;
    datoPartido.equipo2=equipo2;

    ///Pequeña ayuda a argentina
    if(strcmpi((*datoPartido.equipo1).nomEquipo,"Argentina")==0)
    {goles1=(rand()%5)+1;}
    else if(strcmpi((*datoPartido.equipo2).nomEquipo,"Argentina")==0)
    {goles2=(rand()%5)-1;}

    datoPartido.golesEq1=goles1;
    datoPartido.golesEq2=goles2;
    int penales1=0,penales2=0;


    if(goles1==goles2)
    {
        while(penales1==penales2 || (penales1<3 || penales2<3))
        {
            penales1=rand()%6;
            penales2=rand()%6;
        }
    }

    datoPartido.penales1=penales1;
    datoPartido.penales2=penales2;




    return datoPartido;
}

/// cargar lista de partidos octavos de final en arreglo de fases
int cargarListaPartidosEnFaseOctavos(fase arrFase[],int validos,Grupo arrGrupos[])
{
    arrFase[validos].idFase=0;
    arrFase[validos].partidos=NULL;

    Equipo* equipo1;    Equipo* equipo2;
    PartidoFase nuevoPartido;
    char letra='A';     int idPartido=1;/// id partido no se vuelve a inicializar continua hasta cargar todos los partidos

    while(letra<='H')
    {

        equipo1=buscarClasificadosEnArregloGrupos(arrGrupos,letra,1); /// 1 o 2 representa el puesto que vamos a buscar
        equipo2=buscarClasificadosEnArregloGrupos(arrGrupos,letra+1,2);

        nuevoPartido=crearPartidoFases(equipo1,equipo2,idPartido);

        insertarPartidoAlFinal((&arrFase[validos].partidos),nuevoPartido);

        letra+=2; /// tomamos grupo A y B luego +2 indicamos C y D etc...
        idPartido++;

    }



    letra='A';/// la letra del grupo se inicializa para buscar el orden contrario de A el 2 de B 1 etc..
    while(letra<='H')
    {
        equipo1=buscarClasificadosEnArregloGrupos(arrGrupos,letra+1,1);
        equipo2=buscarClasificadosEnArregloGrupos(arrGrupos,letra,2);

        nuevoPartido=crearPartidoFases(equipo1,equipo2,idPartido);

        insertarPartidoAlFinal((&arrFase[validos].partidos),nuevoPartido);

        letra+=2;
        idPartido++;
    }

    validos++;

    return validos;
}

/// buscar ganador de partido por id En lista de partidos
Equipo* buscarEquipoGanadorListaPartidos(nodoPartidoFase* lista,int idPartido)
{
    Equipo* clasificado;
    while(lista)
    {
        if(lista->partido.id==idPartido)
        {
            if(lista->partido.golesEq1 > lista->partido.golesEq2)
            {
                clasificado=lista->partido.equipo1;
            }
            else if(lista->partido.golesEq1 < lista->partido.golesEq2)
            {
                clasificado=lista->partido.equipo2;
            }
            else
            {
                if(lista->partido.penales1 > lista->partido.penales2)
                {
                    clasificado=lista->partido.equipo1;
                }
                else
                {
                    clasificado=lista->partido.equipo2;
                }
            }
        }
        lista=lista->siguiente;
    }
    return clasificado;
}

/// buscar ganador de partido por id En lista de partidos
Equipo* buscarPerdedorListaPartido(nodoPartidoFase* lista,int idPartido)
{
    Equipo* clasificado=buscarEquipoGanadorListaPartidos(lista,idPartido);
    Equipo* perdedor;

    while(lista)
    {
        if(lista->partido.id==idPartido)
        {
            if(strcmpi((*lista->partido.equipo1).nomEquipo,(*clasificado).nomEquipo)==0)
            {
                perdedor=lista->partido.equipo2;
            }
            else
            {
                perdedor=lista->partido.equipo1;
            }
        }

        lista=lista->siguiente;
    }

    return perdedor;
}

/// cargar fase de cuartos semifinal tercer puesto y final
int cuartosSemiFinalTerceros(fase arrFase[],int validos)
{
    Equipo* ganador1; Equipo* ganador2;
    PartidoFase nuevoPartido;
    int i=0,cantPartidos=0;

    while(i<3)
    {
        cantPartidos=cantidadPartidosLista(arrFase[i].partidos);/// la cantidad de partido nos sirve para cargar los partidos necesarios ya que en las fases posteriores el valor disminuye y solo tendemos un while disponible

        arrFase[validos].idFase=validos;
        arrFase[validos].partidos=NULL;

        int idPartido=1; ///en cada carga del arreglo inicializamos para que la nueva lista de partidos tenga su id de partidos del 1 en adelante
        int idParJugado=1;///id partido jugado lo usaremos para la funcion de buscar ganador de un cierto partido con esta id

        while(idParJugado<=cantPartidos)/// 8 4 2 1 1
        {

            if(i==2) /// cuando llegue el turno de los terceros antes de cargar la ultima fase la de final
            {

                while(idParJugado<=cantPartidos) /// la cantidad de partidos en la fase de terceros como final son solo 1
                {
                    ganador1=buscarPerdedorListaPartido(arrFase[i].partidos,idParJugado);
                    ganador2=buscarPerdedorListaPartido(arrFase[i].partidos,idParJugado+1);

                    nuevoPartido=crearPartidoFases(ganador1,ganador2,idPartido);
                    insertarPartidoAlFinal((&arrFase[i+1].partidos),nuevoPartido);
                    idParJugado+=2; /// si bien no cargaremos mas partidos en esta fase necesitamos aumentar para finalizar bucle
                }
                idPartido=1;/*en la siguiente fase */  idParJugado=1;     validos++; /// al haber cargado una fase mas tenemos otro valido en el arreglo
                arrFase[validos].idFase=validos;
                arrFase[validos].partidos=NULL;
            }

            ganador1=buscarEquipoGanadorListaPartidos(arrFase[i].partidos,idParJugado);
            ganador2=buscarEquipoGanadorListaPartidos(arrFase[i].partidos,idParJugado+1);

            nuevoPartido=crearPartidoFases(ganador1,ganador2,idPartido);

            insertarPartidoAlFinal((&arrFase[validos].partidos),nuevoPartido);/// validos al ser un numero mas que el indice nos sirve para indicar en que posision cargaremos la proxima lista de partidos

            idPartido++; idParJugado+=2; /// se suman dos numeros a idPartido jugado porque en cada vuelta tomamos un equipo de dos partidos jugados para enfrentarlos entre si
        }

        i++;    validos++;
    }

    return validos;
}

/// retorna cuantos partidos se disputaron en una lista
int cantidadPartidosLista(nodoPartidoFase* lista)
{
    int cant=0;
    while(lista)
    {
        cant++;
        lista=lista->siguiente;
    }
    return cant;
}

/// insertar partido al final las id que se envian tienen id creciente ordenado
void insertarPartidoAlFinal(nodoPartidoFase** lista,PartidoFase dato)
{
    nodoPartidoFase* nuevo=crearNodoPartidoFase(dato);
    nodoPartidoFase* seg=NULL;

    if (!(*lista))
    {
        (*lista)=nuevo;
    }
    else
    {
        seg=(*lista);
        while (seg->siguiente)
        {
            seg=seg->siguiente;
        }

        seg->siguiente=nuevo;
    }
}

nodoPartidoFase* crearNodoPartidoFase(PartidoFase nuevoPartido)
{
    nodoPartidoFase* nuevo=(nodoPartidoFase*)malloc(sizeof(nodoPartidoFase));
    nuevo->partido=nuevoPartido;
    nuevo->siguiente=NULL;

    return nuevo;
}




/// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR ///
/// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR ///}
/// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR ///
/// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR /// FUNCIONES PARA MOSTRAR ///

void color(int background,int text)
{
    /// consola es de tipo handle
    HANDLE console= GetStdHandle(STD_OUTPUT_HANDLE); /// tomamos la consola
    int New_Color= text+(background*16);
    SetConsoleTextAttribute(console,New_Color);
}


void recuadro(int xs,int ys,int xi,int yi)
{
    int i;

    for(i=xs;i<=xi;i++)
    {
        gotoxy(i,ys); printf("%c",196);
        gotoxy(i,yi); printf("%c",196);
    }

    for(i=ys;i<=yi;i++)
    {
       gotoxy(xs,i); printf("%c",179);
       gotoxy(xi,i); printf("%c",179);
    }

    gotoxy(xs,ys); printf("%c",218);
    gotoxy(xi,yi); printf("%c",217);
    gotoxy(xs,yi); printf("%c",192);
    gotoxy(xi,ys); printf("%c",191);

}


/// tenemos 4 coordenadas que dos columnas y dos filas las cuales se interceptan
void recuadroDif33(int xs,int ys,int xi,int yi)
{
    int i;

    for(i=xs;i<=xi;i++)
    {
        gotoxy(i,ys); printf("%c",223);
        gotoxy(i,yi); printf("%c",219);
    }

    for(i=ys;i<=yi;i++)
    {
       gotoxy(xs,i); printf("%c",177);
       gotoxy(xi,i); printf("%c",177);
    }

}


void recuadroDif(int xs,int ys,int xi,int yi)
{
    int i;

    for(i=xs;i<=xi;i++)
    {
        gotoxy(i,ys); printf("%c",176);
        gotoxy(i,yi); printf("%c",176);
    }

    for(i=ys;i<=yi;i++)
    {
       gotoxy(xs,i); printf("%c",176);
       gotoxy(xi,i); printf("%c",176);
    }

}


/// x col linea horizontal **  y filas linea vertical
void gotoxy(int x,int y)
{
    HANDLE console;
    console = GetStdHandle(STD_OUTPUT_HANDLE); /// tomamos la consola std output handle
    COORD dwPos; /// coord es una estructura
    dwPos.X=x;
    dwPos.Y=y;

    SetConsoleCursorPosition(console,dwPos);
}


void tituloRecuadro()
{
    int negro=0,azul=1,verde=2,aquaM=3,rojo=4,purpura=5,amarillo=6,grisClaro=7,gris=8,azulClaro=9,verClaro=10,aquClaro=11,rojoClaro=12,magenta=13,amarilloClaro=14,blanco=15;
    color(negro,gris);recuadro(0,0,171,59);

    color(rojo,blanco);centrarTexto(" F I X T U R E  M U N D I A L   Q A T A R   2 0 2 2 ",1);
    color(negro,blanco);
}

void centrarTexto(char texto[],int y)
{
    const int anchoConsola=172;
    const int altoConsola=59;
    int longitud= strlen(texto);

    gotoxy((anchoConsola/2)-(longitud/2),y);puts(texto);
}

/// linea horizontal
void lineaHorizontal(int xi,int y,int xf)
{
    int i;
    for(i=xi;i<xf;i++)
    {
        gotoxy(i,y);printf("%c",249);
    }
}

void lineaVertical(int x,int ys,int yi)
{
    int i;
    for(i=ys;i<yi;i++)
    {
        gotoxy(x,i);printf("%c",179);
    }
}

void aMayus(char palabra[])
{
    for (int i = 0; palabra[i] != '\0'; i++){
		palabra[i] = toupper(palabra[i]);
	}
}


void aMinus(char palabra[])
{
    for (int i = 0; palabra[i] != '\0'; i++){
		palabra[i] = tolower(palabra[i]);
	}
}


/// bandera argentina      banderaArg(10,3,20,7);
void banderaArg(int xs,int ys)
{
    int negro=0,azul=1,verde=2,aquaM=3,rojo=4,purpura=5,amarillo=6,grisClaro=7,gris=8,azulClaro=9,verClaro=10,aquClaro=11,rojoClaro=12,magenta=13,amarilloClaro=14,blanco=15;
    int i;

    for(i=xs;i<=(xs+10);i++)
    {
        gotoxy(i,ys);color(negro,azulClaro);printf("%c",219);
        gotoxy(i,ys+1);color(negro,blanco); printf("%c",219);
        gotoxy(i,ys+2);color(negro,azulClaro); printf("%c",219);
        color(negro,blanco);
    }

}


void mostrarArregloGruposGrilla(Grupo arrGrupos[],char equipoSeleccionado[])
{

    int negro=0,azul=1,verde=2,aquaM=3,rojo=4,purpura=5,amarillo=6,grisClaro=7,gris=8,azulClaro=9,verClaro=10,aquClaro=11,rojoClaro=12,magenta=13,amarilloClaro=14,blanco=15;
    tituloRecuadro();
    color(negro,rojo);recuadroDif33(29,6,140,50);
    color(negro,blanco);gotoxy(32,8);printf(" EQUIPO                GRUPO        PTS       GOL FAVOR     GOL CONTRA     WIN    LOSS      MATCH PLAYED");
    color(negro,rojoClaro);gotoxy(32,9);printf("----------------------------------------------------------------------------------------------------------");color(negro,blanco);
    int x=32,y=10,i=0;
    while(i<8)
    {

        MostrarEquiposGrilla(arrGrupos[i].equipos,x,y,arrGrupos[i].letra,equipoSeleccionado);
        i++;
        //color(negro,rojo);gotoxy(x,y+=4);printf("----------------------------------------------------------------------------------------------------------");color(negro,blanco);
        if(y<45)
        {
          color(negro,gris);gotoxy(x,y+4);printf("----------------------------------------------------------------------------------------------------------");color(negro,blanco);
        }

        y+=5;

    }
    printf("\n\n\n");
}

void MostrarEquiposGrilla(nodoGrupoEquipo* listaGrupo,int x,int y,char grupo,char equipoSeleccionado[])///Funcion que muestra todos los equipos y sus estadisticas
{

    while (listaGrupo!=NULL)
    {
        mostrarunEquipoParaGrilla(listaGrupo->equipo,x,y,grupo,equipoSeleccionado);
        listaGrupo=listaGrupo->siguiente;

        y++;
    }
}

void mostrarunEquipoParaGrilla(Equipo* equipos,int x,int y,char grupo,char equipoSeleccionado[])///Funcion que muestra las estadisticas de un Equipo
{
    int negro=0,azul=1,verde=2,aquaM=3,rojo=4,purpura=5,amarillo=6,grisClaro=7,gris=8,azulClaro=9,verClaro=10,aquClaro=11,rojoClaro=12,magenta=13,amarilloClaro=14,blanco=15;

    if( equipoSeleccionado[0]!='\0' && strcmpi((*equipos).nomEquipo,equipoSeleccionado)==0)
    {
        color(rojo,amarillo);gotoxy(x,y);puts((*equipos).nomEquipo);color(negro,blanco);
    }else
    {
        gotoxy(x,y);puts((*equipos).nomEquipo);
    }

    gotoxy(x+25,y);printf("%c",grupo);
    gotoxy(x+36,y);printf("%i",(*equipos).pts);
    gotoxy(x+50,y);printf("%i",(*equipos).gf);
    gotoxy(x+64,y);printf("%i",(*equipos).ga);
    gotoxy(x+76,y);printf("%i",(*equipos).win);
    gotoxy(x+83,y);printf("%i",(*equipos).loss);
    gotoxy(x+97,y);printf("%i",(*equipos).mp);

}



void mostrarArrGrupoPartidosRecuadro(GrupoPartido arrGrupoPartido[],char equipoSeleccionado[])
{
    int negro=0,azul=1,verde=2,aquaM=3,rojo=4,purpura=5,amarillo=6,grisClaro=7,gris=8,azulClaro=9,verClaro=10,aquClaro=11,rojoClaro=12,magenta=13,amarilloClaro=14,blanco=15;
    tituloRecuadro();
    int i=0;
    int x=3,y=8;
    while(i<8)
    {
        if(i<4)
        {
            mostrarListaPartidosGrupoRecuadro(arrGrupoPartido[i].partidos,x,y,rojo,arrGrupoPartido[i].letra,equipoSeleccionado);
            x+=42;

            if(i==3){system("pause");system("cls");x=3;tituloRecuadro();}///reinicia para la segunda vuelta de grupos
        }
        else if(i<8)
        {

            mostrarListaPartidosGrupoRecuadro(arrGrupoPartido[i].partidos,x,y,azulClaro,arrGrupoPartido[i].letra,equipoSeleccionado);
            x+=42;
        }
        i++;
    }
}



void mostrarListaPartidosGrupoRecuadro(nodoPartido* lista,int x,int y,int col,char letra,char equipoSeleccionado[])
{
    int negro=0,azul=1,verde=2,aquaM=3,rojo=4,purpura=5,amarillo=6,grisClaro=7,gris=8,azulClaro=9,verClaro=10,aquClaro=11,rojoClaro=12,magenta=13,amarilloClaro=14,blanco=15;
    Sleep(300);
    color(negro,col);recuadroDif(x-1,y-2,x+41,y+42);color(negro,blanco);
    gotoxy(x+6,y-4);printf("G R U P O  %c",letra);
    while(lista)
    {
        mostrarUnPartidoGrupoRecuadro(lista->partido,x,y,col,equipoSeleccionado);
        printf("\n\n\n\n\n\n\n");
        lista=lista->siguiente;
        y+=7;

    }
}

void mostrarUnPartidoGrupoRecuadro(Partido datoPartido,int x,int y,int col,char equipoSeleccionado[])
{

    int negro=0,azul=1,verde=2,aquaM=3,rojo=4,purpura=5,amarillo=6,grisClaro=7,gris=8,azulClaro=9,verClaro=10,aquClaro=11,rojoClaro=12,magenta=13,amarilloClaro=14,blanco=15;

    if( equipoSeleccionado[0]!='\0' && strcmpi((*datoPartido.equipo1).nomEquipo,equipoSeleccionado)==0)
    {
        color(rojo,amarillo);gotoxy(x+2,y+1);puts((*datoPartido.equipo1).nomEquipo);color(negro,blanco);
        gotoxy(x+23,y+1);puts((*datoPartido.equipo2).nomEquipo);
    }
    else if( equipoSeleccionado[0]!='\0' && strcmpi((*datoPartido.equipo2).nomEquipo,equipoSeleccionado)==0)
    {
        gotoxy(x+2,y+1);puts((*datoPartido.equipo1).nomEquipo);
        color(rojo,amarillo);gotoxy(x+23,y+1);puts((*datoPartido.equipo2).nomEquipo);color(negro,blanco);
    }
    else
    {
        gotoxy(x+2,y+1);puts((*datoPartido.equipo1).nomEquipo);
        gotoxy(x+23,y+1);puts((*datoPartido.equipo2).nomEquipo);
    }
    gotoxy(x+15,y+1);printf("%i - ",datoPartido.golesEq1);
    gotoxy(x+19,y+1);printf("%i",datoPartido.golesEq2);
    //Sleep(500);
    //gotoxy(x+2,y+3);printf("Puntos       %i -",(*datoPartido.equipo1).pts);
    //gotoxy(x+19,y+3);printf("%i       Puntos",(*datoPartido.equipo2).pts);
    if(y<39){
    color(negro,gris);lineaHorizontal(x+3,y+5,x+38);color(negro,blanco);}
}


void mostrarArgentinaCampeon(char equipo1[],char equipo2[],char equipo3[])
{

    centrarTexto("C A M P E O N   C O P A   M U N D I A L",18);
    centrarTexto(equipo1,20);
    banderaArg(81,22);

    centrarTexto("S E G U N D O   P U E S T O",26);
    centrarTexto(equipo2,28);

    centrarTexto("T E R C E R   P U E S T O",31);
    centrarTexto(equipo3,33);
}

void mostrarCampeonSegTer(fase arrFase[])
{
    int negro=0,azul=1,verde=2,aquaM=3,rojo=4,purpura=5,amarillo=6,grisClaro=7,gris=8,azulClaro=9,verClaro=10,aquClaro=11,rojoClaro=12,magenta=13,amarilloClaro=14,blanco=15;

    color(negro,rojo);recuadroDif(57,15,115,35);color(negro,blanco);
    centrarTexto(" R E S U L T A D O S    M U N D I A L    Q A T A R     2 0 2 2",13);
    Equipo* tercerPuesto=buscarEquipoGanadorListaPartidos(arrFase[3].partidos,1);
    Equipo* segundoPuesto=buscarPerdedorListaPartido(arrFase[4].partidos,1);
    Equipo* campeon=buscarEquipoGanadorListaPartidos(arrFase[4].partidos,1);
    aMayus((*campeon).nomEquipo);aMayus((*segundoPuesto).nomEquipo);aMayus((*tercerPuesto).nomEquipo);

    if(strcmpi((*campeon).nomEquipo,"argentina")==0)
    {
        mostrarArgentinaCampeon((*campeon).nomEquipo,(*segundoPuesto).nomEquipo,(*tercerPuesto).nomEquipo);
    }
    else
    {
        centrarTexto("C A M P E O N   C O P A   M U N D I A L",18);
        centrarTexto((*campeon).nomEquipo,20);

        centrarTexto("S E G U N D O   P U E S T O",24);
        centrarTexto((*segundoPuesto).nomEquipo,26);

        centrarTexto("T E R C E R   P U E S T O",30);
        centrarTexto((*tercerPuesto).nomEquipo,32);
    }

    centrarTexto("C  O  M  I  S  I  O  N    6",40);
    color(negro,gris);recuadroDif(50,43,122,51);color(negro,blanco);
    gotoxy(55,45);printf("V  A  L  E  N  T  I  N      S  O  L  A  R  I");
    gotoxy(73,47);printf("G  O  N  Z  A  L  O      M  A  R  T  I  N  O");
    gotoxy(61,49);printf("V  A  R  E  L  A      J  O  S  E    M  A  R  I  A");

    tituloRecuadro();
    aMinus((*campeon).nomEquipo);aMinus((*segundoPuesto).nomEquipo);aMinus((*tercerPuesto).nomEquipo);

}

void mostrarArrPartidoFaseArbol(fase arrPartidoFase[],char equipoSeleccionado[])
{
    int negro=0,azul=1,verde=2,aquaM=3,rojo=4,purpura=5,amarillo=6,grisClaro=7,gris=8,azulClaro=9,verClaro=10,aquClaro=11,rojoClaro=12,magenta=13,amarilloClaro=14,blanco=15;
    tituloRecuadro();
    int i=0;
    int x=2,y=4;
    while(i<5)
    {
        if(i==0)
        {
            color(rojo,negro);gotoxy(x+8,y-2);printf(" O  C  T  A  V  O  S ");color(negro,blanco);
            mostrarListaPartidoFaseArbol(arrPartidoFase[i].partidos,x,y,azulClaro,equipoSeleccionado);
        }
        else if(i==1)
        {
            color(rojo,negro);gotoxy(x+19,y-1);printf(" C  U  A  R  T  O  S ");color(negro,blanco);
            mostrarListaPartidoFaseArbol(arrPartidoFase[i].partidos,x+11,y+1,azulClaro,equipoSeleccionado);
        }
        else if(i==2)
        {
            color(rojo,negro);gotoxy(x+26,y-7);printf(" S  E  M  I    F  I  N  A  L ");color(negro,blanco);
            mostrarListaPartidoFaseArbol(arrPartidoFase[i].partidos,x+21,y-5,amarillo,equipoSeleccionado);
         i++;   /// salta a partido final se saltea terceros
        }
        else if(i==4)
        {
            color(rojo,negro);gotoxy(x+43,y-16);printf(" F  I  N  A  L ");color(negro,blanco);
            mostrarListaPartidoFaseArbol(arrPartidoFase[i].partidos,x+31,y-14,amarillo,equipoSeleccionado);
        }
        i++;
        x+=32;y+=13;
    }

}


void mostrarListaPartidoFaseArbol(nodoPartidoFase* lista,int x,int y,int color,char equipoSeleccionado[])
{
    while(lista)
    {
        mostrarUnPartidoFaseArbol(lista->partido,x,y,color,equipoSeleccionado);
        lista=lista->siguiente;
        y+=7;
    }

}

void mostrarUnPartidoFaseArbol(PartidoFase datoPartido,int x,int y,int col,char equipoSeleccionado[])
{
    int negro=0,azul=1,verde=2,aquaM=3,rojo=4,purpura=5,amarillo=6,grisClaro=7,gris=8,azulClaro=9,verClaro=10,aquClaro=11,rojoClaro=12,magenta=13,amarilloClaro=14,blanco=15;
    Sleep(200);
    color(negro,col);recuadro(x-1,y-1,x+38,y+5);color(negro,blanco);

    if(equipoSeleccionado[0]!='\0' && strcmpi((*datoPartido.equipo1).nomEquipo,equipoSeleccionado)==0)
    {
        color(rojo,amarillo);gotoxy(x+1,y);puts((*datoPartido.equipo1).nomEquipo);color(negro,blanco);
        gotoxy(x+24,y);puts((*datoPartido.equipo2).nomEquipo);
    }
    else if(equipoSeleccionado[0]!='\0' && strcmpi((*datoPartido.equipo2).nomEquipo,equipoSeleccionado)==0)
    {
        gotoxy(x+1,y);puts((*datoPartido.equipo1).nomEquipo);
        color(rojo,amarillo);gotoxy(x+24,y);puts((*datoPartido.equipo2).nomEquipo);color(negro,blanco);
    }
    else
    {
        gotoxy(x+1,y);puts((*datoPartido.equipo1).nomEquipo);
        gotoxy(x+24,y);puts((*datoPartido.equipo2).nomEquipo);
    }
    gotoxy(x+16,y);printf("%i - ",datoPartido.golesEq1);
    gotoxy(x+20,y);printf("%i",datoPartido.golesEq2);
    gotoxy(x,y+2);color(negro,gris);printf("..............         ...............");color(negro,blanco);
    //Sleep(500);
    gotoxy(x+2,y+4);printf("Penales       %i -",datoPartido.penales1);
    gotoxy(x+20,y+4);printf("%i       Penales",datoPartido.penales2);

}



/// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES ///
/// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES ///
/// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES ///
/// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES /// OTRAS FUNCIONES ///


void verificarEquipoSeleccionado(char nombre[],nodoEquipo* equipos)
{
    const int anchoConsola=172;
    const int altoConsola=59;


    int negro=0,azul=1,verde=2,aquaM=3,rojo=4,purpura=5,amarillo=6,grisClaro=7,gris=8,azulClaro=9,verClaro=10,aquClaro=11,rojoClaro=12,magenta=13,amarilloClaro=14,blanco=15;

    Equipo* buscado=NULL;
    do
    {
        tituloRecuadro();
        centrarTexto(" B I E N V E N I D O   A L   M U N D I A L   D E   F U T B O L ",18);
        centrarTexto("SELECCIONE EL EQUIPO QUE CLASIFICARA A LA SIGUIENTE FASE: OCTAVOS",20);
        fflush(stdin);
        gotoxy(80,22);gets(nombre);
        buscado=buscarEquipoEnLista(equipos,nombre);

        if(!buscado)
        {
            color(rojo,grisClaro);centrarTexto("EL EQUIPO INGRESADO NO ESTA DENTRO DE LOS QUE CLASIFICARON AL MUNDIAL",24);color(negro,blanco);
            gotoxy(66,34);
            system("pause");
            system("cls");
        }
        else
        {
            centrarTexto(" FELICIDADES TU EQUPO CLASIFICO A OCTAVOS ",26);
            gotoxy(66,34);
            system("pause");

        }

    }while(!buscado);

    strcpy(nombre,(*buscado).nomEquipo);
}



int cantidadDatosArchivo()
{
    int cant=0;
    FILE* arch=fopen("fechas.dat","rb");

    if(arch)
    {
        fseek(arch,0,SEEK_END);
        cant=ftell(arch)/sizeof(registroFecha);

        fclose(arch);
    }

    return cant;
}

/// buscar dato en archivo y modificarlo
void modificarRegistro(int posRegistro)
{



    registroFecha datoReg;

    FILE* arch=fopen("fechas.dat","r+b");




    if(arch)
    {


            rewind(arch);
            fseek(arch,sizeof(registroFecha)*(posRegistro-1),SEEK_CUR);
            fread(&datoReg,sizeof(registroFecha),1,arch);

            mostrarDatoReg(datoReg);

            datoReg=modificarEstructura(datoReg);

            printf("\nModificado\n");
            mostrarDatoReg(datoReg);

            fseek(arch,sizeof(registroFecha)*(-1),SEEK_CUR);

            fwrite(&datoReg,sizeof(registroFecha),1,arch);

            fclose(arch);

    }
    else
    {
        printf("\nHubo un problema\n");
    }

}

/// modificar un registro
registroFecha modificarEstructura(registroFecha dato)
{

    printf("\nNombre equipo 1\t");
    fflush(stdin);
    gets(dato.Equipo1);
    printf("\nNombre equipo2\n");
    fflush(stdin);
    gets(dato.Equipo2);
    printf("\ngrupo\n");
    fflush(stdin);
    scanf("%c",&dato.grupo);
    printf("\ndia\n");
    scanf("%i",&dato.dia);
    printf("\nMes\n");
    scanf("%i",&dato.mes);
    return dato;

}

void mostrarDatoReg(registroFecha dato)
{
    printf("\nnombre equipo1 \t");
    puts(dato.Equipo1);
    printf("\nnombre equipo2 \n");
    puts(dato.Equipo2);
    printf("\ngrupo %c\n",dato.grupo);
    printf("\ndia %i\n",dato.dia);
    printf("\nmes %i\n",dato.mes);
    printf("\n\n");

}

