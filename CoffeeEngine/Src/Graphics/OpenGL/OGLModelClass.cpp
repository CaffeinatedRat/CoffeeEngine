//--------------------------------------------------------------------------------------
// Description: The OpenGL model class.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Common.hpp"
#include "OGLGraphicsClass.hpp"
#include "OGLCameraClass.hpp"
#include "OGLModelClass.hpp"
#include "OGLCommon.hpp"

#include "OGLShaderClass.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Graphics::OpenGL;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

OGLModelClass::OGLModelClass(const BaseGraphicsClass* pBaseGraphicsClass)
	: ModelClass(pBaseGraphicsClass)
{

}

OGLModelClass::~OGLModelClass()
{
	Shutdown();
}

////////////////////////////////////////////////////////////
//
//                Public Methods
// 
////////////////////////////////////////////////////////////

bool OGLModelClass::Initialize(IShader* pShader)
{
	if(m_pGraphicsClass == nullptr)
		throw NullArgumentException("OGLModelClass", "Initialize", "m_pGraphicsClass");

	m_pGraphicsClass->GetSystem()->WriteToLog("[OGLModelClass::Initialize] Beginning...");

	auto pGraphicsClass = dynamic_cast<const OGLGraphicsClass*>(m_pGraphicsClass);
	assert(pGraphicsClass);

	// Set the number of vertices in the vertex array.
	m_nVertexCount = 6;

	float vertices[] = {
		//positions           //RGBA                    //Textures
		-3.0f,  3.0f, 0.0f,   1.0f, 1.0f, 1.0f, 0.5f,   0.0f, 0.0f,
		 3.0f,  3.0f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
		-3.0f, -3.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
		 3.0f, -3.0f, 0.0f,   1.0f, 1.0f, 1.0f, 0.2f,   1.0f, 1.0f,
	};

	unsigned int indices[] = {
		0, 2, 1, // first triangle
		1, 2, 3  // second triangle
	};

	//Create the vertex buffer and array.
	glGenVertexArrays(1, &m_vertexArrayID);
	glGenBuffers(1, &m_vertexBufferID);
	glGenBuffers(1, &m_indexArrayID);

	// Bind early so we can save our vertex attributes.
	glBindVertexArray(m_vertexArrayID);

	if (m_enableAlphaBlending) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	//Bind the buffer and send the linear block of vertices.
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexArrayID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//Unbind our vertex array.
	//glBindVertexArray(0);

	std::string rootPath = pGraphicsClass->GetSystem()->GetCurrentApplicationDirectory();
	std::string fileName = rootPath;

	fileName.append("/Media/coookeee.jpg");

	// ---------
	glGenTextures(1, &m_defaultTextureID);
	glBindTexture(GL_TEXTURE_2D, m_defaultTextureID);
	
	//Set the texture wrapping to repeat for now.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	//Set the mipmap filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	//stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	//Clean up the data, we've already created the texture.
	stbi_image_free(data);

	m_pGraphicsClass->GetSystem()->WriteToLog("[OGLModelClass::Initialize] Completed.");

	return true;
}

void OGLModelClass::Render(float fElapsedTime) const
{
	if(m_pGraphicsClass == nullptr)
		throw NullArgumentException("OGLModelClass", "Render", "m_pGraphicsClass");

	auto pGraphicsClass = dynamic_cast<const OGLGraphicsClass*>(m_pGraphicsClass);
	assert(pGraphicsClass);

	OGLCameraClass* pMasterCamera = (OGLCameraClass*)pGraphicsClass->GetMasterCamera();
	if(pMasterCamera == nullptr)
		throw Exception("OGLModelClass", "Render", "There is no master camera.  You need a camera to see!");

	//Apply transformations.
	glm::mat4 worldMatrix = pMasterCamera->GetWorldMatrix();

	//NOTE: The order of Matrix transformations matter and will result in different effects.
	// This simple transformation does not take into account more complex transformations.
	//worldMatrix = glm::scale(worldMatrix, m_scale);
	//worldMatrix = glm::rotate(worldMatrix, fElapsedTime,  m_rotate);
	//worldMatrix = glm::translate(worldMatrix, m_translate);

	//worldMatrix = glm::rotate(worldMatrix, std::fmod(fElapsedTime, 360.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//worldMatrix = glm::translate(worldMatrix, glm::vec3(0.5f, -0.5f, 0.0f));
	//worldMatrix = glm::translate(worldMatrix, m_translate);

	//Get the shaders.
	CoffeeEngine::Graphics::OpenGL::OGLShaderClass* firstShader = (CoffeeEngine::Graphics::OpenGL::OGLShaderClass*)(m_shaders.size() > 0 ? m_shaders[0] : nullptr);
	if (firstShader != nullptr) {
		firstShader->SetWorldMatrix(worldMatrix);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_defaultTextureID);

	//Render all shaders.
	if (m_shaders.size() > 1)
	{
		//TODO: Make it dynamic cast, but it requires changing render to be a const function.
		firstShader->Render(fElapsedTime);
	}
	else
	{
		//TODO: Make it dynamic cast, but it requires changing render to be a const function.
		for (const IShader* pShader : m_shaders) {
			CoffeeEngine::Graphics::OpenGL::OGLShaderClass* shader = (CoffeeEngine::Graphics::OpenGL::OGLShaderClass*)pShader;
			if (shader != nullptr) {
				shader->Render(fElapsedTime);
			}
		}
	}

	glBindVertexArray(m_vertexArrayID);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void OGLModelClass::Shutdown()
{
	m_pGraphicsClass->GetSystem()->WriteToLog("[OGLModelClass::Initialize] Shutting down...");

	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteBuffers(1, &m_vertexBufferID);
	glDeleteBuffers(1, &m_indexArrayID);
}

void OGLModelClass::Rotate(float x, float y, float z)
{
	m_rotate = glm::vec3(x, y, z);
}

void OGLModelClass::Translate(float x, float y, float z)
{
	m_translate = glm::vec3(x, y, z);
}

void OGLModelClass::Scale(float x, float y, float z)
{
	m_scale = glm::vec3(x, y, z);
}