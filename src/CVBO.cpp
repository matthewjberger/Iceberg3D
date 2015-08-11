#include "CVBO.h"

VBO::VBO()
{
    // Initialize variables
    mBuffer = 0;
}

VBO::~VBO()
{
    Free();
}

void VBO::Free()
{
    // Delete the buffer 
    glDeleteBuffers(1, &mBuffer);

    // Clear the data
    mData.clear();
}

void VBO::Create(GLint size)
{
    // Create the buffer
    glGenBuffers(1, &mBuffer);

    // Set data size
    mData.reserve(size);
}

void VBO::Bind(GLuint bufferType)
{
    // Set buffer type
    mType = bufferType;

    // Bind VBO as current array
    glBindBuffer(mType, mBuffer);
}

void VBO::Unbind()
{
    // Unbind VBO as current array
    glBindBuffer(mType, NULL);
}

void VBO::AddData(void* data, GLuint dataSize)
{
    // Insert data at the end of the expandable data vector
    // cast data to byte pointers
    mData.insert(mData.end(), (GLbyte*)data, (GLbyte*)data + dataSize);
}

void VBO::UploadData(GLenum drawingHint)
{
    // Upload the data to the gpu
    glBufferData(mType, mData.size(), mData.data(), drawingHint);

    // Clear the data vector
    mData.clear();
}

