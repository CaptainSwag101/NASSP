#include "LM.h"
#include "ScnEditorAPI.h"
#include <string>

// ==============================================================
// API callback interface
// ==============================================================

// --------------------------------------------------------------
// Module initialisation
// --------------------------------------------------------------
DLLCLBK void InitModule(HINSTANCE hModule)
{
	g_Param.hDLL = hModule;

	// allocate SketchPad resources
	g_Param.pen[0] = oapiCreatePen(PS_SOLID, 1, RGB(224, 224, 224));
	g_Param.pen[1] = oapiCreatePen(PS_SOLID, 3, RGB(164, 164, 164));
}

// --------------------------------------------------------------
// Module cleanup
// --------------------------------------------------------------
DLLCLBK void ExitModule(HINSTANCE hModule)
{
	// deallocate SketchPad resources
	for (int i = 0; i < 2; i++) oapiReleasePen(g_Param.pen[i]);
}

// --------------------------------------------------------------
// Vessel initialisation
// --------------------------------------------------------------
DLLCLBK VESSEL* ovcInit(OBJHANDLE hvessel, int flightmodel)
{
	// need to init device-dependent resources here in case the screen mode has changed
	g_Param.col[2] = oapiGetColour(80, 80, 224);
	g_Param.col[3] = oapiGetColour(160, 120, 64);

	return new LM(hvessel, flightmodel);
}

// --------------------------------------------------------------
// Vessel cleanup
// --------------------------------------------------------------
DLLCLBK void ovcExit(VESSEL* vessel)
{
	if (vessel) delete (LM*)vessel;
}

