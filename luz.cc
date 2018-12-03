// Ángela Pozo Mateos
//Clase Luz 

#include "luz.h"

Luz::Luz( Tupla4f ambiental, Tupla4f difuso, Tupla4f especular, Tupla4f pos, GLenum lighti )
{
	color_ambiental = ambiental;
	color_difuso = difuso;
	color_especular = especular;
	posicion = pos ;
	indice = lighti;
	//encendida = false;
}

void Luz::draw(Tupla4f ambiental, Tupla4f difuso, Tupla4f especular, Tupla4f pos, float alpha)
{
		color_ambiental = ambiental;
		color_difuso = difuso;
		color_especular = especular;
		posicion = pos ;		
		glLightfv( indice , GL_AMBIENT, color_ambiental );
		glLightfv( indice , GL_DIFFUSE, color_difuso );
		glLightfv( indice , GL_SPECULAR, color_especular );
		//glLightfv( indice , GL_POSITION, posicion );
		
		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();
			glLoadIdentity();
			glRotatef( alpha, 0.0, 1.0, 0.0 );
			glLightfv( indice, GL_POSITION, posicion );
		glPopMatrix();
}


bool Luz::get_tipo()
{
	return posicion(3);
}

/*
bool Luz::getEncencida(){
	return encendida;
}
void Luz::setEncendida(bool encend){
	encendida = encend;
}
*/

/*
void Luz::rotar( float alpha, float eje_x, float eje_y, float eje_z){
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
		glLoadIdentity();
		glRotatef( alpha, eje_x, eje_y, eje_z );
		glLightfv( indice, GL_POSITION, posicion );
	glPopMatrix();
}
*/
/*
void iniciarAnimacionLuz(){
	using namespace std ;
   using namespace std::chrono ;
	modo_animacion = true;
	cout << "Se inicia animacion LUCES" << endl;
   ultima_actu = steady_clock::now() ;
}

void Luz::pararAnimaciones()
{
	modo_animacion = false;
}
*/
/*
void Luz::actualizarEstado()
{
	if(modo_animacion){
		using namespace std ;
		using namespace std::chrono ;

		// calcular el tiempo transcurrido desde la ultima actualización o
		// desde que se invocó a 'inicio_animaciones' (delta_t_s)
		const Instante   ahora      = steady_clock::now() ;
		const Duracion_s duracion_s = ahora - ultima_actu ;
		const float      delta_t_s  = duracion_s.count();

		// actualizar instante de la última actualización de estado
		ultima_actu = ahora ;
		angulo += delta_t_s*50;
		//rotar( angulo, 0.0 , 1.0 , 0.0 );
	}
}
*/

