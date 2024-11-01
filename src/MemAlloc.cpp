#include "MemAlloc.hpp"



// VERY simple allocator



MemAlloc::MemAlloc()
{}

uint MemAlloc::alloc(uint bsize)
{
    return 0;
}

MemAlloc::MemAlloc(uint siz)
: m_size(siz)
{}



SimpleMemAlloc::SimpleMemAlloc(uint siz)
{
    this->m_size = siz;
    m_ptr = 0;
}

uint SimpleMemAlloc::alloc(uint bsize)
{
    auto outptr = m_ptr;
    m_ptr = bsize + m_ptr;

    assert(m_ptr < m_size);

    return outptr;
}


