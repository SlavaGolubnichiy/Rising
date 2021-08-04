#include "GLObj.h"

class Square : public GLObj
{
	public:
	Square(GLdouble TopLeftX, GLdouble TopLeftY, GLdouble BottomRightX, GLdouble BottomRightY);
	Square(const Square&);
	Square(Square&&);
	~Square();

	double	GetArrayElement(unsigned int index);
	int		Rotate(bool, GLdouble);
	bool	isCollidedWith(GLObj &&another) override;
	void	MoveTo(double TopLeftX, double TopLeftY);
};