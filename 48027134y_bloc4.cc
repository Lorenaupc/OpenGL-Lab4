#include <GL/glut.h>
#include <stdio.h>
#include"model.h"
#include<string>
#include <math.h>
using namespace std;

//Porsche
float girax = 0;
float giray = 0;
float giraz = 0;
float porschex, porschey, porschez = 0;
float rotacio_porsche = -90;

//Tafaner
int tafaner = 0;
float rotacio_tafaner = 0;

//Primera persona
bool caminar = 0;

//Parets visibles
bool parets_visibles = 1;

//Zoom
float zoom = 1.0;
bool shiftActiu = false;

//Walk
float velocitat = 0.6;

//Camera
float angle_original = 45;
int perspectiva = 0;
float dist = 0.0;
float radi_esfera = 0.0;
float dist_original = 0;
float radi_original = 0;
float lastx = 0.0;
float lasty = 0.0;

//Viewport

int ant_x = 0;
int ant_y = 0;

//Llums
int normalscara = 1;
float cantonadax = 5.0;
float cantonaday = 5.0;
bool iluminacio = true;
bool light0 = false;
bool light1 = true;
bool light2 = false;
GLfloat ambient0[] = {0.1, 0.1, 0.1, 1.0};
GLfloat	difuse0[] = {1.0, 1.0, 0.0, 1.0};
GLfloat	specular[] = {0.9, 0.7, 0.7, 1.0};
GLfloat ambient1[] = {0.05, 0.05, 0.05, 1.0};
GLfloat difuse1[] = {1.0, 1.0, 1.0, 1.0};

void pintar_model(){
	
	Model mod;
	mod.load("porsche.obj");

	double xmax,xmin,ymax,ymin,zmax,zmin = 0;

	vector<Vertex> vertex = mod.vertices();
        if (vertex.size() > 2) {
            xmin = xmax = vertex[0];
            ymin = ymax = vertex[1];
            zmin = zmax = vertex[2];
        }
        for (int i = 3; i < vertex.size(); i += 3) {
            if (xmin > vertex[i]) xmin = vertex[i];
            else if (xmax < vertex[i]) xmax = vertex[i];

            if (ymin > vertex[i + 1]) ymin = vertex[i + 1];
            else if (ymax < vertex[i + 1]) ymax = vertex[i + 1];

            if (zmin > vertex[i + 2]) zmin = vertex[i + 2];
            else if (zmax < vertex[i + 2]) zmax = vertex[i + 2];
        }

	glPushMatrix();

		glTranslatef(porschex,porschey,porschez);
		glRotatef(rotacio_porsche,0,1,0);

		float dx = xmax - xmin;
		float dy = ymax - ymin;
		float dz = zmax - zmin;
		float escalat = std::max(std::max(dx, dy), dz);
		glScaled(1.5/escalat, 1.5/escalat, 1.5/escalat);

		dx = -((xmax+xmin)/2);
		dy = -((ymax+ymin)/2);
		dz = -((zmax+zmin)/2);
		dy += ymax;
		glTranslatef(dx,dy,dz);		

		for(int i = 0; i<mod.faces().size();i++){
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,Materials[mod.faces()[i].mat].ambient);
			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,Materials[mod.faces()[i].mat].diffuse);
			glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,Materials[mod.faces()[i].mat].specular);
			glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,Materials[mod.faces()[i].mat].shininess);

			glNormal3dv(mod.faces()[i].normalC);

			glBegin(GL_TRIANGLES);
				bool aplicanormalvertex = !normalscara && !mod.faces()[i].n.empty();
				if (aplicanormalvertex) glNormal3dv(&mod.normals()[mod.faces()[i].n[0]]);
				glVertex3dv(&mod.vertices()[mod.faces()[i].v[0]]);
				if (aplicanormalvertex) glNormal3dv(&mod.normals()[mod.faces()[i].n[1]]);
			    	glVertex3dv(&mod.vertices()[mod.faces()[i].v[1]]);
				if (aplicanormalvertex) glNormal3dv(&mod.normals()[mod.faces()[i].n[2]]);
				glVertex3dv(&mod.vertices()[mod.faces()[i].v[2]]);
			
			glEnd();
		}

	glPopMatrix();

}


void pintar_terra(){

	glPushMatrix();
		glTranslatef(0,0,0);	

		GLfloat ambient[] = {0.0, 0.0, 0.9, 0};
		GLfloat diffuse[] = {0.0, 0.0, 0.3, 0};
		GLfloat specular[] = {0.6, 0.6, 0.6, 0};
		GLfloat shininess = 75;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);		
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

		glNormal3f(0,1,0);

		glBegin(GL_QUADS);
			glVertex3f(5,0,5);
			glVertex3f(-5,0,5);
			glVertex3f(-5,0,-5);
			glVertex3f(5,0,-5);
		glEnd();
	glPopMatrix();

}