// --------------------------------------------------------------
// LM Vessel code
// --------------------------------------------------------------
LM::LM(OBJHANDLE hObj, int fmodel) : VESSEL4(hObj, fmodel) {
	std::string name = this->GetName();

	hPanelMesh = NULL;

	// Init new panel texture handles to NULL
	for (auto& it = panelTextures.begin(); it != panelTextures.end(); ++it) {
		*it = NULL;
	}

	// Load all the new 2D Panel surface textures from file
	DWORD panelTextureAttributes = OAPISURFACE_TEXTURE | OAPISURFACE_SKETCHPAD | OAPISURFACE_ALPHA | OAPISURFACE_ANTIALIAS;
	panelTextures[PANEL_ID::MAIN] = oapiLoadSurfaceEx(Panel2dTexPath("lem_main_panel.dds").c_str(), panelTextureAttributes);
	panelTextures[PANEL_ID::RIGHTWINDOW] = oapiLoadSurfaceEx(Panel2dTexPath("lem_right_window.dds").c_str(), panelTextureAttributes);
	panelTextures[PANEL_ID::LEFTWINDOW] = oapiLoadSurfaceEx(Panel2dTexPath("lem_left_window.dds").c_str(), panelTextureAttributes);
	panelTextures[PANEL_ID::LPDWINDOW] = oapiLoadSurfaceEx(Panel2dTexPath("lem_lpd_window.dds").c_str(), panelTextureAttributes);
	panelTextures[PANEL_ID::RNDZWINDOW] = oapiLoadSurfaceEx(Panel2dTexPath("lem_rendezvous_window.dds").c_str(), panelTextureAttributes);
	panelTextures[PANEL_ID::LEFTPANEL] = oapiLoadSurfaceEx(Panel2dTexPath("lem_left_panel.dds").c_str(), panelTextureAttributes);
	panelTextures[PANEL_ID::AOTVIEW] = oapiLoadSurfaceEx(Panel2dTexPath("lem_aot_panel_wide.dds").c_str(), panelTextureAttributes);
	panelTextures[PANEL_ID::RIGHTPANEL] = oapiLoadSurfaceEx(Panel2dTexPath("lem_right_panel.dds").c_str(), panelTextureAttributes);
	panelTextures[PANEL_ID::ECSPANEL] = oapiLoadSurfaceEx(Panel2dTexPath("lem_ecs_panel.dds").c_str(), panelTextureAttributes);
	panelTextures[PANEL_ID::DOCKVIEW] = oapiLoadSurfaceEx(Panel2dTexPath("lem_dock_view.dds").c_str(), panelTextureAttributes);
	panelTextures[PANEL_ID::AOTZOOM] = oapiLoadSurfaceEx(Panel2dTexPath("lem_aot_panel_zoom.dds").c_str(), panelTextureAttributes);
	panelTextures[PANEL_ID::LEFTZOOM] = oapiLoadSurfaceEx(Panel2dTexPath("lem_left_zoom.dds").c_str(), panelTextureAttributes);
	panelTextures[PANEL_ID::UPPERHATCH] = oapiLoadSurfaceEx(Panel2dTexPath("lem_upper_hatch.dds").c_str(), panelTextureAttributes);
	panelTextures[PANEL_ID::UPPERHATCH_OPEN] = oapiLoadSurfaceEx(Panel2dTexPath("lem_upper_hatch_open.dds").c_str(), panelTextureAttributes);
	panelTextures[PANEL_ID::FWDHATCH] = oapiLoadSurfaceEx(Panel2dTexPath("lem_forward_hatch.dds").c_str(), panelTextureAttributes);
	panelTextures[PANEL_ID::FWDHATCH_OPEN] = oapiLoadSurfaceEx(Panel2dTexPath("lem_forward_hatch_open.dds").c_str(), panelTextureAttributes);

	// Init new panel dimensions to empty
	for (auto& it = panelDimensions.begin(); it != panelDimensions.end(); ++it) {
		*it = RECT{};
	}

	// Define panel dimensions
	panelDimensions[PANEL_ID::MAIN] = { 0, 0, 2700, 1920 };
	panelDimensions[PANEL_ID::RIGHTWINDOW] = { 0, 0, 1920, 1080 };
	panelDimensions[PANEL_ID::LEFTWINDOW] = { 0, 0, 1920, 1080 };
	panelDimensions[PANEL_ID::LPDWINDOW] = { 0, 0, 1920, 1080 };
	panelDimensions[PANEL_ID::RNDZWINDOW] = { 0, 0, 1867, 1050 };
	panelDimensions[PANEL_ID::LEFTPANEL] = { 0, 0, 1920, 1296 };
	panelDimensions[PANEL_ID::AOTVIEW] = { 0, 0, 1867, 1050 };
	panelDimensions[PANEL_ID::RIGHTPANEL] = { 0, 0, 1920, 1080 };
	panelDimensions[PANEL_ID::ECSPANEL] = { 0, 0, 2304, 1296 };
	panelDimensions[PANEL_ID::DOCKVIEW] = { 0, 0, 1867, 1050 };
	panelDimensions[PANEL_ID::AOTZOOM] = { 0, 0, 1867, 1050 };
	panelDimensions[PANEL_ID::LEFTZOOM] = { 0, 0, 1920, 1080 };
	panelDimensions[PANEL_ID::UPPERHATCH] = { 0, 0, 1920, 1080 };
	panelDimensions[PANEL_ID::UPPERHATCH_OPEN] = { 0, 0, 1920, 1080 };
	panelDimensions[PANEL_ID::FWDHATCH] = { 0, 0, 1920, 1080 };
	panelDimensions[PANEL_ID::FWDHATCH_OPEN] = { 0, 0, 1920, 1080 };

	// Init new panel object texture handles to NULL
	for (auto& it = panelObjectTextures.begin(); it != panelObjectTextures.end(); ++it) {
		*it = NULL;
	}

	// Load all the new 2D Panel object surface textures from file
	panelObjectTextures[PANELOBJECT_ID::CautionWarningLights_L] = oapiLoadSurfaceEx(Panel2dTexPath("lem_cw_lights.dds").c_str(), OAPISURFACE_TEXTURE);
	panelObjectTextures[PANELOBJECT_ID::CautionWarningLights_R] = oapiLoadSurfaceEx(Panel2dTexPath("lem_cw_lights.dds").c_str(), OAPISURFACE_TEXTURE);

	// Init new panel object dimensions to empty
	for (auto& it = panelObjectDimensions.begin(); it != panelObjectDimensions.end(); ++it) {
		*it = RECT{};
	}

	// Define panel object dimensions
	panelObjectDimensions[PANELOBJECT_ID::MFD_L] = _R(693, 1577, 1003, 1886);
	panelObjectDimensions[PANELOBJECT_ID::MFD_R] = _R(1698, 1577, 2008, 1886);
	panelObjectDimensions[PANELOBJECT_ID::CautionWarningLights_L] = _R(859, 54, 1180, 180);
	panelObjectDimensions[PANELOBJECT_ID::CautionWarningLights_R] = _R(1696, 54, 1996, 180);
}

