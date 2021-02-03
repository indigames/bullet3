//this file is autogenerated using stringify.bat (premake --stringify) in the build folder of this project
static const char* instancingFragmentShader= \
"#version 330\n"
"precision highp float;\n"
"in vec4 fragment_color;\n"
"in vec2 vert_texcoord;\n"
"uniform sampler2D Diffuse;\n"
"in vec3 lightDir,normal,ambient;\n"
"out vec4 color;\n"
"void main_textured(void)\n"
"{\n"
"   color  = vec4(0.1,0.2,0.3,0.3);\n"
"}\n"
"void main(void)\n"
"{\n"
"    vec4 texel = fragment_color*texture(Diffuse,vert_texcoord); //fragment_color;\n"
"	vec3 ct,cf;\n"
"	float intensity,at,af;\n"
"	\n"
"	intensity = 0.5+0.5*clamp( dot( normalize(normal),lightDir ), -1.0, 1.0 );\n"
"	cf = intensity*(vec3(1.0,1.0,1.0)-ambient)+ambient;\n"
"	af = 1.0;\n"
"		\n"
"	ct = texel.rgb;\n"
"	at = texel.a;\n"
"		\n"
"	color  = vec4(ct * cf, at * af);	\n"
"}\n"
;
