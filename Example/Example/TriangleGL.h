#ifndef UAD_TRIANGLEGL_H
#define UAD_TRIANGLEGL_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <d3dx9math.h>

#include "PrimitiveBase.h"
#include "UtilsGL.h"





class TrangleGL : public PrimitiveBase {
public:
	TrangleGL() : shaderID(0) {}
	void Create() override;
	void Transform(float *t) override;
	void Draw() override;
	void Destroy() override;

	GLuint	shaderID;
	GLuint	vertexAttribLoc;
	GLuint	colorAttribLoc;
	
	GLuint  matUniformLoc;

	triVertex		vertices[4];
	unsigned short	indices[6];
	GLuint			VB;
	GLuint			IB;

	D3DXMATRIX	transform;
};


#endif