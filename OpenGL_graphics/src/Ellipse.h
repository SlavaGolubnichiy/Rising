#include "GLObj.h"

class Ellipse : public GLObj		// Circle yet indeed
{
	public:
	
	Ellipse(GLdouble, GLdouble, GLdouble);
	Ellipse(const Ellipse&);
	Ellipse(Ellipse&&);
	~Ellipse();

	double	GetArrayElement(unsigned int index);
	int		Rotate(bool, GLdouble);
	bool	isCollidedWith(GLObj &&another) override;

};