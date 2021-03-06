#include "UIBatchRenderer.h"
#ifdef WIN32
#include "GL/glew.h"
#else
//#include <OpenGLES/ES2/gl.h>
#endif

#define CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL 1

UIBatchRenderer::UIBatchRenderer()
	: m_pQuads(NULL)
	, m_pIndices(NULL)
	, m_uTotalQuads(0)
	, m_uCapacity(10)
	, m_pTexture(NULL)
{
	m_sBlendFunc.src = CC_BLEND_SRC;
	m_sBlendFunc.dst = CC_BLEND_DST;
}

UIBatchRenderer::~UIBatchRenderer()
{

}

void UIBatchRenderer::initilize()
{
	m_pProgram = ShaderCache::getInstance()->programForKey(kCCShader_PositionTextureColor);
	m_pProgram->retain();

	m_uTotalQuads = 0;
	m_uCapacity = 10;

	unsigned int size = m_uCapacity * sizeof(ccV3F_C4B_T2F_Quad);
	m_pQuads = (V3F_C4B_T2F_Quad*)malloc(size);
	assert(m_pQuads);
	memset(m_pQuads, 0, size);

	size = m_uCapacity * 6 * sizeof(GLushort);
	m_pIndices = (GLushort*)malloc(size);
	assert(m_pIndices);
	memset(m_pIndices, 0, size);

	setupIndices();
}

void UIBatchRenderer::unintilize()
{
	if (m_pQuads){
		free(m_pQuads);
		m_pQuads = NULL;
	}
	if (m_pIndices){
		free(m_pIndices);
		m_pIndices = NULL;
	}
	
	CC_SAFE_RELEASE(m_pTexture);

	m_pProgram->release();
}


void UIBatchRenderer::setShader( CCGLProgram* program )
{
	if (!program)
		return;
	if (m_pProgram == program)
		return;

	flush();

	CC_SAFE_RELEASE(m_pProgram);
	m_pProgram = program;
	CC_SAFE_RETAIN(m_pProgram);
}


void UIBatchRenderer::setTexture(Texture2D* pTexture)
{
	log("UIBatchRenderer::setTexture-->%s", pTexture->getPath().c_str());
	if (m_pTexture != pTexture){
		if (m_pTexture){
			if (!m_pTexture->hasPremultipliedAlpha()){
				m_sBlendFunc.src = GL_SRC_ALPHA;
				m_sBlendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
			}else{
				m_sBlendFunc.src = CC_BLEND_SRC;
				m_sBlendFunc.dst = CC_BLEND_DST;
			}
		}

		flush();
		
		CC_SAFE_RELEASE(m_pTexture);
		m_pTexture = pTexture;
		log("UIBatchRenderer::setTexture-->%d", pTexture->getName());
		CC_SAFE_RETAIN(m_pTexture);
	}
}

#if CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL(__A__) ( (int)(__A__))
#endif

