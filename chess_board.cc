//Ángela Pozo Mateos

#include "chess_board.h"
using namespace std;
ChessBoard::ChessBoard(const char * filename)
{
   // inicializar la tabla de vértices
   vertices =  {  { -1.0, -0.5, 0.0 }, // 0
						{ -1.0, +0.5, 0.0 }, // 1
                  { +1.0, -0.5, 0.0 }, // 2             
                  { +1.0, +0.5, 0.0 }, // 3

               };

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   triangulos = { { 1, 0, 3 }, { 0, 2, 3 } } ;
	calcular_normales();
	
	std::vector<Tupla2f> cv;

	cv.push_back(Tupla2f(0,1));
	cv.push_back(Tupla2f(0,0));
	cv.push_back(Tupla2f(1,1));
	cv.push_back(Tupla2f(1,0));


	cout << "Creando la nueva textura con sorolla" << endl;
	textura = new Textura(filename, cv);
}
