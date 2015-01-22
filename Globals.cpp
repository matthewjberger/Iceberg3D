#include "Globals.h"

GLuint MakeShader(string path, GLuint shaderType)
{
	//  Success flag
	GLint compiled = GL_FALSE;

	// Create a shader of the correct type
	GLuint shaderID = glCreateShader(shaderType);

	// Input stream
	ifstream file(path.c_str());

	// Source string
	string shaderSource;

	// Clear file flags
	file.clear();

	// If the file opened successfully
	if (file.good())
	{
		// Get total length of file
		file.seekg(0, ios::end);

		// Set string size to length of file
		shaderSource.reserve((unsigned int)file.tellg());

		// Reset cursor to beginning of file
		file.seekg(0, ios::beg);

		// Read in file as one string
		shaderSource.assign((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));

	}
	else
	{
		// Print error message
		printf("Couldn't open file %s\n", path.c_str());

		// Set string to empty
		shaderSource = "";
	}

	// Close file
	file.close();

	// Set shader source
	glShaderSource(shaderID, 1, (const GLchar**)&shaderSource, NULL);

	// Compile shader
	glCompileShader(shaderID);

	// Check if shader compiled successfully
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);

	// If compilation failed
	if (compiled != GL_TRUE)
	{
		// Print an error message
		printf("Couldn't compile shader %d\n\n Source code\n%s\n", shaderID, shaderSource.c_str());

		// Print shader log
		PrintShaderLog(shaderID);

		// Delete the shader
		glDeleteShader(shaderID);
		
		// Set shaderID to 0
		shaderID = 0;
	}

	// Return shader ID
	return shaderID;
}

GLuint MakeProgram(GLuint vShaderID, GLuint fShaderID)
{
	// Success flag
	GLint success = GL_TRUE;

	// Create Program ID
	GLuint programID = glCreateProgram();

	// Attach vertex shader
	glAttachShader(programID, vShaderID);

	// Attach fragment shader
	glAttachShader(programID, fShaderID);

	// Make the shader Program
	glLinkProgram(programID);


	// Check if program was created successfully
	glGetProgramiv(programID, GL_COMPILE_STATUS, &success);

	// If program creation failed
	if (success != GL_TRUE)
	{
		// Print an error message
		printf("Couldn't link program %d\n", programID);

		// Delete the program
		glDeleteProgram(programID);

		// Set program ID to 0
		programID = 0;
	}

	// Return ID of finished shader program
	return programID;
}

void PrintShaderLog(GLuint shader)
{
	//Shader log length
	int infoLogLength = 0;
	int maxLength = infoLogLength;

	// Get info string length
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

	// Allocate string
	char* infoLog = new char[maxLength];

	// Get info log
	glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
	if (infoLogLength > 0)
	{
		// Print Log
		printf("%s\n", infoLog);
	}

	//Deallocate string
	delete[] infoLog;
}
