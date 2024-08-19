#include "LM_CWEA.h"
#include "PanelUtils.h"

void LM_CWEA::RedrawLeft(oapi::Sketchpad* sketch, SURFHANDLE sourceTexture, RECT drawDestination, int TexMul) {
	int dx = 0, dy = 0;
	for (int col = 0; col < 4; ++col) {
		switch (col) {
		case 0:
			dx = 0; break;
		case 1:
			dx = 71 * TexMul; break;
		case 2:
			dx = 167 * TexMul; break;
		case 3:
			dx = 238 * TexMul; break;
		}

		for (int row = 0; row < 5; ++row) {
			// Choose lit/unlit texture depending on state
			//if (LightStatus[row][col] == 1 && IsLTGPowered()) {
				dy = 134 * TexMul;
			//}
			//else {
			//	dy = 7 * TexMul;
			//}
			// Draw the texture to the panel
			//if (LightStatus[row][col] == 2) {
			//	// Special Hack: This Lamp Doesn't Exist
			//	RECT srcRect = RectFromLeftTopWidthHeight(8 * TexMul, 7 * TexMul, 67 * TexMul, 19 * TexMul);
			//	sketch->CopyRect(sourceTexture, (LPRECT)&srcRect, 8 * TexMul + dx + drawDestination.left, 7 * TexMul + (row * 23 * TexMul) + drawDestination.top);
			//}
			//else {
				oapiBltToSketchpadDraw(sketch, sourceTexture, 8 * TexMul + dx + drawDestination.left, 7 * TexMul + (row * 23 * TexMul) + drawDestination.top, 8 * TexMul + dx, dy + (row * 23 * TexMul), 67 * TexMul, 19 * TexMul);
			//}
		}
	}
}

void LM_CWEA::RedrawRight(oapi::Sketchpad* sketch, SURFHANDLE sourceTexture, RECT drawDestination, int TexMul) {
	int dx = 0, dy = 0;
	for (int col = 0; col < 4; ++col) {
		switch (col) {
		case 0:
			dx = 0; break;
		case 1:
			dx = 71 * TexMul; break;
		case 2:
			dx = 146 * TexMul; break;
		case 3:
			dx = 217 * TexMul; break;
		}

		for (int row = 0; row < 5; ++row) {
			// Choose lit/unlit texture depending on state
			dy = 134 * TexMul;
			RECT srcRect = RectFromLeftTopWidthHeight(330 * TexMul + dx, dy + (row * 23 * TexMul), 67 * TexMul, 19 * TexMul);
			sketch->CopyRect(sourceTexture, (LPRECT)&srcRect, 8 * TexMul + dx + drawDestination.left, 7 * TexMul + (row * 23 * TexMul) + drawDestination.top);
		}
	}
}