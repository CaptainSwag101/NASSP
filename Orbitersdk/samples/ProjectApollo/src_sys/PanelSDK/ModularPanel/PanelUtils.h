#pragma once

#include "Orbitersdk.h"
#include <array>
#include <string>

std::string Panel2DTexPath(std::string texName);

std::array<NTVERTEX, 4> RectangularPlaneVertices(RECT rect, float texScaleW = 1.0f, float texScaleH = 1.0f);

std::array<WORD, 6> RectangularPlaneIndices();

// For whatever reason, the MFDs don't work with the vertex/index order that the above functions use.
std::array<NTVERTEX, 4> RectangularMFDVertices(RECT rect);

std::array<WORD, 6> RectangularMFDIndices();

RECT RectFromLeftTopWidthHeight(int left, int top, int width, int height);

void oapiBltToSketchpadDraw(oapi::Sketchpad* sketch, SURFHANDLE sourceSurface, int tgtX, int tgtY, int srcX, int srcY, int width, int height, bool colorKey = false);