//Autor: ANGELA POZO MATEOS
#include "tetra.h"

Tetra::Tetra()
{

	// inicializar la tabla de vértices
	vertices = {	{ +0.0, +1.0, +0.0 },	//0
						{ +0.5, +0.0, +0.0 },	//1
						{ -0.4, +0.0, -0.4 },	//2
						{ -0.4, +0.0, +0.4 }		//3
					};

	// inicializar la tabla de caras o triángulos:
	triangulos = { { 3, 2, 1 }, 
						{ 0, 1, 2 },
						{ 0, 3, 1 },
						{ 0, 2, 3 }
					};
	calcular_normales();
}

