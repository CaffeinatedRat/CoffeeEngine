//--------------------------------------------------------------------------------------
// Description: The OpenGL model class.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Common.hpp"
#include "OGLGraphicsClass.hpp"
#include "OGLCameraClass.hpp"
#include "OGLModelClass.hpp"
#include "OGLCommon.hpp"

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

OGLModelClass::OGLModelClass(const OGLModelClass& object)
	: ModelClass(object)
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

bool OGLModelClass::Initialize()
{
	if(m_pGraphicsClass == nullptr)
		throw NullArgumentException("OGLModelClass", "Initialize", "m_pGraphicsClass");

	m_pGraphicsClass->GetSystem()->WriteToLog("[OGLModelClass::Initialize] Beginning...");

	auto pGraphicsClass = dynamic_cast<const OGLGraphicsClass*>(m_pGraphicsClass);
	assert(pGraphicsClass);

	std::string rootPath = pGraphicsClass->GetSystem()->GetCurrentApplicationDirectory();
	std::string fileName = rootPath;
	
	fileName.append("/Media/coookeee.jpg");
	std::wstring fileNameW(fileName.begin(), fileName.end());
	
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)screenData);

	// Set the number of vertices in the vertex array.
	m_nVertexCount = 6;

	//const int totalNumberOfVerticies = m_nVertexCount * 3;
	//auto vertices = std::unique_ptr<float[]>(new float[totalNumberOfVerticies]);
	//auto colors = std::unique_ptr<float[]>(new float[totalNumberOfVerticies]);

	//vertices[0] = -3.0f; vertices[1] = 3.0f; vertices[2] = 0.0f;
	//vertices[3] = 3.0f; vertices[4] = 3.0f; vertices[5] = 0.0f;
	//vertices[6] = -3.0f; vertices[7] = -3.0f; vertices[8] = 0.0f;
	//
	//vertices[9] = -3.0f; vertices[10] = -3.0f; vertices[11] = 0.0f;
	//vertices[12] = -3.0f; vertices[13] = -3.0f; vertices[14] = 0.0f;
	//vertices[15] = -3.0f; vertices[16] = -3.0f; vertices[17] = 0.0f;

	//float vertices[] = {
	//	// positions         // colors
	//	0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
	//	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
	//	0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	//};

	float vertices[] = {
		-3.0f, 3.0f, 0.0f,  1.0f, 1.0f, 1.0f,
		3.0f, 3.0f, 0.0f,  1.0f, 1.0f, 1.0f,
		-3.0f, -3.0f, 0.0f,  1.0f, 1.0f, 1.0f,
		3.0f, 3.0f, 0.0f,  1.0f, 1.0f, 1.0f,
		3.0f, -3.0f, 0.0f,  1.0f, 1.0f, 1.0f,
		-3.0f, -3.0f, 0.0f,  1.0f, 1.0f, 1.0f
	};

	//for (int i = 0; i < totalNumberOfVerticies; i++)
	//{
	//	colors[i] = 1.0;
	//}

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Two VAOs allocation
	//glGenVertexArrays(2, &m_vaoID[0]);

	// First VAO setup
	//glBindVertexArray(m_vaoID[0]);

	//glGenBuffers(2, m_vboID);
	//glGenBuffers(1, m_vboID);

	//glBindBuffer(GL_ARRAY_BUFFER, m_vboID[0]);
	//glBufferData(GL_ARRAY_BUFFER, totalNumberOfVerticies * sizeof(GLfloat), vertices.get(), GL_STATIC_DRAW);
	//glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, m_vboID[1]);
	//glBufferData(GL_ARRAY_BUFFER, totalNumberOfVerticies * sizeof(GLfloat), colors.get(), GL_STATIC_DRAW);
	//glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(1);

	//glBindVertexArray(0);

	m_pGraphicsClass->GetSystem()->WriteToLog("[OGLModelClass::Initialize] Completed.");

	return true;
}

void OGLModelClass::Render(IShader* pShader, float fElapsedTime)
{
	if(m_pGraphicsClass == nullptr)
		throw NullArgumentException("OGLModelClass", "Render", "m_pGraphicsClass");

	auto pGraphicsClass = dynamic_cast<const OGLGraphicsClass*>(m_pGraphicsClass);
	assert(pGraphicsClass);

	OGLCameraClass* pMasterCamera = (OGLCameraClass*)pGraphicsClass->GetMasterCamera();
	if(pMasterCamera == nullptr)
		throw Exception("OGLModelClass", "Render", "There is no master camera.  You need a camera to see!");

	//Render a shader if one was provided...if not good luck!
	if (pShader != nullptr)
		pShader->Render(fElapsedTime);

	//glBindVertexArray(m_vaoID[0]);		// select first VAO
	glBindVertexArray(VAO);		// select first VAO
	glDrawArrays(GL_TRIANGLES, 0, m_nVertexCount);	// draw first object
}

void OGLModelClass::Shutdown()
{
	m_pGraphicsClass->GetSystem()->WriteToLog("[OGLModelClass::Initialize] Shutting down...");

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glDeleteBuffers(2, m_vboID);
	glDeleteBuffers(1, &VBO);

	glBindVertexArray(0);
	//glDeleteVertexArrays(2, m_vaoID);
	glDeleteVertexArrays(1, &VAO);
}

void OGLModelClass::Rotate(float x, float y, float z)
{
	//m_rotate = D3DXVECTOR3(x, y, z);
}

void OGLModelClass::Translate(float x, float y, float z)
{
	//m_translate = D3DXVECTOR3(x, y, z);
}

void OGLModelClass::Scale(float x, float y, float z)
{
	//m_scale = D3DXVECTOR3(x, y, z);
}