void UIBatchRenderer::drawImage(int u, int v, int texWidth, int texHeight, int atlasWidth, int atlasHeight, int x, int y, int width, int height, const ccColor4B& color)
{
	if (m_uTotalQuads + 1 >= m_uCapacity){
		unsigned int newCapacity = (m_uCapacity + 1) * 4 / 3;
		resizeCapicity(newCapacity);
	}

	log("drawImage u=%d, v=%d, texWidth=%d, texHeight=%d, atlasWidth=%d, atlasHeight=%d, x=%d, y=%d, width=%d, height=%d", u, v, texWidth, texHeight, atlasWidth, atlasHeight, x, y, width, height);
#ifdef DQ_BATCH_RENDERER
	/*
	setRectInBase(Rect(Vec2::ZERO, _texture->getContentSize()));
	V3F_C4B_T2F_Quad quads[] =
	{
		{
			{ Vec3(0, 0, 0), Color4B(0, 0, 255, 255), Tex2F(0.0f, 1.0f), },                // bottom left
			{ Vec3(s.width, 0, 0), Color4B(0, 0, 255, 0), Tex2F(1.0f, 1.0f), },            // bottom right
			{ Vec3(0, s.height, 0), Color4B(0, 0, 255, 0), Tex2F(0.0f, 0.0f), },            // top left
			{ Vec3(s.width, s.height, 0), Color4B(0, 0, 255, 255), Tex2F(1.0f, 0.0f), },    // top right
		},
	};
	*/
	V3F_C4B_T2F_Quad quad;

	Rect rectVertices;
	rectVertices.origin.x = (float)x;
	rectVertices.origin.y = (float)y;
	rectVertices.size.width = (float)width;
	rectVertices.size.height = (float)height;

	float x1 = rectVertices.origin.x;
	float y1 = rectVertices.origin.y;
	float x2 = x1 + rectVertices.size.width;
	float y2 = y1 + rectVertices.size.height;

	// update transform

	quad.bl.vertices = vertex3(x1, y1, 0);
	quad.br.vertices = vertex3(x2, y1, 0);
	quad.tl.vertices = vertex3(x1, y2, 0);
	quad.tr.vertices = vertex3(x2, y2, 0);
	/*
	quad.bl.vertices.x = RENDER_IN_SUBPIXEL(quad.bl.vertices.x * out.m[0] + quad.bl.vertices.y * out.m[4] + quad.bl.vertices.z * out.m[8] + out.m[12]);
	quad.bl.vertices.y = RENDER_IN_SUBPIXEL(quad.bl.vertices.x * out.m[1] + quad.bl.vertices.y * out.m[5] + quad.bl.vertices.z * out.m[9] + out.m[13]);
	quad.bl.vertices.z = RENDER_IN_SUBPIXEL(quad.bl.vertices.x * out.m[2] + quad.bl.vertices.y * out.m[6] + quad.bl.vertices.z * out.m[10] + out.m[14]);

	quad.br.vertices.x = RENDER_IN_SUBPIXEL(quad.br.vertices.x * out.m[0] + quad.br.vertices.y * out.m[4] + quad.br.vertices.z * out.m[8] + out.m[12]);
	quad.br.vertices.y = RENDER_IN_SUBPIXEL(quad.br.vertices.x * out.m[1] + quad.br.vertices.y * out.m[5] + quad.br.vertices.z * out.m[9] + out.m[13]);
	quad.br.vertices.z = RENDER_IN_SUBPIXEL(quad.br.vertices.x * out.m[2] + quad.br.vertices.y * out.m[6] + quad.br.vertices.z * out.m[10] + out.m[14]);

	quad.tl.vertices.x = RENDER_IN_SUBPIXEL(quad.tl.vertices.x * out.m[0] + quad.tl.vertices.y * out.m[4] + quad.tl.vertices.z * out.m[8] + out.m[12]);
	quad.tl.vertices.y = RENDER_IN_SUBPIXEL(quad.tl.vertices.x * out.m[1] + quad.tl.vertices.y * out.m[5] + quad.tl.vertices.z * out.m[9] + out.m[13]);
	quad.tl.vertices.z = RENDER_IN_SUBPIXEL(quad.tl.vertices.x * out.m[2] + quad.tl.vertices.y * out.m[6] + quad.tl.vertices.z * out.m[10] + out.m[14]);

	quad.tr.vertices.x = RENDER_IN_SUBPIXEL(quad.tr.vertices.x * out.m[0] + quad.tr.vertices.y * out.m[4] + quad.tr.vertices.z * out.m[8] + out.m[12]);
	quad.tr.vertices.y = RENDER_IN_SUBPIXEL(quad.tr.vertices.x * out.m[1] + quad.tr.vertices.y * out.m[5] + quad.tr.vertices.z * out.m[9] + out.m[13]);
	quad.tr.vertices.z = RENDER_IN_SUBPIXEL(quad.tr.vertices.x * out.m[2] + quad.tr.vertices.y * out.m[6] + quad.tr.vertices.z * out.m[10] + out.m[14]);
	*/

	Rect rectTexture;
	rectTexture.origin.x = (float)u;
	rectTexture.origin.y = (float)v;
	rectTexture.size.width = (float)texWidth;
	rectTexture.size.height = (float)texHeight;

	float left,	right, top,	bottom;
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
	left = (2 * rectTexture.origin.x + 1) / (2 * atlasWidth);
	right = left + (rectTexture.size.width * 2 - 2) / (2 * atlasWidth);
	top = (2 * rectTexture.origin.y + 1) / (2 * atlasHeight);
	bottom = top + (rectTexture.size.height * 2 - 2) / (2 * atlasHeight);
#else
	left = rectTexture.origin.x / atlasWidth;
	right = (rectTexture.origin.x + rectTexture.size.width) / atlasWidth;
	top = rectTexture.origin.y / atlasHeight;
	bottom = (rectTexture.origin.y + rectTexture.size.height) / atlasHeight;
#endif

	quad.bl.texCoords.u = left;
	quad.bl.texCoords.v = bottom;
	quad.br.texCoords.u = right;
	quad.br.texCoords.v = bottom;
	quad.tl.texCoords.u = left;
	quad.tl.texCoords.v = top;
	quad.tr.texCoords.u = right;
	quad.tr.texCoords.v = top;

	quad.bl.colors =
		quad.br.colors =
		quad.tl.colors =
		quad.tr.colors = color;

	quad.bl.colors.r = quad.bl.colors.r * color.a >> 8;
	quad.bl.colors.g = quad.bl.colors.g * color.a >> 8;
	quad.bl.colors.b = quad.bl.colors.b * color.a >> 8;
	quad.bl.colors.a = color.a;

	quad.br.colors.r = quad.br.colors.r * color.a >> 8;
	quad.br.colors.g = quad.br.colors.g * color.a >> 8;
	quad.br.colors.b = quad.br.colors.b * color.a >> 8;
	quad.br.colors.a = color.a;

	quad.tl.colors.r = quad.tl.colors.r * color.a >> 8;
	quad.tl.colors.g = quad.tl.colors.g * color.a >> 8;
	quad.tl.colors.b = quad.tl.colors.b * color.a >> 8;
	quad.tl.colors.a = color.a;

	quad.tr.colors.r = quad.tr.colors.r * color.a >> 8;
	quad.tr.colors.g = quad.tr.colors.g * color.a >> 8;
	quad.tr.colors.b = quad.tr.colors.b * color.a >> 8;
	quad.tr.colors.a = color.a;

	m_uTotalQuads++;
	assert(m_uTotalQuads <= m_uCapacity);

	m_pQuads[m_uTotalQuads - 1] = quad;

	//坐标确定，纹理坐标值越大，单张纹理（0到1）越小
	/*
		float lightScaleX = width / texWidth;
		float lightScaleY = height / texHeight;

		float originX = x;
		float originY = y;

		// 0, 0       0, 1       1, 0          1, 1
		for (int i = 0; i<4; ++i) {
			_verts[i].color = Color4F::WHITE;
			_verts[i].vertices = baseInfo.triangles.verts[i].vertices;
			_verts[i].texCoords = baseInfo.triangles.verts[i].texCoords;
		}
	*/
#else
	if (m_uTotalQuads + 1 >= m_uCapacity){
		unsigned int newCapacity = (m_uCapacity + 1) * 4 / 3;
		resizeCapicity(newCapacity);
	}
	
	Mat4 out;
	kmGLGetMatrix(KM_GL_MODELVIEW, &out);

	V3F_C4B_T2F_Quad quad;

	Rect rectVertices;
	rectVertices.origin.x = (float)x;
	rectVertices.origin.y = (float)y;
	rectVertices.size.width = (float)width;
	rectVertices.size.height = (float)height;

	float x1 = rectVertices.origin.x;
	float y1 = rectVertices.origin.y;
	float x2 = x1 + rectVertices.size.width;
	float y2 = y1 + rectVertices.size.height;

	// update transform
	
	quad.bl.vertices = vertex3(x1, y1, 0);
	quad.br.vertices = vertex3(x2, y1, 0);
	quad.tl.vertices = vertex3(x1, y2, 0);
	quad.tr.vertices = vertex3(x2, y2, 0);
	
	quad.bl.vertices.x = RENDER_IN_SUBPIXEL(quad.bl.vertices.x * out.m[0] + quad.bl.vertices.y * out.m[4] + quad.bl.vertices.z * out.m[8] + out.m[12]);
	quad.bl.vertices.y = RENDER_IN_SUBPIXEL(quad.bl.vertices.x * out.m[1] + quad.bl.vertices.y * out.m[5] + quad.bl.vertices.z * out.m[9] + out.m[13]);
	quad.bl.vertices.z = RENDER_IN_SUBPIXEL(quad.bl.vertices.x * out.m[2] + quad.bl.vertices.y * out.m[6] + quad.bl.vertices.z * out.m[10] + out.m[14]);

	quad.br.vertices.x = RENDER_IN_SUBPIXEL(quad.br.vertices.x * out.m[0] + quad.br.vertices.y * out.m[4] + quad.br.vertices.z * out.m[8] + out.m[12]);
	quad.br.vertices.y = RENDER_IN_SUBPIXEL(quad.br.vertices.x * out.m[1] + quad.br.vertices.y * out.m[5] + quad.br.vertices.z * out.m[9] + out.m[13]);
	quad.br.vertices.z = RENDER_IN_SUBPIXEL(quad.br.vertices.x * out.m[2] + quad.br.vertices.y * out.m[6] + quad.br.vertices.z * out.m[10] + out.m[14]);

	quad.tl.vertices.x = RENDER_IN_SUBPIXEL(quad.tl.vertices.x * out.m[0] + quad.tl.vertices.y * out.m[4] + quad.tl.vertices.z * out.m[8] + out.m[12]);
	quad.tl.vertices.y = RENDER_IN_SUBPIXEL(quad.tl.vertices.x * out.m[1] + quad.tl.vertices.y * out.m[5] + quad.tl.vertices.z * out.m[9] + out.m[13]);
	quad.tl.vertices.z = RENDER_IN_SUBPIXEL(quad.tl.vertices.x * out.m[2] + quad.tl.vertices.y * out.m[6] + quad.tl.vertices.z * out.m[10] + out.m[14]);

	quad.tr.vertices.x = RENDER_IN_SUBPIXEL(quad.tr.vertices.x * out.m[0] + quad.tr.vertices.y * out.m[4] + quad.tr.vertices.z * out.m[8] + out.m[12]);
	quad.tr.vertices.y = RENDER_IN_SUBPIXEL(quad.tr.vertices.x * out.m[1] + quad.tr.vertices.y * out.m[5] + quad.tr.vertices.z * out.m[9] + out.m[13]);
	quad.tr.vertices.z = RENDER_IN_SUBPIXEL(quad.tr.vertices.x * out.m[2] + quad.tr.vertices.y * out.m[6] + quad.tr.vertices.z * out.m[10] + out.m[14]);

	Rect rectTexture;
	rectTexture.origin.x = (float)u;
	rectTexture.origin.y = (float)v;
	rectTexture.size.width = (float)texWidth;
	rectTexture.size.height = (float)texHeight;
	
	float left,
		  right, 
		  top, 
		  bottom;
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
	left = (2 * rectTexture.origin.x + 1) / (2 * atlasWidth);
	right = left + (rectTexture.size.width * 2 - 2) /(2 * atlasWidth);
	top = (2 * rectTexture.origin.y + 1)/(2 * atlasHeight);
	bottom = top + (rectTexture.size.height * 2 - 2) /(2 * atlasHeight);
#else
	left = rectTexture.origin.x / atlasWidth;
	right = (rectTexture.origin.x + rectTexture.size.width) / atlasWidth;
	top = rectTexture.origin.y / atlasHeight;
	bottom = (rectTexture.origin.y + rectTexture.size.height) / atlasHeight;
#endif
	
	quad.bl.texCoords.u = left;
	quad.bl.texCoords.v = bottom;
	quad.br.texCoords.u = right;
	quad.br.texCoords.v = bottom;
	quad.tl.texCoords.u = left;
	quad.tl.texCoords.v = top;
	quad.tr.texCoords.u = right;
	quad.tr.texCoords.v = top;

	quad.bl.colors = 
	quad.br.colors = 
	quad.tl.colors = 
	quad.tr.colors = color;
		
	quad.bl.colors.r = quad.bl.colors.r * color.a >> 8; 
	quad.bl.colors.g = quad.bl.colors.g * color.a >> 8; 
	quad.bl.colors.b = quad.bl.colors.b * color.a >> 8; 
	quad.bl.colors.a = color.a;

	quad.br.colors.r = quad.br.colors.r * color.a >> 8; 
	quad.br.colors.g = quad.br.colors.g * color.a >> 8; 
	quad.br.colors.b = quad.br.colors.b * color.a >> 8; 
	quad.br.colors.a = color.a;
	
	quad.tl.colors.r = quad.tl.colors.r * color.a >> 8; 
	quad.tl.colors.g = quad.tl.colors.g * color.a >> 8; 
	quad.tl.colors.b = quad.tl.colors.b * color.a >> 8; 
	quad.tl.colors.a = color.a;

	quad.tr.colors.r = quad.tr.colors.r * color.a >> 8; 
	quad.tr.colors.g = quad.tr.colors.g * color.a >> 8; 
	quad.tr.colors.b = quad.tr.colors.b * color.a >> 8; 
	quad.tr.colors.a = color.a;
	/*
	quad.bl.colors.r *= color.a / 255.0f; 
	quad.bl.colors.g *= color.a / 255.0f;
	quad.bl.colors.b *=	color.a / 255.0f;
	quad.bl.colors.a = color.a;

	quad.br.colors.r *= color.a / 255.0f; 
	quad.br.colors.g *= color.a / 255.0f;
	quad.br.colors.b *= color.a / 255.0f;
	quad.br.colors.a = color.a;

	quad.tl.colors.r *= color.a / 255.0f; 
	quad.tl.colors.g *= color.a / 255.0f;
	quad.tl.colors.b *= color.a / 255.0f;
	quad.tl.colors.a = color.a;

	quad.tr.colors.r *= color.a / 255.0f; 
	quad.tr.colors.g *= color.a / 255.0f;
	quad.tr.colors.b *= color.a / 255.0f;
	quad.tr.colors.a = color.a;
	*/

	m_uTotalQuads++;
	assert(m_uTotalQuads <= m_uCapacity);
	
	m_pQuads[m_uTotalQuads - 1] = quad;
#endif
}

