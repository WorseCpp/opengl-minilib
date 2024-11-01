#version 330 core
out vec4 FragColor;

in float Intensity;

void main()
{

   vec3 col3 = Intensity * vec3(1., 1., 1.);

   FragColor = vec4(col3, 1.0f);
};