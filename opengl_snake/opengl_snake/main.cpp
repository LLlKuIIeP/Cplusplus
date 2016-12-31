#include <GL\freeglut.h>
#include <time.h>
#include <memory>

#define WIDTH 80
#define HEIGHT 45

class Block {
public:
	int x, y;
	explicit Block(int x_ = -1, int y_ = -1) :x(x_), y(y_) {}

	void drow(bool);
};
std::unique_ptr<Block[]> blocks( std::make_unique<Block[]>(WIDTH * HEIGHT) );


class Food {
public:
	int x, y;
	explicit Food(int x_ = -1, int y_ = -1) :x(x_), y(y_) {}

	void draw_food();
	void spawn();
} food;

class Game {
public:
	int delay; // задержка в мс
	float scale; //коэфициент маштабирования внутри окна
	int win_scale; //коэфициент маштабирования окна
	int win_pos_x, win_pos_y; //положение окна на экране
	int start_pos_x, start_pos_y; //стартовая позиция змейки на экране
	int start_size; //стартовый размер змейки

	Game();

	void init();
} settings;


class Snake {
public:
	int direction; // в какую сторону движется змейка
	int size; //размер змейки
	bool turn; //флаг пворота змейки, чтобы два раза нельзя было повернуть
	Snake();

	void DrawSnake();
	void move();
	void cut();
	void eat();

} player;

Game::Game() {
	start_size = 3;
	start_pos_x = (int)(WIDTH / 2);
	start_pos_y = (int)(HEIGHT / 2);
	delay = 100;
	scale = 1;
	win_scale = 10;
	win_pos_x = 200;
	win_pos_y = 0;
}

//начальные координаты змейки
void Game::init() {
	blocks[0].x = start_pos_x;
	blocks[0].y = start_pos_y;
}

Snake::Snake() {
	turn = false; //
	size = settings.start_size;
	direction = GLUT_KEY_UP;
}


//прорисовка змейки
void Snake::DrawSnake() {
	for (auto i = 0; i < size; ++i) {
		if (i) {
			blocks[i].drow(false);
		}
		else {
			blocks[i].drow(true);
		}
	}
}

//перемещение змейки
void Snake::move() {
	for (auto i = size; i > 0; --i) {
		blocks[i].x = blocks[i - 1].x;
		blocks[i].y = blocks[i - 1].y;
	}

	//события по кнопкам
	switch (direction) {
	case GLUT_KEY_UP:
		blocks[0].y++;
		break;
	case GLUT_KEY_DOWN:
		blocks[0].y--;
		break;
	case GLUT_KEY_LEFT:
		blocks[0].x--;
		break;
	case GLUT_KEY_RIGHT:
		blocks[0].x++;
		break;
	default:
		break;
	}

	//выход змейки за поля окна
	if (blocks[0].x < 0) {
		blocks[0].x += WIDTH;
	}
	if (blocks[0].x >= WIDTH) {
		blocks[0].x -= WIDTH;
	}
	if (blocks[0].y < 0) {
		blocks[0].y += HEIGHT;
	}
	if (blocks[0].y >= HEIGHT) {
		blocks[0].y -= HEIGHT;
	}
}

//откусывает себе хвост
void Snake::cut() {
	for (auto i = 3; i < size; ++i) {
		if (blocks[i].x == blocks[0].x && blocks[i].y == blocks[0].y) {
			size = i;
			break;
		}
	}
}

//змейка кушает
void Snake::eat() {
	if (blocks[0].x == food.x && blocks[0].y == food.y) {
		++size;
		food.spawn();
	}
}


//отвечает за прорисовку
// прорисовка идет через квадраты, задать квадрат можно используя 4-ре вершины
void Block::drow(bool head) {
	if (head) {
		glColor3f(0.745098, 0.745098, 0.745098); // цвет головы змейки
	}
	else {
		glColor3f(1, 1, 1); // цвет остальной змейки
	}
	glVertex2f(x * settings.scale, y * settings.scale); //
	glVertex2f(x * settings.scale + settings.scale, y * settings.scale);
	glVertex2f(x * settings.scale + settings.scale, y * settings.scale + settings.scale);
	glVertex2f(x * settings.scale, y * settings.scale + settings.scale);
}

