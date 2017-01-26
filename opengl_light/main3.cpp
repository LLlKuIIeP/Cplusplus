#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>

// угол поворота камеры
float angle=0.0;
// координаты вектора направления движения камеры
float lx=0.0f,lz=-1.0f;
// XZ позиция камеры
float x=0.0f,z=5.0f;


void drawSnowMan() {
 
	glColor3f(1.0f, 1.0f, 1.0f);
 
// тело снеговика
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);
 
// голова снеговика
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);
// глаза снеговика
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();
// нос снеговика
	glColor3f(1.0f, 0.5f , 0.5f);
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f,0.5f,10,2);
}



void renderScene(void) {
	// Очистка буфера цвета и глубины.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// обнулить трансформацию
	glLoadIdentity();
	// установить камеру
	gluLookAt(   x, 1.0f,     z,
		  x+lx, 1.0f,  z+lz,
		  0.0f, 1.0f,  0.0f );
        // нарисуем "землю"
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS); // полигон с коондинатами
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
        // Нарисуем 64 снеговика
	for(int i = -4; i < 4; i++)
		for(int j=-4; j < 4; j++) {
			glPushMatrix();
			glTranslatef(i*5.0, 0, j * 5.0);
			drawSnowMan();
			glPopMatrix();
		}
	glutSwapBuffers();
}


void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
}


void processSpecialKeys(int key, int xx, int yy) {
	float fraction = 0.1f;
	switch (key) {
		case GLUT_KEY_LEFT :
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_RIGHT :
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_UP :
			x += lx * fraction;
			z += lz * fraction;
			break;
		case GLUT_KEY_DOWN :
			x -= lx * fraction;
			z -= lz * fraction;
			break;
	}
	glutPostRedisplay();
}

void changeSize(int w, int h) {
	// предотвращение деления на ноль
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;
	// используем матрицу проекции
	glMatrixMode(GL_PROJECTION);
	// обнуляем матрицу
	glLoadIdentity();
	// установить параметры вьюпорта
	glViewport(0, 0, w, h);
	// установить корректную перспективу
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	// вернуться к матрице проекции
	glMatrixMode(GL_MODELVIEW);
}



int main(int argc, char **argv) {
	// Инициализация и создание окна
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(400,400);
	glutCreateWindow("Урок 5");
 
	// Регистрация
	glutDisplayFunc(renderScene);
//	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
 
	// Инициализация OpenGL функции теста
	glEnable(GL_DEPTH_TEST);
 
	// Основной цикл GLUT
	glutMainLoop();
 
	return 1;
}

//http://grafika.me/node/129
