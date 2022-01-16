#include <sstream>
#include <commonlib_exception.h>
#include <commonlib_buffer_block.h>
#include <commonlib_vertex_array.h>

namespace mcdane {
namespace commonlib {

void destroyArrayObj(GLuint arrayObj)
{
    if (arrayObj != 0)
    {
        glDeleteVertexArrays(1, &arrayObj);
    }
}

void destroyBufferObj(GLuint bufferObj)
{
    if (bufferObj != 0)
    {
        glDeleteBuffers(1, &bufferObj);
    }
}

void VertexArray::BufferDescriptor::init(const BufferBlock &block,
                                         unsigned int offset)
{
    offset_ = offset;
    numVertices_ = block.numVertices_;
    vertexSize_ = block.vertexSize_;
    totalSize_ = numVertices_ * vertexSize_;
    stride_ = block.stride_;
}

std::string VertexArray::BufferDescriptor::toString() const
{
    std::ostringstream oss;

    oss << "BufferDescriptor(offset=" << offset_
        << ", numVertices=" << numVertices_
        << ", vertexSize=" << vertexSize_
        << ", totalSize=" << totalSize_
        << ", stride=" << stride_
        << ")";

    return oss.str();
}

VertexArray::VertexArray()
    : arrayObj_(0)
    , bufferObj_(0)
{
}

VertexArray::VertexArray(const void *data,
                         unsigned int numVertices,
                         unsigned int vertexSize,
                         unsigned int stride)
    : VertexArray()
{
    load(data, numVertices, vertexSize, stride);
}

VertexArray::VertexArray(std::initializer_list<BufferBlock> blocks)
    : VertexArray(blocks.begin(), blocks.end())
{
}

VertexArray::~VertexArray()
{
    destroyBufferObj(bufferObj_);
    destroyArrayObj(arrayObj_);
}

void VertexArray::load(const void* data,
                       unsigned int numVertices,
                       unsigned int vertexSize,
                       unsigned int stride)
{
    load({ BufferBlock{data, numVertices, vertexSize, stride} });
}

void VertexArray::load(std::initializer_list<BufferBlock> blocks)
{
    load(blocks.begin(), blocks.end());
}

void VertexArray::createArrayObj()
{
    glGenVertexArrays(1, &arrayObj_);
    if (0 == arrayObj_)
    {
        THROW_EXCEPT(OpenGLException,
                     "glGenVertexArrayFailed: " + std::to_string(glGetError()));
    }
}

void VertexArray::createBufferObj()
{
    glBindVertexArray(arrayObj_);
    glGenBuffers(1, &bufferObj_);
    if (0 == bufferObj_)
    {
        THROW_EXCEPT(OpenGLException,
                     "glGenBufferFailed: " + std::to_string(glGetError()));
    }
}

void VertexArray::storeBufferBlock(BufferDescriptor& descriptor,
                                   const BufferBlock& block,
                                   unsigned int offset)
{
    block.validate();
    descriptor.init(block, offset);
    glBufferSubData(GL_ARRAY_BUFFER, offset, descriptor.totalSize_, block.data_);
}

std::string VertexArray::toString() const
{
    std::ostringstream oss;

    oss << "VertexArray(arrayObj=" << arrayObj_
        << ", bufferObj=" << bufferObj_
        << ", descriptors=[";

    if (!descriptors_.empty())
    {
        oss << descriptors_[0].toString();

        for (std::size_t i = 1; i < descriptors_.size(); ++i)
        {
            oss << ", " << descriptors_[i].toString();
        }
    }

    oss << "], Base=" << Object::toString() << ")";

    return oss.str();
}

} // end of namespace commonlib
} // end of namespace mcdane

