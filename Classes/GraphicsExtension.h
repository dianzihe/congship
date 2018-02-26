#pragma once

#include "base.h"
#include "ImageResource.h"
#include "cocos2d.h"

using namespace cocos2d;

//struct RenderBatchData;

void FillRect(const Rect& r, const Color4B& c, bool isHollow = false);

void DrawImage(Texture2D *tex, int x = 0, int y = 0, int nW = 0, int nH = 0, const Color4B& color = Color4B(255, 255, 255, 255));

void DrawImage(RenderBatchData *pRenderBatch, int x = 0, int y = 0, int nW = 0, int nH = 0, const Color4B& color = Color4B(255, 255, 255, 255));

void DrawImage_Reverse(RenderBatchData *pRenderBatch, int x = 0, int y = 0, int nW = 0, int nH = 0, const Color4B& color = Color4B(255, 255, 255, 255));

void DrawImage2(Texture2D *tex, float u1, float v1, float u2, float v2, int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, const Color4B& color = Color4B(255, 255, 255, 255));

void DrawImage9( Texture2D *tex, int x, int y, int nW, int nH, const Color4B& color, const Rect& rt );

void DrawImage9( RenderBatchData *pRenderBatch, int x, int y, int nW, int nH, const Color4B& color, const Rect& rt );