LM::~LM()
{
	// Release panel texture resources
	for (auto& it = panelTextures.begin(); it != panelTextures.end(); ++it) {
		if (*it)
		{
			oapiReleaseTexture(*it);
		}
	}

	for (auto& it = panelObjectTextures.begin(); it != panelObjectTextures.end(); ++it) {
		if (*it)
		{
			oapiReleaseTexture(*it);
		}
	}

	// Delete new 2D Panel mesh
	if (hPanelMesh) oapiDeleteMesh(hPanelMesh);
}

void LM::ScalePanel(PANELHANDLE hPanel, int panelId, DWORD viewW, DWORD viewH) {
	double defscale = (double)viewH / panelDimensions[panelId].bottom;
	double magscale = max(defscale, 1.0);
	// We use magscale here twice to ensure scaling can never
	// get smaller than 1.0 (1 source pixel = 1 visual pixel).
	SetPanelScaling(hPanel, magscale, magscale);
}

void LM::DefinePanel(PANELHANDLE hPanel, int panelId) {
	DWORD panelW = panelDimensions[panelId].right;
	DWORD panelH = panelDimensions[panelId].bottom;
	float fpanelW = (float)panelW;
	float fpanelH = (float)panelH;
	int nearestPowTwoW = static_cast<int>(std::ceil(std::log2(fpanelW)));
	int nearestPowTwoH = static_cast<int>(std::ceil(std::log2(fpanelH)));
	DWORD texW = static_cast<DWORD>(std::pow(2, nearestPowTwoW));
	DWORD texH = static_cast<DWORD>(std::pow(2, nearestPowTwoH));
	float ftexW = (float)texW;
	float ftexH = (float)texH;
	std::array<NTVERTEX, 4> VTX = RectangularPlaneVertices(_R(0, 0, panelW, panelH), fpanelW / ftexW, fpanelH / ftexH);
	std::array<WORD, 6> IDX = RectangularPlaneIndices();

	if (hPanelMesh) oapiDeleteMesh(hPanelMesh);
	hPanelMesh = oapiCreateMesh(0, 0);
	MESHGROUP grp = { VTX.data(), IDX.data(), 4, 6, 0, 0, 0, 0, 0 };
	oapiAddMeshGroup(hPanelMesh, &grp);
	SetPanelBackground(hPanel, &panelTextures[panelId], 1, hPanelMesh, panelW, panelH, 0,
		PANEL_ATTACH_TOP | PANEL_ATTACH_BOTTOM);
}

