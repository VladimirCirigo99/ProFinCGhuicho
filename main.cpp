#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
// carpetas
#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "cmodel/CModel.h"

//incluyendo biblioteca de irrklang
#include <irrKlang.h>

//enlazando al dll
#pragma comment(lib, "irrKlang.lib")

//arrancando el motor de sonido
irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();

//agregando fuente de sonido para el audio de fondo
irrklang::ISoundSource* audioFondo = engine->addSoundSourceFromFile("audios/gta.mp3");

//agregando fuente de sonido para el audio de pikachu que es lanzado con tecla
irrklang::ISoundSource* audioPikachu = engine->addSoundSourceFromFile("audios/disparo.mp3");


#if (_MSC_VER >=1900)
#pragma comment (lib, "legacy_stdio_definitions.lib")
#endif

//objetos de textura para skybox
CTexture textSkyboxUnica;
CTexture textSkyboxFrontal;
CTexture textSkyboxAtras;
CTexture textSkyboxIzquierda;
CTexture textSkyboxDerecha;
CTexture textSkyboxArriba;
CTexture cents;
CTexture logo;
CTexture grada;
CTexture grad;
CTexture equi;
CTexture aler;
CTexture llanta;
CTexture cofre;
CTexture eje;
CTexture body;
CTexture pista;
CTexture balon;
CTexture cilin;
CTexture pasto;
CTexture pavi;
CTexture banque;
CTexture bar;
CTexture cafe;
CTexture pan;
CTexture ladri;
CTexture depas;
CTexture edi;
CTexture store;
CTexture book;
CTexture buti;
CTexture ropa;
CTexture ara;
CTexture arbol;
CTexture neg;
CTexture valla;
CTexture piso;
CTexture pue;
CTexture mesa1;
CTexture mesa2;
CTexture television1;
CTexture television2;
CTexture sillon1;
CTexture sillon2;
CTexture rug;
CTexture Refri;
CTexture refri1;
CTexture escalera;
CTexture cuadroGeek;
CTexture cook;


CTexture campoText;	//textura para campo de futbol

//figuras
CFiguras cili;
CFiguras con;
CFiguras cubo;
CFiguras esfe;
CFiguras toru;
CFiguras jugador;
CFiguras mesa;
CFiguras silla;
CFiguras tele;
CFiguras sillonL;
CFiguras alf;
CFiguras refri;
CFiguras stairs;
CFiguras cuadrop;
CFiguras kitchen;

CModel kit;
CModel kit2;
CModel llant;
// Datos de las componentes ambiente, difusa y especular
// de nuestra fuente de luz.
//ambiente reflejada de todas partes - poca 
//difusa reflejada de la fuente de luz - mucha
//especular reflejada en el punto - mucha
GLfloat luzAmbiente[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat luzDifusa[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat luzEspecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };


//sol - direccional - como el último es cero debe ser a donde alumbra, hacia abajo
GLfloat luzPosicionSol[] = { 0.0f, 1.0f, 0.0f, 0.0f };

//foco - puntual - el último es uno, los otros son las coordenadas del foco
GLfloat luzPosicionFoco[] = { 2.0f, 2.0f, 0.0f, 1.0f };

//linterna - focal - lleva posición de la linterna, vector con la dirección a la q apunta y
// ángulo con el cono de apertura de la luz
GLfloat luzPosicionLinterna[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat luzDireccionLinterna[] = { 0.0f, 0.0f, -2.0f };
float anguloLinterna = 30.0f;

//objetos de figura

CFiguras figSkybox;

float transZ = -10.0f;
float transX = 0.0f;
float transY = 0.0f;

float angleX = 0.0f;
float angleY = 0.0f;
DWORD dwFrames = 0;
DWORD dwCurrentTime = 0;
DWORD dwLastUpdateTime = 0;
DWORD dwElapsedTime = 0;
int giraRotaLuisMi = 1.0f;

// Datos de las componentes ambiente, difusa y especular
// del primer material. 
GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };					// Color background
GLfloat mat_specular[] = { 0.882, 0.866, 0.254, 1.0 };				// Specular color
GLfloat mat_shininess[] = { 100.0 };							// 1 to greatest

// animaciones
static GLuint ciudad_display_list;	//Display List for the Enterprise


//NEW// Keyframes
//Variables de dibujo y manipulacion
float posX = 0, posY = 2.5, posZ = -3.5, rotRodIzq = 0;
float giroMonito = 0;
#define MAX_FRAMES 15
int i_max_steps = 400;
int i_curr_steps = 0;

//variables de dibujo y manipulación de balón
float posXBal = 0, posYBal = 0.3, posZBal = 0;

float offset = 0.3f;

float movX = 0.0f,
movY = 0.3f,
Vinicial = 10.0f,
t = 0.0f,
g = 9.81f,
angulo = 45.0f*3.1416 / 180.0;

//modelo carro
float movKit = 0;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotInc;
	float giroMonito;
	float giroMonitoInc;

	// Variables para frames de balón

		//Variables para GUARDAR Key Frames
	float posXBal;		//Variable para PosicionX
	float posYBal;		//Variable para PosicionY
	float posZBal;		//Variable para PosicionZ
	float incXBal;		//Variable para IncrementoX
	float incYBal;		//Variable para IncrementoY
	float incZBal;		//Variable para IncrementoZ

}FRAME;


FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;
int w = 500, h = 500;
int frame = 0, time, timebase = 0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

long int font = (long int)GLUT_BITMAP_HELVETICA_18;
//variables de animacion para el cubo borg
bool banderaAnimacion = false; // con true se sigue
bool g_fanimacion = false;
bool avanza = true;

float movTroncoMovil = 0.0;

//variables de animacion del disparo
bool bande = false; // con true se sigue
bool ava = true;
float movBal = 0.0;

float giraTroncoRueda = 0.0f;
float giro = 0.0f;


void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].giroMonito = giroMonito;

	printf("\nIndice de FRAME", FrameIndex);
	printf("\nPosicion X: %g", KeyFrame[FrameIndex].posX);
	printf("\nPosicion Y: %g", KeyFrame[FrameIndex].posY);
	printf("\nPosicion Z: %g", KeyFrame[FrameIndex].posZ);

	printf("\nGiro Monito: %g", KeyFrame[FrameIndex].giroMonito);

	//información de frame para balón
	KeyFrame[FrameIndex].posXBal = posXBal;
	KeyFrame[FrameIndex].posYBal = posYBal;
	KeyFrame[FrameIndex].posZBal = posZBal;


	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	giroMonito = KeyFrame[0].giroMonito;

	//información de frame para balón
	posXBal = KeyFrame[0].posXBal;
	posYBal = KeyFrame[0].posYBal;
	posZBal = KeyFrame[0].posZBal;


}

void interpolation(void)
{
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	KeyFrame[playIndex].giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;

	//información de frame para balón
	KeyFrame[playIndex].incXBal = (KeyFrame[playIndex + 1].posXBal - KeyFrame[playIndex].posXBal) / i_max_steps;
	KeyFrame[playIndex].incYBal = (KeyFrame[playIndex + 1].posYBal - KeyFrame[playIndex].posYBal) / i_max_steps;
	KeyFrame[playIndex].incZBal = (KeyFrame[playIndex + 1].posZBal - KeyFrame[playIndex].posZBal) / i_max_steps;
}

