#version 330
precision highp float;
in vec4 scale_obuid;
out vec4 color;



void main(void)
{
	highp int obuid = int(scale_obuid.w);
	float r = float(((obuid>>0 )&0xff))*(1.0/255.0);
	float g = float(((obuid>>8 )&0xff))*(1.0/255.0);
	float b = float(((obuid>>16)&0xff))*(1.0/255.0);
	float a = float(((obuid>>24)&0xff))*(1.0/255.0);
	color  = vec4(r,g,b,a);
}
