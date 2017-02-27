#ifndef UAD_LINEGL_H
#define UAD_LINEGL_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <d3dx9math.h>

#include "PrimitiveBase.h"
#include "UtilsGL.h"


class LineGL : public PrimitiveBase {
public:
	LineGL() : shaderID(0) {}
	void Create() override;
	void Transform(float *t) override;
	void Draw() override;
	void Destroy() override;

	GLuint	shaderID;
	GLuint	vertexAttribLoc;
	GLuint	colorAttribLoc;

	GLuint  matUniformLoc;

	triVertex		vertices[2];
	unsigned short	indices[2];
	GLuint			VB;
	GLuint			IB;

	D3DXMATRIX	transform;
};


#endif