void inicializar(void) {

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
	glEnable(GL_BLEND);			// Turn Blending On


	glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular);


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	textSkyboxFrontal.LoadTGA("skys/criminal-impact_ft.tga");
	textSkyboxFrontal.BuildGLTexture();
	textSkyboxFrontal.ReleaseImage();

	textSkyboxAtras.LoadTGA("skys/criminal-impact_bk.tga");
	textSkyboxAtras.BuildGLTexture();
	textSkyboxAtras.ReleaseImage();

	textSkyboxIzquierda.LoadTGA("skys/criminal-impact_lf.tga");
	textSkyboxIzquierda.BuildGLTexture();
	textSkyboxIzquierda.ReleaseImage();

	textSkyboxDerecha.LoadTGA("skys/criminal-impact_rt.tga");
	textSkyboxDerecha.BuildGLTexture();
	textSkyboxDerecha.ReleaseImage();

	textSkyboxArriba.LoadTGA("skys/criminal-impact_up.tga");
	textSkyboxArriba.BuildGLTexture();
	textSkyboxArriba.ReleaseImage();


	pista.LoadTGA("imagenes/pista.tga");
	pista.BuildGLTexture();
	pista.ReleaseImage();

	cents.LoadTGA("imagenes/logo.tga");
	cents.BuildGLTexture();
	cents.ReleaseImage();

	ladri.LoadTGA("imagenes/ladri.tga");
	ladri.BuildGLTexture();
	ladri.ReleaseImage();

	logo.LoadTGA("imagenes/logo2.tga");
	logo.BuildGLTexture();
	logo.ReleaseImage();

	arbol.LoadTGA("imagenes/arbol.tga");
	arbol.BuildGLTexture();
	arbol.ReleaseImage();

	neg.LoadTGA("imagenes/neg.tga");
	neg.BuildGLTexture();
	neg.ReleaseImage();

	campoText.LoadTGA("imagenes/campo.tga");
	campoText.BuildGLTexture();
	campoText.ReleaseImage();

	grada.LoadTGA("imagenes/grada.tga");
	grada.BuildGLTexture();
	grada.ReleaseImage();

	balon.LoadTGA("imagenes/balon.tga");
	balon.BuildGLTexture();
	balon.ReleaseImage();

	ara.LoadTGA("imagenes/ara.tga");
	ara.BuildGLTexture();
	ara.ReleaseImage();

	grad.LoadTGA("imagenes/grad.tga");
	grad.BuildGLTexture();
	grad.ReleaseImage();

	cilin.LoadTGA("imagenes/cilin.tga");
	cilin.BuildGLTexture();
	cilin.ReleaseImage();

	body.LoadTGA("imagenes/body.tga");
	body.BuildGLTexture();
	body.ReleaseImage();

	bar.LoadTGA("imagenes/bar.tga");
	bar.BuildGLTexture();
	bar.ReleaseImage();

	cafe.LoadTGA("imagenes/cafe.tga");
	cafe.BuildGLTexture();
	cafe.ReleaseImage();

	pan.LoadTGA("imagenes/pan.tga");
	pan.BuildGLTexture();
	pan.ReleaseImage();

	valla.LoadTGA("imagenes/valla.tga");
	valla.BuildGLTexture();
	valla.ReleaseImage();

	aler.LoadTGA("imagenes/aler.tga");
	aler.BuildGLTexture();
	aler.ReleaseImage();

	llanta.LoadTGA("imagenes/llanta.tga");
	llanta.BuildGLTexture();
	llanta.ReleaseImage();

	eje.LoadTGA("imagenes/eje.tga");
	eje.BuildGLTexture();
	eje.ReleaseImage();

	cofre.LoadTGA("imagenes/cofre.tga");
	cofre.BuildGLTexture();
	cofre.ReleaseImage();

	pavi.LoadTGA("imagenes/pavi.tga");
	pavi.BuildGLTexture();
	pavi.ReleaseImage();

	pasto.LoadTGA("imagenes/pasto.tga");
	pasto.BuildGLTexture();
	pasto.ReleaseImage();

	banque.LoadTGA("imagenes/banque.tga");
	banque.BuildGLTexture();
	banque.ReleaseImage();

	buti.LoadTGA("imagenes/buti.tga");
	buti.BuildGLTexture();
	buti.ReleaseImage();

	depas.LoadTGA("imagenes/depas.tga");
	depas.BuildGLTexture();
	depas.ReleaseImage();

	edi.LoadTGA("imagenes/edi.tga");
	edi.BuildGLTexture();
	edi.ReleaseImage();

	book.LoadTGA("imagenes/book.tga");
	book.BuildGLTexture();
	book.ReleaseImage();

	ropa.LoadTGA("imagenes/ropa.tga");
	ropa.BuildGLTexture();
	ropa.ReleaseImage();

	store.LoadTGA("imagenes/store.tga");
	store.BuildGLTexture();
	store.ReleaseImage();

	pue.LoadTGA("imagenes/pue.tga");
	pue.BuildGLTexture();
	pue.ReleaseImage();

	piso.LoadTGA("imagenes/piso.tga");
	piso.BuildGLTexture();
	piso.ReleaseImage();

	mesa1.LoadTGA("imagenes/mesa1.tga");
	mesa1.BuildGLTexture();
	mesa1.ReleaseImage();

	mesa2.LoadTGA("imagenes/mesa2.tga");
	mesa2.BuildGLTexture();
	mesa2.ReleaseImage();

	television1.LoadTGA("imagenes/tv1.tga");
	television1.BuildGLTexture();
	television1.ReleaseImage();

	television2.LoadTGA("imagenes/tv2.tga");
	television2.BuildGLTexture();
	television2.ReleaseImage();

	sillon1.LoadTGA("imagenes/sillon1.tga");
	sillon1.BuildGLTexture();
	sillon1.ReleaseImage();

	sillon2.LoadTGA("imagenes/sillon2.tga");
	sillon2.BuildGLTexture();
	sillon2.ReleaseImage();

	rug.LoadTGA("imagenes/alfomb.TGA");
	rug.BuildGLTexture();
	rug.ReleaseImage();

	Refri.LoadTGA("imagenes/refri.TGA");
	Refri.BuildGLTexture();
	Refri.ReleaseImage();

	refri1.LoadTGA("imagenes/refri1.TGA");
	refri1.BuildGLTexture();
	refri1.ReleaseImage();

	escalera.LoadTGA("imagenes/escaleras.TGA");
	escalera.BuildGLTexture();
	escalera.ReleaseImage();

	cuadroGeek.LoadTGA("imagenes/goku.TGA");
	cuadroGeek.BuildGLTexture();
	cuadroGeek.ReleaseImage();

	cook.LoadTGA("imagenes/cocina.TGA");
	cook.BuildGLTexture();
	cook.ReleaseImage();


	//Carga de Figuras
	kit._3dsLoad("modelos/nave.3DS");
	kit.LoadTextureImages();
	kit.GLIniTextures();

	kit2._3dsLoad("modelos/kitt.3ds");
	kit2.LoadTextureImages();
	kit2.GLIniTextures();

	llant._3dsLoad("modelos/k_rueda.3ds");
	llant.LoadTextureImages();
	llant.GLIniTextures();


	

	objCamera.Position_Camera(0, 3.0f, 5, 0, 2.5f, 0, 0, 1, 0);


	//NEW Iniciar variables de KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{

		
		KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;
		KeyFrame[i].rotInc = 0;
		KeyFrame[i].giroMonito = 0;
		KeyFrame[i].giroMonitoInc = 0;
		

