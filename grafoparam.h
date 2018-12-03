// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.h
// -- declaraciones de clase para el objeto jerárquico de la práctica 3
//
// #############################################################################

#ifndef GRAFOPARAM_H_INCLUDED
#define GRAFOPARAM_H_INCLUDED

#include "malla.h" // añadir .h de cualquier objetos malla indexada usados....
#include "cubo.h"
#include "objrevolucion.h"


constexpr int num_parametros = 3 ; // número de parámetros o grados de libertad
                                   // de este modelo

class GrafoParam
{
   public:

   // crea mallas indexadas (nodos terminales del grafo)
   GrafoParam();

   // función principal de visualización
   void draw( const int p_modo_vis, const bool ajedrez, const int material );

   // actualizar valor efectivo de un parámetro (a partir de su valor no acotado)
   void actualizarValorEfe( const unsigned iparam, const float valor_na );

   // devuelve el número de parámetros
   unsigned numParametros() { return num_parametros ; }

   private:

   // métodos de dibujo de subgrafos
   void pendulo( );
	void brazo( );
	void codo( );

   // objetos tipo malla indexada (nodos terminales)

   //Cilindro * cilindro = nullptr ;
   //Cubo *     cubo     = nullptr ;
	Esfera * bola = nullptr ; 
	Cubo * cuerda = nullptr ;
	Cilindro * barra = nullptr ;
	Cilindro * eje = nullptr ;
	Cubo * soporte = nullptr ; 

   // parámetros de la llamada actual (o última) a 'draw'
   int modo_vis ;      // modo de visualización
   bool modo_ajedrez ; // modo de envío (true -> diferido, false -> inmediato)
	int material_utilizado;


   // valores efectivos de los parámetros (angulos, distancias, factores de
   // escala, etc.....) calculados a partir de los valores no acotados

	float traslacion_brazo = 0.0;
   float angulo_pendulo = 0.0;
	float angulo_eje = 0.0;   
   

} ;

#endif
