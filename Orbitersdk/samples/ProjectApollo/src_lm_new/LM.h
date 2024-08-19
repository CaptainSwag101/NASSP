#pragma once

#include "Orbitersdk.h"
#include "PanelUtils.h"

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

	// Panel related functions
	void ScalePanel(PANELHANDLE hPanel, int panelId, DWORD viewW, DWORD viewH);
	void DefinePanel(PANELHANDLE hPanel, int panelId);
	void DefineMainPanelMFDs(PANELHANDLE hPanel);
	bool clbkLoadPanel2D(int id, PANELHANDLE hPanel, DWORD viewW, DWORD viewH);
	/*bool clbkPanelMouseEvent(int id, int event, int mx, int my);
	bool clbkPanelRedrawEvent(int id, int event, SURFHANDLE surf);*/

	// VC related functions
	/*bool clbkLoadVC(int id);
	bool clbkVCMouseEvent(int id, int event, VECTOR3& p);
	bool clbkVCRedrawEvent(int id, int event, SURFHANDLE surf);*/

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
		// objectCount must be the last element, for counting purposes!
		objectCount
	};

	// Handle for new 2D Panel mesh
	MESHHANDLE hPanelMesh;
	static std::array<SURFHANDLE, (int)PANEL_ID::panelCount> panelTextures;	// handles for NEW 2D Panel textures
	static std::array<RECT, (int)PANEL_ID::panelCount> panelDimensions;		// rectangles for NEW 2D Panel dimensions, since textures may be larger
	const RECT MfdLocationLeft{ 693, 1577,  1003, 1886 };
	const RECT MfdLocationRight{ 1698, 1577, 2008, 1886 };
};