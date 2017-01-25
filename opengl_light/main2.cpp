#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Все просто — не получаем, не возвращаем */
void MyInit( void )
{
  /* Первое, что сделаем, зададим в уже известную нам функцию цвета очистки */
  glClearColor(0,0,0,0);

  /* Задаем модель освещения. Ставим параметр сглаживания для мягких переходов цвета */
  glShadeModel(GL_SMOOTH);

  /* Инициализируем кучу всего. Обо всем по порядку:
   * GL_DEPTH_TEST — проверка глубины, она необходима, чтоб объекты могли перекрывать друг друга
   * GL_NORMALIZE — включить автонормирование всех нормалей
   * GL_AUTO_NORMAL — включить режим автоматической генерации нормалей(позже мы от всего этого откажемся)
   * GL_LIGHTING — собственно, включить освещение
   * GL_LIGHT0 — включить нулевую лампу(для использования n ламп включаем их GL_LIGHTi, где i=0..n-1)
   * GL_COLOR_MATERIAL — включаем выставление параметров материала по его цвету
   */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);

  /* Устанавливаем параметры освещения моделей, разрешая освещать по-разному разные части объектов */
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

}

static double SyncTime;
/*
void Draw( void )
{
  glPushMatrix();

  glColor3d(0,1,0);

  glRotated(30*SyncTime, 0, 1, 0);
  glutWireTorus(2, 5, 50, 50);
  
  glPopMatrix();
}
*/

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	
	glRotatef(10.0, 1.0, 0.0, 0.0);
	glRotatef(40.0, 0.0, 1.0, 0.0);

	//gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	//glColor3ub(25, 200, 55);
/*
	glBegin(GL_TRIANGLES);
		glColor3ub(25, 200, 55);
		glVertex3f(0.0, 0.0, -1.0);
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.5, 0.0);

		glColor3ub(75, 50, 110);
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.5, 0.0);

                glColor3ub(25, 200, 75);
                glVertex3f(0.0, 0.0, 1.0);
                glVertex3f(-1.0, 0.0, 0.0);
                glVertex3f(0.0, 0.5, 0.0);

                glColor3ub(75, 90, 50);
                glVertex3f(-1.0, 0.0, 0.0);
                glVertex3f(0.0, 0.0, -1.0);
                glVertex3f(0.0, 0.5, 0.0);

	glEnd();
*/

//	glPushMatrix();
//	glRotatef(45.0, 0.0, 0.0, 1.0);
//	glPopMatrix();

//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
	
//	GLfloat material_diffuse[] = {1.0, 1.0, 1.0, 1.0};
//	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);


	float Pos[4] = {0.0, 0.0, 1.0, 1};
	float Dir[4] = {0.0, 0.0, 0.0};
	glLightfv(GL_LIGHT0, GL_POSITION, Pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Dir);

        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.4);

	glColor3ub(25, 200, 55);
	glutSolidCube(0.5);
//http://compgraphics.info/OpenGL/lighting/light_sources.php
/*
        glBegin(GL_TRIANGLES);
                glColor3ub(25, 200, 55);
                glVertex3f(0.0, 0.0, -1.0);
                glVertex3f(1.0, 0.0, 0.0);
                glVertex3f(0.0, 0.5, 0.0);

//              glColor3ub(75, 50, 110);
                glVertex3f(1.0, 0.0, 0.0);
                glVertex3f(0.0, 0.0, 1.0);
                glVertex3f(0.0, 0.5, 0.0);

//                glColor3ub(25, 200, 75);
                glVertex3f(0.0, 0.0, 1.0);
                glVertex3f(-1.0, 0.0, 0.0);
                glVertex3f(0.0, 0.5, 0.0);

//                glColor3ub(75, 90, 50);
                glVertex3f(-1.0, 0.0, 0.0);
                glVertex3f(0.0, 0.0, -1.0);
                glVertex3f(0.0, 0.5, 0.0);

        glEnd();
*/


	glPopMatrix();

	glFlush();
	glutSwapBuffers();

  /* Задаем координаты вектора лампочки. В CG вектора принято задавать 4 компонентами x,y,z,w, где x,y,z — координаты вектора в пространстве, а w — делитель, которой позволяет задавать точки удаленные на бесконечность. В рамках нашего курса таких точек мы задавать не будем, а потому делитель логично положим равным 1 */
//  float Pos[4] = {0, 10, -10, 1};

  /* Точка, куда будем светить. Принята давать стандартное расположение в пространстве, т.к. на бесконечность мы обычно не светим :) Специально обособленно определяю, т.к. этот параметр можно проигнорировать, тогда лампочка будет светить во все стороны. */
//  float Dir[4] = {0.0, 0.5, 0.0};
  
  /* Сохраним матрицу преобразований */
//  glPushMatrix();

  /* Проведем движение поворота в зависимости от времени */
//  glRotated(50*SyncTime, 0, 1, 0);

  /* Зададим операцию над лампочкой. fv в конце функции показывают, что параметры будут типа float, и параметром функции будет некий вектор(vector). Функция принимает аргументы:
   * GL_LIGHT0 — имя лампочки
   * GL_POSITION — что будем задавать. В данном случае позицию лампочки.
   * Pos — вектор размещения лампочки */
//  glLightfv(GL_LIGHT0, GL_POSITION, Pos);

  /* Аналогично задаем, если надо, направление свечения */
//  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Dir);
//	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 70.0);


//  ghtfv(GL_LIGHT0, GL_SPOT_DIRECTION, Dir);
/* Восстановим матрицу преобразований */
//  glPopMatrix();

  /* Эта часть кода почти неизменна. Поясню только некоторые аспекты. */
//  glPushMatrix();
//  glColor3d(0,1,0);
  /* Делаем поворот тора на статический угол для лучшего рассмотрения */
  //glRotated(30, 0, 1, 0);
  /* Делаем тор залитым, а не wire, дабы видеть игру светотени */
//  glutSolidTorus(2, 5, 50, 50);
//  glPopMatrix();
} 


void Reshape( int W, int H )
{
  glViewport(0, 0, W, H);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (double)W / H, 1, 500);
  gluLookAt(0, 0, 15, 0, 0, 0, 0, 1, 0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Idle( void )
{
  long Time;
  static long OldTime = -1;

  if(OldTime == -1)
    OldTime = clock();

  Time = clock() - OldTime;

  SyncTime = (double)Time/CLOCKS_PER_SEC;

  glutPostRedisplay();
}

void Display( void )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Draw();

  glutSwapBuffers();
}

void Keyboard( unsigned char Ch, int Mx, int My )
{
  if (Ch == 27)
    exit(0);
}

int main( int argc, char *argv[] )
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(512, 512);
  glutCreateWindow("My window");

 // glClearColor(0,0,0,0);
	MyInit();

//  glutReshapeFunc(Reshape);
  glutDisplayFunc(Display);
//  glutIdleFunc(Idle);
  glutKeyboardFunc(Keyboard);

  glutMainLoop();

  return 0;
}
