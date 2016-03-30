#include "VBO.h"

VBO::VBO()
{
    // Initialize variables
    buffer_ = 0;
    type_ = GL_ARRAY_BUFFER;
}

VBO::~VBO()
{
    free();
}

void VBO::free()
{
    // Delete the buffer
    glDeleteBuffers(1, &buffer_);

    // Clear the data
    data_.clear();
}

void VBO::create(GLint size)
{
    // Create the buffer
    glGenBuffers(1, &buffer_);

    // Set data size
    data_.reserve(size);
}

void VBO::bind(GLuint bufferType)
{
    // Set buffer type
    type_ = bufferType;

    // Bind VBO as current array
    glBindBuffer(type_, buffer_);
}

void VBO::unbind() const
{
    // Unbind VBO as current array
    glBindBuffer(type_, 0);
}

void VBO::add_data(void* newData, GLuint dataSize)
{
    // Insert data at the end of the expandable data vector
    // cast data to byte pointers
    GLbyte* newDataStart = static_cast<GLbyte*>(newData);
    GLbyte* newDataEnd = static_cast<GLbyte*>(newData) + dataSize;
    data_.insert(data_.end(), newDataStart, newDataEnd);
}

void VBO::upload_data(GLenum drawingHint)
{
    // Upload the data to the gpu
    glBufferData(type_, data_.size(), data_.data(), drawingHint);

    // Clear the data vector
    data_.clear();
}