void UIBatchRenderer::flush()
{
	//log("UIBatchRenderer::flush->m_uTotalQuads=%d, m_uCapacity=%d", m_uTotalQuads, m_uCapacity);
	if (m_uTotalQuads == 0)
		return;
#ifdef DQ_BATCH_RENDERER
	//load mv
	//_glProgramState->apply(_modelViewTransform);

#if 0
	// Load the vertex position
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION,  3, GL_FLOAT, GL_FALSE, size, &_verts[0]);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR,     4, GL_FLOAT, GL_FALSE, size, &(_verts[0].color));
	// Load the texture coordinate
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, size, &(_verts[0].texCoords));
#else
#define kQuadSize sizeof(m_pQuads[0].bl)
	long offset = (long)&m_pQuads[0];

	// vertex
	int diff = offsetof(V3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
	// texCoods
	diff = offsetof(V3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
	// color
	diff = offsetof(V3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
#endif

	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD1);

	//bind texture
	GL::bindTextureN(0, m_pTexture->getName());
	//glUniform1i(_glProgramState->getGLProgram()->getUniformLocation(GLProgram::UNIFORM_NAME_SAMPLER0), 0);

	//draw
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, quadIndices);
	glDrawElements(GL_TRIANGLES, (GLsizei)m_uTotalQuads * 6, GL_UNSIGNED_SHORT, (GLvoid*)(m_pIndices));


	//ccGLBindTexture2D(m_pTexture->getName());
	//log("UIBatchRenderer::flush->5");
	//ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);

	CC_INCREMENT_GL_DRAWS(1);

	//kmGLPopMatrix();

	m_uTotalQuads = 0;

#else
	//log("UIBatchRenderer::flush->1");
	if (m_uTotalQuads == 0)
		return;

	kmGLPushMatrix();
	//log("UIBatchRenderer::flush->2");
	Mat4 proj;
	kmGLGetMatrix(KM_GL_PROJECTION, &proj);

	//log("UIBatchRenderer::flush->3");
	m_pProgram->use();
	//->setUniformLocationWithMatrix4fv(m_pProgram->getUniform[kCCUniformMVPMatrix], proj.m, 1);
	//m_pProgram->
	//m_pProgram->setUniformLocationwithMatrix4fv(m_pProgram->m_uUniforms[kCCUniformMVPMatrix], proj.mat, 1);
	//m_pProgram->getbai
	glEnable(GL_BLEND);
	//log("UIBatchRenderer::flush->4");
	ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);

	ccGLBindTexture2D(m_pTexture->getName());
	//log("UIBatchRenderer::flush->5");
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);

