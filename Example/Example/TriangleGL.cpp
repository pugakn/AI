
#include "TriangleGL.h"


void TrangleGL::Create() {
	shaderID = glCreateProgram();

	char *vsSourceP = file2string("VS_tri.glsl");
	char *fsSourceP = file2string("FS_tri.glsl");

	GLuint vshader_id = createShader(GL_VERTEX_SHADER, vsSourceP);
	GLuint fshader_id = createShader(GL_FRAGMENT_SHADER, fsSourceP);

	glAttachShader(shaderID, vshader_id);
	glAttachShader(shaderID, fshader_id);

	glLinkProgram(shaderID);
	glUseProgram(shaderID);

	vertexAttribLoc = glGetAttribLocation(shaderID, "MyVertex");
	colorAttribLoc  = glGetAttribLocation(shaderID, "MyColor");
	
	matUniformLoc = glGetUniformLocation(shaderID, "MyMatrix");

	vertices[0] = {  0.0f,  0.05f, 0.0f , 0.0f, 0.0f, 1.0f };
	vertices[1] = { -0.05f, -0.05f, 0.0f , 0.0f, 1.0f, 0.0f };
	vertices[2] = {  0.05f, -0.05f, 0.0f , 1.0f, 0.0f, 1.0f };

	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(triVertex), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	indices[0] = 2;
	indices[1] = 1;
	indices[2] = 0;

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned short), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	D3DXMatrixIdentity(&transform);
}

void TrangleGL::Transform(float *t) {
	transform = t;
}

void TrangleGL::Draw() {
	glUseProgram(shaderID);

	glUniformMatrix4fv(matUniformLoc, 1, GL_FALSE, &transform.m[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IB);

	glEnableVertexAttribArray(vertexAttribLoc);
	glEnableVertexAttribArray(colorAttribLoc);

	glVertexAttribPointer(vertexAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(triVertex), (void*)0);
	glVertexAttribPointer(colorAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(triVertex), (void*)12);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(vertexAttribLoc);
	glDisableVertexAttribArray(colorAttribLoc);

	glUseProgram(0);
}

void TrangleGL::Destroy() {
	glDeleteProgram(shaderID);
}