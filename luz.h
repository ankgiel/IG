//Ángela Pozo Mateos
//Clase Luz

#ifndef LUZ_H
#define LUZ_H

#include "aux.h"
//#include <chrono>

/*
// tipo para registrar instantes de tiempo
typedef std::chrono::time_point<std::chrono::steady_clock> Instante ;

// tipo para duraciones en segundos (como números 'float', con parte fraccionaria)
typedef std::chrono::duration<float,std::ratio<1,1>> Duracion_s ;
*/ 

class Luz
{
	private:
	Tupla4f color_ambiental;	//Colores ambiental,difuso y especular de la luz
	Tupla4f color_difuso;
	Tupla4f color_especular;
	
	Tupla4f posicion; //El tipo está indicado en la componente w: w=0 -> direccion, si w=1 -> posicion

	GLenum indice; //Valor de Lighti  al que se asociará esta luz

	//bool encendida;
	//bool modo_animacion = false;
   //float angulo = 0;
	// instante de ultima actualización de los parámetros, o bien de la última llamada a 'inicio_animaciones'
   //Instante ultima_actu  ;


	public:
	Luz( Tupla4f ambiental, Tupla4f difuso, Tupla4f especular, Tupla4f pos, GLenum lighti );
	void draw(Tupla4f ambiental, Tupla4f difuso, Tupla4f especular, Tupla4f pos, float alpha);
	//void interruptor();	
	//void activar_luces();
	//void desactivar_luces();
	bool get_tipo();
	//void rotar( float alpha, float eje_x, float eje_y, float eje_z);
	//void iniciarAnimaciones();
	//void pararAnimaciones();
	//void actualizarEstado();
	//bool getEncencida();
	//void setEncendida(bool encend);

};

#endif
