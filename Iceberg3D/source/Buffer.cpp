#include "Buffer.h"

using namespace iceberg;

Buffer::Buffer(GLint size)
{
    buffer_ = 0;
    type_ = GL_ARRAY_BUFFER;
    uploaded_ = false;

    create(size);
}

Buffer::~Buffer()
{
    free();
}

void Buffer::free()
{
    glDeleteBuffers(1, &buffer_);
    data_.clear();
}

void Buffer::create(GLint size)
{
    glGenBuffers(1, &buffer_);
    data_.reserve(size);
}

void Buffer::bind(GLuint bufferType)
{
    type_ = bufferType;
    glBindBuffer(type_, buffer_);
}

void Buffer::unbind() const
{
    glBindBuffer(type_, 0);
}

void Buffer::add_data(void* newData, GLuint dataSize)
{
    GLbyte* newDataStart = static_cast<GLbyte*>(newData);
    GLbyte* newDataEnd = static_cast<GLbyte*>(newData) + dataSize;
    data_.insert(data_.end(), newDataStart, newDataEnd);
}

void Buffer::upload_data(GLenum drawingHint)
{
    glBufferData(type_, data_.size(), data_.data(), drawingHint);
    data_.clear();
    uploaded_ = true;
}

bool Buffer::update_buffer(const GLvoid* data, GLsizeiptr size, GLintptr offset) const
{
    if (!uploaded_) return false;
    glBufferSubData(type_, offset, size, data);
    return true;
}