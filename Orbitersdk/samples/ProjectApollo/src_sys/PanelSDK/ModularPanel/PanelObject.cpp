#include "PanelObject.h"

PanelObject::PanelObject(POINT pos2D, VECTOR3 pos3D, std::string textureFilename, std::string name)
{
	Name = name;
	Pos2D = pos2D;
	Pos3D = pos3D;

	// Load object background texture and create a dynamic surface to draw onto via Sketchpad
	TextureSource = oapiLoadSurfaceEx(textureFilename.c_str(), OAPISURFACE_TEXTURE | OAPISURFACE_ALPHA);
	oapiGetSurfaceSize(TextureSource, &TextureWidth, &TextureHeight);
	DrawDestination = oapiCreateSurfaceEx(TextureWidth, TextureHeight, OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_SKETCHPAD | OAPISURFACE_ALPHA | OAPISURFACE_MIPMAPS);
}

PanelObject::~PanelObject()
{
	oapiReleaseTexture(TextureSource);
}

void PanelObject::Redraw2D()
{
	oapi::Sketchpad* sketch = oapiGetSketchpad(DrawDestination);
	RECT srcRect = _R(0, 0, TextureWidth, TextureHeight);
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

POINT PanelObject::GetPos2D() const { return Pos2D; }
VECTOR3 PanelObject::GetPos3D() const { return Pos3D; }
int PanelObject::GetTextureWidth() const { return TextureWidth; }
int PanelObject::GetTextureHeight() const { return TextureHeight; }
int PanelObject::GetVisibleWidth() const { return VisibleWidth; }
int PanelObject::GetVisibleHeight() const { return VisibleHeight; }
SURFHANDLE PanelObject::GetDrawDestinationSurface() const { return DrawDestination; }