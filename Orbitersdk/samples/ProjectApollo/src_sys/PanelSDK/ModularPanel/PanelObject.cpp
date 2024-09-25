#include "PanelObject.h"

PanelObject::PanelObject(POINT pos2D, VECTOR3 pos3D, std::string textureFilename, std::string name)
{
	Name = name;
	Pos2D = pos2D;
	Pos3D = pos3D;

	// Load object background texture and create a dynamic surface to draw onto via Sketchpad
	TextureSource = oapiLoadSurfaceEx(textureFilename.c_str(), OAPISURFACE_TEXTURE);
	oapiGetSurfaceSize(TextureSource, &Width2D, &Height2D);
	DrawDestination = oapiCreateSurfaceEx(Width2D, Height2D, OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_SKETCHPAD | OAPISURFACE_MIPMAPS);
}

PanelObject::~PanelObject()
{
	oapiReleaseTexture(TextureSource);
}

void PanelObject::Redraw2D()
{
	oapi::Sketchpad* sketch = oapiGetSketchpad(DrawDestination);
	RECT srcRect = _R(0, 0, Width2D, Height2D);
	sketch->CopyRect(TextureSource, (LPRECT)&srcRect, 0, 0);
	oapiReleaseSketchpad(sketch);
}

void PanelObject::RedrawVC()
{
}

void PanelObject::ProcessMouse2D()
{
}

void PanelObject::ProcessMouseVC()
{
}

POINT PanelObject::GetPos2D() { return Pos2D; }
VECTOR3 PanelObject::GetPos3D() { return Pos3D; }
int PanelObject::GetWidth2D() { return Width2D; }
int PanelObject::GetHeight2D() { return Height2D; }
SURFHANDLE PanelObject::GetDrawDestinationSurface() { return DrawDestination; }