void pintar_paret(){

	GLfloat ambient[] = {0.0, 0.15, 0.0, 1.0};
	GLfloat diffuse[] = {0.0, 0.5, 0.0, 1.0};
	GLfloat specular[] = {0.0, 0,0, 0.0, 0.0};
	GLfloat shininess = 0.0;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);		
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	glPushMatrix();
		glTranslatef(2.5,1.5/2,-1.5);
		glScalef(4,1.5,0.2);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-4.9,1.5/2,0);
		glScalef(0.2,1.5,10);
		glutSolidCube(1);
	glPopMatrix();

}


void pintar_ninot(float coord_x, float coord_y, float coord_z){
	

	GLfloat ambientcos[] = {0.7, 0.7, 0.7, 0.0};
	GLfloat diffusecos[] = {0.8, 0.8, 0.8, 0.0};
	GLfloat specularcos[] = {0.9, 0.9, 0.9, 0.0};
	GLfloat shininesscos = 127;

	GLfloat ambientnas[] = {0.3, 0.15, 0, 0.0};
	GLfloat diffusenas[] = {0.6, 0.3, 0, 0.0};
	GLfloat specularnas[] = {0.8, 0.4, 0, 0.0};
	GLfloat shininessnas = 127;

	glPushMatrix();
		glTranslated(coord_x, coord_y+0.4, coord_z);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientcos);		
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffusecos);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularcos);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininesscos);


		glutSolidSphere(0.4, 60, 60);
		glTranslated(0, 0.6, 0);
		glutSolidSphere(0.2, 60, 60);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientnas);		
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffusenas);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularnas);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininessnas);

		glTranslated(0.1, 0, 0);
		glRotated(90, 0, 1, 0);
		glutSolidCone(0.1, 0.2, 20, 20);
	glPopMatrix();

}



void onMouseClick(int button, int state, int x, int y) {

	if (state == GLUT_DOWN) {
		lastx = x;
		lasty = y;
    	}

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		lastx = x;
		lasty = y;
		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT){
			shiftActiu = true;
		}
		else shiftActiu = false;
	}

}

void zoomin(){
	zoom *= 0.95;
}

void zoomout(){
	zoom *= 1.05;
}

void variazoom(float y){
	if (y < lasty){
		zoomin();
	}
	else zoomout();
}

void onMotion(int x, int y){

	if (shiftActiu){
		variazoom(y);		
	}
	else{
		float height = glutGet(GLUT_WINDOW_HEIGHT);
		float width  = glutGet(GLUT_WINDOW_WIDTH);

		girax += (double)((y - lasty)*100/height);
	    	giray += (double)((x - lastx)*100/width);

		lastx = x;
		lasty = y;
		glutPostRedisplay();
	}
}


void aplicacaminar(){

	float aspect_radio = (float)ant_x/(float)ant_y;
	angle_original = asin(radi_esfera/dist);
	if (aspect_radio >= 1.0){
		angle_original *= 0.5*57.8;
		angle_original*=2;
		gluPerspective(angle_original,aspect_radio,1,50);
	}
	else{
		float tangent = tan(angle_original);
		float angle_euler = atan(tangent/aspect_radio)*57.8;	
		gluPerspective(angle_euler*2,aspect_radio,1,50);
	}
}

