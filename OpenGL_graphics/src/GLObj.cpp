#include "GLObj.h"

void GLObj::SetColor3f(float red, float green, float blue)
{
	delete[] this->color3f;
	this->color3f = new float[3]{ red, green, blue };
}

void GLObj::Draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawArrays(GL_LINE_LOOP, 0, 150 /* <- this equals to (Quantity/2), but ????????????? */);		// A number of ar elements / 2 = number of vertices (here we need to pass a number of vertices)
	glVertexPointer(2, GL_DOUBLE, 0, this->VertexArray);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void GLObj::MoveOn(GLdouble dX, GLdouble dY, bool isBorderedByWnd)
{
	if (VertexArray != nullptr)
	{
		bool MovementAllowed = 1;

		if (isBorderedByWnd)
		{
			for (int i = 0; i < Quantity; i += 2)
				if ((VertexArray[i] + dX) < -1 || 1 < (VertexArray[i] + dX) || (VertexArray[i + 1] + dY) < -1 || 1 < (VertexArray[i + 1] + dY))
					MovementAllowed = 0;
		}

		for (GLint i = 0; i < Quantity && MovementAllowed; i += 2)
		{
			VertexArray[i] += dX;
			VertexArray[i + 1] += dY;
		}
	}
}

bool GLObj::isCollidedWith(GLObj && another)
{
	return false;
}

GLfloat GLObj::GetAspectRatio()
{
	return AspectRatio;
}

int GLObj::GetQuantity()
{
	return Quantity;
}