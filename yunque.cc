//Autor: ANGELA POZO MATEOS
#include "yunque.h"

Yunque::Yunque()
{

   // inicializar la tabla de vértices
   vertices =  {  { -0.5, -0.5, -0.5 }, // 0
                  { -0.5, -0.5, +0.5 }, // 1
                  { -0.5, +0.5, -0.5 }, // 2
                  { -0.5, +0.5, +0.5 }, // 3
                  { +0.5, -0.5, -0.5 }, // 4
                  { +0.5, -0.5, +0.5 }, // 5
                  { +0.5, +0.5, -0.5 }, // 6
                  { +0.5, +0.5, +0.5 },  //7

						{ -1.5, +0.0, +0.0 },  //8
						{ +1.5, +0.0, +0.0 }   //9
               };

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   triangulos = { { 0, 2, 4 }, { 4, 2, 6 },
                  { 1, 5, 3 }, { 3, 5, 7 },
                  { 1, 3, 0 }, { 0, 3, 2 },
                  { 5, 4, 7 }, { 7, 4, 6 },
                  { 1, 0, 5 }, { 5, 0, 4 },
                  { 3, 7, 2 }, { 2, 7, 6 },

						{ 8, 1, 3 }, { 8, 3, 2},
						{ 8, 2, 0 }, { 8, 0, 1},

						{ 9, 6, 7 }, { 9, 7, 5},
						{ 9, 5, 4 }, { 9, 4, 6}
                } ;
	calcular_normales();
}

