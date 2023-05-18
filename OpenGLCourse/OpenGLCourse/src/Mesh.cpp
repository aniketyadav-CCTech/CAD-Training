#include "Mesh.h"
#include <iostream>
#include <sstream>
#include <fstream>

Mesh::Mesh()
	:mLoaded(false)
{
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);
}

//bool Mesh::loadOBJ(const std::string& filename)
//{
//	std::vector<unsigned int> vertexIndices, uvIndices;
//	std::vector <glm::vec3> tempVertices;
//	std::vector <glm::vec2> tempUVs;
//
//	if (filename.find(".obj") != std::string::npos) {
//		std::ifstream fin(filename, std::ios::in);
//		if (!fin) {
//			std::cerr << "Cannot open " << filename << std::endl;
//			return false;
//		}
//		std::cout << "Loading OBJ file " << filename << " ..." << std::endl;
//
//		std::string lineBuffer;
//		while (std::getline(fin, lineBuffer)) {
//			if (lineBuffer.substr(0, 2) == "v ") {
//				std::istringstream v(lineBuffer.substr(2));
//				glm::vec3 vertex;
//				v >> vertex.x >> vertex.y >> vertex.z;
//				tempVertices.push_back(vertex);
//			}
//			else if (lineBuffer.substr(0, 2) == "vt") {
//				std::istringstream vt(lineBuffer.substr(2));
//				glm::vec2 uv;
//				vt >> uv.s >> uv.t;
//				tempUVs.push_back(uv);
//			}
//			else if (lineBuffer.substr(0, 2) == "f ")
//			{
//				int p1, p2, p3;
//				int t1, t2, t3;
//				int n1, n2, n3;
//				const char* face = lineBuffer.c_str();
//				int match = sscanf_s(face, "f %i/%i/%i %i/%i/%i %i/%i/%i",
//					&p1, &t1, &n1,
//					&p2, &t2, &n2,
//					&p3, &t3, &n3);
//				if (match != 9)
//					std::cout << "Failed to parse OBJ file" << std::endl;
//
//				vertexIndices.push_back(p1);
//				vertexIndices.push_back(p2);
//				vertexIndices.push_back(p3);
//
//				uvIndices.push_back(t1);
//				uvIndices.push_back(t2);
//				uvIndices.push_back(t3);
//			}
//		}
//		fin.close();
//		for (unsigned int i = 0; i < vertexIndices.size(); i++) {
//			glm::vec3 vertex = tempVertices[vertexIndices[i] - 1];
//			glm::vec2 uv = tempUVs[uvIndices[i] - 1];
//
//			Vertex meshVertex;
//			meshVertex.position = vertex;
//			meshVertex.texCoords = uv;
//
//			mVertices.push_back(meshVertex);
//		}
//		initBuffers();
//
//		return (mLoaded = true);
//	}
//	return false;
//}

bool Mesh::loadSTL(const std::string& filename)
{
	std::vector <glm::vec3> tempVertices;
	std::vector <glm::vec3> tempNormals;

	if (filename.find(".stl") != std::string::npos || filename.find(".STL") != std::string::npos) {
		std::ifstream fin(filename, std::ios::in);
		if (!fin) {
			std::cerr << "Cannot open " << filename << std::endl;
			return false;
		}
		std::cout << "Loading STL  file " << filename << " ..." << std::endl;

		std::string lineBuffer;
		glm::vec3 normal;
		while (std::getline(fin, lineBuffer)) {
			if (lineBuffer.find("facet normal") != std::string::npos)
			{
				std::stringstream ss;
				ss << lineBuffer.substr(lineBuffer.find("facet normal") + 12);
				ss >> normal.x >> normal.y >> normal.z;
			}
			else if (lineBuffer.find("vertex") != std::string::npos) {
				std::stringstream ss;
				ss << lineBuffer.substr(lineBuffer.find("vertex") + 6);
				glm::vec3 vertex;
				ss >> vertex.x >> vertex.y >> vertex.z;
				Vertex meshVertex;
				meshVertex.position = vertex;
				meshVertex.normal = normal;
				mVertices.push_back(meshVertex);
			}
		}
		fin.close();
		
		initBuffers();

		return (mLoaded = true);
	}
	return false;
}

void Mesh::draw()
{
	if (!mLoaded) return;
	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
	glBindVertexArray(0);
}

void Mesh::initBuffers()
{
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// tex coords
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}