void LM::DefinePanelMain(PANELHANDLE hPanel) {
	//MFDSPEC mfds_left = { { 693, 1577,  1003, 1886 }, 6, 6, 55, 44 };
	//MFDSPEC mfds_right = { { 1698, 1577, 2008, 1886 }, 6, 6, 55, 44 };

	// Define MFDs
	static std::array<WORD, 6> IDX = RectangularMFDIndices();
	static std::array<NTVERTEX, 4> VTX_MFD_LEFT = RectangularMFDVertices(panelObjectDimensions[PANELOBJECT_ID::MFD_L]);
	MESHGROUP grp_mfd_left = { VTX_MFD_LEFT.data(), IDX.data(), 4, 6, 0, 0, 0, 0, 0 };
	oapiAddMeshGroup(hPanelMesh, &grp_mfd_left);
	RegisterPanelMFDGeometry(hPanel, MFD_LEFT, 0, 1);
	RegisterPanelArea(hPanel, (int)PANELOBJECT_ID::MFD_L, panelObjectDimensions[PANELOBJECT_ID::MFD_L], PANEL_REDRAW_ALWAYS, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBPRESSED | PANEL_MOUSE_ONREPLAY, panelTextures[PANEL_ID::MAIN]);
	oapiToggleMFD_on(MFD_LEFT);

	static std::array<NTVERTEX, 4> VTX_MFD_RIGHT = RectangularMFDVertices(panelObjectDimensions[PANELOBJECT_ID::MFD_R]);
	MESHGROUP grp_mfd_right = { VTX_MFD_RIGHT.data(), IDX.data(), 4, 6, 0, 0, 0, 0, 0 };
	oapiAddMeshGroup(hPanelMesh, &grp_mfd_right);
	RegisterPanelMFDGeometry(hPanel, MFD_RIGHT, 0, 2);
	RegisterPanelArea(hPanel, (int)PANELOBJECT_ID::MFD_R, panelObjectDimensions[PANELOBJECT_ID::MFD_R], PANEL_REDRAW_ALWAYS, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBPRESSED | PANEL_MOUSE_ONREPLAY, panelTextures[PANEL_ID::MAIN]);
	oapiToggleMFD_on(MFD_RIGHT);

	// Define FDAIs

}



