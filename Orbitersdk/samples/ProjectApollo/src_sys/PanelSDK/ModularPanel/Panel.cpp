#include "Panel.h"

Panel::Panel(int visibleWidth, int visibleHeight, std::string textureFilename, std::string name)
{
	Name = name;
	VisibleWidth = visibleWidth;
	VisibleHeight = visibleHeight;
	Neighbors = {};

	// Load object background texture and create a dynamic surface to draw onto via Sketchpad
	TextureSource = oapiLoadSurfaceEx(textureFilename.c_str(), OAPISURFACE_TEXTURE | OAPISURFACE_ALPHA);
	oapiGetSurfaceSize(TextureSource, &TextureWidth, &TextureHeight);
	DrawDestination = oapiCreateSurfaceEx(TextureWidth, TextureHeight, OAPISURFACE_TEXTURE | OAPISURFACE_RENDERTARGET | OAPISURFACE_SKETCHPAD | OAPISURFACE_ALPHA | OAPISURFACE_MIPMAPS);
}

Panel::~Panel()
{
	oapiReleaseTexture(TextureSource);
}

void Panel::Redraw2D()
{
	oapi::Sketchpad* sketch = oapiGetSketchpad(DrawDestination);

	// Draw the panel background to the destination surface
	RECT srcRect = _R(0, 0, TextureWidth, TextureHeight);
	sketch->ColorKey(TextureSource, (LPRECT)&srcRect, 0, 0);

	// Iterate through all objects on this panel, have them redraw themselves,
	// then draw the result to the destination surface in the proper position
	for (auto panelObj = Objects.begin(); panelObj != Objects.end(); ++panelObj)
	{
		panelObj->Redraw2D();
		srcRect = _R(0, 0, panelObj->GetTextureWidth(), panelObj->GetTextureHeight());
		POINT pos2D = panelObj->GetPos2D();
		sketch->CopyRect(panelObj->GetDrawDestinationSurface(), (LPRECT)&srcRect, pos2D.x, pos2D.y);
	}

	oapiReleaseSketchpad(sketch);
}

void Panel::RedrawVC()
{
}

void Panel::ProcessMouse2D()
{
}

void Panel::ProcessMouseVC()
{
}

int Panel::GetTextureWidth() const { return TextureWidth; }
int Panel::GetTextureHeight() const { return TextureHeight; }
int Panel::GetVisibleWidth() const { return VisibleWidth; }
int Panel::GetVisibleHeight() const { return VisibleHeight; }
SURFHANDLE* Panel::GetDrawDestinationSurfacePtr() { return &DrawDestination; }