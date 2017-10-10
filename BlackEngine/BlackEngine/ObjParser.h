#pragma once

#include "VertexFormat.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>

class ObjParser
{
public:
	ObjParser();
	~ObjParser();
	std::vector<VertexFormat> ParseObj(const std::string & path);
};

