// JSONAnimParser.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "json.hpp"
#include <fstream>
#include "JSONToBinary.h"
#include <string>
#include <vector>
using json = nlohmann::json;
int main()
{
	std::string fileName="champion";
	std::ifstream i("Files/"+fileName+".json");
	json j;
	i >> j;
	JSONToBinary toBinary;
	toBinary.ToBinary(j, fileName);
    return 0;
}

