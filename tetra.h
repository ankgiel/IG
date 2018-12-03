//Autor: ANGELA POZO MATEOS
#ifndef TETRA_H

#define TETRA_H
#include "malla.h"

// clases derivadas de ObjMallaIndexada (definen constructores específicos)
//
// *****************************************************************************
// *****************************************************************************
// Tetraedro con 3 puntos sobre el plano formado por los ejes X y Z.
// Y su punto más alto en el eje Y
// (tiene 4 vertices y 4 caras)

class Tetra : public ObjMallaIndexada
{
   public:
   Tetra() ;

} ;
#endif
