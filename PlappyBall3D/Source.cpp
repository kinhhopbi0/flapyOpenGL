#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <gl/glut.h>
#include <math.h>
#include <string.h>

//playGame variable
GLbyte stop;
GLint point;
GLbyte gameOver;
GLint val;// thời gian rơi

// ball var
GLdouble _BirX;
GLdouble _birY;
GLdouble _birZ;

//pie var
GLint _pX;
GLint _pX2;
GLint _pX3;
GLint _pY;
GLint _pY2;
GLint _pY3;
GLint _pieKc;
GLint _pieW;// độ rộng width của ống 

//windows config
GLint _w = 600;
GLint _h = 300;
GLint _clientX = 400;
GLint _clientY = 200;

//Generates Random Numbers 
int RandomNumber(int high, int low)
{
	return (rand() % (high - low)) + low;
}
void Initialize(void)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.7f, 0.9f, 1.0f, 1.0f); //background 	
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// khi thay ddooir kihc thuoc cua so
void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45.0, (double)w / (double)h, 1, 800.0);
	glOrtho(0, _w, 0, _h, -5, 50);
}
#define DEG2RAD (3.14159/180.0)
void DrawBird()
{
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);//Color it Yellow
	glTranslated(_BirX, _birY, 0);
	//glBegin(GL_LINE_LOOP);
	/*for (int angle = 0; angle< 360; angle++)
	glVertex2f(50*cos(angle*DEG2RAD), 30*sin(angle*DEG2RAD));	*/
	//glEnd();	
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 20, 0);
	glVertex3f(20, 20, 0);
	glVertex3f(20, 0, 0);
	glEnd();
	glPopMatrix();
}

void DrawPie(GLint _pX, GLint _pY)
{
	glPushMatrix();
	glColor3ub(84, 213, 21);
	glTranslated(_w - _pX, _h - _pY, 0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 20, 0);
	glVertex3f(_pieW, 20, 0);
	glVertex3f(_pieW, 0, 0);
	glEnd();
	glColor3ub(84, 250, 21);
	glBegin(GL_POLYGON);
	glVertex3f(_pieW - 50, 20, 0);
	glVertex3f(_pieW - 50, 600, 0);
	glVertex3f(_pieW - 20, 600, 0);
	glVertex3f(_pieW - 10, 20, 0);
	glEnd();
	glColor3ub(84, 213, 21);
	glBegin(GL_POLYGON);
	glVertex3f(0, -_pieKc, 0);
	glVertex3f(_pieW, -_pieKc, 0);
	glVertex3f(_pieW, -20 - _pieKc, 0);
	glVertex3f(0, -20 - _pieKc, 0);
	glEnd();
	glColor3ub(84, 250, 21);
	glBegin(GL_POLYGON);
	glVertex3f(_pieW - 50, -20 - _pieKc, 0);
	glVertex3f(_pieW - 50, -600 - _pieKc, 0);
	glVertex3f(_pieW - 20, -600 - _pieKc, 0);
	glVertex3f(_pieW - 10, -20 - _pieKc, 0);
	glEnd();
	glPopMatrix();
}
// intialize values default for game
void Reset()
{
	stop = false;
	point = 0;
	gameOver = false;
	val = 0;
	_BirX = 50;// tọa độ ox của ball
	_birY = 150;// tọa độ oy
	_birZ = 10;
	_pX = 0;//
	_pY = RandomNumber(200, 10);
	_pY2 = RandomNumber(200, 10);
	_pY3 = RandomNumber(200, 10);
	_pX2 = _pX - 180;
	_pX3 = _pX - 360;
	_pieKc = 65; // khoang cách giữa 2 ống
	_pieW = 60;// độ rong của ống
}

//Show string on the screen
void ShowString(double x, double y, char *s){
	glRasterPos3d(x, y, 0);
	while (*s)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *s++);
}
void Check(GLint _pX, GLint _pY)
{
	if (_w - _pX <= _BirX + 20 && _BirX <= _w - _pX + _pieW && !stop)// khi nam trong vung giữa 2 vật cản
	{
		if (_birY + 20 >= _h - _pY)// va cham diem tren với vật cản
		{
			PlaySound(TEXT("dead.wav"), NULL, SND_FILENAME | SND_ASYNC);
			stop = true;
		}
		if (_birY <= _h - _pY - _pieKc)// va cham duoi vật cản
		{
			PlaySound(TEXT("dead.wav"), NULL, SND_FILENAME | SND_ASYNC);
			stop = true;
		}
	}
	if (_BirX + 1 == _w - _pX + _pieW)
	{
		PlaySound(TEXT("coin.wav"), NULL, SND_FILENAME | SND_ASYNC);
		point++;
		//am thanh
	}
}
void Run(int value)
{
	if (!stop && !gameOver)
	{
		_pX++;// vật cản dịch chuyển
		_pX2++;
		_pX3++;
	}

	if (_pX - _pieW >= _w)
	{
		_pX = -_pieW;
		_pY = RandomNumber(200, 10);
	}
	if (_pX2 - _pieW >= _w)
	{
		_pX2 = -_pieW;
		_pY2 = RandomNumber(200, 10);
	}
	if (_pX3 - _pieW >= _w)
	{
		_pX3 = -_pieW;
		_pY3 = RandomNumber(200, 10);
	}
	Check(_pX, _pY);
	Check(_pX2, _pY2);
	Check(_pX3, _pY3);
	if (stop && val < 0)
	{
		val = 1;
	}
	_birY -= ((GLdouble)value) * 0.035;// rơi	
	if (_birY <= 0)
		gameOver = true;
	glutTimerFunc(8, Run, ++val);//
}

void Display(void)
{
	// clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	char *s = new char[10];
	_itoa(point, s, 10);// convert int point to char* 
	if (!gameOver)
	{
		glColor3f(0, 0, 0);
		ShowString((double)_w / 2 - 20, (double)_h / 2 + 80, s);
		DrawBird();
		DrawPie(_pX, _pY);
		DrawPie(_pX2, _pY2);
		DrawPie(_pX3, _pY3);
	}
	else//game over
	{
		glColor3f(0, 0, 0);
		ShowString(_w / 2 - 20, _h / 2 + 42, s);
		ShowString(_w / 2 - 200, _h / 2 + 10, "Game Over, press any key to replay, ESC to exit.");

		DrawPie(_pX, _pY);
		DrawPie(_pX2, _pY2);
		DrawPie(_pX3, _pY3);
	}
	glColor3f(1, 1, 1);
	ShowString(10, 10, "Vinh Pham Dinh - 2014");
	// Updates the screen
	glutPostRedisplay();
	glutSwapBuffers();
}
void Up()
{
	if (val>0)
		val = -45;
	else
	{
		val += -25;
	}
}
void MouseDow(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
	{
							 if (!stop)
							 {
								 Up();
							 }
							 if (gameOver)
							 {
								 Reset();
							 }

	}
	default:
		break;
	}
}
void KeyPress(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:{//ESC
				exit(0);
	}break;
	case '+':
	{
				_pieKc += 2;
	}break;
	case '-':
	{
				_pieKc -= 2;
	}break;
	default:
	{
			   if (!stop)
				   Up();
			   if (gameOver)
			   {
				   Reset();
			   }

	}break;
	}
}
void main()
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(_w, _h);
	glutInitWindowPosition(_clientX, _clientY);
	glutCreateWindow("Plappy Ball");
	Reset();
	glutKeyboardFunc(KeyPress);
	glutMouseFunc(MouseDow);
	glutDisplayFunc(Display);
	glutReshapeFunc(resize);
	Run(0);
	Initialize();
	glutMainLoop();
}