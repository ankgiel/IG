// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.cc
// -- implementación del objeto jerárquico de la práctica 3
//
// #############################################################################


#include "grafoparam.h"

// -----------------------------------------------------------------------------
// constructor: crea mallas indexadas en los nodos terminales del grafo

GrafoParam::GrafoParam()
{
   cuerda 	= new Cubo();
   bola     = new Esfera(40,40);
	barra		= new Cilindro(10,20);
	eje		= new Cilindro(10,20);
	soporte 	= new Cubo();
}
// -----------------------------------------------------------------------------
// actualizar valor efectivo de un parámetro (a partir de su valor no acotado)

void GrafoParam::actualizarValorEfe( const unsigned iparam, const float valor_na )
{
   assert( iparam < num_parametros );

   //using namespace std ;
   constexpr float vp = 2.5 ;

   switch( iparam )
   {
      case 0:
			angulo_pendulo = 120.0*sin(valor_na * PI / 180.0);
         break ;
      case 1:
			traslacion_brazo = 0 + 12.0*sin( valor_na*0.01 );
         break ;
      case 2:
			angulo_eje = 0 + 180.0*sin(valor_na * PI / 180.0) ; 
         break ;
   }
}

// -----------------------------------------------------------------------------
// visualización del objeto Jerárquico con OpenGL,
// mediante llamadas a los métodos 'draw' de los sub-objetos

void GrafoParam::draw( const int modo_draw, const bool ajedrez, const int material )
{
   // asegurarnos que está inicializado ok

   assert( cuerda     != nullptr );
   assert( bola		 != nullptr );
	assert( barra		 != nullptr );
	assert( eje			 != nullptr );

   // guardar parametros de visualización para esta llamada a 'draw'
   // (modo de visualización, modo de envío)

   modo_vis      = modo_draw ;
   modo_ajedrez = ajedrez ;
	material_utilizado = material;

	glPushMatrix();
		glTranslatef( 0.0, 15.0, 0.0 );
		glScalef( 4.0, 30.0, 4.0 );
		soporte->draw( modo_vis, modo_ajedrez, material_utilizado ); 
   glPopMatrix();
   glPushMatrix();
		glTranslatef( 0.0, 35.0, 0.0 );
		codo( );
   glPopMatrix();
}
// -----------------------------------------------------------------------------
//Dibuja un sub-objeto parametrizado:
//Es un péndulo (esfera) con una cuerda (cubo) encima. 
//Rotado en torno al eje X en un angulo de 'ang_pendulo'



// dibuja un sub-objeto parametrizado:
// rotado entorno a X un ángulo en grados = 'ang_cuerda'

void GrafoParam::pendulo( )
{
	glRotatef( angulo_pendulo, 1.0, 0.0, 0.0 );
	glPushMatrix();
		glTranslatef( 0.0, -20.0, 0.0 );      
		glScalef( 5, 5, 5 );
      bola->draw( modo_vis, modo_ajedrez, material_utilizado );
   glPopMatrix();
   glPushMatrix( );
      glTranslatef( 0.0, -8.0, 0.0 );
		glScalef( 1, 16, 1 );
      cuerda->draw( modo_vis, modo_ajedrez, material_utilizado);
   glPopMatrix();
}

void GrafoParam::brazo( )
{
	glTranslatef( traslacion_brazo, 0.0, 0.0 );
	glPushMatrix();
		glTranslatef( -20.5, 0.0, 0.0 );
		pendulo( );
	glPopMatrix();
	glPushMatrix();
		glRotatef( 90.0, 0.0, 0.0, 1.0 );
		glScalef( 2, 40, 2 );
		barra->draw( modo_vis, modo_ajedrez, material_utilizado );
	glPopMatrix();
}

void GrafoParam::codo( )
{	
	glRotatef( angulo_eje, 0.0, 1.0, 0.0 );
	glPushMatrix();
		brazo( );
	glPopMatrix();
	glPushMatrix();
		glRotatef( 90.0, 0.0, 0.0, 1.0 );
		glScalef( 5, 10, 5 );
		eje->draw( modo_vis, modo_ajedrez, material_utilizado );
	glPopMatrix();
}
