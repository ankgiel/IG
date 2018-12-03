//Autor: ANGELA POZO MATEOS

#include "ply_reader.h"
#include "malla.h"
#define PI 3.141592

using namespace std ;

GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram )
{
	GLuint id_vbo;
	// resultado: identificador de VBO
	glGenBuffers( 1, & id_vbo );
	// crear nuevo VBO, obtener identificador (nunca 0)
	glBindBuffer( tipo_vbo, id_vbo ); // activar el VBO usando su identificador
	// esta instrucción hace la transferencia de datos desde RAM hacia GPU
	glBufferData( tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW );
	glBindBuffer( tipo_vbo, 0 );
	return id_vbo ;
}

// *****************************************************************************
//
// Clase ObjMallaIndexada
//
// *****************************************************************************
// Visualización en modo inmediato con 'glDrawElements'
void ObjMallaIndexada::draw_ModoInmediato(bool ajedrez)
{
	glVertexPointer( 3, GL_FLOAT, 0, vertices.data() ) ;
	glEnableClientState( GL_VERTEX_ARRAY );

	if( glIsEnabled(GL_LIGHTING) ){	//Si la luz está activa, ussamos las normales de vertices
		glNormalPointer( GL_FLOAT, 0, normales_vertices.data() );
		glEnableClientState( GL_NORMAL_ARRAY );
	}	

	if(ajedrez){ //Modo ajedrez
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, colores_pares.data());
		glDrawElements( GL_TRIANGLES, triangulos_pares.size()*3, GL_UNSIGNED_INT, triangulos_pares.data());
		glColorPointer(3, GL_FLOAT, 0, colores_impares.data());
		glDrawElements( GL_TRIANGLES, triangulos_impares.size()*3, GL_UNSIGNED_INT, triangulos_impares.data());
	}
	else{
		if(t_activa){ //La textura está activa
			glColor3f(1,1,1);		
			textura->activar_textura();
			textura->habilitar_texturas();
		}
		else if(!glIsEnabled(GL_LIGHTING)){	//La luz no está activa y no hay textura, a colorear
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(3, GL_FLOAT, 0, lista_colores.data());
		}
		glDrawElements(GL_TRIANGLES,triangulos.size()*3,GL_UNSIGNED_INT, triangulos.data() );
		if(t_activa)
			textura->deshabilitar_texturas();
	}

	if(glIsEnabled( GL_COLOR_ARRAY ))
		glDisableClientState( GL_COLOR_ARRAY );

	glDisableClientState( GL_VERTEX_ARRAY );
	if( glIsEnabled(GL_LIGHTING) )
		glDisableClientState( GL_NORMAL_ARRAY );
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void ObjMallaIndexada::draw_ModoDiferido(bool ajedrez)
{// (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
	if( !vbo_vertices	)
		vbo_vertices = CrearVBO( GL_ARRAY_BUFFER, vertices.size()*3*sizeof(float), vertices.data());
	if ( !vbo_triangulos ) 
		vbo_triangulos = CrearVBO( GL_ELEMENT_ARRAY_BUFFER, triangulos.size()*3*sizeof(int), triangulos.data() );
	if( !vbo_colores ) 
		vbo_colores = CrearVBO(GL_ARRAY_BUFFER,lista_colores.size()*3*sizeof(float), lista_colores.data());
	if( !vbo_normales )
		vbo_normales = CrearVBO(GL_ARRAY_BUFFER,normales_vertices.size()*3*sizeof(float), normales_vertices.data());


   glBindBuffer( GL_ARRAY_BUFFER, vbo_vertices ); // activar VBO de vértices
	glVertexPointer( 3, GL_FLOAT, 0, 0 ); // especifica formato y offset (=0)
	glBindBuffer( GL_ARRAY_BUFFER, 0 ); // desactivar VBO de vértices.
	glEnableClientState( GL_VERTEX_ARRAY ); // habilitar tabla de vértices
	

	if(glIsEnabled(GL_LIGHTING)){	//Si la luz esta activa usamos las normales de vertices
		glBindBuffer( GL_ARRAY_BUFFER, vbo_normales );
		glNormalPointer( GL_FLOAT,0,0);
		glBindBuffer( GL_ARRAY_BUFFER,0);
		glEnableClientState( GL_NORMAL_ARRAY );
	}

	if(t_activa){ //La textura está activa
		glColor3f(1,1,1);
		textura->activar_textura();
		textura->habilitar_texturas();
	}
	else if(!glIsEnabled(GL_LIGHTING)){ //No hay textura ni luz, a colorear
		glBindBuffer( GL_ARRAY_BUFFER, vbo_colores);
		glColorPointer( 3, GL_FLOAT, 0 , 0);
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		glEnableClientState( GL_COLOR_ARRAY );
	}

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vbo_triangulos );// activar VBO de triángulos
	glDrawElements( GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	if(t_activa)
		textura->deshabilitar_texturas();

	if(glIsEnabled( GL_COLOR_ARRAY ))
		glDisableClientState( GL_COLOR_ARRAY );
	
	if(glIsEnabled( GL_NORMAL_ARRAY ))
		glDisableClientState(GL_NORMAL_ARRAY);
	
	glDisableClientState( GL_VERTEX_ARRAY );
/*
	if(ajedrez){
		for(int i=0 ; i<triangulos.size() ; i++){
			if(i%2==0) glColor3f(1.0,1.0,0.0);
			else glColor3f(0.0,1.0,0.0);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int)*3*i) );
		}
	}
	else
		glDrawElements( GL_TRIANGLES, 3*triangulos.size(), GL_UNSIGNED_INT, 0 ) ;
*/
}



// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido
void ObjMallaIndexada::draw( int modo_draw, bool ajedrez, int material )
{
	glEnable(GL_CULL_FACE);
	activar_material(material);

	if(ajedrez){	
		colores_pares.clear();
		colores_impares.clear();
		for(int i=0 ; i<vertices.size() ; i++){
				colores_pares.push_back( {1.0,0.0,0.0} );				
				colores_impares.push_back( {0.0,1.0,0.0} );
		}
		
		triangulos_impares.clear();
		triangulos_pares.clear();
		for(int i=0 ; i<triangulos.size() ; i++){
			if(i%2==0)
				triangulos_pares.push_back(triangulos[i]);
			else 
				triangulos_impares.push_back(triangulos[i]);
		}
	}
	else{
		lista_colores.clear();
		for(int i=0 ; i<vertices.size() ; i++){
			if(modo_draw)
				lista_colores.push_back( {0.0, 0.0, 1.0} );
			else
				lista_colores.push_back( {0.0, 5.0, 5.0} );
		}
	}

	switch( modo_draw ){
		case 0:
			draw_ModoInmediato(ajedrez);
			break;
		case 1:
			draw_ModoDiferido(ajedrez);
			break;
	}
}
// -----------------------------------------------------------------------------
// Recalcula la tabla de normales de vértices (el contenido anterior se pierde)

