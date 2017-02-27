#ifndef UAD_PRIMITIVEBASE_H
#define UAD_PRIMITIVEBASE_H

struct triVertex {
	float x, y, z;
	float r, g, b;
};
class PrimitiveBase {
public:
	virtual void Create() = 0;
	virtual void Transform(float *t) = 0;
	virtual void Draw() = 0;
	virtual void Destroy() = 0;
};


#endif