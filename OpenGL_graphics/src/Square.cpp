#include "Square.h"

Square::Square(GLdouble TopLeftX, GLdouble TopLeftY, GLdouble BottomRightX, GLdouble BottomRightY)
{
	Quantity = 300;

	VertexArray = new GLdouble[Quantity];

	VertexArray[0] = TopLeftX * AspectRatio;			VertexArray[1] = TopLeftY;
	VertexArray[2] = BottomRightX * AspectRatio;		VertexArray[3] = TopLeftY;
	VertexArray[4] = BottomRightX * AspectRatio;		VertexArray[5] = BottomRightY;
	VertexArray[6] = TopLeftX * AspectRatio;			VertexArray[7] = BottomRightY;

	// vertex array drawing errors' prevention (temporary -> U need to fix it)

	for (int i = 8; i < Quantity; i += 2)
	{
		VertexArray[i] = VertexArray[6];
		VertexArray[i + 1] = VertexArray[7];
	}
}

Square::Square(const Square& other)
{
	for (int i = 0; i < other.Quantity; i++)
		this->VertexArray[i] = other.VertexArray[i];
}

Square::Square(Square&& other)
{
	for (int i = 0; i < other.Quantity; i++)
		this->VertexArray[i] = other.VertexArray[i];

	other.~Square();
}

Square::~Square()
{
	delete[] VertexArray;
	VertexArray = nullptr;
}

double Square::GetArrayElement(unsigned int index_from0to7)
{
	if (index_from0to7 < 8)		return VertexArray[index_from0to7];
	else						return VertexArray[0];
}

int Square::Rotate(bool isClockwise, GLdouble Degree)
{
	// rotate at (Degree) degrees
	return 0;
}

bool Square::isCollidedWith(GLObj && another)
{
	return false;
}

void Square::MoveTo(double TopLeftX, double TopLeftY)
{
	double width = VertexArray[2] - VertexArray[0];
	double height = VertexArray[3] - VertexArray[5];

	VertexArray[0] = TopLeftX;				VertexArray[1] = TopLeftY;
	VertexArray[2] = TopLeftX + width;		VertexArray[3] = TopLeftY;
	VertexArray[4] = TopLeftX + width;		VertexArray[5] = TopLeftY - height;
	VertexArray[6] = TopLeftX;				VertexArray[7] = TopLeftY - height;

	for (int i = 8; i < Quantity; i += 2)
	{
		VertexArray[i] = VertexArray[6];
		VertexArray[i + 1] = VertexArray[7];
	}
}