//FrameIndex++;

		
	}


	//valida si pudo crear el motor de audio
	if (!engine)
	{
		printf("\n No pude crear el motor de audio :(");
		exit(0); //termina ejecución justo aquí
	}

	//reproduce con el 20% del sonido
	audioFondo->setDefaultVolume(0.6f);

	//reproduce el sonido sin detenerse
	engine->play2D(audioFondo, true);
}

void pintaTexto(float x, float y, float z, void *font, char *string)
{

	char *c;     //Almacena los caracteres a escribir
	glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
	//glWindowPos2i(150,100);
	for (c = string; *c != '\0'; c++) //Condicion de fin de cadena
	{
		glutBitmapCharacter(font, *c); //imprime
	}
}

void remodelar(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 300.0);
	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
	glutSwapBuffers();
}

void arbolfondo()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glBindTexture(GL_TEXTURE_2D, arbol.GLindex);

	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_LIGHTING);

	glPopMatrix();
}

void plano()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glBindTexture(GL_TEXTURE_2D, valla.GLindex);

	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glEnable(GL_LIGHTING);

	glPopMatrix();
}

void carro (void) {

		glPushMatrix();

		cili.cilindro(0.5, 2.0, 30.0, body.GLindex);
		glPushMatrix();
		glTranslatef(0,-0.2,0.5);
		cili.cilindro(0.15,0.5,15,cofre.GLindex);
		glTranslatef(0,0,0.1);
		glScalef(2,0.3,0.1);
		cubo.prisma(aler.GLindex, aler.GLindex);
		glPopMatrix();
		//dibuja punta de cono
		glPushMatrix();
		glTranslatef(0.0, 2.0, 0.0);
		con.cono(1.0, 0.5, 30.0, cofre.GLindex);
		glPopMatrix();

		//dibuja eje delantero
		glPushMatrix();
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		glTranslatef(-2.0, -0.75, -0.1);
		cili.cilindro(0.05, 1.5, 10.0, eje.GLindex);
		glPopMatrix();

		//dibuja eje trasero
		glPushMatrix();
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		glTranslatef(-0.5, -0.75, -0.1);
		cili.cilindro(0.05, 1.5, 10.0, eje.GLindex);
		glPopMatrix();
		glPopMatrix();
	}

void Comedor(void) 
{
	glScalef(0.65, 0.65, 0.65);

	glPushMatrix();
	glPushMatrix();
	glTranslatef(3.0, 13.0, -7.0);
	mesa.prisma2(1.0, 8.0, 3.0, mesa1.GLindex);				//crea comedor
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.0, 8.0, -6.0);
	mesa.cilindro(0.25, 5.0, 10.0, mesa1.GLindex);			//crea pata de mesa
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.0, 8.0, -8.0);
	mesa.cilindro(0.25, 5.0, 10.0, mesa1.GLindex);			//crea pata de mesa
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 8.0, -8.0);
	mesa.cilindro(0.25, 5.0, 10.0, mesa1.GLindex);			//crea pata de mesa
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 8.0, -6.0);
	mesa.cilindro(0.25, 5.0, 10.0, mesa1.GLindex);			//crea pata de mesa
	glPopMatrix();
	glPopMatrix();
}

void chair(void)
{
	glScalef(0.65, 0.65, 0.65);

	glPushMatrix();
	glPushMatrix();
	glTranslatef(10.0, 10.0, -6.0);
	silla.prisma2(2.0, 0.25, 0.25, mesa1.GLindex);		//crea pata de la silla
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0, 10.0, -6.0);
	silla.prisma2(2.0, 0.25, 0.25, mesa1.GLindex);		//crea pata de la silla
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0, 10.0, -4.0);
	silla.prisma2(2.0, 0.25, 0.25, mesa1.GLindex);		//crea pata de la silla
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.0, 10.0, -4.0);
	silla.prisma2(2.0, 0.25, 0.25, mesa1.GLindex);		//crea pata de la silla
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.0, 11.0, -5.0);
	silla.prisma2(0.5, 2.3, 2.3, mesa1.GLindex);			//crea asiento silla
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.0, 11.0, -4.0);
	silla.cilindro(0.15, 4.0, 20.0, mesa1.GLindex);		//crea respaldo de la silla
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.0, 11.0, -5.0);
	silla.cilindro(0.15, 4.0, 20.0, mesa1.GLindex);		//crea respaldo de la silla
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.0, 11.0, -6.0);
	silla.cilindro(0.15, 4.0, 20.0, mesa1.GLindex);		//crea respaldo de la silla
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.0, 15.0, -5.0);
	silla.prisma2(1.0, 0.25, 2.8, mesa1.GLindex);		//crea respaldo de la silla
	glPopMatrix();
	glPopMatrix();
}

void chair1(void)
{
	glScalef(0.65, 0.65, 0.65);
	glPushMatrix();

	glPushMatrix();
	glTranslatef(10.0, 10.0, -6.0);
	silla.prisma2(2.0, 0.25, 0.25, mesa1.GLindex);		//crea pata de la silla
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0, 10.0, -6.0);
	silla.prisma2(2.0, 0.25, 0.25, mesa1.GLindex);		//crea pata de la silla
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0, 10.0, -4.0);
	silla.prisma2(2.0, 0.25, 0.25, mesa1.GLindex);		//crea pata de la silla
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.0, 10.0, -4.0);
	silla.prisma2(2.0, 0.25, 0.25, mesa1.GLindex);		//crea pata de la silla
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.0, 11.0, -5.0);
	silla.prisma2(0.5, 2.3, 2.3, mesa1.GLindex);			//crea asiento silla
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.0, 11.0, -4.0);
	silla.cilindro(0.15, 4.0, 20.0, mesa1.GLindex);		//crea respaldo de la silla
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.0, 11.0, -5.0);
	silla.cilindro(0.15, 4.0, 20.0, mesa1.GLindex);		//crea respaldo de la silla
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.0, 11.0, -6.0);
	silla.cilindro(0.15, 4.0, 20.0, mesa1.GLindex);		//crea respaldo de la silla
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.0, 15.0, -5.0);
	silla.prisma2(1.0, 0.25, 2.8, mesa1.GLindex);		//crea respaldo de la silla
	glPopMatrix();

	glPopMatrix();
}

