#include "stdafx.h"
#include "Edge.h"
bool Edge::operator==(const Edge & other) const
{
	return (((other.p1.p == this->p1.p) && (other.p2.p == this->p2.p))
		|| ((other.p2.p == this->p1.p) && (other.p1.p == this->p2.p)));
}

