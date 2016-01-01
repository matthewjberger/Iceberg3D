#include "VBO.h"

VBO::VBO()
{
    // Initialize variables
    buffer = 0;
}

VBO::~VBO()
{
    Free();
}

void VBO::Free()
{
    // Delete the buffer
    glDeleteBuffers(1, &buffer);

    // Clear the data
    data.clear();
}

void VBO::Create(GLint size)
{
    // Create the buffer
    glGenBuffers(1, &buffer);

    // Set data size
    data.reserve(size);
}

void VBO::Bind(GLuint bufferType)
{
    // Set buffer type
    type = bufferType;

    // Bind VBO as current array
    glBindBuffer(type, buffer);
}

void VBO::Unbind()
{
    // Unbind VBO as current array
    glBindBuffer(type, 0);
}

void VBO::AddData(void* newData, GLuint dataSize)
{
    // Insert data at the end of the expandable data vector
    // cast data to byte pointers
    data.insert(data.end(), (GLbyte*)newData, (GLbyte*)newData + dataSize);
}

void VBO::UploadData(GLenum drawingHint)
{
    // Upload the data to the gpu
    glBufferData(type, data.size(), data.data(), drawingHint);

    // Clear the data vector
    data.clear();
}

