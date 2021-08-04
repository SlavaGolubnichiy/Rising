#ifndef _IOSTREAM_
	#include <iostream>
#endif

#include "Ellipse.h"

Ellipse::Ellipse(GLdouble CenterX, GLdouble CenterY, GLdouble Radius)
{
	Quantity = 300;
	VertexArray = new GLdouble[Quantity];

	const double pi = 3.14159;

	int* i = new int{ 0 };
	for (double angle = 0; angle <= (2 * pi) && *i < Quantity; angle += (pi / Quantity * 4), *i += 2)
	{
		VertexArray[*i] = sin(angle) * Radius * AspectRatio;			/// angle -> radians	transformation
		VertexArray[*i + 1] = cos(angle) * Radius;
	}

	delete i;	i = nullptr;
}

Ellipse::Ellipse(const Ellipse& other)
{
	for (int i = 0; i < other.Quantity; i++)
		this->VertexArray[i] = other.VertexArray[i];
}

Ellipse::Ellipse(Ellipse&& other)
{
	for (int i = 0; i < other.Quantity; i++)
		this->VertexArray[i] = other.VertexArray[i];

	other.~Ellipse();
}

Ellipse::~Ellipse()
{
	delete[] VertexArray;
	VertexArray = nullptr;
}

double Ellipse::GetArrayElement(unsigned int index_from0to300)
{
	if (index_from0to300 < 300)	return VertexArray[index_from0to300];
	else						return VertexArray[0];
}

int Ellipse::Rotate(bool isClockwise, GLdouble Degree)
{
	// rotate at (Degree) degrees
	return 0;
}

bool Ellipse::isCollidedWith(GLObj && another)
{
	for (int i = 0; i < Quantity; i++)
	{
		//if (this->VertexArray[i]
	}
	return false;
}