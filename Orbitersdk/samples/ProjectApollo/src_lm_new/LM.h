#pragma once

#include "Orbitersdk.h"
#include "PanelUtils.h"

#include "LM_CWEA.h"

#include <array>
#include <vector>

typedef struct {
	HINSTANCE hDLL;
	DWORD col[4];
	oapi::Pen* pen[2];
	SURFHANDLE surf;
} GDIParams;

static GDIParams g_Param;
static MESHHANDLE hPanelMesh;

class LM : public VESSEL4 {
public:
	explicit LM(OBJHANDLE hVessel, int fModel);
	~LM();

	// Panel-specific 2D panel functions
	void DefinePanelMain(PANELHANDLE hPanel);

	// General 2D panel related functions
	void ScalePanel(PANELHANDLE hPanel, int panelId, DWORD viewW, DWORD viewH);
	void DefinePanel(PANELHANDLE hPanel, int panelId);
	bool clbkLoadPanel2D(int id, PANELHANDLE hPanel, DWORD viewW, DWORD viewH);
	bool clbkPanelRedrawEvent(int id, int event, SURFHANDLE surf);
	//bool clbkPanelMouseEvent(int id, int event, int mx, int my);

	// VC related functions
	/*bool clbkLoadVC(int id);
	bool clbkVCRedrawEvent(int id, int event, SURFHANDLE surf);
	bool clbkVCMouseEvent(int id, int event, VECTOR3& p);*/

	// Simulator related functions
	/*int clbkConsumeDirectKey(char* keystate);
	int  clbkConsumeBufferedKey(DWORD key, bool down, char* kstate);
	void clbkPreStep(double simt, double simdt, double mjd);
	void clbkPostStep(double simt, double simdt, double mjd);
	void clbkLoadStateEx(FILEHANDLE scn, void* vs);
	void clbkSetClassCaps(FILEHANDLE cfg);
	void clbkSaveState(FILEHANDLE scn);
	bool clbkLoadGenericCockpit();
	void clbkMFDMode(int mfd, int mode);
	void clbkPostCreation();
	void clbkVisualCreated(VISHANDLE vis, int refcount);
	void clbkVisualDestroyed(VISHANDLE vis, int refcount);
	void clbkDockEvent(int dock, OBJHANDLE connected);
	void clbkFocusChanged(bool getfocus, OBJHANDLE hNewVessel, OBJHANDLE hOldVessel);
	void clbkGetRadiationForce(const VECTOR3& mflux, VECTOR3& F, VECTOR3& pos);*/

private:
	// New 2D Panel IDs for texture surface reference
	enum PANEL_ID {
		MAIN,
		RIGHTWINDOW,
		LEFTWINDOW,
		LPDWINDOW,
		RNDZWINDOW,
		LEFTPANEL,
		AOTVIEW,
		RIGHTPANEL,
		ECSPANEL,
		DOCKVIEW,
		AOTZOOM,
		LEFTZOOM,
		UPPERHATCH,
		FWDHATCH,
		UPPERHATCH_OPEN,
		FWDHATCH_OPEN,
		// panelCount must be the last element, for counting purposes!
		panelCount
	};

	enum PANELOBJECT_ID {
		MFD_L,
		MFD_R,
		CautionWarningLights_L,
		CautionWarningLights_R,
		// objectCount must be the last element, for counting purposes!
		objectCount
	};

	// Handle for new 2D Panel mesh
	MESHHANDLE hPanelMesh;
	// For clarification, the "dimensions" are the locations on the panel where a given texture/surface will be placed.
	// To obtain the actual surface dimensions (which may include blank space due to DDS textures needing their resolution
	// to be a power of two, use the oapiGetSurfaceSize() function.
	static std::array<SURFHANDLE, PANEL_ID::panelCount> panelTextures;	// handles for NEW 2D Panel textures
	static std::array<RECT, PANEL_ID::panelCount> panelDimensions;		// rectangles for NEW 2D Panel dimensions, since textures may be larger
	static std::array<SURFHANDLE, PANELOBJECT_ID::objectCount> panelObjectTextures;	// handles for NEW 2D Panel object textures
	static std::array<RECT, PANELOBJECT_ID::objectCount> panelObjectDimensions;		// rectangles for NEW 2D Panel object dimensions, since textures may be larger

	// Components and systems
	LM_CWEA cwea;
};