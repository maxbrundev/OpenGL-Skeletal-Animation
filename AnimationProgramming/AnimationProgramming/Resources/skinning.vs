
/////////////////////
// INPUT VARIABLES //
/////////////////////
in lowp vec3 inputPosition;
in lowp vec3 normal;
in lowp vec4 boneIndices;
in lowp vec4 boneWeights;

//////////////////////
// OUTPUT VARIABLES //
//////////////////////
smooth out vec2 texCoord;
smooth out vec3 outNormal;

uniform SceneMatrices
{
	uniform mat4 projectionMatrix;
} sm;

uniform mat4 modelViewMatrix;

uniform SkinningMatrices
{
	uniform mat4 mat[64];
} skin;



////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	// Calculate the position of the vertex against the world, view, and projection matrices.
	// Calculate the position of the vertex against the world, view, and projection matrices.
	vec4 pos = vec4(inputPosition, 1.0f);

	vec4 pos2 = vec4(0, 0, 0, 1);
	pos2 += boneWeights[0] * (pos * skin.mat[int(boneIndices[0])]);
	pos2 += boneWeights[1] * (pos * skin.mat[int(boneIndices[1])]);
	pos2 += boneWeights[2] * (pos * skin.mat[int(boneIndices[2])]);
	pos2 += boneWeights[3] * (pos * skin.mat[int(boneIndices[3])]);

	vec3 norm = normal;
	vec3 n2 = vec3(0, 0, 0);
	n2 += boneWeights[0] * (norm * mat3(skin.mat[int(boneIndices[0])]));
	n2 += boneWeights[1] * (norm * mat3(skin.mat[int(boneIndices[1])]));
	n2 += boneWeights[2] * (norm * mat3(skin.mat[int(boneIndices[2])]));
	n2 += boneWeights[3] * (norm * mat3(skin.mat[int(boneIndices[3])]));

	gl_Position = sm.projectionMatrix * (modelViewMatrix * vec4(pos2.xyz, 1.0f)); // pos2 instead
	outNormal = mat3(modelViewMatrix) * n2; //* n2 instead

	outNormal = normalize(outNormal);
}
