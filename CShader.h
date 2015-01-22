#ifndef CSHADER_H
#define CSHADER_H

#include "Globals.h"

class Shader
{
public:

	Shader();
	~Shader();
	
	// Loads shader from file
	bool Load(string path, GLuint shaderType);

	// Deletes shader
	void DeleteShader();

	// Print log
	void PrintLog();

	// Loaded if shader was compiled succesfully
	bool IsLoaded()
	{
		return loaded;
	}

	// Returns ID
	GLuint GetID()
	{
		return shaderID;
	}

private:

	// Shader ID
	GLuint shaderID;

	// Shader type
	GLuint type;

	// Load success flag
	bool loaded;
};

#endif