#define kQuadSize sizeof(m_pQuads[0].bl)
	long offset = (long)&m_pQuads[0];
	//log("UIBatchRenderer::flush->6");

	// vertex
	int diff = offsetof(V3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
	//log("UIBatchRenderer::flush->7");
	// texCoods
	diff = offsetof(V3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
	//log("UIBatchRenderer::flush->8");
	// color
	diff = offsetof(V3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));

	glDrawElements(GL_TRIANGLES, (GLsizei)m_uTotalQuads * 6, GL_UNSIGNED_SHORT, (GLvoid*)(m_pIndices));
	//log("UIBatchRenderer::flush->9");
	CC_INCREMENT_GL_DRAWS(1);

	kmGLPopMatrix();

	m_uTotalQuads = 0;
#endif
}
void UIBatchRenderer::drawImage_Reverse(int u, int v, int texWidth, int texHeight, int atlasWidth, int atlasHeight, int x, int y, int width, int height, const ccColor4B& color)
{
	if (m_uTotalQuads + 1 >= m_uCapacity)
	{
		unsigned int newCapacity = (m_uCapacity + 1) * 4 / 3;
		resizeCapicity(newCapacity);
	}
	
	Mat4 out;
	kmGLGetMatrix(KM_GL_MODELVIEW, &out);

	V3F_C4B_T2F_Quad quad;

	Rect rectVertices;
	rectVertices.origin.x = (float)x;
	rectVertices.origin.y = (float)y;
	rectVertices.size.width = (float)width;
	rectVertices.size.height = (float)height;

	float x1 = rectVertices.origin.x;
	float y1 = rectVertices.origin.y;
	float x2 = x1 + rectVertices.size.width;
	float y2 = y1 + rectVertices.size.height;

	// update transform
	
	quad.bl.vertices = vertex3(x2, y1, 0);
	quad.br.vertices = vertex3(x1, y1, 0);
	quad.tl.vertices = vertex3(x2, y2, 0);
	quad.tr.vertices = vertex3(x1, y2, 0);

	quad.bl.vertices.x = RENDER_IN_SUBPIXEL(quad.bl.vertices.x * out.m[0] + quad.bl.vertices.y * out.m[4] + quad.bl.vertices.z * out.m[8] + out.m[12]);
	quad.bl.vertices.y = RENDER_IN_SUBPIXEL(quad.bl.vertices.x * out.m[1] + quad.bl.vertices.y * out.m[5] + quad.bl.vertices.z * out.m[9] + out.m[13]);
	quad.bl.vertices.z = RENDER_IN_SUBPIXEL(quad.bl.vertices.x * out.m[2] + quad.bl.vertices.y * out.m[6] + quad.bl.vertices.z * out.m[10] + out.m[14]);

	quad.br.vertices.x = RENDER_IN_SUBPIXEL(quad.br.vertices.x * out.m[0] + quad.br.vertices.y * out.m[4] + quad.br.vertices.z * out.m[8] + out.m[12]);
	quad.br.vertices.y = RENDER_IN_SUBPIXEL(quad.br.vertices.x * out.m[1] + quad.br.vertices.y * out.m[5] + quad.br.vertices.z * out.m[9] + out.m[13]);
	quad.br.vertices.z = RENDER_IN_SUBPIXEL(quad.br.vertices.x * out.m[2] + quad.br.vertices.y * out.m[6] + quad.br.vertices.z * out.m[10] + out.m[14]);

	quad.tl.vertices.x = RENDER_IN_SUBPIXEL(quad.tl.vertices.x * out.m[0] + quad.tl.vertices.y * out.m[4] + quad.tl.vertices.z * out.m[8] + out.m[12]);
	quad.tl.vertices.y = RENDER_IN_SUBPIXEL(quad.tl.vertices.x * out.m[1] + quad.tl.vertices.y * out.m[5] + quad.tl.vertices.z * out.m[9] + out.m[13]);
	quad.tl.vertices.z = RENDER_IN_SUBPIXEL(quad.tl.vertices.x * out.m[2] + quad.tl.vertices.y * out.m[6] + quad.tl.vertices.z * out.m[10] + out.m[14]);

	quad.tr.vertices.x = RENDER_IN_SUBPIXEL(quad.tr.vertices.x * out.m[0] + quad.tr.vertices.y * out.m[4] + quad.tr.vertices.z * out.m[8] + out.m[12]);
	quad.tr.vertices.y = RENDER_IN_SUBPIXEL(quad.tr.vertices.x * out.m[1] + quad.tr.vertices.y * out.m[5] + quad.tr.vertices.z * out.m[9] + out.m[13]);
	quad.tr.vertices.z = RENDER_IN_SUBPIXEL(quad.tr.vertices.x * out.m[2] + quad.tr.vertices.y * out.m[6] + quad.tr.vertices.z * out.m[10] + out.m[14]);

	Rect rectTexture;
	rectTexture.origin.x = (float)u;
	rectTexture.origin.y = (float)v;
	rectTexture.size.width = (float)texWidth;
	rectTexture.size.height = (float)texHeight;
	
	float left,
		  right, 
		  top, 
		  bottom;
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
	left = (2 * rectTexture.origin.x + 1) / (2 * atlasWidth);
	right = left + (rectTexture.size.width * 2 - 2) /(2 * atlasWidth);
	top = (2 * rectTexture.origin.y + 1)/(2 * atlasHeight);
	bottom = top + (rectTexture.size.height * 2 - 2) /(2 * atlasHeight);
#else
	left = rectTexture.origin.x / atlasWidth;
	right = (rectTexture.origin.x + rectTexture.size.width) / atlasWidth;
	top = rectTexture.origin.y / atlasHeight;
	bottom = (rectTexture.origin.y + rectTexture.size.height) / atlasHeight;
#endif
	
	quad.bl.texCoords.u = left;
	quad.bl.texCoords.v = bottom;
	quad.br.texCoords.u = right;
	quad.br.texCoords.v = bottom;
	quad.tl.texCoords.u = left;
	quad.tl.texCoords.v = top;
	quad.tr.texCoords.u = right;
	quad.tr.texCoords.v = top;

	quad.bl.colors = 
	quad.br.colors = 
	quad.tl.colors = 
	quad.tr.colors = color;
		
	quad.bl.colors.r = quad.bl.colors.r * color.a >> 8; 
	quad.bl.colors.g = quad.bl.colors.g * color.a >> 8; 
	quad.bl.colors.b = quad.bl.colors.b * color.a >> 8; 
	quad.bl.colors.a = color.a;

	quad.br.colors.r = quad.br.colors.r * color.a >> 8; 
	quad.br.colors.g = quad.br.colors.g * color.a >> 8; 
	quad.br.colors.b = quad.br.colors.b * color.a >> 8; 
	quad.br.colors.a = color.a;
	
	quad.tl.colors.r = quad.tl.colors.r * color.a >> 8; 
	quad.tl.colors.g = quad.tl.colors.g * color.a >> 8; 
	quad.tl.colors.b = quad.tl.colors.b * color.a >> 8; 
	quad.tl.colors.a = color.a;

	quad.tr.colors.r = quad.tr.colors.r * color.a >> 8; 
	quad.tr.colors.g = quad.tr.colors.g * color.a >> 8; 
	quad.tr.colors.b = quad.tr.colors.b * color.a >> 8; 
	quad.tr.colors.a = color.a;
	/*
	quad.bl.colors.r *= color.a / 255.0f; 
	quad.bl.colors.g *= color.a / 255.0f;
	quad.bl.colors.b *=	color.a / 255.0f;
	quad.bl.colors.a = color.a;

	quad.br.colors.r *= color.a / 255.0f; 
	quad.br.colors.g *= color.a / 255.0f;
	quad.br.colors.b *= color.a / 255.0f;
	quad.br.colors.a = color.a;

	quad.tl.colors.r *= color.a / 255.0f; 
	quad.tl.colors.g *= color.a / 255.0f;
	quad.tl.colors.b *= color.a / 255.0f;
	quad.tl.colors.a = color.a;

	quad.tr.colors.r *= color.a / 255.0f; 
	quad.tr.colors.g *= color.a / 255.0f;
	quad.tr.colors.b *= color.a / 255.0f;
	quad.tr.colors.a = color.a;
	*/

	m_uTotalQuads++;
	assert(m_uTotalQuads <= m_uCapacity);
	
	m_pQuads[m_uTotalQuads - 1] = quad;
}

