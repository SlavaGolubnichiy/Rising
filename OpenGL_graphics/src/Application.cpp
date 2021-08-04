// version 1.0, released on 2nd July, 2018
/* version 1.1, released on 28 April, 2021
	// Release v1.1 notes:
	// 1.1	Implementation of class GLObj placed in to GLObj.h and GLObj.cpp files.
	// 1.2	Implementation of class Square placed in to Square.h and Square.cpp files.
	// 1.3	Implementation of class Ellipse placed in to Ellipse.h and Ellipse.cpp files.
	// 2.	VSYNC enabled (using glfwSwapInterval(1); function - line 244)
	// 3.	Physics calculation now depends on 1/60 of a second (frame time) when VSYNC enabled.
			Physics is calculated as many times per frame as phys_iterations variable value is.
	// 4.
*/


/// TODO
/// 1. Implement "Reset game world" function.









#include <iostream>
#include <conio.h>
#include <chrono>		// movement calculation
#include <ctime>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Square.h"
#include "Ellipse.h"

using namespace std;



#define DEBUG_ENABLED false





/// For graphics
#define SCREEN_WIDTH	1920
#define SCREEN_HIGHT	1080

#define SET_BACKGR_COLOR	glClearColor;

/// For data input
#define INT_DECIMAL_RADIXES			10
#define FLOAT_DECIMAL_RADIXES		16
#define DOUBLE_DECIMAL_RADIXES		18









/// Colors
GLfloat BackRed = 0.1,	BackGreen = 0.1,	BackBlue = 0.1;



void ToggleNightmode		(unsigned int);
void CoutDebugInfo			();
void RandomArrayOfDouble	(double*, unsigned int, double, double);
bool AreApproxEqual			(double, double, double);

/// Functions' declarations

struct KeysPressed
{
	bool KEY_W_PRESSED = false;
	bool KEY_A_PRESSED = false;
	bool KEY_S_PRESSED = false;
	bool KEY_D_PRESSED = false;
};
KeysPressed keys_pressed;
void keyCallback			(GLFWwindow *window,	int key, int scancode,	int action,	int mods);

void CursorCallback			(GLFWwindow *window,	double CursorX,	double CursorY);
void CursorEnterCallback	(GLFWwindow *window,	int CursorEntered);
void MouseButtonCallback	(GLFWwindow *window,	int button,	int action,	int mods);

void DelayAndPrintDelayInfo	(uint64_t delay);

/// Service variables
bool ContinueWindow = true;
bool GameOver = false;
bool stop = false;
bool tryagain = true;



// Global variables

/// Cursor and mouse
double CursorLastPosX		= 0,	CursorLastPosY		= 0;
double CurrentCursorPosX	= 0,	CurrentCursorPosY	= 0;
double CursorDeltaX			= 0,	CursorDeltaY		= 0;

double CursorPositionX		= 0,	CursorPositionY		= 0;

int Mousebutton				= 0,	Mouseaction			= 0;
int CursorInWindow			= 0;











#pragma region Not_Implemented_Classes

/*

class Triangle : public GLObj
{
public:
	Triangle(GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble);
	Triangle(const Triangle&);
	Triangle(Triangle&&);
	~Triangle();

	double	GetArrayElement(unsigned int index);
	int		Rotate	(bool, GLdouble);
	bool	isCollidedWith(GLObj &&another) override;
};

Triangle::Triangle(GLdouble X1, GLdouble Y1, GLdouble X2, GLdouble Y2, GLdouble X3, GLdouble Y3)
{
	Quantity = 300;
	VertexArray = new GLdouble[Quantity];

	VertexArray[0] = X1 * AspectRatio;		VertexArray[1] = Y1;
	VertexArray[2] = X2 * AspectRatio;		VertexArray[3] = Y2;
	VertexArray[4] = X3 * AspectRatio;		VertexArray[5] = Y3;

	/// vertex array drawing errors' prevention (temporary -> U need to fix it)

	for (int i = 6; i < Quantity; i += 2)
	{
		VertexArray[i] = VertexArray[4];
		VertexArray[i + 1] = VertexArray[5];
	}
}

Triangle::Triangle(const Triangle& other)
{
	for (int i = 0; i < other.Quantity; i++)
		this->VertexArray[i] = other.VertexArray[i];
}

Triangle::Triangle(Triangle&& other)
{
	for (int i = 0; i < other.Quantity; i++)
		this->VertexArray[i] = other.VertexArray[i];

	other.~Triangle();
}

Triangle::~Triangle()
{
	delete[] VertexArray;
	VertexArray = nullptr;
}

double Triangle::GetArrayElement(unsigned int index_from0to5)
{
	if (index_from0to5 < 6)		return VertexArray[index_from0to5];
	else						return VertexArray[0];
}

int Triangle::Rotate(bool isClockwise, GLdouble Degree)
{
	// rotate at (Degree) degrees
	return 0;
}

bool Triangle::isCollidedWith(GLObj && another)
{
	return false;
}

*/




