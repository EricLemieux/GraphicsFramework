#version 330 core

in vec2 passTexcoord;

uniform sampler2D sceneDiffuse;

out vec4 fragColour;

vec3 rgb2hsl(in vec3 rgb);
vec3 hsl2rgb(in vec3 hsl);

vec3 kernel(in vec2 tex, in sampler2D image, in mat3 kernel);

void main()
{
	//fragColour.rgb = texture(sceneDiffuse, passTexcoord).rgb;
	//
	//fragColour.g += 0.5;
	//
	//fragColour.xyz = rgb2hsl(fragColour.rgb);
	//
	//fragColour.y += 0.4;
	//
	////fragColour.xyz = 1 - fragColour.xyz;
	//
	//fragColour.rgb = hsl2rgb(fragColour.xyz);

	

	vec3 diffuse = texture(sceneDiffuse, passTexcoord).rgb;

	mat3 edgeDetect =	mat3(0,1,0
							,1,-4,1
							,0,1,0);

	vec3 outline = kernel( passTexcoord, sceneDiffuse, edgeDetect);
	float maxVal = max(outline.r, max(outline.g, outline.b));
	outline = vec3(maxVal);

	//fragColour.rgb =	outline + diffuse;
	fragColour.rgb = diffuse;
}

vec3 kernel(in vec2 tex, in sampler2D image, in mat3 kernel)
{
	vec3 outputValue = vec3(0);

	float size = 0.001;

	outputValue += kernel[0].x * texture(image, tex + (vec2(-1, 1) * size)).rgb;
	outputValue += kernel[0].y * texture(image, tex + (vec2(-1, 0) * size)).rgb;
	outputValue += kernel[0].z * texture(image, tex + (vec2(-1,-1) * size)).rgb;
												
	outputValue += kernel[1].x * texture(image, tex + (vec2( 0, 1) * size)).rgb;
	outputValue += kernel[1].y * texture(image, tex + (vec2( 0, 0) * size)).rgb;
	outputValue += kernel[1].z * texture(image, tex + (vec2( 0,-1) * size)).rgb;
														
	outputValue += kernel[2].x * texture(image, tex + (vec2( 1, 1) * size)).rgb;
	outputValue += kernel[2].y * texture(image, tex + (vec2( 1, 0) * size)).rgb;
	outputValue += kernel[2].z * texture(image, tex + (vec2( 1,-1) * size)).rgb;

	return outputValue;
}

// convert RGB to HSL
vec3 rgb2hsl(in vec3 rgb)
{
	float r = rgb.r, g = rgb.g, b = rgb.b;

	float minimum = min(r, min(g, b));
	float maximum = max(r, max(g, b));

	// luminance is the average of the minimum and maximum
	float h, s;
	float l = (minimum + maximum)*0.5;

	// if the min and max are the same, it implies 
	//	the colour is greyscale (achromatic), meaning 
	//	completely desaturated and hue doesn't matter
	// btw it's faster to put 'if !=' because that's more likely
	if (minimum != maximum)
	{
		// saturation describes how far the colour is 
		//	from being greyscale
		float diff = maximum - minimum;
		s = (l > 0.5) ? (diff / (2.0 - maximum - minimum)) : (diff / (maximum + minimum));

		// now select the hue
		// we divide by six at the end because this process 
		//	returns a number between 0 and 6 and we want it 
		//	to be normalized!
		if (maximum == r)
			h = (g - b)/diff;
		else if (maximum == g)
			h = (b - r)/diff + 2.0;
		else
			h = (r - g)/diff + 4.0;

		// normalize and make sure it's in [0, 1]
		h /= 6.0;
		if (h < 0.0)
			h += 1.0;
	}
	else
	{
		h = s = 0.0;
	}

	return vec3(h, s, l);
}

// internal function that converts 
//	hue into its respective RGB colour
// why these names? dunno... it just works
float h2rgb(in float p, in float q, in float t)
{
	// t is obviously important if it needs to be in [0, 1]
	if (t < 0.0)		t += 1.0;
	else if (t > 1.0)	t -= 1.0;

	// wizardry
	if (t*6.0 < 1.0)	return ( p + (q - p)*6.0*(t) );
	if (t < 0.5)		return ( q );
	if (t*3.0 < 2.0)	return ( p + (q - p)*6.0*(2.0/3.0 - t));
	
	// when in doubt, always choose p... because magic
	return p;
}

// use witchcraft to convert HSL to RGB
vec3 hsl2rgb(in vec3 hsl)
{
	float h = hsl.x, s = hsl.y, l = hsl.z;

	// if the saturation is zero, then we are greyscale
	// it's more likely we will not be totally greyscale
	if (s != 0.0)
	{
		float r, g, b;

		float q = (l < 0.5) ? (l*(1.0 + s)) : (l + s - l*s);
		float p = 2.0*l - q;
		r = h2rgb(p, q, (h + 1.0/3.0));
		g = h2rgb(p, q, (h));
		b = h2rgb(p, q, (h - 1.0/3.0));

		return vec3(r, g, b);
	}

	// if we are greyscale, just return the luminance
	return vec3(l);
}