bool LM::clbkLoadPanel2D(int id, PANELHANDLE hPanel, DWORD viewW, DWORD viewH) {
	// Restore the previous FOV after leaving panels which override it, like the AOT
	static double previousFOV = 60.0 * RAD / 2;
	double overrideFOV = -1.0;	// Measured in degrees
	static bool previousOverride = false;

	SetCameraDefaultDirection(_V(0, 0, 1));  // forward
	oapiCameraSetCockpitDir(0, 0);   // look forward
	// Stop the user from being able to right-click and drag to look around in 2D
	SetCameraRotationRange(0, 0, 0, 0);


	// First pass: Define initial panel geometry, background, camera angle, and FOV.
	switch (id) {
	case PANEL_ID::MAIN:
		oapiSetPanelNeighbours(PANEL_ID::LEFTWINDOW, PANEL_ID::RIGHTWINDOW, PANEL_ID::RNDZWINDOW, PANEL_ID::FWDHATCH);
		break;

	case PANEL_ID::RIGHTWINDOW:
		oapiSetPanelNeighbours(PANEL_ID::MAIN, PANEL_ID::RIGHTPANEL, -1, -1);
		break;

	case PANEL_ID::LEFTWINDOW:
		oapiSetPanelNeighbours(PANEL_ID::LEFTPANEL, PANEL_ID::MAIN, PANEL_ID::LEFTZOOM, PANEL_ID::LPDWINDOW);
		break;

	case PANEL_ID::LPDWINDOW:
		oapiSetPanelNeighbours(-1, PANEL_ID::MAIN, PANEL_ID::LEFTWINDOW, -1);
		break;

	case PANEL_ID::RNDZWINDOW:
		oapiSetPanelNeighbours(-1, PANEL_ID::AOTVIEW, PANEL_ID::DOCKVIEW, PANEL_ID::MAIN);
		SetCameraDefaultDirection(_V(0, 1, 0));  // up
		oapiCameraSetCockpitDir(0, 0);   // center view on new angle
		break;

	case PANEL_ID::LEFTPANEL:
		oapiSetPanelNeighbours(PANEL_ID::ECSPANEL, PANEL_ID::LEFTWINDOW, -1, -1);
		SetCameraDefaultDirection(_V(-1, 0, 0));  // left
		oapiCameraSetCockpitDir(0, 0);   // center view on new angle
		break;

	case PANEL_ID::AOTVIEW:
		oapiSetPanelNeighbours(PANEL_ID::RNDZWINDOW, -1, PANEL_ID::AOTZOOM, PANEL_ID::MAIN);
		break;

	case PANEL_ID::RIGHTPANEL:
		oapiSetPanelNeighbours(PANEL_ID::RIGHTWINDOW, PANEL_ID::ECSPANEL, -1, -1);
		SetCameraDefaultDirection(_V(1, 0, 0));  // right
		oapiCameraSetCockpitDir(0, 0);   // center view on new angle
		break;

	case PANEL_ID::ECSPANEL:
		oapiSetPanelNeighbours(PANEL_ID::RIGHTPANEL, PANEL_ID::LEFTPANEL, PANEL_ID::UPPERHATCH, -1);
		break;

	case PANEL_ID::DOCKVIEW:
		overrideFOV = 30.0;
		oapiSetPanelNeighbours(-1, -1, -1, PANEL_ID::RNDZWINDOW);
		SetCameraDefaultDirection(_V(0, 1, 0));  // up
		oapiCameraSetCockpitDir(0, 0);   // center view on new angle
		break;

	case PANEL_ID::AOTZOOM:
		overrideFOV = 60.0;
		oapiSetPanelNeighbours(-1, -1, -1, PANEL_ID::AOTVIEW);
		break;

	case PANEL_ID::LEFTZOOM:
		overrideFOV = 30.0;
		oapiSetPanelNeighbours(-1, -1, -1, PANEL_ID::LEFTWINDOW);
		break;

	case PANEL_ID::UPPERHATCH:
		oapiSetPanelNeighbours(-1, -1, -1, PANEL_ID::ECSPANEL);
		break;

	case PANEL_ID::FWDHATCH:
		oapiSetPanelNeighbours(-1, -1, PANEL_ID::MAIN, -1);
		break;

	default:
		return false;
	}

	// FOV override logic
	if (overrideFOV > 0.0) {
		// This prevents overwriting the restore FOV if we switch from one overridden FOV to another.
		if (!previousOverride) {
			previousFOV = oapiCameraAperture();
		}
		// Modify the degrees into half-radians. Documentation says radians but that doesn't give us the right conversion.
		oapiCameraSetAperture(overrideFOV * RAD / 2.0);
		previousOverride = true;
	}
	else {
		// If the last FOV was not overridden, update our FOV to restore.
		if (!previousOverride) {
			previousFOV = oapiCameraAperture();
		}
		oapiCameraSetAperture(previousFOV);
		previousOverride = false;
	}

	DefinePanel(hPanel, id);
	ScalePanel(hPanel, id, viewW, viewH);

	// Disable HUD
	oapiSetHUDMode(HUD_NONE);


	// Second pass: Define applicable panel areas, MFDs, etc.

	switch (id) {
	case PANEL_ID::MAIN:
		DefinePanelMain(hPanel);
		break;
	}

	return true;
}

bool LM::clbkPanelRedrawEvent(int id, int event, SURFHANDLE surf) {
	oapi::Sketchpad* sketch = oapiGetSketchpad(surf);

	switch (id) {
	case PANEL_ID::MAIN:
		cwea.RedrawLeft(sketch, panelObjectTextures[PANELOBJECT_ID::CautionWarningLights_L], panelObjectDimensions[PANELOBJECT_ID::CautionWarningLights_L]);
		cwea.RedrawRight(sketch, panelObjectTextures[PANELOBJECT_ID::CautionWarningLights_R], panelObjectDimensions[PANELOBJECT_ID::CautionWarningLights_R]);
		break;
	}

	oapiReleaseSketchpad(sketch);
	return true;
}


// Static variable definitions
std::array<SURFHANDLE, (int)LM::PANEL_ID::panelCount> LM::panelTextures;
std::array<RECT, (int)LM::PANEL_ID::panelCount> LM::panelDimensions;
std::array<SURFHANDLE, (int)LM::PANELOBJECT_ID::objectCount> LM::panelObjectTextures;
std::array<RECT, (int)LM::PANELOBJECT_ID::objectCount> LM::panelObjectDimensions;