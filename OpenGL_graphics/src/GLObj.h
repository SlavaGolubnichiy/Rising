#ifndef _glfw3_h_
	#include <GLFW/glfw3.h>
#endif

#ifndef _GLOBJ_CLASS_
	#define _GLOBJ_CLASS_

	class GLObj
	{
		protected:

		const float		AspectRatio = 0.5625;
		GLdouble*		VertexArray = nullptr;
		int				Quantity = 0;
		float*			color3f = new float[3]{1.0, 1.0, 1.0};

		public:

		void	SetColor3f(float red, float green, float blue);
		void			Draw();
		void			MoveOn(GLdouble, GLdouble, bool);
		virtual bool	isCollidedWith(GLObj &&another);
		GLfloat			GetAspectRatio();
		int				GetQuantity();
	};

#endif