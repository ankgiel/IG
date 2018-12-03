//Ángela Pozo Mateos

#ifndef TEXTURA_H
#define TEXTURA_H

#include "aux.h"
#include <GL/glut.h>
#include "CImg.h"
#include <string>

using namespace cimg_library;

typedef struct _AUX_RGBImageRec{
	GLint sizeX, sizeY;
	unsigned char *data;
} aUX_RGBImageRec;



class Textura
{
		protected: 
			GLuint id_textura = 0; 
			bool activa;
			std::vector<Tupla2f> coordenadas_textura;

		public: 
			Textura( const char *filename, std::vector<Tupla2f> coordenadas );
			void activar_textura();
			void deshabilitar_texturas();
			void habilitar_texturas();
			std::vector<Tupla2f> get_coordenadas();
};

#endif
