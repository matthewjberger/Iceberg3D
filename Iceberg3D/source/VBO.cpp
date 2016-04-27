#include "VBO.h"

using namespace iceberg;

VBO::VBO()
{
    buffer_ = 0;
    type_ = GL_ARRAY_BUFFER;
    uploaded_ = false;
}

VBO::~VBO()
{
    free();
}

void VBO::free()
{
    glDeleteBuffers(1, &buffer_);
    data_.clear();
}

void VBO::create(GLint size)
{
    glGenBuffers(1, &buffer_);
    data_.reserve(size);
}

void VBO::bind(GLuint bufferType)
{
    type_ = bufferType;
    glBindBuffer(type_, buffer_);
}

void VBO::unbind() const
{
    glBindBuffer(type_, 0);
}

void VBO::add_data(void* newData, GLuint dataSize)
{
    GLbyte* newDataStart = static_cast<GLbyte*>(newData);
    GLbyte* newDataEnd = static_cast<GLbyte*>(newData) + dataSize;
    data_.insert(data_.end(), newDataStart, newDataEnd);
}

void VBO::upload_data(GLenum drawingHint)
{
    glBufferData(type_, data_.size(), data_.data(), drawingHint);
    data_.clear();
    uploaded_ = true;
}

bool VBO::update_buffer(GLintptr offset, GLsizeiptr size, const GLvoid* data) const
{
    if (!uploaded_) return false;
    glBufferSubData(type_, offset, size, data);
    return true;
}