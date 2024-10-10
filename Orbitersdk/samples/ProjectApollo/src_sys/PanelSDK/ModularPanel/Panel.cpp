#include "Panel.h"

Panel::Panel(std::string name, int visibleWidth, int visibleHeight, std::string textureFilename, std::optional<double> fov, std::optional<double> offsetX, std::optional<double> offsetY, std::optional<double> offsetZ)
{
	Name = name;
	VisibleWidth = visibleWidth;
	VisibleHeight = visibleHeight;
	Neighbors = {};

	// Load object background texture and create a dynamic surface to draw onto via Sketchpad
	TextureName = textureFilename;

	FovOverride = fov;
	ViewOffsetX = offsetX;
	ViewOffsetY = offsetY;
	ViewOffsetZ = offsetZ;
}

Panel::~Panel()
{

}

void Panel::Redraw2D(SURFHANDLE surf)
{
	oapi::Sketchpad* sketch = oapiGetSketchpad(surf);

	// Iterate through all objects on this panel, have them redraw themselves,
	// then draw the result to the destination surface in the proper position
	for (auto& panelObj : Objects)
	{
		panelObj.Redraw2D();
		RECT srcRect = _R(0, 0, panelObj.GetTextureWidth(), panelObj.GetTextureHeight());
		POINT pos2D = panelObj.GetPos2D();
		sketch->CopyRect(panelObj.GetDrawDestinationSurface(), (LPRECT)&srcRect, pos2D.x, pos2D.y);
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

int Panel::GetVisibleWidth() const { return VisibleWidth; }
int Panel::GetVisibleHeight() const { return VisibleHeight; }