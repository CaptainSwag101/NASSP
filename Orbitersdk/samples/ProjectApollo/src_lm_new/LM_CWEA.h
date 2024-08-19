#pragma once

#include "Orbitersdk.h"

class LM_CWEA {
public:
	void RedrawLeft(oapi::Sketchpad* sketch, SURFHANDLE sourceTexture, RECT drawDestination, int TexMul = 1);
	void RedrawRight(oapi::Sketchpad* sketch, SURFHANDLE sourceTexture, RECT drawDestination, int TexMul = 1);
};