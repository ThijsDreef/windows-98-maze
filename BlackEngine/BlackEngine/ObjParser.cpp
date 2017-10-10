#include "ObjParser.h"

ObjParser::ObjParser()
{
}


ObjParser::~ObjParser()
{
}

std::vector<VertexFormat> ObjParser::ParseObj(const std::string & path)
{
	std::cout << "parsing obj";
	std::vector<int> verticesIndices;
	std::vector<int> normalsIndices;
	std::vector<int> textureIndices;
	std::vector<VertexFormat> finalVertices;
	std::vector<Vec3<float>> vertices;
	std::vector<Vec2<float>> texture;
	std::vector<Vec3<float>> normals;
	std::vector<Vec4<float>> colors;
	Vec4<float> currentMaterial(1.0f, 1.0f, 1.0f, 1.0f);
	std::map<std::string, Vec4<float>> materials;
	std::ifstream objFile(path);
	std::string line;
	if (objFile.is_open())
	{
		while (std::getline(objFile, line))
		{
			if (line.substr(0, 2) == "v ")
			{
				Vec3<float> vertex;
				sscanf_s(line.c_str(), "%*s %f %f %f", &vertex.x, &vertex.y, &vertex.z);
				vertices.push_back(vertex);
			}
			else if (line.substr(0, 2) == "vn")
			{
				Vec3<float> vertex;
				sscanf_s(line.c_str(), "%*s %f %f %f", &vertex.x, &vertex.y, &vertex.z);
				normals.push_back(vertex);
			}
			else if (line.substr(0, 2) == "vt")
			{
				Vec2<float> vertex;
				sscanf_s(line.c_str(), "%*s %f %f", &vertex.x, &vertex.y);
				//vertex.x = 1 - vertex.x;
				vertex.y = 1 - vertex.y;
				texture.push_back(vertex);
			}
			else if (line.substr(0, 7) == "usemtl ")
			{
				currentMaterial = materials[line.substr(7, line.size())];
			}
			else if (line.substr(0, 2) == "f ")
			{
				int vertexIndice[3];
				int uvIndice[3];
				int normalIndice[3];
				sscanf_s(line.c_str(), "%*s %i/%i/%i %i/%i/%i %i/%i/%i", &vertexIndice[0], &uvIndice[0], &normalIndice[0],
																	   &vertexIndice[1], &uvIndice[1], &normalIndice[1],
																	   &vertexIndice[2], &uvIndice[2], &normalIndice[2]);
				for (int i = 0; i < 3; i++)
				{
					verticesIndices.push_back(vertexIndice[i]);
					normalsIndices.push_back(normalIndice[i]);
					textureIndices.push_back(uvIndice[i]);
					colors.push_back(currentMaterial);
				}
			}
			else if (line.substr(0, 7) == "mtllib ")
			{
				std::ifstream mtlFile("models/" + line.substr(7, line.size()));
				std::string mtlLine;
				std::string currentMaterialName;
				while (std::getline(mtlFile, mtlLine))
				{
					if (mtlLine.substr(0, 3) == "Kd ")
					{
						Vec4<float> matColor;
						matColor.a = 1;
						sscanf_s(mtlLine.c_str(), "%*s %f %f %f", &matColor.r, &matColor.g, &matColor.b);
						materials[currentMaterialName] = matColor;
					}
					else if (mtlLine.substr(0, 7) == "newmtl ")
					{
						currentMaterialName = mtlLine.substr(7, mtlLine.size());
					}
				}
				mtlFile.close();
			}
		}
		std::cout << vertices.size() << "something";
		for (unsigned int i = 0; i < verticesIndices.size(); i++)
		{
			finalVertices.push_back(VertexFormat(vertices[verticesIndices[i] - 1], colors[i], normals[normalsIndices[i] - 1], texture[textureIndices[i] - 1]));
		}
	}
	objFile.close();
	std::cout << finalVertices.size();
	return finalVertices;
}
