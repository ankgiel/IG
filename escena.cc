//Autor: ANGELA POZO MATEOS	

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

using namespace std;
//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
	Front_plane = 0.1;
	Back_plane = 2000.0;
	Observer_distance = 2.0;
	Observer_angle_x  = 0.0 ;
   Observer_angle_y  = 0.0 ;

   ejes.changeAxisSize( 5000 );
	
	

    // crear los objetos de las prácticas: Mallas o Jerárquicos....
   cubo = new Cubo();
	tetra = new Tetra();
	yunque = new Yunque();
	cilindro = new Cilindro(3, 50);
	cono = new Cono(6, 50);
	esfera = new Esfera(40, 40);
	cuenco = new Cuenco(20, 16);
	ply_1 = new ObjRevolucion("peon.ply");
   ply_2 = new ObjPLY("beethoven.ply");
   demoledora = new ObjJerarquico();
	cout << "Todos los obj creados" << endl;
   // .....

   num_objetos = 11; // se usa al pulsar la tecla 'O' (rotar objeto actual)

	//Creación de luces
	//Luz que rotará alrededor del objeto
	Tupla4f c_ambiente = {1.0, 0.0, 0.0, 1.0};
	Tupla4f c_difuso = {1.0, 0.0, 1.0, 1.0};
	Tupla4f c_especular = {1.0, 0.0, 1.0, 1.0};
	Tupla4f posicion  = {5.0, 0.0, 0.0, 1.0};
	luz_posicional = new Luz(c_ambiente, c_difuso, c_especular, posicion, GL_LIGHT1);	///Light1

	//Luz en el infinito	
	c_ambiente = {0.0, 0.0, 0.0, 1.0};
	c_difuso = {1.0, 1.0, 1.0, 1.0};
	c_especular = {1.0, 1.0, 1.0, 1.0};
	posicion = {0.0, 0.0, 15.0, 0.0};
	luz_direccional = new Luz(c_ambiente, c_difuso, c_especular, posicion, GL_LIGHT0); //Light0
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	using namespace std ;	
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer
	
	cuadro = new ChessBoard("./img/sorolla.jpg");
	redimensionar( UI_window_width, UI_window_height );
	
	cout << " LAS TECLAS DE CONTROL SON D:cambiar Inmediato/Diferido   O: cambiar objeto actual    M:cambiar modo de dibujo " << endl;
}


void Escena::iniciarAnimacionLuz(){
	using namespace std ;
   using namespace std::chrono ;
	animacion_luz = true;
	cout << "Se inicia animacion LUCES" << endl;
   ultima_actu = steady_clock::now() ;
}

void Escena::pararAnimacionLuz()
{
	animacion_luz = false;
}

void Escena::actualizarEstado()
{
	if(animacion_luz){
		//using namespace std ;
		using namespace std::chrono ;

		// calcular el tiempo transcurrido desde la ultima actualización o
		// desde que se invocó a 'inicio_animaciones' (delta_t_s)
		const Instante   ahora      = steady_clock::now() ;
		const Duracion_s duracion_s = ahora - ultima_actu ;
		const float      delta_t_s  = duracion_s.count();

		// actualizar instante de la última actualización de estado
		ultima_actu = ahora ;
		angulo_luz += delta_t_s*50;
	}
}

// **************************************************************************
// Funcion que dibuja el objeto activo actual, usando su método 'draw'
// (llamada desde Escena::dibujar)
// ***************************************************************************

void Escena::dibujar_objeto_actual()
{
   using namespace std ;

	
	glLineWidth(2);
	glPointSize(4);
   // (1) configurar OpenGL para el modo actual (puntos/lineas/sólido)
	switch( modo )
	{
		case 0:
			glPolygonMode(GL_FRONT, GL_POINT);	
			break;
		case 1:
			glPolygonMode(GL_FRONT, GL_LINE);
			break;
		case 2:
			glPolygonMode(GL_FRONT, GL_FILL);
			break;
		case 3:
			glPolygonMode(GL_FRONT, GL_FILL);
			break;
	}


   switch( objeto_actual )
   {
      case 0:
         if( demoledora != nullptr ) demoledora->draw( modo_draw, modo==3, material );
			break;
      case 1:
			if ( tetra != nullptr ) tetra->draw( modo_draw , modo==3, material ) ;
			break;
		case 2:
			if ( cilindro != nullptr ) cilindro->draw( modo_draw, modo==3, material );
			break;
		case 3:
			if( cono != nullptr ) cono->draw( modo_draw, modo==3, material );
			break;
		case 4: 
			if( esfera != nullptr ) esfera->draw( modo_draw, modo==3, material );
			break;
		case 5:
			if( ply_1 != nullptr ) ply_1->draw( modo_draw, modo==3, material );
			break;
		case 6:
			if( ply_2 != nullptr ) ply_2->draw( modo_draw, modo==3, material );
			break;
		case 7:
			if ( cubo != nullptr )cubo->draw( modo_draw, modo==3, material ) ;
         break ;
		case 8:
			if ( yunque != nullptr ) yunque->draw( modo_draw, modo==3, material );
			break;
		case 9:
			if( cuenco != nullptr ) cuenco->draw(modo_draw , modo==3, material);
			break;
		case 10: 
			if( cuadro != nullptr ) cuadro->draw(modo_draw , modo==3 , material);			
			break;

      default:
         cout << "draw_object: el número de objeto actual (" << objeto_actual << ") es incorrecto." << endl ;
         break ;
   }
}


