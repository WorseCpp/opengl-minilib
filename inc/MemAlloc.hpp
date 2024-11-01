
#include "glCommon.hpp"

// VERY simple allocator

class MemAlloc
{
    protected:
    uint m_size;
    
    MemAlloc();

    public:
    
    MemAlloc(uint siz);

    virtual uint alloc(uint size);
};

class SimpleMemAlloc : public MemAlloc
{
    protected:
    uint m_ptr;

    public:

    SimpleMemAlloc(uint siz);

    uint alloc(uint bsize);

};
