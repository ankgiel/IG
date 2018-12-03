//Ángela Pozo Mateos

#ifndef CHESS_H
#define CHESS_H

#include "aux.h"
#include "malla.h"

class ChessBoard : public ObjMallaIndexada
{
	public:
		ChessBoard(const char * filename);
};

#endif
