#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in float aModel;
layout (location = 2) in float aCol;


uniform mat4 ModelMatricies[16];

uniform mat4 MVP;

out float Intensity;

void main()
{ 

   vec4 pos = vec4(aPos.x, aPos.y, aPos.z, 1.0);

   int model = int(aPos.w);

   Intensity = aCol;

   gl_Position = MVP * (ModelMatricies[int(aModel)] * pos);
}