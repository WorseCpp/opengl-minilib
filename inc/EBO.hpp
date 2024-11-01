
#include "glCommon.hpp"


class EBO
{
    unsigned int m_ID;
    uint m_max;
public:
    EBO();
    EBO(int size); // Constructor declaration
    ~EBO(); // Destructor declaration
    void bind(); // bind function declaration
    void addData(unsigned int* data, unsigned int num, int idx); // addData function declaration
    void unbind();
};