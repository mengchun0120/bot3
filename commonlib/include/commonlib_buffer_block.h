#ifndef INCLUDE_COMMONLIB_BUFFER_BLOCK_H
#define INCLUDE_COMMONLIB_BUFFER_BLOCK_H

namespace mcdane {
namespace commonlib {

struct BufferBlock {
    BufferBlock();

    BufferBlock(const void *data,
                unsigned int numVertices,
                unsigned int vertexSize,
                unsigned int stride);

    void validate() const;

    const void *data_;
    unsigned int numVertices_;
    unsigned int vertexSize_;
    unsigned int stride_;
};

} // end of namespace commonlib
} // end of namespace mcdane

#endif
