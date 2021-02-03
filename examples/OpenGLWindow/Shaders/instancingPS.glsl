#version 330
precision highp float;

in vec4 fragment_color;
in vec2 vert_texcoord;

uniform sampler2D Diffuse;
in vec3 lightDir,normal,ambient;
out vec4 color;

void main_textured(void)
{
   color  = vec4(0.1,0.2,0.3,0.3);
}

void main(void)
{
    vec4 texel = fragment_color*texture(Diffuse,vert_texcoord); //fragment_color;
	vec3 ct,cf;
	float intensity,at,af;
	
	intensity = 0.5+0.5*clamp( dot( normalize(normal),lightDir ), -1.0, 1.0 );
	cf = intensity*(vec3(1.0,1.0,1.0)-ambient)+ambient;
	af = 1.0;
		
	ct = texel.rgb;
	at = texel.a;
		
	color  = vec4(ct * cf, at * af);	
}
