#include "Mesh.h"
#include <iostream>
#include <sstream>
#include <fstream>

std::vector<std::string> split(std::string s, std::string t) {
	std::vector<std::string> res;
	while (1) {
		int pos = s.find(t);
		if (pos == -1) {
			res.push_back(s);
			break;
		}
		res.push_back(s.substr(0, pos));
		s = s.substr(pos + 1, s.size() - pos - 1);
	}
	return res;
}

Mesh::Mesh()
    :mLoaded(false)
{
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);
}

bool Mesh::loadOBJ(const std::string& filename)
{
	std::vector<unsigned int> vertexIndices, normalIndices, uvIndices;
	std::vector <glm::vec3> tempVertices;
	std::vector <glm::vec3> tempNormals;
	std::vector <glm::vec2> tempUVs;

	if (filename.find(".obj") != std::string::npos) {
		std::ifstream fin(filename, std::ios::in);
		if(!fin){
			std::cerr << "Cannot open " << filename << std::endl;
			return false;
		}
		std::cout << "Loading OBJ file " << filename << " ..." << std::endl;

		std::string lineBuffer;
		while (std::getline(fin, lineBuffer)) {
			std::stringstream ss(lineBuffer);
			std::string cmd;
			ss >> cmd;

			if (cmd == "v") {
				glm::vec3 vertex;
				int dim = 0;
				while (dim < 3 && ss >> vertex[dim])
					dim++;
				tempVertices.push_back(vertex);
			}
			else if (cmd == "vt") {
				glm::vec2 uv;
				int dim = 0;
				while (dim < 2 && ss >> uv[dim])
					dim++;
				tempUVs.push_back(uv);
			}
			else if (cmd == "vn") {
				glm::vec3 normal;
				int dim = 0;
				while (dim < 3 && ss >> normal[dim])
					dim++;
				normal = glm::normalize(normal);
				tempNormals.push_back(normal);
			}
			else if (cmd == "f")
			{
				std::string faceData;
				int vertexIndex, uvIndex, normalIndex;

				while (ss >> faceData) {
					std::vector<std::string> data = split(faceData, "/");
					
					// vertex index
					if (data[0].size() > 0) {
						sscanf_s(data[0].c_str(), "%d", &vertexIndex);
						vertexIndices.push_back(vertexIndex);
					}
					// if the face vertex has a texture coordinate index
					if (data[1].size() >= 1) {
						if (data[1].size() > 0) {
							sscanf_s(data[1].c_str(), "%d", &uvIndex);
							uvIndices.push_back(uvIndex);
						}
					}
					// does the face vertex have a normal index
					if (data.size() >= 2) {
						if (data[2].size() > 0) {
							sscanf_s(data[2].c_str(), "%d", &normalIndex);
							normalIndices.push_back(normalIndex);
						}
					}
				}
			}
		}
		fin.close();
		std::cout << __LINE__ << std::endl;
		for (unsigned int i = 0; i < vertexIndices.size(); i++) {
			Vertex meshVertex;
			if (tempVertices.size() > 0) {
				glm::vec3 vertex = tempVertices[vertexIndices[i] - 1];
				meshVertex.position = vertex;
			}
			if (tempNormals.size() > 0) {
				glm::vec3 normal = tempNormals[normalIndices[i] - 1];
				meshVertex.normal = normal;
			}
			if (tempUVs.size() > 0) {
				glm::vec2 uv = tempUVs[uvIndices[i] - 1];
				meshVertex.texCoords = uv;
			}
			mVertices.push_back(meshVertex);
		}
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	glEnableVertexAttribArray(0);

	// normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// tex coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}