void television(void) 
{
	glScalef(0.65, 0.65, 0.65);
	glPushMatrix();
	glPushMatrix();
	glTranslatef(11.5, 10.0, 3.0);
	tele.prisma2(8.0, 1.0, 7.0, television1.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(11.0, 10.0, 3.0);
	glRotatef(90, 0, 0, 1);
	glRotatef(180, 0, 1, 0);
	tele.prisma2(0.1, 6.0, 6.0, television2.GLindex);
	glPopMatrix();
	glPopMatrix();
}

void sillon(void) 
{
	glScalef(0.65, 0.65, 0.65);
	glPushMatrix();
	glPushMatrix();
	glTranslatef(-1.0, 9.6, 3.0);
	glRotatef(90, 1, 0, 0);
	sillonL.prisma2(8.0, 2.0, 1.5, sillon2.GLindex);			//crea sillon largo
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.0, 9.6, -2.0);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	sillonL.prisma2(8.0, 2.0, 1.5, sillon2.GLindex);			//crea sillon largo
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 10.8, 6.0);
	sillonL.prisma2(1.0, 2.0, 2.0, sillon1.GLindex);			//crea cojin sillon largo
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 10.8, 4.0);
	sillonL.prisma2(1.0, 2.0, 2.0, sillon1.GLindex);			//crea cojin sillon largo
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 10.8, 2.0);
	sillonL.prisma2(1.0, 2.0, 2.0, sillon1.GLindex);			//crea cojin sillon largo
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 10.8, 0.0);
	sillonL.prisma2(1.0, 2.0, 2.0, sillon1.GLindex);			//crea cojin sillon largo
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 10.8, -2.0);
	sillonL.prisma2(1.0, 2.0, 2.0, sillon1.GLindex);			//crea cojin sillon largo
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, 10.8, -2.0);
	sillonL.prisma2(1.0, 2.0, 2.0, sillon1.GLindex);			//crea cojin sillon largo
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0, 10.8, -2.0);
	sillonL.prisma2(1.0, 2.0, 2.0, sillon1.GLindex);			//crea cojin sillon largo
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.0, 10.8, -2.0);
	sillonL.prisma2(1.0, 2.0, 2.0, sillon1.GLindex);			//crea cojin sillon largo
	glPopMatrix();
	glPopMatrix();
}

void mesaCentro(void) 
{
	glScalef(0.65, 0.65, 0.65);
	glPushMatrix();
	glPushMatrix();
	glTranslatef(4.0, 10.0, 4.0);
	mesa.prisma2(0.5, 4.0, 4.0, mesa1.GLindex);				//crea mesa de centro
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.5, 9.0, 5.0);
	mesa.cilindro(0.25, 1.0, 10.0, mesa1.GLindex);			//crea pata de mesa
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.5, 9.0, 3.0);
	mesa.cilindro(0.25, 1.0, 10.0, mesa1.GLindex);			//crea pata de mesa
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5, 9.0, 5.0);
	mesa.cilindro(0.25, 1.0, 10.0, mesa1.GLindex);			//crea pata de mesa
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5, 9.0, 3.0);
	mesa.cilindro(0.25, 1.0, 10.0, mesa1.GLindex);			//crea pata de mesa
	glPopMatrix();
	glPopMatrix();
}

void alfombra(void) 
{
	glScalef(0.65, 0.65, 0.65);
	glPushMatrix();
	glTranslatef(3.0, 8.5, 2.0);
	alf.prisma2(0.1, 12.0, 12.0,rug.GLindex);				//crea alfombra
	glPopMatrix();
}

void refrigerador()
{
	glScalef(0.65, 0.65, 0.65);
	glPushMatrix();

	glPushMatrix();
	glTranslatef(-6.0, 15.0, -10.1);
	refri.prisma2(14.0, 4.0, 4.0, Refri.GLindex);			//crea refrigerador
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6.0, 15.0, -8.1);
	glRotatef(90, 1, 0, 0);
	glRotatef(270, 0, 1, 0);
	refri.prisma2(0.1, 14.0, 4.0, refri1.GLindex);			//crea refrigerador
	glPopMatrix();

	glPopMatrix();
}

void escalerasFalsas()
{
	glScalef(0.65, 0.65, 0.65);
	glPushMatrix();
	glPushMatrix();
	glTranslatef(9.5, 19.0, -12.2);
	glRotatef(90, 1, 0, 0);
	glRotatef(270, 0, 1, 0);
	stairs.prisma2(0.1, 22.0, 5.5, escalera.GLindex);		//crea escaleras 
	glPopMatrix();
	glPopMatrix();
}

void cuadro()
{
	glScalef(0.65, 0.65, 0.65);
	glPushMatrix();
	glPushMatrix();
	glTranslatef(9.5, 19.0, -12.2);
	glRotatef(90, 1, 0, 0);
	glRotatef(270, 0, 1, 0);
	cuadrop.prisma2(0.1, 15.0, 5.5, cuadroGeek.GLindex);		//crea escaleras 
	glPopMatrix();
	glPopMatrix();
}

void cocina() 
{
	glScalef(0.65, 0.65, 0.65);
	glPushMatrix();
	glPushMatrix();
	glTranslatef(-10.25, 11.0, -3.75);
	kitchen.prisma2(6.0, 3.3, 14.0, cook.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10.25, 14.0, -3.75);
	kitchen.prisma2(0.1, 3.3, 14.0, mesa2.GLindex);
	glPopMatrix();
	glPopMatrix();
}

void dibujaTroncoRueda(void)
	{
		glPushMatrix();
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		cili.cilindro(0.3, 0.1, 10.0,llanta.GLindex);
		glPopMatrix();
	}

void monito()
	{
		//glNewList(1, GL_COMPILE);
		glPushMatrix();//Pecho
		glScalef(0.5, 0.5, 0.5);
		cubo.prisma2(2.0, 2.0, 1, cents.GLindex);

		glPushMatrix();//Cuello
		glTranslatef(0, 1.0, 0.0);
		cili.cilindro(0.25, 0.25, 15, 0);
		glPushMatrix();//Cabeza
		glTranslatef(0, 1.0, 0);
		esfe.esfera(0.75, 15, 15, 0);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix(); //Brazo derecho-->
		glTranslatef(1.25, 0.65, 0);
		jugador.esfera(0.5, 12, 12, 0);
		glPushMatrix();
		glTranslatef(0.25, 0, 0);
		glRotatef(-45, 0, 1, 0);
		glTranslatef(0.75, 0, 0);
		jugador.prisma2(0.7, 1.5, 0.7, 0);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix(); //Brazo izquierdo <--
		glTranslatef(-1.25, 0.65, 0);
		jugador.esfera(0.5, 12, 12, 0);
		glPushMatrix();
		glTranslatef(-0.25, 0, 0);
		glRotatef(45, 0, 1, 0);
		glRotatef(25, 0, 0, 1);
		glRotatef(25, 1, 0, 0);
		glTranslatef(-0.75, 0, 0);
		jugador.prisma2(0.7, 1.5, 0.7, 0);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();//Cintura
		glColor3f(0, 0, 1);
		glTranslatef(0, -1.5, 0);
		jugador.prisma2(1, 2, 1, 0);

		glPushMatrix(); //Pie Derecho -->
		glTranslatef(0.75, -0.5, 0);
		glRotatef(-15, 1, 0, 0);
		glTranslatef(0, -0.5, 0);
		jugador.prisma2(1.0, 0.5, 1, 0);

		glPushMatrix();
		glTranslatef(0, -0.5, 0);
		glRotatef(15, 1, 0, 0);
		glTranslatef(0, -0.75, 0);
		jugador.prisma2(1.5, 0.5, 1, 0);

		glPushMatrix();
		glTranslatef(0, -0.75, 0.3);
		jugador.prisma2(0.2, 1.2, 1.5, 0);
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix(); //Pie Izquierdo -->
		glTranslatef(-0.75, -0.5, 0);
		glRotatef(-5, 1, 0, 0);
		glTranslatef(0, -0.5, 0);
		jugador.prisma2(1.0, 0.5, 1, 0);

		glPushMatrix();
		glTranslatef(0, -0.5, 0);
		glRotatef(15 + rotRodIzq, 1, 0, 0);
		glTranslatef(0, -0.75, 0);
		jugador.prisma2(1.5, 0.5, 1, 0);

		glPushMatrix();
		glTranslatef(0, -0.75, 0.3);
		jugador.prisma2(0.2, 1.2, 1.5, 0);
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();


		glPopMatrix();


		glColor3f(1, 1, 1);
		glPopMatrix();
		//glEndList();
	}
	
