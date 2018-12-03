#ifndef OBJETOS_PLY_INCLUDED
#define OBJETOS_PLY_INCLUDED

#include "malla.h"
#include "ply_reader.h"
// *****************************************************************************
// objeto leído de un archivo PLY

class ObjPLY : public ObjMallaIndexada 
{
   public:
      ObjPLY( const std::string & nombre_archivo );

};

#endif
