//--------------------------------------------------------------------------------------
// Description: The OpenGL shader class.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Common.hpp"
#include "OGLGraphicsClass.hpp"
#include "OGLShaderClass.hpp"
#include "OGLCommon.hpp"

#include <fstream>

#include <glm/gtc/type_ptr.hpp>

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Graphics::OpenGL;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

OGLShaderClass::OGLShaderClass(const BaseGraphicsClass* pBaseGraphicsClass)
	: ShaderClass(pBaseGraphicsClass)
{

}

OGLShaderClass::OGLShaderClass(const OGLShaderClass& object)
	: ShaderClass(object)
{
}

OGLShaderClass::~OGLShaderClass()
{
	Shutdown();
}

////////////////////////////////////////////////////////////
//
//                Public Methods
// 
////////////////////////////////////////////////////////////

bool OGLShaderClass::Initialize(const std::string& sFileName)
{
	if(sFileName.length() == 0)
		throw NullArgumentException("OGLShaderClass", "Initialize", "sFileName");

	m_pGraphicsClass->GetSystem()->WriteToLog("[OGLShaderClass::Initialize] Beginning...");

	bool status = false;

	//Post-Condition Note: This should never be null as only constructor requires this class to be passed as valid (non-null).
	auto pGraphicsClass = dynamic_cast<const OGLGraphicsClass*>(m_pGraphicsClass);
	assert(pGraphicsClass);

	// Compile the vertex shader code.
	std::string shaderPath = pGraphicsClass->GetSystem()->GetCurrentApplicationDirectory();
	shaderPath.append("/Shaders/OpenGL/");
	shaderPath.append(sFileName);

	std::string vertexShaderPath = shaderPath;
	vertexShaderPath.append(".vs");
	m_pGraphicsClass->GetSystem()->WriteToLog("[OGLShaderClass::Initialize] Attempting to load the default vertex shader...");
	GLuint vertexShader = LoadShaderFromFile(vertexShaderPath, ShaderType::Vertex);

	std::string fragmentShaderPath = shaderPath;
	fragmentShaderPath.append(".fs");
	m_pGraphicsClass->GetSystem()->WriteToLog("[OGLShaderClass::Initialize] Attempting to load the default fragment shader...");
	GLuint fragmentShader = LoadShaderFromFile(fragmentShaderPath, ShaderType::Fragment);

	// Create a Shader Program
	m_programId = glCreateProgram();
	assert(m_programId > 0);
	if (m_programId > 0)
	{
		glAttachShader(m_programId, vertexShader);
		glAttachShader(m_programId, fragmentShader);
		glLinkProgram(m_programId);

		GLint success = 0;
		glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
		assert(success > 0);
		if (success == 0)
		{
			GLchar infoLog[512];
			glGetProgramInfoLog(m_programId, 512, NULL, infoLog);

			std::stringstream errorMessage;
			errorMessage << "[OGLShaderClass::Initialize] Failure to compile the program shader due to " << infoLog;
			m_pGraphicsClass->GetSystem()->WriteToLog(errorMessage);
		}
		else
		{
			status = true;
		}
	}
	else
	{
		m_pGraphicsClass->GetSystem()->WriteToLog("[OGLShaderClass::Initialize] The shader program could not be created and returned 0 meaning that OpenGL is rendering to another context.");
	}

	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	Render(0);
	setInt("texture1", 0);

	m_pGraphicsClass->GetSystem()->WriteToLog("[OGLShaderClass::Initialize] Completed.");
	return status;
}

/// <summary>
/// Loads a shader from the specified file.
/// </summary>
/// <param name="shaderFile">
/// The name of the shader file to load.
/// </param>
/// <param name="shaderType">
/// Determines the type of shader to load such as vertex, fragment, etc.
/// </param>
/// <returns>
/// A valid handle to a shader if it was created succesfully, otherwise zero is returned.
/// </returns>
GLuint OGLShaderClass::LoadShaderFromFile(std::string shaderFile, ShaderType shaderType)
{
	//Load the vertex shader from a file.
	std::string shaderData;
	std::ifstream shaderFileStream;
	shaderFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		shaderFileStream.open(shaderFile);

		std::stringstream vShaderStream;
		vShaderStream << shaderFileStream.rdbuf();
		shaderData = vShaderStream.str();
		shaderFileStream.close();
	}
	catch (std::ifstream::failure e)
	{
		std::stringstream errorMessage;
		errorMessage << "[OGLShaderClass::LoadShader] Failure to load the " << shaderFile << " shader due to " << e.what() << ".";
		m_pGraphicsClass->GetSystem()->WriteToLog(errorMessage);
		return (GLuint)0;
	}

	// Create the shader.
	GLuint shader = 0;
	switch (shaderType)
	{
		case ShaderType::Vertex:
			shader = glCreateShader(GL_VERTEX_SHADER);
			break;

		case ShaderType::Fragment:
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			break;
	}
	
	assert(shader > 0);
	if (shader == 0)
	{
		m_pGraphicsClass->GetSystem()->WriteToLog("[OGLShaderClass::LoadShader] The shader could not be created and returned 0 meaning that OpenGL is rendering to another context.");
		return (GLuint)0;
	}

	const char* vShaderCode = shaderData.c_str();
	glShaderSource(shader, 1, &vShaderCode, NULL);
	glCompileShader(shader);

	//Verify the compiler's success.
	GLint success = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == 0)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);

		std::stringstream errorMessage;
		errorMessage << "[OGLShaderClass::LoadShader] Failure to compile the shader due to " << infoLog;
		m_pGraphicsClass->GetSystem()->WriteToLog(errorMessage);
		glDeleteShader(shader);
		return (GLuint)0;
	}

	return shader;
}

bool OGLShaderClass::SetShaderParameters(float fElapsedTime)
{
	m_pGraphicsClass->GetSystem()->WriteToLog("[OGLShaderClass::SetShaderParameters] Beginning...", LogLevelType::DeepDiagnostic);

	//Cast to the OGL graphics class so that we can get access to OGL specific methods.
	//Post-Condition Note: This should never be null as only constructor requires this class to be passed as valid (non-null).
	auto pGraphicsClass = dynamic_cast<const OGLGraphicsClass*>(m_pGraphicsClass);
	assert(pGraphicsClass);

	//OGLCameraClass* pMasterCamera = (OGLCameraClass*)pGraphicsClass->GetMasterCamera();
	auto pMasterCamera = dynamic_cast<OGLCameraClass*>(pGraphicsClass->GetMasterCamera());
	if (pMasterCamera == nullptr)
		throw Exception("OGLShaderClass", "SetShaderParameters", "There is no master camera.  You need a camera to see!");

	//Retrieve all of our matrices
	auto worldMatrix = pMasterCamera->GetWorldMatrix();
	auto viewMatrix = pMasterCamera->GetViewMatrix();
	auto projectionMatrix = pMasterCamera->GetProjectionMatrix();

	setMatrix4("world", worldMatrix);
	setMatrix4("view", viewMatrix);
	setMatrix4("projection", projectionMatrix);
	
	m_pGraphicsClass->GetSystem()->WriteToLog("[OGLShaderClass::SetShaderParameters] Completed.", LogLevelType::DeepDiagnostic);

	return true;
}

void OGLShaderClass::Render(float fElapsedTime)
{
	glUseProgram(m_programId);
	SetShaderParameters(fElapsedTime);
	return;
}

void OGLShaderClass::Shutdown()
{
	m_pGraphicsClass->GetSystem()->WriteToLog("[OGLShaderClass::Shutdown] Shutting down...");
}