void Food::draw_food() {
	glColor3f(0, 0, 1); // цвет еды
	glVertex2f(x * settings.scale, y * settings.scale); //
	glVertex2f(x * settings.scale + settings.scale, y * settings.scale);
	glVertex2f(x * settings.scale + settings.scale, y * settings.scale + settings.scale);
	glVertex2f(x * settings.scale, y * settings.scale + settings.scale);
}


void Food::spawn() {
	// рандомные координаты спавна еды по оси x и y, не выходищие за края поля
	x = (rand() % WIDTH);
	y = (rand() % HEIGHT);

	// проверка, что еда не спавнится на змейке
	for (auto i = 0; i < player.size; ++i) {
		if (x == blocks[i].x && y == blocks[i].y) {
			spawn(); //рекурсивный вызов самой себя, если еда появилась на змейке
		}
	}
}


/*==============================================
	Обработка событий клавиатуры
===============================================*/

void key_up() {
	if (player.direction != GLUT_KEY_DOWN && player.turn) {
		player.direction = GLUT_KEY_UP;
	}

	player.turn = false;
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 27: { // Esc
			exit(0);
		}
		case 'w': { // w
			key_up();
			break;
		}


		default:
			break;
	}
}


void spec_keyboard(int key, int x, int y) {

	switch(key) {
		case GLUT_KEY_UP: {
				if(player.direction != GLUT_KEY_DOWN && player.turn) {
					player.direction = GLUT_KEY_UP;
				}

				player.turn = false;
				break;
		}
		case (int)'w': {
			if (player.direction != GLUT_KEY_DOWN && player.turn) {
				player.direction = GLUT_KEY_UP;
			}

			player.turn = false;
			break;
		}
		case GLUT_KEY_DOWN: {
			if (player.direction != GLUT_KEY_UP && player.turn) {
				player.direction = GLUT_KEY_DOWN;
			}

			player.turn = false;
			break;
		}
		case GLUT_KEY_LEFT: {
			if (player.direction != GLUT_KEY_RIGHT && player.turn) {
				player.direction = GLUT_KEY_LEFT;
			}

			player.turn = false;
			break;
		}
		case GLUT_KEY_RIGHT: {
			if (player.direction != GLUT_KEY_LEFT && player.turn) {
				player.direction = GLUT_KEY_RIGHT;
			}

			player.turn = false;
			break;
		}
		default:
			break;
	}
}

//функция таймера
void Timer(int value) {
	player.turn = true;
	player.move();
	player.cut();
	player.eat();
	glutPostRedisplay(); //перерисовать
	glutTimerFunc(settings.delay, Timer, 0);
}

//функция прорисовки змейки
void draw() {
	glClear(GL_COLOR_BUFFER_BIT); // очистить буфер цветов
	glBegin(GL_QUADS); // задаем не просто 4 точки а цельный четырехугольник
	food.draw_food();
	player.DrawSnake();
	glEnd();
	glutSwapBuffers();
}

int main(int argc, char *argv[]) {
	settings.init();
	food.spawn();
	srand(time(NULL));
	glutInit(&argc, argv); //инициализация opengl
	glutInitDisplayMode(GLUT_RGB); // цвет, количество буферов экрана
	glutInitWindowSize(WIDTH * settings.win_scale, HEIGHT * settings.win_scale); //размеры окна, ширина и высота в пикселях
	glutInitWindowPosition(settings.win_pos_x, settings.win_pos_y); //положение окна на экране
	glutCreateWindow("***Snake***"); //создает окно и заголовком в качестве параметра
	glutDisplayFunc(draw); //отвечает за то, что будет тображено на окне
	glutTimerFunc(settings.delay, Timer, 0); //1-отрисовка каждые n миллисекунд(задержка), 2 - имя функци в которой будут происходить вычисления, 3 - параметр функции 2го аргумента
	glutKeyboardFunc(keyboard); // обработка событий нажатия на клавиатуру
	glutSpecialFunc(spec_keyboard); // отвечает за клавиатуру(спецклавиши F1-F12 стрелки и т.д.)
	glMatrixMode(GL_PROJECTION); //задает способ отображения в плоскую картинку
	glLoadIdentity(); //очистка матрицы
	glOrtho(0, WIDTH, 0 , HEIGHT, -1, 1); //задаем систему отчета внутри нашего нового окна
	glutMainLoop(); //запускает


	return 0;
}