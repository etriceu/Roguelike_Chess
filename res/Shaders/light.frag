#define SIZE 96
uniform sampler2D texture;
uniform vec3 ambient;
uniform int size;
uniform vec4[SIZE] color;//r, g, b, intensity
uniform vec3[SIZE] circle;//x, y, radius 

void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

	vec3 c;
	for(int n = 0; n < size; n++)
	{
		float d = distance(circle[n].xy, gl_TexCoord[0].xy);
		if(d <= circle[n].z)
			c += color[n].xyz*clamp(1.0-d/circle[n].z, 0.0, 1.0)*color[n].w;
	}
	gl_FragColor = vec4((c+ambient)*pixel.xyz, pixel.w);
}
