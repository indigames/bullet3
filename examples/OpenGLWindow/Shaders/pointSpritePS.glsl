
#version 330
precision highp float;

in vec4 fragment_color;

in vec3 ambient;

out vec4 color;

void main_textured(void)
{
    color =  fragment_color;//texture2D(Diffuse,vert_texcoord);//fragment_color;
}

void main(void)
{
	vec3 N;
	N.xy = gl_PointCoord.st*vec2(2.0, -2.0) + vec2(-1.0, 1.0);
    float mag = dot(N.xy, N.xy);
    if (mag > 1.0) discard; 
    vec4 texel = fragment_color;//vec4(1,0,0,1);//fragment_color*texture(Diffuse,vert_texcoord);//fragment_color;
	vec3 ct;
	float at,af;
	af = 1.0;
		
	ct = texel.rgb;
	at = texel.a;
		
 vec3 lightDir= vec3(1,0,0);
	float diffuse = max(0.0, dot(lightDir, N));
	color  = vec4(ct * diffuse, at * af);	
}
