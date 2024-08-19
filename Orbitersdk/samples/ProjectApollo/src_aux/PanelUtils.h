#pragma once

#include "Orbitersdk.h"
#include <array>

inline std::string Panel2dTexPath(std::string texName) {
	return "ProjectApollo/2DPanel/" + texName;
}

inline std::array<NTVERTEX, 4> RectangularPlaneVertices(RECT rect, float texScaleW = 1.0f, float texScaleH = 1.0f) {
	return std::array<NTVERTEX, 4> {
			NTVERTEX{ (float)(rect.left),(float)(rect.top),0,      0,0,0,	0.0f,1.0f - texScaleH },
			NTVERTEX{ (float)(rect.left),(float)(rect.bottom),0,   0,0,0,	0.0f,1.0f },
			NTVERTEX{ (float)(rect.right),(float)(rect.bottom),0,  0,0,0,	texScaleW,1.0f },
			NTVERTEX{ (float)(rect.right),(float)(rect.top),0,     0,0,0,	texScaleW,1.0f - texScaleH }
	};
}

inline std::array<WORD, 6> RectangularPlaneIndices() {
	return std::array<WORD, 6> {
		0, 2, 1,
		2, 0, 3
	};
};

// For whatever reason, the MFDs don't work with the vertex/index order that the above functions use.
inline std::array<NTVERTEX, 4> RectangularMFDVertices(RECT rect) {
	return std::array<NTVERTEX, 4> {
			NTVERTEX{ (float)(rect.left),(float)(rect.top),0,      0,0,0,	0.0f,0.0f },
			NTVERTEX{ (float)(rect.right),(float)(rect.top),0,     0,0,0,	1.0f,0.0f },
			NTVERTEX{ (float)(rect.left),(float)(rect.bottom),0,   0,0,0,	0.0f,1.0f },
			NTVERTEX{ (float)(rect.right),(float)(rect.bottom),0,  0,0,0,	1.0f,1.0f },
	};
}

inline std::array<WORD, 6> RectangularMFDIndices() {
	return std::array<WORD, 6> {
		0, 1, 2,
		3, 2, 1
	};
};