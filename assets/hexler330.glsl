uniform vec3      	iResolution; 			// viewport resolution (in pixels)
uniform float     	iGlobalTime; 			// shader playback time (in seconds)
uniform vec4      	iMouse; 				// mouse pixel coords. xy: current (if MLB down), zw: click
uniform sampler2D 	iChannel0; 				// input channel 0
uniform sampler2D 	iChannel1; 				// input channel 1
uniform sampler2D 	iChannel2; 				// input channel 2
uniform sampler2D 	iChannel3; 				// input channel 3
uniform vec4      	iDate; 					// (year, month, day, time in seconds)
// videodromm specific
uniform vec3        iBackgroundColor;    	// background color
uniform vec3        iColor;              	// color
uniform int         iSteps;              	// steps for iterations
uniform float       iRatio;
uniform vec2        iRenderXY;           	// move x y
uniform float       iZoom;               	// zoom
uniform float       iCrossfade;          	// CrossFade 2 shaders
uniform float       iAlpha;          	  	// alpha
uniform bool        iFlipH;					// flip horizontally
uniform bool        iFlipV;					// flip vertically
uniform float       iFreq0;              // sound
uniform float       iFreq1;              // sound
uniform float       iFreq2;              // sound
uniform float       iFreq3;              // sound
uniform vec3 		spectrum;              // sound
uniform int         iInvert;           		// 1 for color inversion
uniform float		iFps;
uniform float		iBadTv;
uniform float     	iTempoTime; 			// texture animation

out vec4 fragColor;
vec2  fragCoord = gl_FragCoord.xy; // keep the 2 spaces between vec2 and fragCoord
void main() {
	vec2 uv = 2 * (gl_FragCoord.xy / iResolution.xy - vec2(0.5));

	float radius = length(uv);
	float angle = atan(uv.y,uv.x);
	
    float col = .0;
    col += 1.5*sin(iGlobalTime + 13.0 * angle + uv.y * 20);
    col += cos(.9 * uv.x * angle * 60.0 + radius * 5.0 -iGlobalTime * 2.);
	//col = 1.0 -col;
   	fragColor = (1.2 - radius) * vec4(vec3( col ),1.0);
}
