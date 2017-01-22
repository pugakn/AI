// AI.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <Vector3D.h>
#include <Vector4D.h>
#include <Matrix4D.h>
#include <iostream>


int main()
{
	Vector4D A(1, 3, 1,1);
	Vector3D B(2, 5, 6);
	Matrix4D M;
	M.Row0 = Vector4D(2,3,1,1);
	M.Row1 = Vector4D(1, 2, 5, 3);
	M.Row2 = Vector4D(1, 1, 5, 3);
	M.Row3 = Vector4D(1, 2, 14, 3);
	std::cout << A*M  << endl;  //Falta std para endl, o quitar std de cout, una o la otra

    return 0;
}