void ObjMallaIndexada::calcular_normales()
{
	normales_caras.clear();
	normales_vertices.clear();

	//Cálculo de normales de caras	
	Tupla3f p0, p1, p2, A, B, normal_c;
	float modulo;
	for(int i=0 ; i<triangulos.size() ; i++)
	{
		p0 = vertices[ triangulos[i](0) ] ; //Guardo el primer vértice asociado al triangulo i
		p1 = vertices[ triangulos[i](1) ] ;
		p2 = vertices[ triangulos[i](2) ] ;

		A = p1 - p0;
		B = p2 - p0;
		
		normal_c(0) = A(1)*B(2) - A(2)*B(1) ;
		normal_c(1) = A(0)*B(2) - A(2)*B(0) ;
		normal_c(2) = A(0)*B(1) - A(1)*B(0) ;

		modulo = sqrt( normal_c(0)*normal_c(0) + normal_c(1)*normal_c(1) + normal_c(2)*normal_c(2) );
		
		normal_c(0) = normal_c(0)/modulo; 	//Vector normalizado
		normal_c(1) = normal_c(1)/modulo;
		normal_c(2) = normal_c(2)/modulo;

		normales_caras.push_back(normal_c); //Guardamos la normal de cada cara en el mismo orden que las caras
	}


	//Para cada vertice vamos a recorrer todas las caras y calcular la media de las normales de las adyacentes
	for(int i=0 ; i<vertices.size() ; i++)
	{
		Tupla3f normal_v(0,0,0);
		
		for(int j=0 ; j<triangulos.size() ; j++)
		{
			//Si el numero del vertice de la cara j coincide con el vertice del que queremos calcular la normal
			if( triangulos[j](0)==i  ||  triangulos[j](1)==i || triangulos[j](2)==i )
			{
				normal_v(0) += normales_caras[j](0);
				normal_v(1) += normales_caras[j](1);
				normal_v(2) += normales_caras[j](2);
			}
		}	//Ahora ya tenemos la media de las normales de caras

		modulo = sqrt( normal_v(0)*normal_v(0) + normal_v(1)*normal_v(1) + normal_v(2)*normal_v(2) );
		normal_v(0) = normal_v(0)/modulo; 	//Vector normalizado
		normal_v(1) = normal_v(1)/modulo;
		normal_v(2) = normal_v(2)/modulo;	

		normales_vertices.push_back(normal_v);
	}
}

void ObjMallaIndexada::set_material_basico()
{
	Material m;
	m.m_emision = {0, 0, 0};
	m.m_ambiente =  {0.2, 0.2, 0.2};
	m.m_difuso = {0.5, 0.5, 0.5};
	m.m_especular = {0, 0, 0};
	m.brillo = 0.0;
	materiales.push_back(m);
}

void ObjMallaIndexada::set_material(Tupla3f emision, Tupla3f ambiente, Tupla3f difuso, Tupla3f especular, float brillo)
{
	Material m;
	m.m_emision = emision;
	m.m_ambiente = ambiente;
	m.m_difuso = difuso;
	m.m_especular = especular;
	m.brillo = brillo;
	materiales.push_back(m);
}

ObjMallaIndexada::ObjMallaIndexada()
{		
	set_material( 	{0.0, 0.0 , 0.0} , 
						{0.19125 , 0.0735 , 0.0225} , 
						{0.7038 , 0.27048 , 0.0828} ,
						{0.256777 , 0.137622 , 0.086014} ,
						12.8	 );
	set_material( 	{0.0, 0.0 , 0.0} , 
						{0.0, 0.1 , 0.06} , 
						{0.0, 0.50980392 , 0.50980392} , 
						{0.50196078 , 0.50196078 , 0.50196078} , 
						32.0 ); //Cyan plastic
	set_material(	{0.0 , 0.0 , 0.0} , 
						{0.329412 , 0.223529 , 0.027451} , 
						{0.780392 , 0.568627 , 0.113725} , 
						{0.992157 , 0.941176 , 0.807843} , 
						27.8974 ); //Brass
	material_actual = 0;
}

void ObjMallaIndexada::activar_material(int i)
{
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);	
	glMaterialfv( GL_FRONT, GL_EMISSION, materiales[i].m_emision);
	glMaterialfv( GL_FRONT, GL_AMBIENT, materiales[i].m_ambiente);
	glMaterialfv( GL_FRONT, GL_DIFFUSE, materiales[i].m_difuso);
	glMaterialfv( GL_FRONT, GL_SPECULAR, materiales[i].m_especular);
	glMaterialfv( GL_FRONT, GL_SHININESS, &materiales[i].brillo);
}

void ObjMallaIndexada::activar_imagen()
{
	t_activa = true;
}








