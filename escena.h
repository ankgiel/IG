//Autor: ANGELA POZO MATEOS
#ifndef _ESCENA_H
#define _ESCENA_H

#include <fstream>
#include "ejes.h"
#include "malla.h"
#include "luz.h"
#include "cubo.h"
#include "tetra.h"
#include "yunque.h"
#include "objrevolucion.h"
#include "ply.h"
#include "jerarquico.h"
#include "chess_board.h"


// tipo para registrar instantes de tiempo
typedef std::chrono::time_point<std::chrono::steady_clock> Instante ;

// tipo para duraciones en segundos (como números 'float', con parte fraccionaria)
typedef std::chrono::duration<float,std::ratio<1,1>> Duracion_s ;

class Escena
{

   private:

   Ejes ejes;

   // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;


   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;


   void clear_window();
	void dibujar_objeto_actual();
	void dibujar_luces();


   // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
	bool animacion_luz = false;
   Instante ultima_actu  ;

   int modo_draw = 0, 
		modo = 0,
		material = 0,
		objeto_actual = 0 , // objeto actual (el que se visualiza)
      num_objetos   = 0 ; // número de objetos (actualizado al crear los objetos en el constructor)


   // Objetos de la escena
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
	Tetra * tetra = nullptr ;
	Yunque * yunque = nullptr;
	Cilindro * cilindro = nullptr;
	Cono * cono = nullptr;
	Esfera * esfera = nullptr;
	Cuenco * cuenco = nullptr ;
	ObjRevolucion * ply_1 = nullptr;
	ObjPLY * ply_2 = nullptr;
	ObjJerarquico * demoledora = nullptr;
	ChessBoard * cuadro = nullptr;

	//Luces de la escena
	Luz * luz_posicional = nullptr;
	Luz * luz_direccional = nullptr;
	float angulo_luz = 0;

   public:

   Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;
	void animar_escena();
	void actualizarEstado();
	void iniciarAnimacionLuz();
	void pararAnimacionLuz();
	void rotarLuz(GLenum i, float alpha, float eje_x, float eje_y, float eje_z);

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

};
#endif