/*
// 1. GLObj Container for collision detection

class Level
{
	public:
		Level();
		~Level();

	private:
		GLObj * ar;
		unsigned int size;
};

Level::Level()
{
	
}

Level::~Level()
{
}


*/

#pragma endregion


Ellipse		e1(0, 0, 0.1);

int main()
{
	// ___ DATA INITIALISATION

	srand(time(0));

	unsigned long int Score = 0, ScorePrev = Score;

	double s1TopLeftX = -0.1*(rand() % 3 + 7);
	double s2TopLeftX = -0.1*(rand() % 3 + 3);
	double s3TopLeftX = -0.1*(rand() % 3 - 1);
	double s4TopLeftX = 0.1*(rand() % 3 + 3);
	double s5TopLeftX = 0.1*(rand() % 3 + 7);

	Square s1(s1TopLeftX, 1.4, (s1TopLeftX + 0.2), 1.2);
	Square s2(s2TopLeftX, 1.4, (s2TopLeftX + 0.2), 1.2);
	Square s3(s3TopLeftX, 1.4, (s3TopLeftX + 0.2), 1.2);
	Square s4(s4TopLeftX, 1.4, (s4TopLeftX + 0.2), 1.2);
	Square s5(s5TopLeftX, 1.4, (s5TopLeftX + 0.2), 1.2);

	// -----------------------------------------------------



	GLFWwindow* window;
	if (!glfwInit())	return -1;
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HIGHT, "Rising", NULL, NULL);
	if (!window)		{ glfwTerminate();		return -1; }
	glewInit();
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);		// VSYNC



	while (tryagain)
	{
		s1TopLeftX = -0.1*(rand() % 3 + 7);
		s2TopLeftX = -0.1*(rand() % 3 + 3);
		s3TopLeftX = -0.1*(rand() % 3 - 1);
		s4TopLeftX = 0.1*(rand() % 3 + 3);
		s5TopLeftX = 0.1*(rand() % 3 + 7);

		while (!glfwWindowShouldClose(window) && ContinueWindow)			// Main graphics frame loop
		{

			std::chrono::steady_clock::time_point start = chrono::high_resolution_clock::now();
	
			glfwSetKeyCallback(window, keyCallback);
			//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			//glfwSetMouseButtonCallback(window, MouseButtonCallback);
			//glfwSetCursorPosCallback(window, CursorCallback);
	
			/// ___ START OF FRAME RENDERING
	
			SET_BACKGR_COLOR(BackRed, BackGreen, BackBlue, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			e1.Draw();
			s1.Draw();
			s2.Draw();
			s3.Draw();
			s4.Draw();
			s5.Draw();

			/// ___ END OF FRAME RENDERING ***

			if(!GameOver)
			{



				/// ___ START OF NEXT FRAME CALCULATING
				
				// *** GamePlay & objects' movement ***
	

				// how to draw objects with different number of vertices ???
	
				for (int phys_iterations = 20; phys_iterations > 0; phys_iterations--)
				{
					#pragma region player_gravity

					e1.MoveOn(0, -0.0001, 1);

					for (int i = 1; i < e1.GetQuantity(); i += 2)
						if (e1.GetArrayElement(i) <= -0.999)
							GameOver = 1;

					#pragma endregion

					#pragma region Squares falling animation

					if (s1.GetArrayElement(1) < -1 && s1.GetArrayElement(5) < -1)
					{
						s1TopLeftX = -0.1*(rand() % 3 + 7);
						s1.MoveTo(s1TopLeftX, 1.4);
						Score++;
					}
					else s1.MoveOn(0, -0.0004, 0);

					if (s2.GetArrayElement(1) < -1 && s2.GetArrayElement(5) < -1)
					{
						s2TopLeftX = -0.1*(rand() % 3 + 3);
						s2.MoveTo(s2TopLeftX, 1.4);
						Score++;
					}
					else s2.MoveOn(0, -0.00015, 0);

					if (s3.GetArrayElement(1) < -1 && s3.GetArrayElement(5) < -1)
					{
						s3TopLeftX = -0.1*(rand() % 3 - 1);
						s3.MoveTo(s3TopLeftX, 1.4);
						Score++;
					}
					else s3.MoveOn(0, -0.00028, 0);

					if (s4.GetArrayElement(1) < -1 && s4.GetArrayElement(5) < -1)
					{
						s4TopLeftX = 0.1*(rand() % 3 + 3);
						s4.MoveTo(s4TopLeftX, 1.4);
						Score++;
					}
					else s4.MoveOn(0, -0.00035, 0);

					if (s5.GetArrayElement(1) < -1 && s5.GetArrayElement(5) < -1)
					{
						s5TopLeftX = 0.1*(rand() % 3 + 7);
						s5.MoveTo(s5TopLeftX, 1.4);
						Score++;
					}
					else
					{
						s5.MoveOn(0, -0.0005, 0);
					}

					#pragma endregion

					if (keys_pressed.KEY_W_PRESSED)		e1.MoveOn(0, 0.0005, 1);
					if (keys_pressed.KEY_A_PRESSED)		e1.MoveOn(-0.0005 * e1.GetAspectRatio(), 0, 1);
					if (keys_pressed.KEY_S_PRESSED)		e1.MoveOn(0, -0.0005, 1);
					if (keys_pressed.KEY_D_PRESSED)		e1.MoveOn(0.0005 * e1.GetAspectRatio(), 0, 1);
				}
				
				#pragma region Collision detection

				// L - low, T - top
				// X - X axis, Y - Y axis

				double s1LX = s1.GetArrayElement(0), s1RX = s1.GetArrayElement(2);
				double s2LX = s2.GetArrayElement(0), s2RX = s2.GetArrayElement(2);
				double s3LX = s3.GetArrayElement(0), s3RX = s3.GetArrayElement(2);
				double s4LX = s4.GetArrayElement(0), s4RX = s4.GetArrayElement(2);
				double s5LX = s5.GetArrayElement(0), s5RX = s5.GetArrayElement(2);

				double s1TY = s1.GetArrayElement(3), s1BY = s1.GetArrayElement(5);
				double s2TY = s2.GetArrayElement(3), s2BY = s2.GetArrayElement(5);
				double s3TY = s3.GetArrayElement(3), s3BY = s3.GetArrayElement(5);
				double s4TY = s4.GetArrayElement(3), s4BY = s4.GetArrayElement(5);
				double s5TY = s5.GetArrayElement(3), s5BY = s5.GetArrayElement(5);

				double CheckX;
				double CheckY;

				for (int i = 0; i < e1.GetQuantity(); i += 38)
				{
					CheckX = e1.GetArrayElement(i);
					CheckY = e1.GetArrayElement(i + 1);

					// not optimized

					if (s1LX <= CheckX && CheckX <= s1RX && s1BY <= CheckY && CheckY <= s1TY ||
						s2LX <= CheckX && CheckX <= s2RX && s2BY <= CheckY && CheckY <= s2TY ||
						s3LX <= CheckX && CheckX <= s3RX && s3BY <= CheckY && CheckY <= s3TY ||
						s4LX <= CheckX && CheckX <= s4RX && s4BY <= CheckY && CheckY <= s4TY ||
						s5LX <= CheckX && CheckX <= s5RX && s5BY <= CheckY && CheckY <= s5TY
						)
					{
						GameOver = true;
						break;
					}

					// optimized
					GameOver = 
						s1LX <= CheckX && CheckX <= s1RX && s1BY <= CheckY && CheckY <= s1TY ||
						s2LX <= CheckX && CheckX <= s2RX && s2BY <= CheckY && CheckY <= s2TY ||
						s3LX <= CheckX && CheckX <= s3RX && s3BY <= CheckY && CheckY <= s3TY ||
						s4LX <= CheckX && CheckX <= s4RX && s4BY <= CheckY && CheckY <= s4TY ||
						s5LX <= CheckX && CheckX <= s5RX && s5BY <= CheckY && CheckY <= s5TY;
					if (GameOver)
					{
						break;
					}
				}

				#pragma endregion

			

				if (GameOver)
				{
					cout << "Score: " << Score << endl;
					cout << "GameOver" << endl;
				}
				else if	(ScorePrev < Score)
				{
					cout << "Score: " << Score << endl;
					ScorePrev = Score;
				}

				glfwSwapBuffers(window);

				/// ___ END OF NEXT FRAME CALCULATING
			}
			else
			{
				//GameOver = false;
				//DelayAndPrintDelayInfo(0x000000000FFFFFFF);
				/// reset game world function (not implemented)
			}

			glfwPollEvents();

			std::chrono::steady_clock::time_point end;
			end = chrono::high_resolution_clock::now();			//end time point
			chrono::duration<double> duration = end - start;
			if (DEBUG_ENABLED)
				std::cout << "FrameTime: \t" << duration.count() * 1000 << " ms \t" << "FPS: \t" << 1 / duration.count() << std::endl;
		}

		glfwTerminate();

		//cout << "Try again? (1/0) Your answer: "; cin >> tryagain;
		//if (tryagain)
		//{	
		//	GameOver = false;
		//	Score = 0;
		//}
		//else
		//{
		//	break;
		//}
	}

	return 0;
}