void UIBatchRenderer::drawImage2(float u1, float v1, float u2, float v2, int texWidth, int texHeight, int atlasWidth, int atlasHeight, int mx1, int my1, int mx2, int my2, const ccColor4B& color)
{
	if (m_uTotalQuads + 1 >= m_uCapacity)
	{
		unsigned int newCapacity = (m_uCapacity + 1) * 4 / 3;
		resizeCapicity(newCapacity);
	}
	
	Mat4 out;
	kmGLGetMatrix(KM_GL_MODELVIEW, &out);

	V3F_C4B_T2F_Quad quad;

	float x1 = (float)mx1;
	float y1 = (float)my1;
	float x2 = (float)mx2;
	float y2 = (float)my2;

	// update transform
	Point dir(y2-y1, -x2+x1);
	float len = sqrt(dir.x*dir.x + dir.y*dir.y);
	dir.x = dir.x / len;
	dir.y = dir.y / len;
// 	quad.bl.vertices = vertex3(x1, y1, 0);
// 	quad.br.vertices = vertex3(x2, y2 - 10.0f, 0);
// 	quad.tl.vertices = vertex3(x1, y1 + 10.0f, 0);
// 	quad.tr.vertices = vertex3(x2, y2, 0);

	quad.tl.vertices = vertex3(x1-dir.x*(float)texWidth/2, y1-dir.y*(float)texHeight/2,0);
	quad.bl.vertices = vertex3(x1+dir.x*(float)texWidth/2, y1+dir.y*(float)texHeight/2,0);
	quad.tr.vertices = vertex3(x2-dir.x*(float)texWidth/2, y2-dir.y*(float)texHeight/2,0);
	quad.br.vertices = vertex3(x2+dir.x*(float)texWidth/2, y2+dir.y*(float)texHeight/2,0);

	quad.bl.vertices.x = RENDER_IN_SUBPIXEL(quad.bl.vertices.x * out.m[0] + quad.bl.vertices.y * out.m[4] + quad.bl.vertices.z * out.m[8] + out.m[12]);
	quad.bl.vertices.y = RENDER_IN_SUBPIXEL(quad.bl.vertices.x * out.m[1] + quad.bl.vertices.y * out.m[5] + quad.bl.vertices.z * out.m[9] + out.m[13]);
	quad.bl.vertices.z = RENDER_IN_SUBPIXEL(quad.bl.vertices.x * out.m[2] + quad.bl.vertices.y * out.m[6] + quad.bl.vertices.z * out.m[10] + out.m[14]);

	quad.br.vertices.x = RENDER_IN_SUBPIXEL(quad.br.vertices.x * out.m[0] + quad.br.vertices.y * out.m[4] + quad.br.vertices.z * out.m[8] + out.m[12]);
	quad.br.vertices.y = RENDER_IN_SUBPIXEL(quad.br.vertices.x * out.m[1] + quad.br.vertices.y * out.m[5] + quad.br.vertices.z * out.m[9] + out.m[13]);
	quad.br.vertices.z = RENDER_IN_SUBPIXEL(quad.br.vertices.x * out.m[2] + quad.br.vertices.y * out.m[6] + quad.br.vertices.z * out.m[10] + out.m[14]);

	quad.tl.vertices.x = RENDER_IN_SUBPIXEL(quad.tl.vertices.x * out.m[0] + quad.tl.vertices.y * out.m[4] + quad.tl.vertices.z * out.m[8] + out.m[12]);
	quad.tl.vertices.y = RENDER_IN_SUBPIXEL(quad.tl.vertices.x * out.m[1] + quad.tl.vertices.y * out.m[5] + quad.tl.vertices.z * out.m[9] + out.m[13]);
	quad.tl.vertices.z = RENDER_IN_SUBPIXEL(quad.tl.vertices.x * out.m[2] + quad.tl.vertices.y * out.m[6] + quad.tl.vertices.z * out.m[10] + out.m[14]);

	quad.tr.vertices.x = RENDER_IN_SUBPIXEL(quad.tr.vertices.x * out.m[0] + quad.tr.vertices.y * out.m[4] + quad.tr.vertices.z * out.m[8] + out.m[12]);
	quad.tr.vertices.y = RENDER_IN_SUBPIXEL(quad.tr.vertices.x * out.m[1] + quad.tr.vertices.y * out.m[5] + quad.tr.vertices.z * out.m[9] + out.m[13]);
	quad.tr.vertices.z = RENDER_IN_SUBPIXEL(quad.tr.vertices.x * out.m[2] + quad.tr.vertices.y * out.m[6] + quad.tr.vertices.z * out.m[10] + out.m[14]);

 	Rect rectTexture;
 	rectTexture.origin.x = (float)0;
 	rectTexture.origin.y = (float)0;
 	rectTexture.size.width = (float)texWidth;
 	rectTexture.size.height = (float)texHeight;
	
 	float left,
 		  right, 
 		  top, 
 		  bottom;
// #if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
 	left = (2 * rectTexture.origin.x + 1) / (2 * atlasWidth);
 	right = left + (rectTexture.size.width * 2 - 2) /(2 * atlasWidth);
 	top = (2 * rectTexture.origin.y + 1)/(2 * atlasHeight);
 	bottom = top + (rectTexture.size.height * 2 - 2) /(2 * atlasHeight);
// #else
// 	left = rectTexture.origin.x / atlasWidth;
// 	right = (rectTexture.origin.x + rectTexture.size.width) / atlasWidth;
// 	top = rectTexture.origin.y / atlasHeight;
// 	bottom = (rectTexture.origin.y + rectTexture.size.height) / atlasHeight;
// #endif
	
	quad.bl.texCoords.u = (GLfloat)u2;
	quad.bl.texCoords.v = (GLfloat)v1;
	quad.br.texCoords.u = (GLfloat)u1;
	quad.br.texCoords.v = (GLfloat)v1;
	quad.tl.texCoords.u = (GLfloat)u2;
	quad.tl.texCoords.v = (GLfloat)v2;
	quad.tr.texCoords.u = (GLfloat)u1;
	quad.tr.texCoords.v = (GLfloat)v2;

	quad.bl.colors = 
	quad.br.colors = 
	quad.tl.colors = 
	quad.tr.colors = color;
		
	quad.bl.colors.r = quad.bl.colors.r * color.a >> 8; 
	quad.bl.colors.g = quad.bl.colors.g * color.a >> 8; 
	quad.bl.colors.b = quad.bl.colors.b * color.a >> 8; 
	quad.bl.colors.a = color.a;

	quad.br.colors.r = quad.br.colors.r * color.a >> 8; 
	quad.br.colors.g = quad.br.colors.g * color.a >> 8; 
	quad.br.colors.b = quad.br.colors.b * color.a >> 8; 
	quad.br.colors.a = color.a;
	
	quad.tl.colors.r = quad.tl.colors.r * color.a >> 8; 
	quad.tl.colors.g = quad.tl.colors.g * color.a >> 8; 
	quad.tl.colors.b = quad.tl.colors.b * color.a >> 8; 
	quad.tl.colors.a = color.a;

	quad.tr.colors.r = quad.tr.colors.r * color.a >> 8; 
	quad.tr.colors.g = quad.tr.colors.g * color.a >> 8; 
	quad.tr.colors.b = quad.tr.colors.b * color.a >> 8; 
	quad.tr.colors.a = color.a;
	/*
	quad.bl.colors.r *= color.a / 255.0f; 
	quad.bl.colors.g *= color.a / 255.0f;
	quad.bl.colors.b *=	color.a / 255.0f;
	quad.bl.colors.a = color.a;

	quad.br.colors.r *= color.a / 255.0f; 
	quad.br.colors.g *= color.a / 255.0f;
	quad.br.colors.b *= color.a / 255.0f;
	quad.br.colors.a = color.a;

	quad.tl.colors.r *= color.a / 255.0f; 
	quad.tl.colors.g *= color.a / 255.0f;
	quad.tl.colors.b *= color.a / 255.0f;
	quad.tl.colors.a = color.a;

	quad.tr.colors.r *= color.a / 255.0f; 
	quad.tr.colors.g *= color.a / 255.0f;
	quad.tr.colors.b *= color.a / 255.0f;
	quad.tr.colors.a = color.a;
	*/

	m_uTotalQuads++;
	assert(m_uTotalQuads <= m_uCapacity);
}