void camera(){
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspect_radio = (float)ant_x/(float)ant_y;
	if (caminar == 1){
		aplicacaminar();
	}
	
	else if (perspectiva == 1){
		angle_original = asin(radi_esfera/dist);
		if (aspect_radio >= 1.0){
			angle_original *= 57.8;
			angle_original*=2;
			gluPerspective(angle_original*zoom,aspect_radio,1,50);
		}
		else{
			float tangent = tan(angle_original);
			float angle_euler = atan(tangent/aspect_radio)*57.8;	
			gluPerspective(angle_euler*2*zoom,aspect_radio,1,50);
		}
	}
	else if (perspectiva == 0){
		if (aspect_radio >= 1.0){
			glOrtho((-radi_esfera*aspect_radio)*zoom, (radi_esfera*aspect_radio)*zoom, (-radi_esfera)*zoom, (radi_esfera)*zoom, 1,50);

		}
		else{
			glOrtho((-radi_esfera)*zoom, (radi_esfera)*zoom, (-radi_esfera/aspect_radio)*zoom, (radi_esfera/aspect_radio)*zoom, 1, 50);
		}
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}

void calcularcantonada(){

	if (cantonadax == 5.0) {
                if (cantonaday == 5.0) {
                    cantonadax = 5.0; cantonaday = -5.0;
                } 
                else {
                    cantonadax = -5.0; cantonaday = -5.0;
                }
            
        } 
	else {
                if (cantonaday == -5.0) {
                    cantonadax = -5.0; cantonaday = 5.0;
                } 
                else {
                    cantonadax = 5.0; cantonaday = 5.0;
                }
        }

}

void inici_llums(){

	if(light0) {

		glPushMatrix();
			glEnable(GL_LIGHT0);
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, difuse0);
			glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

			GLfloat posicio0[] = {cantonadax, 1, cantonaday, 1};
			glLightfv(GL_LIGHT0,GL_POSITION, posicio0);
		glPopMatrix();
	}  

	else if(light1) {
		
		glPushMatrix();
			glLoadIdentity();
			glEnable(GL_LIGHT1);
			glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, difuse1);
			glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

			GLfloat posicio1[] = {0, 0, radi_esfera*2, 1};
			glLightfv(GL_LIGHT1, GL_POSITION, posicio1);
		glPopMatrix();	
	}

	else if(light2) {

		glPushMatrix();
			glEnable(GL_LIGHT2);
			glLightfv (GL_LIGHT2, GL_AMBIENT, ambient1);
			glLightfv (GL_LIGHT2, GL_DIFFUSE, difuse1);
			glLightfv (GL_LIGHT2, GL_SPECULAR, specular);

			GLfloat posicio2[] = {porschex, 0.4, porschez, 1};
			glLightfv(GL_LIGHT2, GL_POSITION, posicio2);
		glPopMatrix();
	}	

}


void display(void) {

	glClearColor(0.4,0.4,1.0,1.0); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glDisable(GL_LIGHT0); 
	glDisable(GL_LIGHT1); 
	glDisable(GL_LIGHT2);

	if(iluminacio) {
		inici_llums();
    	}

	camera();
	
	if (caminar == 1){
		if (tafaner == 0){
			float obsx = porschex;
			float obsz = porschez;
			glLoadIdentity();
			gluLookAt(obsx,0.75,obsz,obsx+sin(rotacio_porsche*3.14159/180),0.75,obsz+cos(-rotacio_porsche*3.14159/180),0,1,0);
		}
		else{
			float obsx = porschex;
			float obsz = porschez;
			glLoadIdentity();
			gluLookAt(obsx,0.75,obsz,obsx+sin(rotacio_tafaner*3.14159/180),0.75,obsz+cos(-rotacio_tafaner*3.14159/180),0,1,0);
		}
	}

	else {
		glScaled(1,1,1);
		glTranslatef(0,0,-radi_esfera*2);
		glRotated(girax,1,0,0);
		glRotated(giray,0,1,0);
		glRotated(giraz,0,0,1);
		glTranslatef(0,0,0);
	}
	
	pintar_terra();
	pintar_ninot(2.5,0,2.5);
	pintar_ninot(-2.5,0,2.5);
	pintar_ninot(-2.5,0,-2.5);
	pintar_ninot(2.5,0,-2.5);
	pintar_model();
	if (parets_visibles == 1){
		pintar_paret();
	}

	glutSwapBuffers();
}

void reset(){

	zoom = 1.0;
	perspectiva = 0;
	iluminacio = true;
	light0=false;
	light1=true;
	light2=false;
	normalscara = true;

	glutPostRedisplay();

}

