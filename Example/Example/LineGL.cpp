
#include "LineGL.h"


void LineGL::Create() {
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
	colorAttribLoc = glGetAttribLocation(shaderID, "MyColor");

	matUniformLoc = glGetUniformLocation(shaderID, "MyMatrix");

	vertices[0] = { 0.0f, 0.0f, 0.0f , 1.0f, 0.0f, 0.0f };
	vertices[1] = { 0.05f, 0.0f, 0.0f , 1.0f, 0.0f, 0.0f };


	D3DXMatrixIdentity(&transform);
}

void LineGL::Transform(float *t) {
	transform = t;
}

void LineGL::Draw() {
	glUseProgram(shaderID);

	glUniformMatrix4fv(matUniformLoc, 1, GL_FALSE, &transform.m[0][0]);

	glEnableVertexAttribArray(vertexAttribLoc);
	float *pos = (float*)&vertices[0].x;
	glVertexAttribPointer(vertexAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(triVertex), pos);

	glEnableVertexAttribArray(colorAttribLoc);
	float *color = (float*)&vertices[0].r;
	glVertexAttribPointer(colorAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(triVertex), color);

	glDrawArrays(GL_LINES, 0, 2);

	glDisableVertexAttribArray(vertexAttribLoc);
	glDisableVertexAttribArray(colorAttribLoc);

	glUseProgram(0);
}

void LineGL::Destroy() {
	glDeleteProgram(shaderID);
}