void UIBatchRenderer::resizeCapicity(unsigned int capacity)
{
	if (m_uCapacity == capacity)
		return;
	
	unsigned int oldCapacity = capacity;

	m_uTotalQuads = MIN(m_uTotalQuads, capacity);
	m_uCapacity = capacity;
	
	V3F_C4B_T2F_Quad* tmpQuads = NULL;

	if (!m_pQuads) {
		tmpQuads = (V3F_C4B_T2F_Quad*)malloc(sizeof(V3F_C4B_T2F_Quad) * m_uCapacity);
		assert(tmpQuads);
		memset(tmpQuads, 0, sizeof(V3F_C4B_T2F_Quad) * m_uCapacity);
	} else {
		tmpQuads = (V3F_C4B_T2F_Quad*)realloc(m_pQuads, sizeof(V3F_C4B_T2F_Quad) * m_uCapacity);
		assert(tmpQuads);
		if (m_uCapacity > oldCapacity) {
			memset(tmpQuads + oldCapacity, 0, sizeof(V3F_C4B_T2F_Quad) * (m_uCapacity - oldCapacity));
		}
	}
	
	GLushort* tmpIndices = NULL;

	if (!m_pIndices){
		tmpIndices = (GLushort*)malloc(sizeof(GLushort) * 6 * m_uCapacity);
		assert(tmpIndices);
		memset(tmpIndices, 0, sizeof(GLushort) * 6 * m_uCapacity);
	}else{
		tmpIndices = (GLushort*)realloc(m_pIndices, sizeof(GLushort) * 6 * m_uCapacity);
		assert(tmpIndices);
		if (m_uCapacity > oldCapacity){
			memset(tmpIndices + oldCapacity, 0, sizeof(GLushort) * 6 * (m_uCapacity - oldCapacity));
		}
	}

	m_pQuads = tmpQuads;
	m_pIndices = tmpIndices;
	
	setupIndices();
}

void UIBatchRenderer::setupIndices()
{
	if (m_uCapacity == 0)
		return;
	for (unsigned int i = 0; i < m_uCapacity; ++i){
		m_pIndices[i * 6 + 0] = i * 4 + 0;
		m_pIndices[i * 6 + 1] = i * 4 + 1;
		m_pIndices[i * 6 + 2] = i * 4 + 2;

		m_pIndices[i * 6 + 3] = i * 4 + 3;
		m_pIndices[i * 6 + 4] = i * 4 + 2;
		m_pIndices[i * 6 + 5] = i * 4 + 1;
	}
}