void Escena::dibujar_luces(){
	if( luz_posicional != nullptr ) luz_posicional->draw(	{1.0, 0.0, 0.0, 1.0}, {1.0, 0.0, 1.0, 1.0}, {1.0, 0.0, 1.0, 1.0}, {5.0, 0.0, 0.0, 1.0}, angulo_luz);
	if( luz_direccional != nullptr ) luz_direccional->draw( {0.0, 0.0, 0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {0.0, 0.0, 15.0, 0.0}, 0.0);
}

void activar_luces(){
	glEnable(GL_LIGHTING);
}

void desactivar_luces(){
	glDisable(GL_LIGHTING);
}

void interruptor_luz(GLenum i){
	if( !glIsEnabled(i) )
		glEnable(i);
	else
		glDisable(i);
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glEnable( GL_NORMALIZE );	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();

	bool luz_estaba_encendida = glIsEnabled(GL_LIGHTING);
	if( luz_estaba_encendida )
		glDisable( GL_LIGHTING );
   ejes.draw();
	if( luz_estaba_encendida )
		glEnable( GL_LIGHTING );

	dibujar_luces();	
	
	dibujar_objeto_actual();
}


void Escena::animar_escena()
{
	if( demoledora!= nullptr )
		demoledora->actualizarEstado();
	if( luz_posicional != nullptr && glIsEnabled(GL_LIGHTING) )
		actualizarEstado();
}
//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'  " ;

   switch( toupper(tecla) )
   {
      /*case 'Q' :
         // salir
         return true ;
         break ;*/
      case 'O' :
         // activar siguiente objeto
         objeto_actual = (objeto_actual+1) % num_objetos ;
         cout << "objeto actual == " << objeto_actual << endl ;
         break ;
		case 'N' :
			//Cambiar de modo inmediato a modo diferido
			modo_draw = (modo_draw+1) % 2;
			cout << "Nuevo modo_draw (inmediato|diferido): " << modo_draw << endl;
			break;		
		case 'M' :
			modo = (modo+1) % 4;
			cout << "Nuevo modo (puntos/lineas/solido/ajedrez): " << modo << endl; 
			break;
		case '7' :
			objeto_actual = 0 ; 
			cout << "Objeto Actual == Jerárquico" << endl;
			break;
		case 'Q' :		//Aumenta primer grado libertad. Gira cuerda en sentido horario		
			demoledora->incrementaParam(0);
			break;
		case 'W' : 		//Disminuye el primer grado de libertad. Gira cuerda en antihorario
			demoledora->decrementaParam(0);			
			break;
		case 'S' :		
			demoledora->incrementaParam(1);
			break;
		case 'D' : 	
			demoledora->decrementaParam(1);			
			break; 
		case 'Z' :	
			demoledora->incrementaParam(2);
			break;
		case 'X' : 	
			demoledora->decrementaParam(2);			
			break; 
		case 'E' :		
			demoledora->aceleraParam(0);
			break;
		case 'R' : 	
			demoledora->deceleraParam(0);			
			break;
		case 'T' :		
			demoledora->aceleraParam(1);
			break;
		case 'Y' : 		
			demoledora->deceleraParam(1);			
			break; 		
		case 'U' :
			demoledora->aceleraParam(2);
			break;
		case 'I' : 		
			demoledora->deceleraParam(2);			
			break; 
		case 'A' : 
			demoledora->inicioAnimaciones();
			cout << "Iniciando animacion demoledora" << endl;
			break;
		case 'P' : 
			demoledora->pararAnimaciones();
			cout << "Parando animacion demoledora" << endl;
			break;
		case 'K' : 
			iniciarAnimacionLuz();
			cout << "Iniciando animacion luz" << endl;
			break;
		case 'L' : 
			pararAnimacionLuz();
			cout << "Parando animacion luz" << endl;
			break;
		case 'H':
			glShadeModel(GL_FLAT);
			cout << "Modo flat activado" <<endl;
			break;
		case 'J':
			glShadeModel(GL_SMOOTH);
			cout << "Modo flat activado" <<endl;
			break;
		case 'C':
			activar_luces();
			cout << "Activando luces" << endl;
			break;
		case 'V':
			desactivar_luces();
			cout << "Desactivando luces" << endl;
			break;
		case 'F':
			interruptor_luz(GL_LIGHT0);
			cout << "Interruptor luz infinito" << endl;
			break;
		case 'G':
			interruptor_luz(GL_LIGHT1);
			cout << "Interruptor luz posicional" << endl;
			break;
		case 'B':
			material = (material+1) % 3;
			cout << "Material actual: " << material << endl;
			break;
		case '.':
			cuadro->activar_imagen();
			cout << "Activando cuadro" << endl;
			break;

			
   }
   return false ;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wy = 0.84*Front_plane,
	wx = ratio_xy*wy ;
	glFrustum( -wx, +wx, -wy, +wy, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width = newWidth;
	Height = newHeight;
	change_projection( float(Width)/float(Height) );
	glViewport( 0, 0, Width, Height );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_x, 1.0 ,0.0, 0.0 );
	glRotatef( Observer_angle_y, 0.0, 1.0, 0.0 );
}
