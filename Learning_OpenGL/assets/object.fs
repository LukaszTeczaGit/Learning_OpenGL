#version 330 core
//collecting data form vertex shader and setting coordinates to color

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixVal;

void main(){
	//FragColor = vec4(1.0f, 0.2f, 0.6f, 1.0f);
	//FragColor = vec4(ourColor, 1.0f);
	//FragColor = texture(texture1, TexCoord);
	//FragColor = vec4(ourColor, 1.0f) * texture(texture2, TexCoord);
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixVal);
}