void monito2()
	{
		//glNewList(1, GL_COMPILE);
		glPushMatrix();//Pecho
		glScalef(0.5, 0.5, 0.5);
		cubo.prisma2(2.0, 2.0, 1, logo.GLindex);

		glPushMatrix();//Cuello
		glTranslatef(0, 1.0, 0.0);
		cili.cilindro(0.25, 0.25, 15, 0);
		glPushMatrix();//Cabeza
		glTranslatef(0, 1.0, 0);
		esfe.esfera(0.75, 15, 15, 0);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix(); //Brazo derecho-->
		glTranslatef(1.25, 0.65, 0);
		jugador.esfera(0.5, 12, 12, 0);
		glPushMatrix();
		glTranslatef(0.25, 0, 0);
		glRotatef(-45, 0, 1, 0);
		glTranslatef(0.75, 0, 0);
		jugador.prisma2(0.7, 1.5, 0.7, 0);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix(); //Brazo izquierdo <--
		glTranslatef(-1.25, 0.65, 0);
		jugador.esfera(0.5, 12, 12, 0);
		glPushMatrix();
		glTranslatef(-0.25, 0, 0);
		glRotatef(45, 0, 1, 0);
		glRotatef(25, 0, 0, 1);
		glRotatef(25, 1, 0, 0);
		glTranslatef(-0.75, 0, 0);
		jugador.prisma2(0.7, 1.5, 0.7, 0);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();//Cintura
		glColor3f(0, 0, 1);
		glTranslatef(0, -1.5, 0);
		jugador.prisma2(1, 2, 1, 0);

		glPushMatrix(); //Pie Derecho -->
		glTranslatef(0.75, -0.5, 0);
		glRotatef(-15, 1, 0, 0);
		glTranslatef(0, -0.5, 0);
		jugador.prisma2(1.0, 0.5, 1, 0);

		glPushMatrix();
		glTranslatef(0, -0.5, 0);
		glRotatef(15, 1, 0, 0);
		glTranslatef(0, -0.75, 0);
		jugador.prisma2(1.5, 0.5, 1, 0);

		glPushMatrix();
		glTranslatef(0, -0.75, 0.3);
		jugador.prisma2(0.2, 1.2, 1.5, 0);
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix(); //Pie Izquierdo -->
		glTranslatef(-0.75, -0.5, 0);
		glRotatef(-5, 1, 0, 0);
		glTranslatef(0, -0.5, 0);
		jugador.prisma2(1.0, 0.5, 1, 0);

		glPushMatrix();
		glTranslatef(0, -0.5, 0);
		glRotatef(15 + rotRodIzq, 1, 0, 0);
		glTranslatef(0, -0.75, 0);
		jugador.prisma2(1.5, 0.5, 1, 0);

		glPushMatrix();
		glTranslatef(0, -0.75, 0.3);
		jugador.prisma2(0.2, 1.2, 1.5, 0);
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();


		glPopMatrix();


		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	
void dibujar(void) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		glLightfv(GL_LIGHT1, GL_POSITION, luzPosicionLinterna);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, luzDireccionLinterna);


		glTranslatef(transX, transY, transZ);

		glRotatef(angleY, 0.0, 1.0, 0.0);
		glRotatef(angleX, 1.0, 0.0, 0.0);



		glRotatef(g_lookupdown, 1.0f, 0, 0);

		gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
			objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
			objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);
		//base gigante
		glPushMatrix();
		glTranslatef(0,-0.5,0);
		glScalef(200.0f,0.1f,200.0f);
		glDisable(GL_LIGHTING);
		cubo.prisma4(pasto.GLindex,0);
		glEnable(GL_LIGHTING);
		glPopMatrix();
		//modelo
		glPushMatrix();
		glTranslatef(0, 30, 0);
		glRotatef(giraRotaLuisMi, 0, 1, 0);
		glScalef(0.3f, 0.3f, 0.3f);
		kit.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

		//carro
		//dibuja troncomovil y coloca troncomovil
		glPushMatrix();
		glTranslatef(0, 0.5, 50);
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		glTranslatef(0.0, movTroncoMovil, 0.0);
		carro();

		//carga llanta trasera izquierda
		glPushMatrix();
		glTranslatef(-0.7, 0.5, -0.1);
		glRotatef(-giraTroncoRueda, 1.0, 0.0, 0.0);
		dibujaTroncoRueda();
		glPopMatrix();

		//carga llanta trasera derecha
		glPushMatrix();
		glTranslatef(0.6, 0.5, -0.1);
		glRotatef(-giraTroncoRueda, 1.0, 0.0, 0.0);
		dibujaTroncoRueda();
		glPopMatrix();

		//carga llanta delantera izquierda
		glPushMatrix();
		glTranslatef(-0.7, 2.0, -0.1);
		glRotatef(-giraTroncoRueda, 1.0, 0.0, 0.0);
		dibujaTroncoRueda();
		glPopMatrix();

		//carga llanta delantera derecha
		glPushMatrix();
		glTranslatef(0.6, 2.0, -0.1);
		glRotatef(-giraTroncoRueda, 1.0, 0.0, 0.0);
		dibujaTroncoRueda();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		//Para que el coche conserve sus colores
		glDisable(GL_COLOR_MATERIAL);
		glTranslatef(-20, 0, -43.3);
		glRotatef(90, 0, 1, 0);
		glScalef(0.3, 0.3, 0.3);

		glTranslatef(0, 4, movKit);
		//Pongo aquí la carroceria del carro
		kit2.GLrender(NULL, _SHADED, 1.0);  //_WIRED O _POINTS

		glPushMatrix();
		glTranslatef(-6.0, -1.0, 7.5);
		glRotatef(giro, 1.0, 0.0, 0.0);
		//glRotatef(rota_llanta, 0.0, 0.0, 1.0);
		llant.GLrender(NULL, _SHADED, 1.0); //llanta delantera derecha 
		glPopMatrix();

		glPushMatrix();
		glTranslatef(6.0, -1.0, 7.5);
		glRotatef(180, 0.0, 1.0, 0.0);
		glRotatef(-giro, 1.0, 0.0, 0.0);
		//glRotatef(rota_llanta, 0.0, 0.0, 1.0);
		llant.GLrender(NULL, _SHADED, 1.0); //llanta delantera izq
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-6.0, -1.0, -9.5);
		glRotatef(giro, 1.0, 0.0, 0.0);
		//glRotatef(rota_llanta, 0.0, 0.0, 1.0);
		llant.GLrender(NULL, _SHADED, 1.0); //llanta atras derecha 
		glPopMatrix();

		glPushMatrix();
		glTranslatef(6.0, -1.0, -9.5);
		glRotatef(180, 0.0, 1.0, 0.0);
		glRotatef(-giro, 1.0, 0.0, 0.0);
		//glRotatef(rota_llanta, 0.0, 0.0, 1.0);
		llant.GLrender(NULL, _SHADED, 1.0); //llanta atras izq 
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glPushMatrix(); //Creamos cielo
		glDisable(GL_LIGHTING);
		glTranslatef(0, 60, 0);
		figSkybox.skyboxH(300.0, 300.0, 300.0, textSkyboxFrontal.GLindex, textSkyboxAtras.GLindex, textSkyboxIzquierda.GLindex, textSkyboxDerecha.GLindex, textSkyboxArriba.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();
		
		//CASA INTERIOR
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-49.0, -5.2, 79.0);
		Comedor();
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-49.5, -5.8, 78.0);
		chair();
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-44.5, -5.8, 71.5);
		glRotatef(180, 0, 1, 0);
		chair1();
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-50.0, 0.0, 68.0);
		television();
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-53.0, -5.6, 68.0);
		sillon();
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-53.0, -5.7, 67.5);
		mesaCentro();
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-53.5, -5.4, 68.0);
		alfombra();
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-54.0, -5.4, 71.0);
		glRotatef(90, 0,1,0);
		refrigerador();
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-51.0, -5.0, 69.0);
		glRotatef(180, 0, 1, 0);
		escalerasFalsas();
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-42.0, -5.0, 69.0);
		glRotatef(180, 0, 1, 0);
		cuadro();
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-54.0, -5.4, 73.0);
		cocina();
		glEnable(GL_LIGHTING);
		glPopMatrix();

		//campo
		glPushMatrix();
		glScalef(54, 0.1, 36);
		glDisable(GL_LIGHTING);
		cubo.prisma(campoText.GLindex, 0);
		glEnable(GL_LIGHTING);

		glPopMatrix();
		glPushMatrix();
		glPushMatrix(); //Grada frontal
		glDisable(GL_LIGHTING);
		glTranslatef(30.0, 3, 21.0);
		glScalef(4.0f, 6.0f, 4.0f);
		cubo.prisma(neg.GLindex, cilin.GLindex);
		glTranslatef(0.0, 0, -10.5);
		cubo.prisma(neg.GLindex, cilin.GLindex);
		glTranslatef(-15.0, 0, 0);
		cubo.prisma(neg.GLindex, cilin.GLindex);
		glTranslatef(0.0, 0, 10.5);
		cubo.prisma(neg.GLindex, cilin.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();
		glPopMatrix();
		//bancas
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(0,0.5,20);
		glScalef(56.0f,1.0f,0.5f);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glTranslatef(0, 1, 1);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glTranslatef(0, 1, 1);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glTranslatef(0, 1, 1);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glTranslatef(0, 1, 1);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glTranslatef(0, 1, 1);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();
		
	//	en frente
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(0, 0.5, -20);
		glScalef(56.0f, 1.0f, 0.5f);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glTranslatef(0, 1, -1);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glTranslatef(0, 1, -1);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glTranslatef(0, 1, -1);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glTranslatef(0, 1, -1);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glTranslatef(0, 1, -1);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		//	derecha
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(29, 0.5, 0);
		glRotatef(90,0,1,0);
		glScalef(38.0f, 1.0f, 0.5f);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glTranslatef(0, 1, 1);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glTranslatef(0, 1, 1);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glTranslatef(0, 1, 1);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glTranslatef(0, 1, 1);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glTranslatef(0, 1, 1);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		//	izquierda
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-29, 0.5, 0);
		glRotatef(90, 0, 1, 0);
		glScalef(38.0f, 1.0f, 0.5f);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glTranslatef(0, 1, -1);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glTranslatef(0, 1, -1);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glTranslatef(0, 1, -1);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glTranslatef(0, 1, -1);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glTranslatef(0, 1, -1);
		cubo.prisma3(neg.GLindex, cilin.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
		glPushMatrix(); //poste1
		glTranslatef(25.0, 0.0, -3.6);
		cili.cilindro(0.1, 3.5, 30.0, 0);
		glPopMatrix();

		glPushMatrix(); //poste2
		glTranslatef(25.0, 0.0, 3.6);
		cili.cilindro(0.1, 3.5, 30.0, 0);
		glPopMatrix();

		glPushMatrix(); //travesaño
		glTranslatef(25.0, 3.5, -3.65);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		cili.cilindro(0.1, 7.32, 30.0, 0);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-50, 0, 0);
		glPushMatrix(); //poste1
		glTranslatef(25.0, 0.0, -3.6);
		cili.cilindro(0.1, 3.5, 30.0, 0);
		glPopMatrix();

		glPushMatrix(); //poste2
		glTranslatef(25.0, 0.0, 3.6);
		cili.cilindro(0.1, 3.5, 30.0, 0);
		glPopMatrix();

		glPushMatrix(); //travesaño
		glTranslatef(25.0, 3.5, -3.65);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		cili.cilindro(0.1, 7.32, 30.0, 0);
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		//JUGADORES 
		glPushMatrix();
		glTranslatef(15, 0, 5);
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(1, 1, 1);
		glCallList(ciudad_display_list);
		glTranslatef(posX, posY, posZ);
		glRotatef(giroMonito, 0, 1, 0);
		monito();
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(15, 0, 0);
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(1, 1, 1);
		glCallList(ciudad_display_list);
		glTranslatef(posX, posY, posZ);
		glRotatef(giroMonito, 0, 1, 0);
		monito();
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(15, 0, -5);
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(1, 1, 1);
		glCallList(ciudad_display_list);
		glTranslatef(posX, posY, posZ);
		glRotatef(giroMonito, 0, 1, 0);
		monito();
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();

		//otro equipo
		glPushMatrix();
		glTranslatef(-15, 0, 0);
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(1, 1, 1);
		glCallList(ciudad_display_list);
		glTranslatef(posX, posY, posZ);
		glRotatef(giroMonito, 0, 1, 0);
		monito2();
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-15, 0, 5);
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(1, 1, 1);
		glCallList(ciudad_display_list);
		glTranslatef(posX, posY, posZ);
		glRotatef(giroMonito, 0, 1, 0);
		monito2();
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-15, 0, -5);
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(1, 1, 1);
		glCallList(ciudad_display_list);
		glTranslatef(posX, posY, posZ);
		glRotatef(giroMonito, 0, 1, 0);
		monito2();
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();
		//balon

		glPushMatrix();
		glTranslatef(posXBal, posYBal, posZBal);
		glTranslatef(movX, movY, posZBal);
		esfe.esfera(0.4, 15, 15, balon.GLindex);
		glPopMatrix();

		//torus

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0.741, 0.768, 0.670);
		//glLightfv(GL_LIGHT1, GL_POSITION, luzPosicionFoco);
		glTranslatef(0, 13, 0);
		toru.torus(35, 30.8, 30, 30);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		//base del torus
		glPushMatrix();
		glTranslatef(33.5, 0, 0);
		cili.cilindro(0.5, 11, 20, cilin.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-33.5, 0, 0);
		cili.cilindro(0.5, 11, 20, cilin.GLindex);

		glPopMatrix();

		//pista
		glPushMatrix();
		glTranslatef(0, 0, 26);
		glScalef(80.0f, 0.1f, 5.0f);
		cubo.prisma5(pista.GLindex, 0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 0, -26);
		glScalef(80.0f, 0.1f, 5.0f);
		cubo.prisma5(pista.GLindex, 0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(37.5, 0, 0);
		glRotatef(90, 0, 1, 0);
		glScalef(48.0f, 0.1f, 5.0f);
		cubo.prisma5(pista.GLindex, 0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-37.5, 0, 0);
		glRotatef(90, 0, 1, 0);
		glScalef(48.0f, 0.1f, 5.0f);
		cubo.prisma5(pista.GLindex, 0);
		glPopMatrix();
	

		//banqueta
		glPushMatrix();
		glTranslatef(0, 0, 37.5);
		glScalef(90.0f, 0.1f, 6.0f);
		cubo.prisma3(banque.GLindex, 0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 0, -37.5);
		glScalef(90.0f, 0.1f, 6.0f);
		cubo.prisma3(banque.GLindex, 0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(47.5, 0, 0);
		glRotatef(90, 0, 1, 0);
		glScalef(81.0f, 0.1f, 5.0f);
		cubo.prisma3(banque.GLindex, 0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-47.5, 0, 0);
		glRotatef(90, 0, 1, 0);
		glScalef(81.0f, 0.1f, 5.0f);
		cubo.prisma3(banque.GLindex, 0);
		glPopMatrix();

	//carretera
		glPushMatrix();
		glTranslatef(0, 0, 47.0);
		glRotatef(90,0,1,0);
		glScalef(13.0f, 0.1f, 126.0f);
		cubo.prisma(pavi.GLindex, 0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 0, -47.0);
		glRotatef(90, 0, 1, 0);
		glScalef(13.0f, 0.1f, 126.0f);
		cubo.prisma(pavi.GLindex, 0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(56.5, 0, 0);
		glScalef(13.0f, 0.1f, 81.0f);
		cubo.prisma(pavi.GLindex, 0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-56.5, 0, 0);
		glScalef(13.0f, 0.1f, 81.0f);
		cubo.prisma(pavi.GLindex, 0);
		glPopMatrix();

		//banqueta del lado de las casas
		glPushMatrix();
		glTranslatef(0, 0, 56.5);
		glScalef(126.0f, 0.1f, 6.0f);
		cubo.prisma3(banque.GLindex, 0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 0, -56.5);
		glScalef(126.0f, 0.1f, 6.0f);
		cubo.prisma3(banque.GLindex, 0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(65.5, 0, 0);
		glRotatef(90, 0, 1, 0);
		glScalef(119.0f, 0.1f, 5.0f);
		cubo.prisma3(banque.GLindex, 0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-65.5, 0, 0);
		glRotatef(90, 0, 1, 0);
		glScalef(119.0f, 0.1f, 5.0f);
		cubo.prisma3(banque.GLindex, 0);
		glPopMatrix();

		//CIUDAD

		glPushMatrix();
		glTranslatef(0,5,-65);
		glRotatef(90,1,0,0);
		glScalef(9.0f,9.0f,9.0f);
		cubo.prisma(cafe.GLindex, ladri.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(15, 5, -65);
		glRotatef(90, 1, 0, 0);
		glScalef(9.0f, 9.0f, 9.0f);
		cubo.prisma(bar.GLindex, ladri.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-25, 5, -65);
		glRotatef(90, 1, 0, 0);
		glScalef(9.0f, 9.0f, 9.0f);
		cubo.prisma(book.GLindex, ladri.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-45, 5, -65);
		glRotatef(90, 1, 0, 0);
		glScalef(9.0f, 9.0f, 9.0f);
		cubo.prisma(buti.GLindex, ladri.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 5, 65);
		glRotatef(90, 1, 0, 0);
		glRotatef(180, 0, 0, 1);
		glScalef(9.0f, 9.0f, 9.0f);
		cubo.prisma(bar.GLindex, ladri.GLindex);
		glPopMatrix();


		glPushMatrix();
		glTranslatef(15, 5, 65);
		glRotatef(90, 1, 0, 0);
		glRotatef(180, 0, 0, 1);
		glScalef(9.0f, 9.0f, 9.0f);
		cubo.prisma(ropa.GLindex, ladri.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-25, 5, 65);
		glRotatef(90, 1, 0, 0);
		glRotatef(180, 0, 0, 1);
		glScalef(9.0f, 9.0f, 9.0f);
		cubo.prisma(pan.GLindex, ladri.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(30, 5, 65);
		glRotatef(90, 1, 0, 0);
		glRotatef(180, 0, 0, 1);
		glScalef(9.0f, 9.0f, 9.0f);
		cubo.prisma(store.GLindex, ladri.GLindex);
		glPopMatrix();

		//edificios grandes
		glPushMatrix();
		glTranslatef(85, 9, 0);
		glRotatef(90, 1, 0, 0);
		glRotatef(90,0,0,1);
		glScalef(59.0f, 31.0f, 19.0f);
		cubo.prisma(depas.GLindex, ladri.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-85, 9, 0);
		glRotatef(90, 1, 0, 0);
		glRotatef(90, 0, 0, 1);
		glRotatef(180,0,0,1);
		glScalef(59.0f, 31.0f, 19.0f);
		cubo.prisma(edi.GLindex, ladri.GLindex);
		glPopMatrix();

		//modelado de la casa

		glPushMatrix();
		//Paredes
		//enfrente
		glPushMatrix();
		glTranslatef(-52,7,64);
		glScalef(20.0f,15.0f,0.1f);
		cubo.prisma(0, pue.GLindex);
		//atras
		glTranslatef(0, 0, 130.0);
		cubo.prisma(ladri.GLindex, ladri.GLindex);
		glPopMatrix();
		//der
		glPushMatrix();
		glTranslatef(-42, 7, 70.5);
		glRotatef(-90,0,1,0);
		glScalef(13.0f,15.0f,0.1f);
		cubo.prisma(ladri.GLindex,ladri.GLindex);
		//izq
		glTranslatef(0, 0, 200);
		cubo.prisma(ladri.GLindex, ladri.GLindex);
		glPopMatrix();
		//piso
		glPushMatrix();
		glTranslatef(-52, 0.1, 70.5);
		glScalef(20.0f,0.1f,13.0f);
		cubo.prisma(piso.GLindex, ladri.GLindex);
		//arriba
		glTranslatef(0, 145, 0);
		cubo.prisma(ladri.GLindex, ladri.GLindex);

		glPopMatrix();
		glPopMatrix();

		//arboles
		glPushMatrix();
		glTranslatef(62,-0.5,-65);
		arbolfondo();
		glTranslatef(2, 0, -15);
		arbolfondo();
		glTranslatef(-85, 0, -10);
		arbolfondo();
		glTranslatef(-35, 0, 0);
		arbolfondo();
		glTranslatef(-15, 0, 10);
		arbolfondo();
		glTranslatef(-7, 0, 10);
		arbolfondo();
		glTranslatef(0, 0, 15);
		arbolfondo();
		glTranslatef(2, 0, 90);
		arbolfondo();
		glTranslatef(0, 0, 30);
		arbolfondo();
		glTranslatef(0, 0, 30);
		arbolfondo();
		glTranslatef(40, 0, 0);
		arbolfondo();
		glTranslatef(40, 0, 0);
		arbolfondo();
		glTranslatef(50, 0, 0);
		arbolfondo();
		glTranslatef(30, 0, 0);
		arbolfondo();
		glTranslatef(0, 0, -40);
		arbolfondo();
		glPopMatrix();

		//planos vallas
		glPushMatrix();
		glTranslatef(0,0,32);
		glScalef(0.2f,0.2f,0.2f);
		plano();
		glTranslatef(0, 0, 5);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glTranslatef(0, 0, -20);
		plano();
		glTranslatef(0, 0, -20);
		plano();
		glTranslatef(0, 0, -20);
		plano();
		glTranslatef(0, 0, -20);
		plano();
		glTranslatef(0, 0, -20);
		plano();
		glTranslatef(0, 0, -20);
		plano();
		glTranslatef(0, 0, -20);
		plano();
		glTranslatef(0, 0, -20);
		plano();
		glTranslatef(0, 0, -20);
		plano();
		glTranslatef(0, 0, -20);
		plano();
		glTranslatef(0, 0, -20);
		plano();
		glTranslatef(0, 0, -20);
		plano();
		glTranslatef(0, 0, -20);
		plano();
		glTranslatef(0, 0, -20);
		plano();
		glTranslatef(0, 0, -20);
		plano();
		glTranslatef(0, 0, -20);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(-20, 0, 0);
		plano();
		glTranslatef(0, 0, 20);
		plano();
		glTranslatef(0, 0, 20);
		plano();
		glTranslatef(0, 0, 20);
		plano();
		glTranslatef(0, 0, 20);
		plano();
		glTranslatef(0, 0, 20);
		plano();
		glTranslatef(0, 0, 20);
		plano();
		glTranslatef(0, 0, 20);
		plano();
		glTranslatef(0, 0, 20);
		plano();
		glTranslatef(0, 0, 20);
		plano();
		glTranslatef(0, 0, 20);
		plano();
		glTranslatef(0, 0, 20);
		plano();
		glTranslatef(0, 0, 20);
		plano();
		glTranslatef(0, 0, 20);
		plano();
		glTranslatef(0, 0, 20);
		plano();
		glTranslatef(0, 0, 20);
		plano();
		glTranslatef(0, 0, 20);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glTranslatef(20, 0, 0);
		plano();
		glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 1.0, 1.0);
	pintaTexto(-20, 14.0, -14.0, (void *)font, "PROYECTO CG");
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glutSwapBuffers();
}

void anima(void)
{


	//Movimiento del Carro
	if (play)
	{

		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();

			}
		}
		else
		{
			//Draw animation
			posX += KeyFrame[playIndex].incX;
			posY += KeyFrame[playIndex].incY;
			posZ += KeyFrame[playIndex].incZ;

			giroMonito += KeyFrame[playIndex].giroMonitoInc;

			i_curr_steps++;
		}
	}

	dwCurrentTime = GetTickCount(); // Even better to use timeGetTime()
	dwElapsedTime = dwCurrentTime - dwLastUpdateTime;
	if (dwElapsedTime >= 30)
	{
		giraRotaLuisMi = (giraRotaLuisMi - 1) % 360;
		dwLastUpdateTime = dwCurrentTime;
	}
	// ANIMACION DE DISPARO
	if (bande) //si es verdadero
	{
		if (ava) //si es verdadero
		{
			movBal += 0.30;
			if (movBal > 10.0)
				ava = false;
		}
		else {
			movBal -= 0.30;

			movBal = 0;
			// aparece en el punto de origen
			ava = false;
		}
	}
	glutPostRedisplay();
}

void teclado(unsigned char key, int x, int y)  // Create Keyboard Function
{

	switch (key) {
	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED + 0.2);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.2));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.4);
		break;

	case 'k':		//
	case 'K':
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}

		break;

	case 'l':
	case 'L':
		if (play == false && (FrameIndex > 1))
		{
			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}

		break;

	case 'y':
	case 'Y':
		posZ++;
		printf("%f \n", posZ);
		break;

	case 'g':
	case 'G':
		posX--;
		printf("%f \n", posX);
		break;

	case 'h':
	case 'H':
		posZ--;
		printf("%f \n", posZ);
		break;

	case 'j':
	case 'J':
		posX++;
		printf("%f \n", posX);
		break;

	case 'o':
		giroMonito++;
		break;

	case 'O':
		giroMonito--;
		break;

	case '1':
		bande = !bande;
		ava = true;
		//engine->play2D(audioPikachu);
		break;

	case ' ':		//activa o desactiva animación
		banderaAnimacion = !banderaAnimacion;


		break;
	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}

	glutPostRedisplay();

	glutPostRedisplay();
}