//_____________________________________________________________________________________________________________________________ FUNCTIONS



// -------------------------------------------------------------------------------- CONTROLS



void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch(key)
		{
			case GLFW_KEY_UP:
				if (!GameOver)	keys_pressed.KEY_W_PRESSED = true;
				break;

			case GLFW_KEY_LEFT:
				if (!GameOver)	keys_pressed.KEY_A_PRESSED = true;
				break;

			case GLFW_KEY_DOWN:
				if (!GameOver)	keys_pressed.KEY_S_PRESSED = true;
				break;

			case GLFW_KEY_RIGHT:
				if (!GameOver)	keys_pressed.KEY_D_PRESSED = true;
				break;

			case GLFW_KEY_ESCAPE:
				ContinueWindow = false;
				break;
		}
	}

	if (action == GLFW_RELEASE)
	{
		switch(key)
		{
			case GLFW_KEY_UP:
				keys_pressed.KEY_W_PRESSED = false;
				break;

			case GLFW_KEY_LEFT:
				keys_pressed.KEY_A_PRESSED = false;
				break;

			case GLFW_KEY_DOWN:
				keys_pressed.KEY_S_PRESSED = false;
				break;

			case GLFW_KEY_RIGHT:
				keys_pressed.KEY_D_PRESSED = false;
				break;

			case GLFW_KEY_ESCAPE:
				ContinueWindow = false;
				break;
		}
	}
}

