//Ángela Pozo Mateos
//El trozo de código para cargar imagenes ha sido proporcionado por Pedro Luis Fuertes Moreno

#include "textura.h"
#include <GL/glut.h>
#include "CImg.h"
#include <string>

using namespace cimg_library;
using namespace std;

Textura::Textura( const char *filename, std::vector<Tupla2f> coordenadas )
{
	coordenadas_textura = coordenadas;	
	activa = false;
	std::vector<unsigned char> data;
	
	CImg<unsigned char> imagen;
	imagen.load(filename);
	
	for(	long y=0 ; y<imagen.height() ; y++ )
	{
		for( long x=0 ; x<imagen.width() ; x++ )
		{	
			unsigned char * red = imagen.data(x,y,0,0);
			unsigned char * green = imagen.data(x,y,0,1);
			unsigned char * blue = imagen.data(x,y,0,2);
			data.push_back(*red);
			data.push_back(*green);
			data.push_back(*blue);
		}
	}

	glGenTextures(1, &id_textura);
	glBindTexture(GL_TEXTURE_2D, id_textura);
	glActiveTexture(GL_TEXTURE0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	cout << "Textura1" << endl;
	gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, imagen.width(), imagen.height(), GL_RGB, GL_UNSIGNED_BYTE, data.data());
}

void Textura::activar_textura()
{
	glTexCoordPointer(2, GL_FLOAT, 0, coordenadas_textura.data());
}

void Textura::habilitar_texturas()
{
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
}
void Textura::deshabilitar_texturas()
{
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
}

std::vector<Tupla2f> Textura::get_coordenadas()
{
	return coordenadas_textura;
}
