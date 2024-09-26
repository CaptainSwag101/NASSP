/***************************************************************************
  This file is part of Project Apollo - NASSP
  Copyright 2024-2024 James Pelster

  System & Panel SDK (SPSDK) - New Modular Panel System

  Project Apollo is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Project Apollo is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Project Apollo; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See http://nassp.sourceforge.net/license/ for more details.

  **************************************************************************/

#pragma once

#include <string>
#include <vector>
#include "PanelObject.h"

struct PanelNeighbors {
	int Above, Below, Left, Right;
};

class Panel {
public:
	explicit Panel(int visibleWidth, int visibleHeight, std::string textureFilename, std::string name);
	~Panel();

	virtual void Redraw2D();
	virtual void RedrawVC();
	virtual void ProcessMouse2D();
	virtual void ProcessMouseVC();

	int GetTextureWidth() const;
	int GetTextureHeight() const;
	int GetVisibleWidth() const;
	int GetVisibleHeight() const;
	SURFHANDLE* GetDrawDestinationSurfacePtr();

	std::string Name;
	int TextureWidth, TextureHeight;
	int VisibleWidth, VisibleHeight;
	PanelNeighbors Neighbors;

protected:
	SURFHANDLE TextureSource, DrawDestination;
	std::vector<PanelObject> Objects;
};