void CursorCallback(GLFWwindow *window, double CursorX, double CursorY)
{
	if (Mousebutton == GLFW_MOUSE_BUTTON_LEFT && Mouseaction == GLFW_PRESS)
		cout << "LMB pressed" << endl;
}

void CursorEnterCallback(GLFWwindow *window, int CursorEntered)
{
	if (CursorEntered)	CursorInWindow = CursorEntered;
	else				CursorInWindow = 0;
}

void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch(button)
		{
			case GLFW_MOUSE_BUTTON_LEFT:
				Mousebutton = GLFW_MOUSE_BUTTON_LEFT;
				Mouseaction = GLFW_PRESS;
				break;

		}
	}

	else
	{
		Mousebutton = 0;
		Mouseaction = 0;
	}
}






// Local functions

void DelayAndPrintDelayInfo(uint64_t delay)
{
	std::chrono::steady_clock::time_point delay_start = chrono::high_resolution_clock::now();

	for (uint64_t delay_param = delay; delay_param > 1; delay_param--);

	std::chrono::steady_clock::time_point delay_end;
	delay_end = chrono::high_resolution_clock::now();			//end time point
	chrono::duration<double> delay_duration = delay_end - delay_start;
	std::cout << "GameOverDelay: \t" << delay_duration.count() * 1000 << " ms \t" << std::endl;
}

void ToggleNightmode(unsigned int BackColor)
{
	if (BackRed > 0.2)
	{
		BackRed = 0.1;	BackGreen = 0.1;	BackBlue = 0.1;
	}
	else if (BackRed < 0.8)
	{
		BackRed = 0.9;	BackGreen = 0.9;	BackBlue = 0.9;
	}
}

void CoutDebugInfo()
{
	if (Mousebutton == GLFW_MOUSE_BUTTON_1 && Mouseaction == GLFW_REPEAT)
	{
		cout << CurrentCursorPosX << "\t - " << CursorLastPosX << "\t = " << CursorDeltaX << endl;
		cout << CurrentCursorPosY << "\t - " << CursorLastPosY << "\t = " << CursorDeltaY << endl << endl;
	}
}

void RandomArrayOfDouble(double* ar, unsigned int size, double from, double to)
{
	int Range;

	if		(from < to)			Range = to - from;
	else if (to < from)			Range = from - to;
	else
	{
		for(int i = 0; i < size; i++)
			ar[i] = from;

			return;
	}
	
	int shift;	// shift calculation

//	for (int i = 0; i < size; i++)
//		ar[i] = 0.1*(rand()%Range + shift);

//	return;
}

bool AreApproxEqual(double a, double b, double b_equality_area)
{
	if		(a == b)	return 1;
	else if (a >  b)
	{
		if (a < (b + b_equality_area))	return 1;
		else							return 0;
	}
	else
	{
		if (a > (b - b_equality_area))	return 1;
		else							return 0;
	}
}