#include "glCommon.hpp"

struct v3
{
    float xyz[3];
};

struct ModelV3
{
    // w is the model (integer)
    float xyzw[4];
    float model;
    float col;
    float packing[2];
};

void set_attrib(const v3 * in);
void set_attrib(const ModelV3 * in);