void teclasFlechas(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

	case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

	case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View(CAMERASPEED);
		break;
	case GLUT_KEY_F1:
		//camara de casa modelada
		objCamera.Position_Camera(-50.0, 7.0f, 68, 10, 2.5f, 0, 0, 1, 0);
		break;
	case GLUT_KEY_F2:
		//camara de transmision partido
		objCamera.Position_Camera(0, 20.0, 23.0, 0, 2.5f, 0, 0, 1, 0);
		break;
	case GLUT_KEY_F3:
		//camara tiro de esquina
		objCamera.Position_Camera(22.0, 2.5f, 10.0, 20, 2.5f, 0, 0, 1, 0);
		break;
	case GLUT_KEY_F4:
		//Cámara desde el centro hacia la porteria
		objCamera.Position_Camera(5, 2.5f, 0, 20, 2.5f, 0, 0, 1, 0);
		break;
	case GLUT_KEY_F5:
		//camara de auto modelado
		objCamera.Position_Camera(0, 3.0f, 48, 0, 2.5f, 0, 0, 1, 0);
		break;
	case GLUT_KEY_F6:
		//camara de auto modelo kit
		objCamera.Position_Camera(-20.0, 3.0f, -45.0, 0, 2.5f, 0, 0, 1, 0);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void menuKeyFrame(int id)
{
	switch (id)
	{
	case 0:	//Save KeyFrame
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
		break;

	case 1:	//Play animation
		if (play == false && FrameIndex > 1)
		{

			resetElements();
			//First Interpolation
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;


	}
}

void menu(int id)
{

}


int main(int argc, char *argv[]) {
	int submenu;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 500);
	glutInitWindowPosition(300, 0);
	glutCreateWindow("Proyecto final");
	inicializar();
	glutDisplayFunc(dibujar);
	glutReshapeFunc(remodelar);
	glutKeyboardFunc(teclado);
	glutSpecialFunc(teclasFlechas);
	glutIdleFunc(anima);
	submenu = glutCreateMenu(menuKeyFrame);
	glutAddMenuEntry("Guardar KeyFrame", 0);
	glutAddMenuEntry("Reproducir Animacion", 1);
	glutCreateMenu(menu);
	glutAddSubMenu("Animacion Monito y balon", submenu);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}