void keyboard(unsigned char c, int x, int y){

	if(c == 'h'){
		printf("Ajuda\n");
		printf("Amb el ratolí es pot moure tota la figura\n");
		printf("Si es prem el botó 'p', es canvia de càmera (ortogonal / perspectiva)\n");
		printf("Si es prem el botó 'Esc' es sortirà del programa\n");
		printf("Si es prem el botó 'w' el Porsche caminarà cap endavant\n");
		printf("Si es prem el botó 's' el Porsche caminarà cap endarrere\n");
		printf("Si es prem el botó 'a', el Porsche girarà lleugerament cap a l'esquerre\n");
		printf("Si es prem el botó 'd', el Porsche girarà lleugerament cap a la dreta\n");
		printf("Si es prem el botó 'v', s'activaran les parets\n");
		printf("Si es prem el botó 'z', s'augmentarà la velocitat del cotxe\n");
		printf("Si es prem el botó 'r', es reiniciarà la càmara a ortogonal i sense zoom\n");
		printf("Si es prem el botó 'x', disminuirà la velocitat del cotxe\n");
		printf("Si es prem el botó 'c', la càmara canviarà de tercera a primera persona\n");
		printf("Si es prem el botó 't', s'activarà el mode tafaner NOMÉS si s'ha pres la tecla 'c' per vista de primera persona\n");
		printf("Si es prem el botó Shift, botó esquerra ratolí i s'arrossega el ratolí, s'activarà el zoom i la càmera s'aproparà o s'allunyarà\n");
		printf("Opcions de il·luminació o llums\n");
		printf("Si es prem el botó 'n', es commutarà entre normals per cada i normals per vèrtex\n");
		printf("Si es prem el botó 'i', s'activarà/desectivarà la il·luminació\n");
		printf("Si es prem el botó '0' s'activarà una llum estàtica groguenca que es mourà per les cantonades si premem el botó 'm'\n");
		printf("Si es prem el botó '1' s'activarà una llum estàtica blanca\n");
		printf("Si es prem el botó '2' s'activarà una llum blanca que es mourà amb el cotxe\n");
		
	}

	else if(c == 'r')reset();

	else if(c == 'p'){
		if (perspectiva == 0) perspectiva = 1;
		else perspectiva = 0;
		glutPostRedisplay();
	}
	else if(c == 27){	
		exit(1);
	}
	else if (c == 'a'){
		if (tafaner == 0){
			rotacio_porsche -= -5;
		}
		else{ 
			rotacio_tafaner -= -5;
		}

		glutPostRedisplay();
	}
	else if (c == 'd'){
		if (tafaner == 0){
			rotacio_porsche += -5;
		}
		else{ 
			rotacio_tafaner += -5;
		}

		glutPostRedisplay();
	}
	else if (c == 'w'){
		if (tafaner == 0) {
			porschex += velocitat*sin(rotacio_porsche*3.14159/180);
			porschez += velocitat*cos(rotacio_porsche*3.14159/180);
		}

		glutPostRedisplay();
	}
	else if (c == 's'){
		if (tafaner == 0){
			porschex -= velocitat*sin(rotacio_porsche*3.14159/180);
			porschez -= velocitat*cos(rotacio_porsche*3.14159/180);
		} 
		glutPostRedisplay();
	}
	else if(c == 'z') velocitat += 0.2;
	else if(c == 'x') {
		if (velocitat > 0){
			velocitat -= 0.2;
		}
	}
	else if (c == 'v'){
		if (parets_visibles == 1){
			parets_visibles = 0;
		}
		else parets_visibles = 1;
		glutPostRedisplay();
	}
	else if (c == 'c'){
		if (caminar == 1){
			caminar = 0;
		}
		else caminar = 1;
		glutPostRedisplay();
	}
	else if (c == 't'){
		if (caminar == 1){
			if (tafaner == 1){
				tafaner = 0;
			}
			else {
				tafaner = 1;
				rotacio_tafaner = rotacio_porsche;
			}
		}
		else{
			printf("Per activar o desactivar el mode tafaner has d'estar en mode primera persona (prem tecla c)\n");		
		}
		glutPostRedisplay();
	}
	else if (c == '-'){
		zoomout();
		glutPostRedisplay();
	}
	else if (c == '+'){
		zoomin();
		glutPostRedisplay();	
	}

	else if (c == 'n'){
		if (normalscara == 0) normalscara = 1;
		else normalscara = 0;
		glutPostRedisplay();
	}

	else if(c  == 'm') {
		if(iluminacio and light0) {            
		    calcularcantonada();
		}
		glutPostRedisplay();
    	} 

	else if(c == 'i') {
		iluminacio = !iluminacio;
		glutPostRedisplay();    
   	}
 
	else if(c == '0') {
		light0 = !light0;
		light1 = false;
		light2 = false;

		glutPostRedisplay();   
    	} 

	else if(c == '1') {
		light1 = ! light1;
		light0 = false;
		light2 = false;

		glutPostRedisplay();
    	}
 
	else if(c == '2') {
		light2 = !light2;
		light0 = false;
		light1 = false;

		glutPostRedisplay(); 
    	}
}


void reshape(int x, int y) {

	ant_x = x;
	ant_y = y;
	if (y == 0){
		y = 1;	
	}
	glViewport(0,0,x,y);
	camera();
	
}


void calcular_esfera(){

	float x_max = 5;
	float x_min = -5;
	float y_max = 1.5;
	float y_min = 0;
	float z_max = 5;
	float z_min = -5;

	radi_esfera = sqrt(pow((x_max-x_min),2) + pow((y_max-y_min),2) + pow((z_max-z_min),2));
	dist = radi_esfera;  
	dist_original = dist;
	radi_esfera /= 2;
	radi_original = radi_esfera;
	
}


void initGL(int argc, char **argv){

	glutInit(&argc, argv);
	glutInitWindowSize(600,600);
	glutCreateWindow("INDI Bloc 4");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(onMouseClick);
	glutMotionFunc(onMotion);
	glutKeyboardFunc(keyboard);

	calcular_esfera();

	glutMainLoop();

}

int main(int argc, char **argv) {
	
	initGL(argc, argv);
	return 0;
}
