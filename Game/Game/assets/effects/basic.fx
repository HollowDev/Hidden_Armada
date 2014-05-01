// application exposed variables
float4x4 gWorld : WORLD;
float4x4 gView : VIEW;
float4x4 gProj : PROJECTION;
float4x4 gViewProjection : VIEWPROJECTION;

float4 gRenderColor;

// vertex shader inputs (must match the vertex declaration in C++)
struct VS_INPUT
{
	float3 position	: POSITION0;
	float2 texcoord : TEXCOORD0;
};
// vertex shader outputs
struct VS_OUTPUT
{
	float4 position	: POSITION0;
	float2 texcoord : TEXCOORD0;
};

// the vertex shader, run once for each vertex
VS_OUTPUT myVertexShader(VS_INPUT input)
{
	VS_OUTPUT output; 
	// Transform position into world coords
	float4 worldloc = float4(input.position,1.0f);
	worldloc = mul(worldloc, gWorld);
	output.position = mul(worldloc, gViewProjection);
	
	// Transfer the normal
	output.texcoord = input.texcoord;
	
	// send data along to the pixel shader (will be interpolated)
	return output; 
}

// the pixel shader, each rasterized triangle's pixels will run through this 
float4 myPixelShader(VS_OUTPUT input) : COLOR
{	
	return gRenderColor;
}

float4 myWireframeShader(VS_OUTPUT input) : COLOR
{
	return gRenderColor;
}

// Techniques are read in by the effect framework.
// They allow one to add variation to how a particular shader might be executed. 
technique myTechnique
{
	// Each pass in the technique corresponds to a single iteration over all 
	// verticies sent during a draw call and the subsequently created pixels. 
	// If we had a special effect that required us to draw our geometry and pixels more than once,
	// we could acheive this by adding more passes across our vertex and pixel data.
    pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
		vertexShader = compile vs_3_0 myVertexShader();
		pixelShader  = compile ps_3_0 myPixelShader();
        //FillMode = WIREFRAME; // no wireframes, no point drawing.
        CullMode = NONE; // cull any clockwise polygons.
    }
}