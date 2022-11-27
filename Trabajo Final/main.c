#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include "Fixture.h"

                                     ///FIXTURE QATAR 2022
/// GONZALO MARTINO
/// JOSE VARELA
/// VALENTIN SOLARI
/// COMISION 6

int main()
{
    system("mode con: cols=172 lines=60");

    srand(time(NULL));

    tituloRecuadro();



    nodoEquipo* listaSelecciones=NULL;

    CargarSelecciones(&listaSelecciones);


    Grupo arregloGrupos[8];

    CargarGrupos(arregloGrupos,8,listaSelecciones);



    GrupoPartido arrPartidosGrupo[8];
    int validos=0;


    char equipoSeleccionado[30]="";
    char opcion='n';
    centrarTexto("D E S E A   I N G R E S A R   U N   E Q U I P O   ?",10);
    centrarTexto("s aceptar, u otra letra para cancelar",12);
    fflush(stdin);
    gotoxy(85,14);scanf("%c",&opcion);

    gotoxy(3,58);
    if(opcion =='s' || opcion =='S')
    {
        verificarEquipoSeleccionado(equipoSeleccionado,listaSelecciones);
        //centrarTexto(equipoQueClasifica,30);
    }else{system("cls");}

    tituloRecuadro();



    validos=leerArchivoCargarArreglo(arrPartidosGrupo,validos,listaSelecciones,equipoSeleccionado);



    system("cls");
    mostrarArrGrupoPartidosRecuadro(arrPartidosGrupo,equipoSeleccionado);

    gotoxy(3,58);
    system("pause");
    system("cls");


    mostrarArregloGruposGrilla(arregloGrupos,equipoSeleccionado);

    system("pause");
    system("cls");

    int validos2=0;
    fase arrFase[5];
    validos2=cargarListaPartidosEnFaseOctavos(arrFase,validos2,arregloGrupos);

    validos2=cuartosSemiFinalTerceros(arrFase,validos2);



    mostrarArrPartidoFaseArbol(arrFase,equipoSeleccionado);

    gotoxy(3,58);
    system("pause");
    system("cls");

    mostrarCampeonSegTer(arrFase);

    return 0;
}


