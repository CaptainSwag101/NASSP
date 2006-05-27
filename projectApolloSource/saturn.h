/***************************************************************************
  This file is part of Project Apollo - NASSP
  Copyright 2004-2005

  Generic Saturn class for AGC interface. As much code as possible will be shared
  here between the SaturnV and Saturn1B.

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

  **************************** Revision History ****************************
  *	$Log$
  *	Revision 1.180  2006/05/26 22:01:50  movieman523
  *	Revised stage handling some. Removed two of the three second-stage functions and split out the mesh and engine code.
  *	
  *	Revision 1.179  2006/05/25 04:04:53  jasonims
  *	Initial VC Stop point...unknown why buttons not working yet, but skeleton of VC panel programming is there...
  *	
  *	Revision 1.178  2006/05/19 13:48:28  tschachim
  *	Fixed a lot of devices and power consumptions.
  *	DirectO2 valve added.
  *	
  *	Revision 1.177  2006/05/06 06:00:35  jasonims
  *	No more venting our Astronauts into space...and no more LRV popping out of an Astronauts pocket....well sorta.
  *	
  *	Revision 1.176  2006/05/01 03:33:22  jasonims
  *	New CM and all the fixin's....
  *	
  *	Revision 1.175  2006/04/29 23:16:56  movieman523
  *	Fixed LMPAD and added CHECKLISTS option to scenario file.
  *	
  *	Revision 1.174  2006/04/25 13:39:50  tschachim
  *	Removed GetXXXSwitchState.
  *	
  *	Revision 1.173  2006/04/24 21:06:33  quetalsi
  *	Buxfix in EXT RNDZ LTS switch
  *	
  *	Revision 1.172  2006/04/17 19:12:27  movieman523
  *	Removed some unused switches.
  *	
  *	Revision 1.171  2006/04/17 15:16:16  movieman523
  *	Beginnings of checklist code, added support for flashing borders around control panel switches and updated a portion of the Saturn panel switches appropriately.
  *	
  *	Revision 1.170  2006/04/06 19:32:49  movieman523
  *	More Apollo 13 support.
  *	
  *	Revision 1.169  2006/04/04 23:36:15  dseagrav
  *	Added the beginnings of the telecom subsystem.
  *	
  *	Revision 1.168  2006/04/04 22:00:54  jasonims
  *	Apollo Spacecraft Mesh offset corrections and SM Umbilical Animation.
  *	
  *	Revision 1.167  2006/03/30 01:59:37  movieman523
  *	Added RCS to SM DLL.
  *	
  *	Revision 1.166  2006/03/30 00:14:47  movieman523
  *	First pass at SM DLL.
  *	
  *	Revision 1.165  2006/03/29 19:06:50  movieman523
  *	First support for new SM.
  *	
  *	Revision 1.164  2006/03/29 16:34:00  jasonims
  *	GPFPI Meters added supporting proper LV Fuel Quantities and SPS Gimbel Position display.  LV Tank Quantities now accessable from outside Saturn class.
  *	
  *	Revision 1.163  2006/03/27 19:22:44  quetalsi
  *	Bugfix RCS PRPLNT switches and wired to brakers.
  *	
  *	Revision 1.162  2006/03/25 00:12:42  dseagrav
  *	SCS ECA added.
  *	
  *	Revision 1.161  2006/03/19 17:06:13  dseagrav
  *	Fixed mistake with RCS TRNFR, it's a 3-position switch and is ignored for now.
  *	
  *	Revision 1.160  2006/03/18 22:55:55  dseagrav
  *	Added more RJEC functionality.
  *	
  *	Revision 1.159  2006/03/16 04:53:21  dseagrav
  *	Added preliminary RJEC, connected CMC to RJEC.
  *	
  *	Revision 1.158  2006/03/14 02:48:57  dseagrav
  *	Added ECA object, moved FDAI redraw stuff into ECA to clean up FDAI redraw mess.
  *	
  *	Revision 1.157  2006/03/12 01:13:29  dseagrav
  *	Added lots of SCS items and FDAI stuff.
  *	
  *	Revision 1.156  2006/03/09 20:40:22  quetalsi
  *	Added Battery Relay Bus. Wired Inverter 1/2/3, EPS Sensor Unit DC A/B, EPS Sensor Unit AC 1/2 and Bat Rly Bus BAT A/B brakers.
  *	
  *	Revision 1.155  2006/03/05 00:49:48  movieman523
  *	Wired up Auto RCS Select switches to bus A and B.
  *	
  *	Revision 1.154  2006/03/03 12:39:41  tschachim
  *	Fixes for using DInput.
  *	
  *	Revision 1.153  2006/03/03 05:12:37  dseagrav
  *	Added DirectInput code and THC/RHC interface. Changes 20060228-20060302
  *	
  *	Revision 1.152  2006/02/28 20:40:32  quetalsi
  *	Bugfix and added CWS FC BUS DISCONNECT. Reset DC switches now work.
  *	
  *	Revision 1.151  2006/02/28 00:03:58  quetalsi
  *	MainBus A & B Switches and Talkbacks woks and wired.
  *	
  *	Revision 1.150  2006/02/27 00:57:48  dseagrav
  *	Added SPS thrust-vector control. Changes 20060225-20060226.
  *	
  *	Revision 1.149  2006/02/23 22:46:41  quetalsi
  *	Added AC ovevoltage control and Bugfix
  *	
  *	Revision 1.148  2006/02/23 15:50:11  tschachim
  *	Restored changes lost in last version.
  *	
  *	Revision 1.147  2006/02/23 14:13:49  dseagrav
  *	Split CM RCS into two systems, moved CM RCS thrusters (close to) proper positions, eliminated extraneous thrusters, set ISP and thrust values to match documentation, connected CM RCS to AGC IO channels 5 and 6 per DAP documentation, changes 20060221-20060223.
  *
  *	Revision 1.146  2006/02/22 01:03:02  movieman523
  *	Initial Apollo 5 support.	
  *	
  *	Revision 1.145  2006/02/21 12:19:21  tschachim
  *	Moved TLI sequence to the IU.
  *	
  *	Revision 1.144  2006/02/13 21:43:32  tschachim
  *	C/W ISS light.
  *	
  *	Revision 1.143  2006/02/02 21:38:47  lazyd
  *	Added a variable to save orbit-normal vector for launch
  *	
  *	Revision 1.142  2006/02/02 18:54:16  tschachim
  *	Smoother acceleration calculations.
  *	
  *	Revision 1.141  2006/02/01 18:30:48  tschachim
  *	Pyros and secs logic cb's.
  *	
  *	Revision 1.140  2006/01/27 22:11:38  movieman523
  *	Added support for low-res Saturn 1b.
  *	
  *	Revision 1.139  2006/01/26 19:26:31  movieman523
  *	Now we can set any scenario state from the config file for Saturn 1b or Saturn V. Also wired up a couple of LEM switches.
  *	
  *	Revision 1.138  2006/01/26 03:31:57  movieman523
  *	Less hacky low-res mesh support for Saturn V.
  *	
  *	Revision 1.137  2006/01/24 13:47:07  tschachim
  *	Smoother staging with more eye-candy.
  *	
  *	Revision 1.136  2006/01/15 02:38:59  movieman523
  *	Moved CoG and removed phantom thrusters. Also delete launch site when we get a reasonable distance away.
  *	
  *	Revision 1.135  2006/01/15 01:23:19  movieman523
  *	Put 'phantom' RCS thrusters back in and adjusted RCS thrust and ISP based on REALISM value.
  *	
  *	Revision 1.134  2006/01/14 18:57:49  movieman523
  *	First stages of pyro and SECS simulation.
  *	
  *	Revision 1.133  2006/01/14 12:34:16  flydba
  *	New panel added (325/326) for cabin press control.
  *	
  *	Revision 1.132  2006/01/14 00:54:35  movieman523
  *	Hacky wiring of sequential systems and pyro arm switches.
  *	
  *	Revision 1.131  2006/01/12 14:47:25  tschachim
  *	Added prelaunch tank venting.
  *	
  *	Revision 1.130  2006/01/11 22:34:20  movieman523
  *	Wired Virtual AGC to RCS and SPS, and added some CMC guidance control switches.
  *	
  *	Revision 1.129  2006/01/11 02:59:43  movieman523
  *	Valve talkbacks now check the valve state directlry. This means they barberpole on SM sep and can't then be changed.
  *	
  *	Revision 1.128  2006/01/11 02:16:25  movieman523
  *	Added RCS propellant quantity gauge.
  *	
  *	Revision 1.127  2006/01/10 23:20:51  movieman523
  *	SM RCS is now enabled per quad.
  *	
  *	Revision 1.126  2006/01/10 21:09:30  movieman523
  *	Improved AoA/thrust meter.
  *	
  *	Revision 1.125  2006/01/10 20:49:50  movieman523
  *	Added CM RCS propellant dump and revised thrust display.
  *	
  *	Revision 1.124  2006/01/10 19:34:45  movieman523
  *	Fixed AC bus switches and added ELS Logic/Auto support.
  *	
  *	Revision 1.123  2006/01/09 21:56:44  movieman523
  *	Added support for LEM and CSM AGC PAD loads in scenario file.
  *	
  *	Revision 1.122  2006/01/08 21:43:34  movieman523
  *	First phase of implementing inverters, and stopped PanelSDK trying to delete objects which weren't allocated with new().
  *	
  *	Revision 1.121  2006/01/08 19:04:30  movieman523
  *	Wired up AC bus switches in a quick and hacky manner.
  *	
  *	Revision 1.120  2006/01/08 17:50:38  movieman523
  *	Wired up electrical meter switches other than battery charger.
  *	
  *	Revision 1.119  2006/01/08 17:01:09  flydba
  *	Switches added on main panel 3.
  *	
  *	Revision 1.118  2006/01/08 14:51:24  movieman523
  *	Revised camera 3 position to be more photogenic, and added seperation particle effects.
  *	
  *	Revision 1.117  2006/01/08 04:37:50  movieman523
  *	Added camera 3.
  *	
  *	Revision 1.116  2006/01/08 04:00:24  movieman523
  *	Added first two engineering cameras.
  *	
  *	Revision 1.115  2006/01/07 03:28:28  movieman523
  *	Removed a lot of unused switches and wired up the FDAI power switch.
  *	
  *	Revision 1.114  2006/01/07 03:16:04  flydba
  *	Switches added on main panel 2.
  *	
  *	Revision 1.113  2006/01/07 01:34:08  movieman523
  *	Added AC bus overvoltage and main bus undervolt lights.
  *	
  *	Revision 1.112  2006/01/07 00:43:58  movieman523
  *	Added non-essential buses, though there's nothing connected to them at the moment.
  *	
  *	Revision 1.111  2006/01/06 22:55:53  movieman523
  *	Fixed SM seperation and cut off fuel cell power when it happens.
  *	
  *	Revision 1.110  2006/01/06 21:40:15  movieman523
  *	Quick hack for damping electrical meters.
  *	
  *	Revision 1.109  2006/01/06 20:37:18  movieman523
  *	Made the voltage and current meters work. Currently hard-coded to main bus A and AC bus 1.
  *	
  *	Revision 1.108  2006/01/06 19:45:45  flydba
  *	Switches added on main panel 1.
  *	
  *	Revision 1.107  2006/01/06 02:06:07  flydba
  *	Some changes done on the main panel.
  *	
  *	Revision 1.106  2006/01/05 12:11:02  tschachim
  *	New dockingprobe handling.
  *	
  *	Revision 1.105  2006/01/05 04:55:52  flydba
  *	All clickable areas of the right & left hand side panels added now!
  *	
  *	Revision 1.104  2006/01/04 23:06:03  movieman523
  *	Moved meshes into ProjectApollo directory and renamed a few.
  *	
  *	Revision 1.103  2006/01/04 01:57:08  flydba
  *	Switches on panel 8 now set.
  *	
  *	Revision 1.102  2006/01/03 17:52:32  flydba
  *	Switches on panel 9 are set up now.
  *	
  *	Revision 1.101  2006/01/03 03:59:16  flydba
  *	Some changes done on panel 15.
  *	
  *	Revision 1.100  2005/12/19 16:39:12  tschachim
  *	New devices.
  *	
  **************************************************************************/

#if !defined(_PA_SATURN_H)
#define _PA_SATURN_H

//
// I hate nested includes, but this is much easier than adding them to all the files
// which need them.
//

#include "PanelSDK/PanelSDK.h"

#include "cautionwarning.h"
#include "csmcautionwarning.h"
#include "missiontimer.h"
#include "FDAI.h"
#include "iu.h"
#include "satswitches.h"
#include "powersource.h"
#include "dockingprobe.h"
#include "pyro.h"
#include "secs.h"
// DS20060304 Include SCS
#include "scs.h"
// DS20060326 Include Telecom
#include "csm_telecom.h"
// DS20060301 Include DirectInput
#define DIRECTINPUT_VERSION 0x0800
#include "dinput.h"

//
// Valves.
//

#define CSM_He1_TANKA_VALVE				1
#define CSM_He1_TANKB_VALVE				2
#define CSM_He1_TANKC_VALVE				3
#define CSM_He1_TANKD_VALVE				4
#define CSM_He2_TANKA_VALVE				5
#define CSM_He2_TANKB_VALVE				6
#define CSM_He2_TANKC_VALVE				7
#define CSM_He2_TANKD_VALVE				8
#define CSM_PRIOXID_INSOL_VALVE_A		9
#define CSM_PRIOXID_INSOL_VALVE_B		10
#define CSM_PRIOXID_INSOL_VALVE_C		11
#define CSM_PRIOXID_INSOL_VALVE_D		12
#define CSM_SECOXID_INSOL_VALVE_A		13
#define CSM_SECOXID_INSOL_VALVE_B		14
#define CSM_SECOXID_INSOL_VALVE_C		15
#define CSM_SECOXID_INSOL_VALVE_D		16
#define CSM_PRIFUEL_INSOL_VALVE_A		17
#define CSM_PRIFUEL_INSOL_VALVE_B		18
#define CSM_PRIFUEL_INSOL_VALVE_C		19
#define CSM_PRIFUEL_INSOL_VALVE_D		20
#define CSM_SECFUEL_INSOL_VALVE_A		21
#define CSM_SECFUEL_INSOL_VALVE_B		22
#define CSM_SECFUEL_INSOL_VALVE_C		23
#define CSM_SECFUEL_INSOL_VALVE_D		24
#define CSM_SECFUEL_PRESS_VALVE_A		25
#define CSM_SECFUEL_PRESS_VALVE_B		26
#define CSM_SECFUEL_PRESS_VALVE_C		27
#define CSM_SECFUEL_PRESS_VALVE_D		28


#define CM_VALVES_START					29
#define CM_RCSPROP_TANKA_VALVE			30
#define CM_RCSPROP_TANKB_VALVE			31

#define N_CSM_VALVES	32

#define RCS_SM_QUAD_A		0
#define RCS_SM_QUAD_B		1
#define RCS_SM_QUAD_C		2
#define RCS_SM_QUAD_D		3

#define RCS_CM_RING_1		4
#define RCS_CM_RING_2		5

//
// Random failure flags.
//

typedef union {
	struct {
		unsigned Init:1;
		unsigned CoverFail:1;
		unsigned DrogueFail:1;
		unsigned MainFail:1;
	} u;
	int word;
} LandingFailures;

typedef union {
	struct {
		unsigned Init:1;
		unsigned EarlySICenterCutoff:1;
		unsigned EarlySIICenterCutoff:1;
		unsigned LETAutoJetFail:1;
		unsigned SIIAutoSepFail:1;
	} u;
	int word;
} LaunchFailures;

typedef union {
	struct {
		unsigned Init:1;
		unsigned TowerJett1Fail:1;
		unsigned TowerJett2Fail:1;
		unsigned SMJett1Fail:1;
		unsigned SMJett2Fail:1;
	} u;
	int word;
} SwitchFailures;

typedef struct {
	double O2Tank1PressurePSI;
	double O2Tank2PressurePSI;
	double H2Tank1PressurePSI;
	double H2Tank2PressurePSI;
	double O2SurgeTankPressurePSI;
} TankPressures;

typedef struct {
	double O2Tank1Quantity;
	double O2Tank1QuantityKg;
	double O2Tank2Quantity;
	double O2Tank2QuantityKg;
	double H2Tank1Quantity;
	double H2Tank2Quantity;
} TankQuantities;

typedef struct {
	double SICQuantity;
	double SIIQuantity;
	double SIVBOxQuantity;
	double SIVBFuelQuantity;
	double SICFuelMass;
	double SIIFuelMass;
	double S4BFuelMass;
	double S4BOxMass;
} LVTankQuantities;

typedef struct {
	double SuitTempK;
	double CabinTempK;
	double CabinPressureMMHG;
	double SuitPressureMMHG;
	double SuitReturnPressureMMHG;
	double CabinPressurePSI;
	double SuitPressurePSI;
	double SuitReturnPressurePSI;
	double SuitCO2MMHG;
	double CabinCO2MMHG;
	double CabinRegulatorFlowLBH;
	double O2DemandFlowLBH;
	double DirectO2FlowLBH;
} AtmosStatus;

typedef struct {
	double DisplayedO2FlowLBH;
	double DisplayedSuitComprDeltaPressurePSI;
	double DisplayedEcsRadTempPrimOutletMeterTemperatureF;
} DisplayedAtmosStatus;

typedef struct {
	double RadiatorInletPressurePSI;
	double RadiatorInletTempF;
	double RadiatorOutletTempF;
	double EvaporatorOutletTempF;
	double EvaporatorSteamPressurePSI;
	double AccumulatorQuantityPercent;
} PrimECSCoolingStatus;

typedef struct {
	double RadiatorInletPressurePSI;
	double RadiatorInletTempF;
	double RadiatorOutletTempF;
	double EvaporatorOutletTempF;
	double EvaporatorSteamPressurePSI;
	double AccumulatorQuantityPercent;
} SecECSCoolingStatus;

typedef struct {
	double PotableH2oTankQuantityPercent;
	double WasteH2oTankQuantityPercent;
} ECSWaterStatus;

typedef struct {
	double MainBusAVoltage;
	double MainBusBVoltage;
	bool Enabled_DC_A_CWS;
	bool Enabled_DC_B_CWS;
	bool Fc_Disconnected;
} MainBusStatus;

typedef struct {
	bool ISSWarning;
	bool TestAlarms;
} AGCWarningStatus;

class Saturn: public VESSEL2, public PanelSwitchListener {

public:
	Saturn(OBJHANDLE hObj, int fmodel);
	virtual ~Saturn();

	void SetAutopilot(bool ap) { autopilot = ap; };
	bool GetAutopilot() { return autopilot; };
	void SetSIISep() { SIISepState = true; };
	void ClearSIISep() { SIISepState = false; };
	void SetEngineIndicator(int i);
	void ClearEngineIndicator(int i);

	void UpdateLaunchTime(double t);	

	//
	// Set up the default mesh for the virtual cockpit.
	//

	void DefaultCMMeshSetup();

	virtual void SetRCSState(int Quad, int Thruster, bool Active);
	virtual void SetCMRCSState(int Thruster, bool Active);
	virtual void SetSPSState(bool Active);
	// DS20060226 Added
	double sps_pitch_position;
	double sps_yaw_position;
	virtual double SetSPSPitch(double direction);
	virtual double SetSPSYaw(double direction);

	// DS20060301 DirectInput stuff
	// Handle to DLL instance
	HINSTANCE dllhandle;
	// pointer to DirectInput class itself
	LPDIRECTINPUT8 dx8ppv;
	// Joysticks-Enabled flag / counter - Zero if we aren't using DirectInput, nonzero is the number of joysticks we have.
	int js_enabled;
	// Pointers to DirectInput joystick devices
	LPDIRECTINPUTDEVICE8 dx8_joystick[2]; // One for THC, one for RHC, ignore extras
	DIDEVCAPS			 dx8_jscaps[2];   // Joystick capabilities
	DIJOYSTATE2			 dx8_jstate[2];   // Joystick state
	HRESULT				 dx8_failure;     // DX failure reason
	int rhc_id;							  // Joystick # for the RHC
	int rhc_rot_id;						  // ID of ROTATOR axis to use for RHC Z-axis
	int rhc_sld_id;                       // ID of SLIDER axis to use for RHC Z-axis
	int rhc_rzx_id;                       // Flag to use native Z-axis as RHC Z-axis
	int thc_id;                           // Joystick # for the THC
	int thc_rot_id;						  // ID of ROTATOR axis to use for THC Z-axis
	int thc_sld_id;                       // ID of SLIDER axis to use for THC Z-axis
	int thc_rzx_id;                       // Flag to use native Z-axis as THC Z-axis	
	int rhc_debug;						  // Flags to print debugging messages.
	int thc_debug;

	//
	// General functions that handle calls from Orbiter.
	//
	void clbkDockEvent(int dock, OBJHANDLE connected);
	bool clbkLoadGenericCockpit ();
	bool clbkPanelMouseEvent(int id, int event, int mx, int my);
	bool clbkPanelRedrawEvent(int id, int event, SURFHANDLE surf);
	void clbkMFDMode (int mfd, int mode);
	void clbkSaveState (FILEHANDLE scn);
	void clbkPostStep (double simt, double simdt, double mjd);
	void clbkPreStep(double simt, double simdt, double mjd);
	bool clbkLoadPanel (int id);
	int clbkConsumeDirectKey(char *keystate);
	int clbkConsumeBufferedKey(DWORD key, bool down, char *kstate);
	bool clbkLoadVC (int id);
	bool clbkVCMouseEvent (int id, int event, VECTOR3 &p);
	bool clbkVCRedrawEvent (int id, int event, SURFHANDLE surf);
	virtual void Timestep(double simt, double simdt) = 0;

	void InitVC (int vc);

	void PanelSwitchToggled(ToggleSwitch *s);
	void PanelIndicatorSwitchStateRequested(IndicatorSwitch *s); 
	void PanelRotationalSwitchChanged(RotationalSwitch *s);
	void PanelThumbwheelSwitchChanged(ThumbwheelSwitch *s);

	bool DisplayingPropellantQuantity();

	// Called by Crawler/ML
	virtual void LaunchVehicleRolloutEnd() {};	// after arrival on launch pad
	virtual void LaunchVehicleBuild() {};		// build/unbuild during assembly
	virtual void LaunchVehicleUnbuild() {};
	
	int GetBuildStatus() { return buildstatus; }
	int GetStage() { return stage; };
	int GetApolloNo() { return ApolloNo; };
	double GetMissionTime() { return MissionTime; };

	//
	// CWS functions.
	//

	void GetAtmosStatus(AtmosStatus &atm);
	void GetDisplayedAtmosStatus(DisplayedAtmosStatus &atm);
	void GetTankPressures(TankPressures &press);
	void GetTankQuantities(TankQuantities &q);
	void SetO2TankQuantities(double q);
	void GetFuelCellStatus(int index, FuelCellStatus &fc);
	void GetPrimECSCoolingStatus(PrimECSCoolingStatus &pcs);
	void GetSecECSCoolingStatus(SecECSCoolingStatus &scs);
	void GetECSWaterStatus(ECSWaterStatus &ws);
	void GetMainBusStatus(MainBusStatus &ms);
	void GetACBusStatus(ACBusStatus &as, int busno);
	void DisconectInverter(bool disc, int busno);
	void GetAGCWarningStatus(AGCWarningStatus &aws);
	double GetAccelG() { return aZAcc / G; };

	// LV Status Check
	void GetLVTankQuantities(LVTankQuantities &LVq);

	//
	// Panel SDK support.
	//
	
	void SetValveState(int valve, bool open);
	bool GetValveState(int valve);
	void CheckSPSState();
	void CheckRCSState();
	void SetRCSThrusters(THRUSTER_HANDLE *th, PROPELLANT_HANDLE ph);
	void CheckSMSystemsState();
	bool PyrosArmed();
	bool SECSLogicActive();
	void SlowIfDesired();
	void ActivateS4RCS();
	void DeactivateS4RCS();

protected:

	//
	// PanelSDK functions as a interface between the
	// actual System & Panel SDK and VESSEL class
	//
	// Note that this must be defined early in the file, so it will be initialised
	// before any other classes which rely on it at creation. Don't move it further
	// down without good reason, or you're likely to crash!
	//

    PanelSDK Panelsdk;
	// FILE *PanelsdkLogFile;

	void InitSwitches();
	void SetEngineIndicators();
	void ClearEngineIndicators();
	void SetLiftoffLight();
	void ClearLiftoffLight();
	void SetLVGuidLight();
	void ClearLVGuidLight();
	void SetLVRateLight();
	void ClearLVRateLight();

	bool ELSActive();
	bool ELSAuto();
	bool RCSLogicActive();
	bool RCSDumpActive();
	bool RCSPurgeActive();
	bool LETAttached();

	bool SaturnHasCSM();

	//
	// State that needs to be saved.
	//

	char StagesString[256];

	bool autopilot;
	bool SIISepState;
	bool ABORT_IND;

	bool InterstageAttached;
	bool LESAttached;

	//
	// Checklists.
	//

	bool useChecklists;
	char lastChecklist[256];

	bool DeleteLaunchSite;

	int buildstatus;

	//
	// Current mission time and mission times for stage events.
	//

	double MissionTime;
	double NextMissionEventTime;
	double LastMissionEventTime;
	double NextDestroyCheckTime;
	double NextFailureTime;

	//
	// Offset from mission time for clock display on control
	// panel, and offset of event timer from mission time.
	//

	MissionTimer MissionTimerDisplay;
	EventTimer EventTimerDisplay;
	
	//
	// Center engine shutdown times for first and
	// second stage.
	//

	double FirstStageCentreShutdownTime;
	double SecondStageCentreShutdownTime;

	//
	// Interstage and LES jettison time.
	//

	double InterstageSepTime;
	double LESJettisonTime;

	//
	// Mixture-ratio shift time for second stage.
	//

	double SecondStagePUShiftTime;

	//
	// Stage shutdown times.
	//

	double FirstStageShutdownTime;
	double SecondStageShutdownTime;

	//
	// Iterative Guidance Mode start time, when we stop following the pitch program and start aiming for
	// the correct orbit.
	//

	double IGMStartTime;
	bool IGMEnabled;

	//
	// Low-res mesh?
	//

	bool LowRes;

	//
	// Mesh handles.
	//

	MESHHANDLE hStage1Mesh;
	MESHHANDLE hStage2Mesh;
	MESHHANDLE hStage3Mesh;
	MESHHANDLE hInterstageMesh;
	MESHHANDLE hStageSLA1Mesh;
	MESHHANDLE hStageSLA2Mesh;
	MESHHANDLE hStageSLA3Mesh;
	MESHHANDLE hStageSLA4Mesh;

	UINT SPSidx;

	bool LEM_DISPLAY;

	int dockstate;

	int VehicleNo;
	int ApolloNo;

	bool UseATC;
	int Realism;

	bool Scorrec;
	bool ApolloExploded;
	bool Burned;
	bool EVA_IP;
	bool HatchOpen;
	bool CryoStir;

	double TCPO;

	//
	// Failures.
	//

	LandingFailures LandFail;
	LaunchFailures LaunchFail;
	SwitchFailures SwitchFail;

	//
	// Pitch table.
	//

	#define PITCH_TABLE_SIZE	16

	double met[PITCH_TABLE_SIZE];
	double cpitch[PITCH_TABLE_SIZE];

	// DS20060304 SCS COMPONENTS	
	BMAG bmag1;
	BMAG bmag2;
	GDC  gdc;
	ASCP ascp;
	EDA  eda;
	RJEC rjec;
	ECA  eca;
	// DS20060326 TELECOM EQUIPMENT
	PCM  pcm;

	//
	// Switches
	//
	int coasEnabled;

	FDAI fdaiRight;
	FDAI fdaiLeft;
	int fdaiDisabled;
	int fdaiSmooth;

	HBITMAP hBmpFDAIRollIndicator;

	SwitchRow IMUCageSwitchRow;
	SwitchRow CautionWarningRow;
	SwitchRow MissionTimerSwitchesRow;
	SwitchRow SPSRow;

	SwitchRow AccelGMeterRow;
	SaturnAccelGMeter AccelGMeter;

	GuardedPushSwitch LiftoffNoAutoAbortSwitch;
	GuardedPushSwitch LesMotorFireSwitch;
	GuardedPushSwitch CanardDeploySwitch;
	GuardedPushSwitch CsmLvSepSwitch;
	GuardedPushSwitch ApexCoverJettSwitch;
	GuardedPushSwitch DrogueDeploySwitch;
	GuardedPushSwitch MainDeploySwitch;
	GuardedPushSwitch CmRcsHeDumpSwitch;

	ToggleSwitch	    EDSSwitch;				
	GuardedToggleSwitch CsmLmFinalSep1Switch;
	GuardedToggleSwitch CsmLmFinalSep2Switch;
	GuardedTwoOutputSwitch CmSmSep1Switch;
	GuardedTwoOutputSwitch CmSmSep2Switch;
	GuardedToggleSwitch SivbLmSepSwitch;

	ToggleSwitch   CabinFan1Switch;
	ToggleSwitch   CabinFan2Switch;
	ThreePosSwitch H2Heater1Switch;
	ThreePosSwitch H2Heater2Switch;
	ThreePosSwitch O2Heater1Switch;
	ThreePosSwitch O2Heater2Switch;	
	ToggleSwitch   O2PressIndSwitch;	
	ThreePosSwitch H2Fan1Switch; 
	ThreePosSwitch H2Fan2Switch; 
	ThreePosSwitch O2Fan1Switch; 
	ThreePosSwitch O2Fan2Switch; 

	IndicatorSwitch FuelCellPhIndicator;
	IndicatorSwitch FuelCellRadTempIndicator;

	IndicatorSwitch FuelCellRadiators1Indicator;
	IndicatorSwitch FuelCellRadiators2Indicator;
	IndicatorSwitch FuelCellRadiators3Indicator;
	ThreePosSwitch FuelCellRadiators1Switch;
	ThreePosSwitch FuelCellRadiators2Switch;
	ThreePosSwitch FuelCellRadiators3Switch;

	RotationalSwitch FuelCellIndicatorsSwitch;

	ToggleSwitch FuelCellHeater1Switch;
	ToggleSwitch FuelCellHeater2Switch;
	ToggleSwitch FuelCellHeater3Switch;

	ThreePosSwitch FuelCellPurge1Switch;
	ThreePosSwitch FuelCellPurge2Switch;
	ThreePosSwitch FuelCellPurge3Switch;

	IndicatorSwitch FuelCellReactants1Indicator;
	IndicatorSwitch FuelCellReactants2Indicator;
	IndicatorSwitch FuelCellReactants3Indicator;
	ThreePosSwitch FuelCellReactants1Switch;
	ThreePosSwitch FuelCellReactants2Switch;
	ThreePosSwitch FuelCellReactants3Switch;

	ToggleSwitch FCReacsValvesSwitch;
	ToggleSwitch H2PurgeLineSwitch;

	ThreeSourceSwitch FuelCellPumps1Switch;
	ThreeSourceSwitch FuelCellPumps2Switch;
	ThreeSourceSwitch FuelCellPumps3Switch;

	SaturnSuitCompressorSwitch SuitCompressor1Switch;
	SaturnSuitCompressorSwitch SuitCompressor2Switch;

	TimerControlSwitch MissionTimerSwitch;
	CWSModeSwitch CautionWarningModeSwitch;
	CWSSourceSwitch CautionWarningCMCSMSwitch;
	CWSPowerSwitch CautionWarningPowerSwitch;
	CWSLightTestSwitch CautionWarningLightTestSwitch;

	TimerUpdateSwitch MissionTimerHoursSwitch;
	TimerUpdateSwitch MissionTimerMinutesSwitch;
	TimerUpdateSwitch MissionTimerSecondsSwitch;

	IMUCageSwitch IMUGuardedCageSwitch;

	SwitchRow SMRCSHelium1Row;
	SaturnValveSwitch SMRCSHelium1ASwitch;
	SaturnValveSwitch SMRCSHelium1BSwitch;
	SaturnValveSwitch SMRCSHelium1CSwitch;
	SaturnValveSwitch SMRCSHelium1DSwitch;

	SwitchRow SMRCSHelium1TalkbackRow;
	SaturnValveTalkback SMRCSHelium1ATalkback;
	SaturnValveTalkback SMRCSHelium1BTalkback;
	SaturnValveTalkback SMRCSHelium1CTalkback;
	SaturnValveTalkback SMRCSHelium1DTalkback;

	SwitchRow SMRCSHelium2Row;
	SaturnValveSwitch SMRCSHelium2ASwitch;
	SaturnValveSwitch SMRCSHelium2BSwitch;
	SaturnValveSwitch SMRCSHelium2CSwitch;
	SaturnValveSwitch SMRCSHelium2DSwitch;

	SwitchRow SMRCSHelium2TalkbackRow;
	SaturnValveTalkback SMRCSHelium2ATalkback;
	SaturnValveTalkback SMRCSHelium2BTalkback;
	SaturnValveTalkback SMRCSHelium2CTalkback;
	SaturnValveTalkback SMRCSHelium2DTalkback;

	AGCIOSwitch CMUplinkSwitch;
	ToggleSwitch IUUplinkSwitch;

	GuardedToggleSwitch CMRCSPressSwitch;
	ToggleSwitch SMRCSIndSwitch;

	SwitchRow RCSGaugeRow;
	RCSQuantityMeter RCSQuantityGauge;

	SwitchRow SMRCSProp1Row;
	SaturnPropValveSwitch SMRCSProp1ASwitch;
	SaturnPropValveSwitch SMRCSProp1BSwitch;
	SaturnPropValveSwitch SMRCSProp1CSwitch;
	SaturnPropValveSwitch SMRCSProp1DSwitch;

	ThreePosSwitch SMRCSHeaterASwitch;
	ThreePosSwitch SMRCSHeaterBSwitch;
	ThreePosSwitch SMRCSHeaterCSwitch;
	ThreePosSwitch SMRCSHeaterDSwitch;

	SwitchRow SMRCSProp1TalkbackRow;
	SaturnPropValveTalkback SMRCSProp1ATalkback;
	SaturnPropValveTalkback SMRCSProp1BTalkback;
	SaturnPropValveTalkback SMRCSProp1CTalkback;
	SaturnPropValveTalkback SMRCSProp1DTalkback;

	SwitchRow SMRCSProp2Row;
	SaturnValveSwitch SMRCSProp2ASwitch;
	SaturnValveSwitch SMRCSProp2BSwitch;
	SaturnValveSwitch SMRCSProp2CSwitch;
	SaturnValveSwitch SMRCSProp2DSwitch;

	ThreePosSwitch RCSCMDSwitch;
	ThreePosSwitch RCSTrnfrSwitch;
	SaturnValveSwitch CMRCSIsolate1;
	SaturnValveSwitch CMRCSIsolate2;

	SwitchRow SMRCSProp2TalkbackRow;
	SaturnValveTalkback CMRCSIsolate1Talkback;
	SaturnValveTalkback CMRCSIsolate2Talkback;
	SaturnPropValveTalkback SMRCSProp2ATalkback;
	SaturnPropValveTalkback SMRCSProp2BTalkback;
	SaturnPropValveTalkback SMRCSProp2CTalkback;
	SaturnPropValveTalkback SMRCSProp2DTalkback;

	SwitchRow RCSIndicatorsSwitchRow;
	PropellantRotationalSwitch RCSIndicatorsSwitch;

	SwitchRow ECSIndicatorsSwitchRow;
	RotationalSwitch ECSIndicatorsSwitch;

	SwitchRow AttitudeControlRow;
	ThreePosSwitch ManualAttRollSwitch;
	ThreePosSwitch ManualAttPitchSwitch;
	ThreePosSwitch ManualAttYawSwitch;
	ToggleSwitch LimitCycleSwitch;
	ToggleSwitch AttDeadbandSwitch;
	ToggleSwitch AttRateSwitch;
	ToggleSwitch TransContrSwitch;

	SwitchRow BMAGRow;
	ThreePosSwitch BMAGRollSwitch;
	ThreePosSwitch BMAGPitchSwitch;
	ThreePosSwitch BMAGYawSwitch;

	SwitchRow EntryModeRow;
	ThreePosSwitch EntryModeSwitch;

	SwitchRow EMSFunctionSwitchRow;
	RotationalSwitch EMSFunctionSwitch;

	SwitchRow GTASwitchRow;
	GuardedToggleSwitch GTASwitch;

	SwitchRow SCContCMCModeSwitchesRow;
	AGCIOSwitch SCContSwitch;
	CMCModeHoldFreeSwitch CMCModeSwitch;

	SwitchRow SCSTvcSwitchesRow;
	ThreePosSwitch SCSTvcPitchSwitch;
	ThreePosSwitch SCSTvcYawSwitch;

	SwitchRow SPSGimbalMotorsRow;
	ThreePosSwitch Pitch1Switch;
	ThreePosSwitch Pitch2Switch;
	ThreePosSwitch Yaw1Switch;
	ThreePosSwitch Yaw2Switch;

	SwitchRow EntrySwitchesRow;
	ToggleSwitch EMSRollSwitch;
	ToggleSwitch GSwitch;

	SwitchRow LVSPSIndSwitchesRow;
	ToggleSwitch LVSPSPcIndicatorSwitch;
	ToggleSwitch LVFuelTankPressIndicatorSwitch;

	SwitchRow TVCGimbalDriveSwitchesRow;
	ThreePosSwitch TVCGimbalDrivePitchSwitch;
	ThreePosSwitch TVCGimbalDriveYawSwitch;

	SwitchRow CSMLightSwitchesRow;
	ToggleSwitch RunEVALightSwitch;
	ThreePosSwitch RndzLightSwitch;
	ToggleSwitch TunnelLightSwitch;

	SwitchRow LMPowerSwitchRow;
	ThreePosSwitch LMPowerSwitch;

	SwitchRow PostLDGVentValveLeverRow;
	CircuitBrakerSwitch PostLDGVentValveLever;
	
	//
	// Communication switches (s-band, vhf etc.)
	//

	ThreePosSwitch SBandNormalXPDRSwitch;
	ThreePosSwitch SBandNormalPwrAmpl1Switch;
	ThreePosSwitch SBandNormalPwrAmpl2Switch;
	ThreePosSwitch SBandNormalMode1Switch;
	ThreePosSwitch SBandNormalMode2Switch;
	ToggleSwitch SBandNormalMode3Switch;

	SwitchRow SBandAuxSwitchesRow;
	ThreePosSwitch SBandAuxSwitch1;
	ThreePosSwitch SBandAuxSwitch2;

	SwitchRow UPTLMSwitchesRow;
	ThreePosSwitch UPTLMSwitch1;
	ThreePosSwitch UPTLMSwitch2;

	SwitchRow SBandAntennaSwitchesRow;
	ThreePosSwitch SBandAntennaSwitch1;
	ThreePosSwitch SBandAntennaSwitch2;

	SwitchRow VHFAmThumbwheelsRow;
	ThumbwheelSwitch SquelchAThumbwheel;
	ThumbwheelSwitch SquelchBThumbwheel;

	SwitchRow VHFSwitchesRow;
	ThreePosSwitch VHFAMASwitch;
	ThreePosSwitch VHFAMBSwitch;
	ThreePosSwitch RCVOnlySwitch;
	ToggleSwitch VHFBeaconSwitch;
	ToggleSwitch VHFRangingSwitch;

	SwitchRow TapeRecorderSwitchesRow;
	ToggleSwitch TapeRecorder1Switch;
	ThreePosSwitch TapeRecorder2Switch;
	ThreePosSwitch TapeRecorder3Switch;

	SwitchRow PowerSwitchesRow;
	ThreePosSwitch SCESwitch;
	ThreePosSwitch PMPSwitch;

	SwitchRow PCMBitRateSwitchRow;
	ToggleSwitch PCMBitRateSwitch;
	ThreePosSwitch DummySwitch;
	
	//
	// VHF antenna rotary
	//
	
	SwitchRow VHFAntennaRotaryRow;
	RotationalSwitch VHFAntennaRotarySwitch;

	//
	// SPS switches (panel 3)
	//

	SwitchRow SPSTestSwitchRow;
	ThreePosSwitch SPSTestSwitch;

	SwitchRow SPSOxidFlowValveSwitchesRow;
	ThreePosSwitch SPSOxidFlowValveSwitch;
	ToggleSwitch SPSOxidFlowValveSelectorSwitch;

	SwitchRow PugModeSwitchRow;
	ThreePosSwitch PugModeSwitch;

	SwitchRow SPSSwitchesRow;
	ThreePosSwitch LineHTRSSwitch;
	ThreePosSwitch PressIndSwitch;

	//
	// Electricals switches & indicators
	//

	SwitchRow DCIndicatorsRotaryRow;
	PowerStateRotationalSwitch DCIndicatorsRotary;

	SwitchRow BatteryChargeRotaryRow;
	PowerStateRotationalSwitch BatteryChargeRotary;

	SwitchRow ACIndicatorRotaryRow;
	PowerStateRotationalSwitch ACIndicatorRotary;

	SwitchRow ACInverterSwitchesRow;
	TwoSourceSwitch MnA1Switch;
	TwoSourceSwitch MnB2Switch;
	ThreeSourceSwitch MnA3Switch;
	TwoSourceSwitch AcBus1Switch1;
	TwoSourceSwitch AcBus1Switch2;
	TwoSourceSwitch AcBus1Switch3;
	ThreeSourceSwitch AcBus1ResetSwitch;
	TwoSourceSwitch AcBus2Switch1;
	TwoSourceSwitch AcBus2Switch2;
	TwoSourceSwitch AcBus2Switch3;
	ThreeSourceSwitch AcBus2ResetSwitch;

	IndicatorSwitch MainBusBIndicator1;
	IndicatorSwitch MainBusBIndicator2;
	IndicatorSwitch MainBusBIndicator3;
	IndicatorSwitch MainBusAIndicator1;
	IndicatorSwitch MainBusAIndicator2;
	IndicatorSwitch MainBusAIndicator3;
	ThreePosSwitch MainBusBSwitch1;
	ThreePosSwitch MainBusBSwitch2;
	ThreePosSwitch MainBusBSwitch3;
	ThreeSourceSwitch MainBusBResetSwitch;
	ThreePosSwitch MainBusASwitch1;
	ThreePosSwitch MainBusASwitch2;
	ThreePosSwitch MainBusASwitch3;
	ThreeSourceSwitch MainBusAResetSwitch;
	
	//
	// FDAI control switches.
	//

	SwitchRow FDAISwitchesRow;
	ThreePosSwitch FDAIScaleSwitch;
	ThreePosSwitch FDAISourceSwitch;
	ThreePosSwitch FDAISelectSwitch;
	ToggleSwitch FDAIAttSetSwitch;

	//
	// CMC Att: IMU is normal state, GDC does nothing.
	//

	SwitchRow CMCAttRow;
	ToggleSwitch CMCAttSwitch;

	//
	// Launch vehicle switches.
	//

	SwitchRow LVRow;
	GuardedToggleSwitch LVGuidanceSwitch;
	GuardedToggleSwitch SIISIVBSepSwitch;
	XLunarSwitch TLIEnableSwitch;

	//
	// ELS and CSM propellant switches.
	//

	SwitchRow ELSRow;
	AGCIOSwitch CGSwitch;
	GuardedTwoOutputSwitch ELSLogicSwitch;
	ToggleSwitch ELSAutoSwitch;
	TwoOutputSwitch CMRCSLogicSwitch;
	GuardedToggleSwitch CMPropDumpSwitch;
	GuardedToggleSwitch CPPropPurgeSwitch;

	//
	// Event Timer switches.
	//

	SwitchRow EventTimerRow;
	ToggleSwitch FCSMSPSASwitch;
	ToggleSwitch FCSMSPSBSwitch;
	EventTimerResetSwitch EventTimerUpDownSwitch;
	EventTimerControlSwitch EventTimerControlSwitch;
	TimerUpdateSwitch EventTimerMinutesSwitch;
	TimerUpdateSwitch EventTimerSecondsSwitch;

	//
	// Main chute release switch.
	//
	// Currently this does nothing, as the parachutes automatically release from the CM
	// after landing.
	//

	SwitchRow MainReleaseRow;
	GuardedToggleSwitch MainReleaseSwitch;

	//
	// Abort switches.
	//

	SwitchRow AbortRow;
	ToggleSwitch PropDumpAutoSwitch;
	ToggleSwitch TwoEngineOutAutoSwitch;
	ToggleSwitch LVRateAutoSwitch;
	GuardedThreePosSwitch TowerJett1Switch;
	GuardedThreePosSwitch TowerJett2Switch;

	//
	// Rotational Controller power switches.
	//

	SwitchRow RotContrPowerRow;
	ThreePosSwitch RotPowerNormal1Switch;
	ThreePosSwitch RotPowerNormal2Switch;
	ThreePosSwitch RotPowerDirect1Switch;
	ThreePosSwitch RotPowerDirect2Switch;

	//
	// dV Thrust switches.
	//

	SwitchRow dvThrustRow;
	GuardedToggleSwitch dVThrust1Switch;
	GuardedToggleSwitch dVThrust2Switch;

	//
	// SPS Switch.
	//

	SaturnSPSSwitch SPSswitch;

	//
	// Cryo tank meters
	//
	SwitchRow CryoTankMetersRow;
	SaturnH2PressureMeter H2Pressure1Meter;
	SaturnH2PressureMeter H2Pressure2Meter;
	SaturnO2PressureMeter O2Pressure1Meter;
	SaturnO2PressureMeter O2Pressure2Meter;
	SaturnCryoQuantityMeter H2Quantity1Meter;
	SaturnCryoQuantityMeter H2Quantity2Meter;
	SaturnCryoQuantityMeter O2Quantity1Meter;
	SaturnCryoQuantityMeter O2Quantity2Meter;

	//
	// Fuel cell meters
	//
	SwitchRow FuelCellMetersRow;
	SaturnFuelCellH2FlowMeter FuelCellH2FlowMeter;
	SaturnFuelCellO2FlowMeter FuelCellO2FlowMeter;
	SaturnFuelCellTempMeter FuelCellTempMeter;
	SaturnFuelCellCondenserTempMeter FuelCellCondenserTempMeter;

	//
	// Cabin meters
	//
	SwitchRow CabinMetersRow;
	SaturnSuitTempMeter SuitTempMeter;
	SaturnCabinTempMeter CabinTempMeter;
	SaturnSuitPressMeter SuitPressMeter; 
	SaturnCabinPressMeter CabinPressMeter;
	SaturnPartPressCO2Meter PartPressCO2Meter; 

	//
	// Suit compressor delta pressure meter
	//
	SwitchRow SuitComprDeltaPMeterRow;
	SaturnSuitComprDeltaPMeter SuitComprDeltaPMeter;
	SaturnLeftO2FlowMeter LeftO2FlowMeter;

	//
	// Suit cabin delta pressure meter
	//
	SwitchRow SuitCabinDeltaPMeterRow;
	SaturnSuitCabinDeltaPMeter SuitCabinDeltaPMeter;
	SaturnRightO2FlowMeter RightO2FlowMeter;

	//
	// ECS radiator/evaporator temperature/pressure meters
	//
	SwitchRow EcsRadTempMetersRow;
	SaturnEcsRadTempInletMeter EcsRadTempInletMeter;
	SaturnEcsRadTempPrimOutletMeter EcsRadTempPrimOutletMeter;

	SwitchRow EcsEvapTempMetersRow;
	SaturnEcsRadTempSecOutletMeter EcsRadTempSecOutletMeter;
	SaturnGlyEvapTempOutletMeter GlyEvapTempOutletMeter;

	SwitchRow EcsPressMetersRow;
	SaturnGlyEvapSteamPressMeter GlyEvapSteamPressMeter;
	SaturnGlycolDischPressMeter GlycolDischPressMeter;

	SwitchRow EcsQuantityMetersRow;
	SaturnAccumQuantityMeter AccumQuantityMeter;
	SaturnH2oQuantityMeter H2oQuantityMeter;

	//
	// ECS radiator switches
	//
	SwitchRow EcsRadiatorIndicatorRow;
	IndicatorSwitch EcsRadiatorIndicator;

	SwitchRow EcsRadiatorSwitchesRow;
	ThreePosSwitch EcsRadiatorsFlowContAutoSwitch;
	ThreePosSwitch EcsRadiatorsFlowContPwrSwitch;
	ThreePosSwitch EcsRadiatorsManSelSwitch;
	ThreePosSwitch EcsRadiatorsHeaterPrimSwitch;
	ToggleSwitch EcsRadiatorsHeaterSecSwitch;

	//
	// ECS switches
	//
	SwitchRow EcsSwitchesRow;
	ThreePosSwitch PotH2oHtrSwitch;
	ThreePosSwitch SuitCircuitH2oAccumAutoSwitch;
	ThreePosSwitch SuitCircuitH2oAccumOnSwitch;
	ThreePosSwitch SuitCircuitHeatExchSwitch;
	ThreePosSwitch SecCoolantLoopEvapSwitch;
	ThreeSourceSwitch SecCoolantLoopPumpSwitch;
	ToggleSwitch H2oQtyIndSwitch;
	ToggleSwitch GlycolEvapTempInSwitch;
	ToggleSwitch GlycolEvapSteamPressAutoManSwitch;
	ThreePosSwitch GlycolEvapSteamPressIncrDecrSwitch;
	ThreePosSwitch GlycolEvapH2oFlowSwitch;
	ToggleSwitch CabinTempAutoManSwitch;

	SwitchRow CabinTempAutoControlSwitchRow;
	ThumbwheelSwitch CabinTempAutoControlSwitch;

	SwitchRow EcsGlycolPumpsSwitchRow;
	SaturnEcsGlycolPumpsSwitch EcsGlycolPumpsSwitch;

	//
	// High gain antenna
	//
	
	SwitchRow HighGainAntennaUpperSwitchesRow;
	ThreePosSwitch GHATrackSwitch;
	ThreePosSwitch GHABeamSwitch;

	SwitchRow HighGainAntennaLowerSwitchesRow;
	ThreePosSwitch GHAPowerSwitch;
	ToggleSwitch GHAServoElecSwitch;
	
	SwitchRow HighGainAntennaPitchPositionSwitchRow;
	RotationalSwitch HighGainAntennaPitchPositionSwitch;

	SwitchRow HighGainAntennaYawPositionSwitchRow;
	RotationalSwitch HighGainAntennaYawPositionSwitch;

	//
	// Docking probe switches
	//
	SwitchRow DockingProbeSwitchesRow;
	GuardedThreePosSwitch DockingProbeExtdRelSwitch;
	ThreePosSwitch DockingProbeRetractPrimSwitch;
	ThreePosSwitch DockingProbeRetractSecSwitch;

	SwitchRow DockingProbeIndicatorsRow;
	IndicatorSwitch DockingProbeAIndicator;
	IndicatorSwitch DockingProbeBIndicator;

	//
	// Orbiter switches
	//

	SwitchRow OrbiterAttitudeToggleRow;
	AttitudeToggle OrbiterAttitudeToggle;

	/////////////////////////////
	// Panel 5 circuit brakers //
	/////////////////////////////
	
	// EPS sensor signal circuit brakers

	SwitchRow EpsSensorSignalDcCircuitBrakersRow;
	CircuitBrakerSwitch EpsSensorSignalDcMnaCircuitBraker;
	CircuitBrakerSwitch EpsSensorSignalDcMnbCircuitBraker;
	
	SwitchRow EpsSensorSignalAcCircuitBrakersRow;
	CircuitBrakerSwitch EpsSensorSignalAc1CircuitBraker;
	CircuitBrakerSwitch EpsSensorSignalAc2CircuitBraker;

	// C/W circuit brakers

	SwitchRow CWCircuitBrakersRow;
	CircuitBrakerSwitch CWMnaCircuitBraker;
	CircuitBrakerSwitch CWMnbCircuitBraker;

	// LEM PWR circuit brakers
	
	SwitchRow LMPWRCircuitBrakersRow;
	CircuitBrakerSwitch MnbLMPWR1CircuitBraker;
	CircuitBrakerSwitch MnbLMPWR2CircuitBraker;

	// Inverter control circuit brakers
	
	SwitchRow InverterControlCircuitBrakersRow;
	CircuitBrakerSwitch InverterControl1CircuitBraker;
	CircuitBrakerSwitch InverterControl2CircuitBraker;
	CircuitBrakerSwitch InverterControl3CircuitBraker;

	// EPS sensor unit circuit brakers
	
	SwitchRow EPSSensorUnitCircuitBrakersRow;
	CircuitBrakerSwitch EPSSensorUnitDcBusACircuitBraker;
	CircuitBrakerSwitch EPSSensorUnitDcBusBCircuitBraker;
	CircuitBrakerSwitch EPSSensorUnitAcBus1CircuitBraker;
	CircuitBrakerSwitch EPSSensorUnitAcBus2CircuitBraker;

	// Battery relay bus circuit brakers

	SwitchRow BATRLYBusCircuitBrakersRow;
	CircuitBrakerSwitch BATRLYBusBatACircuitBraker;
	CircuitBrakerSwitch BATRLYBusBatBCircuitBraker;

	// ECS radiators circuit brakers

	SwitchRow ECSRadiatorsCircuitBrakersRow;
	CircuitBrakerSwitch ControllerAc1CircuitBraker;
	CircuitBrakerSwitch ControllerAc2CircuitBraker;
	CircuitBrakerSwitch CONTHTRSMnACircuitBraker;
	CircuitBrakerSwitch CONTHTRSMnBCircuitBraker;
	CircuitBrakerSwitch HTRSOVLDBatACircuitBraker;
	CircuitBrakerSwitch HTRSOVLDBatBCircuitBraker;

	// Battery charger circuit brakers

	SwitchRow BatteryChargerCircuitBrakersRow;
	CircuitBrakerSwitch BatteryChargerBatACircuitBraker;
	CircuitBrakerSwitch BatteryChargerBatBCircuitBraker;
	CircuitBrakerSwitch BatteryChargerMnACircuitBraker;
	CircuitBrakerSwitch BatteryChargerMNBCircuitBraker;
	CircuitBrakerSwitch BatteryChargerAcPWRCircuitBraker;

	// Instrument lighting circuit brakers

	SwitchRow InstrumentLightingCircuitBrakersRow;
	CircuitBrakerSwitch InstrumentLightingESSMnACircuitBraker;
	CircuitBrakerSwitch InstrumentLightingESSMnBCircuitBraker;
	ThreeSourceSwitch InstrumentLightingNonESSCircuitBraker;
	CircuitBrakerSwitch InstrumentLightingSCIEquipSEP1CircuitBraker;
	CircuitBrakerSwitch InstrumentLightingSCIEquipSEP2CircuitBraker;
	CircuitBrakerSwitch InstrumentLightingSCIEquipHatchCircuitBraker;
	
	// ECS circuit brakers

	SwitchRow ECSCircuitBrakersRow;
	CircuitBrakerSwitch ECSPOTH2OHTRMnACircuitBraker;
	CircuitBrakerSwitch ECSPOTH2OHTRMnBCircuitBraker;
	CircuitBrakerSwitch ECSH2OAccumMnACircuitBraker;
	CircuitBrakerSwitch ECSH2OAccumMnBCircuitBraker;
	CircuitBrakerSwitch ECSTransducerWastePOTH2OMnACircuitBraker;
	CircuitBrakerSwitch ECSTransducerWastePOTH2OMnBCircuitBraker;
	CircuitBrakerSwitch ECSTransducerPressGroup1MnACircuitBraker;
	CircuitBrakerSwitch ECSTransducerPressGroup1MnBCircuitBraker;
	CircuitBrakerSwitch ECSTransducerPressGroup2MnACircuitBraker;
	CircuitBrakerSwitch ECSTransducerPressGroup2MnBCircuitBraker;
	CircuitBrakerSwitch ECSTransducerTempMnACircuitBraker;
	CircuitBrakerSwitch ECSTransducerTempMnBCircuitBraker;

	// ECS circuit brakers lower row 

	SwitchRow ECSLowerRowCircuitBrakersRow;
	CircuitBrakerSwitch ECSSecCoolLoopAc1CircuitBraker;
	CircuitBrakerSwitch ECSSecCoolLoopAc2CircuitBraker;
	CircuitBrakerSwitch ECSSecCoolLoopRADHTRMnACircuitBraker;
	CircuitBrakerSwitch ECSSecCoolLoopXducersMnACircuitBraker;
	CircuitBrakerSwitch ECSSecCoolLoopXducersMnBCircuitBraker;
	CircuitBrakerSwitch ECSWasteH2OUrineDumpHTRMnACircuitBraker;
	CircuitBrakerSwitch ECSWasteH2OUrineDumpHTRMnBCircuitBraker;
	CircuitBrakerSwitch ECSCabinFanAC1ACircuitBraker;
	CircuitBrakerSwitch ECSCabinFanAC1BCircuitBraker;
	CircuitBrakerSwitch ECSCabinFanAC1CCircuitBraker;
	CircuitBrakerSwitch ECSCabinFanAC2ACircuitBraker;
	CircuitBrakerSwitch ECSCabinFanAC2BCircuitBraker;
	CircuitBrakerSwitch ECSCabinFanAC2CCircuitBraker;

	// Guidance/navigation circuit brakers 

	SwitchRow GNCircuitBrakersRow;
	CircuitBrakerSwitch GNPowerAc1CircuitBraker;
	CircuitBrakerSwitch GNPowerAc2CircuitBraker;
	CircuitBrakerSwitch GNIMUMnACircuitBraker;
	CircuitBrakerSwitch GNIMUMnBCircuitBraker;
	CircuitBrakerSwitch GNIMUHTRMnACircuitBraker;
	CircuitBrakerSwitch GNIMUHTRMnBCircuitBraker;
	CircuitBrakerSwitch GNComputerMnACircuitBraker;
	CircuitBrakerSwitch GNComputerMnBCircuitBraker;
	CircuitBrakerSwitch GNOpticsMnACircuitBraker;
	CircuitBrakerSwitch GNOpticsMnBCircuitBraker;

	/////////////////////////////
	// Panel 4 circuit brakers //
	/////////////////////////////
	
	// Suit compressors circuit brakers 

	SwitchRow SuitCompressorsAc1ACircuitBrakerRow;
	CircuitBrakerSwitch SuitCompressorsAc1ACircuitBraker;

	SwitchRow SuitCompressorsAc1BCircuitBrakerRow;
	CircuitBrakerSwitch SuitCompressorsAc1BCircuitBraker;

	SwitchRow SuitCompressorsAc1CCircuitBrakerRow;
	CircuitBrakerSwitch SuitCompressorsAc1CCircuitBraker;

	SwitchRow SuitCompressorsAc2ACircuitBrakerRow;
	CircuitBrakerSwitch SuitCompressorsAc2ACircuitBraker;

	SwitchRow SuitCompressorsAc2BCircuitBrakerRow;
	CircuitBrakerSwitch SuitCompressorsAc2BCircuitBraker;

	SwitchRow SuitCompressorsAc2CCircuitBrakerRow;
	CircuitBrakerSwitch SuitCompressorsAc2CCircuitBraker;

	// ECS glycol pumps circuit brakers 

	SwitchRow ECSGlycolPumpsAc1ACircuitBrakerRow;
	CircuitBrakerSwitch ECSGlycolPumpsAc1ACircuitBraker;

	SwitchRow ECSGlycolPumpsAc1BCircuitBrakerRow;
	CircuitBrakerSwitch ECSGlycolPumpsAc1BCircuitBraker;

	SwitchRow ECSGlycolPumpsAc1CCircuitBrakerRow;
	CircuitBrakerSwitch ECSGlycolPumpsAc1CCircuitBraker;

	SwitchRow ECSGlycolPumpsAc2ACircuitBrakerRow;
	CircuitBrakerSwitch ECSGlycolPumpsAc2ACircuitBraker;

	SwitchRow ECSGlycolPumpsAc2BCircuitBrakerRow;
	CircuitBrakerSwitch ECSGlycolPumpsAc2BCircuitBraker;

	SwitchRow ECSGlycolPumpsAc2CCircuitBrakerRow;
	CircuitBrakerSwitch ECSGlycolPumpsAc2CCircuitBraker;

	/////////////////////////
	// Panel 6 thumbwheels //
	/////////////////////////

	SwitchRow ModeIntercomVOXSensThumbwheelSwitchRow;
	ThumbwheelSwitch ModeIntercomVOXSensThumbwheelSwitch;

	SwitchRow PowerMasterVolumeThumbwheelSwitchRow;
	VolumeThumbwheelSwitch PowerMasterVolumeThumbwheelSwitch;

	SwitchRow PadCommVolumeThumbwheelSwitchRow;
	ThumbwheelSwitch PadCommVolumeThumbwheelSwitch;

	SwitchRow IntercomVolumeThumbwheelSwitchRow;
	ThumbwheelSwitch IntercomVolumeThumbwheelSwitch;

	SwitchRow SBandVolumeThumbwheelSwitchRow;
	ThumbwheelSwitch SBandVolumeThumbwheelSwitch;

	SwitchRow VHFAMVolumeThumbwheelSwitchRow;
	ThumbwheelSwitch VHFAMVolumeThumbwheelSwitch;

	//////////////////////
	// Panel 6 switches //
	//////////////////////

	SwitchRow RightModeIntercomSwitchRow;
	ThreePosSwitch RightModeIntercomSwitch;

	SwitchRow RightAudioPowerSwitchRow;
	ThreePosSwitch RightAudioPowerSwitch;

	SwitchRow RightPadCommSwitchRow;
	ThreePosSwitch RightPadCommSwitch;

	SwitchRow RightIntercomSwitchRow;
	ThreePosSwitch RightIntercomSwitch;

	SwitchRow RightSBandSwitchRow;
	ThreePosSwitch RightSBandSwitch;

	SwitchRow RightVHFAMSwitchRow;
	ThreePosSwitch RightVHFAMSwitch;
	
	SwitchRow AudioControlSwitchRow;
	ToggleSwitch AudioControlSwitch;

	SwitchRow SuidPowerSwitchRow;
	ToggleSwitch SuidPowerSwitch;

	///////////////////////
	// Panel 16 switches //
	///////////////////////

	SwitchRow RightCOASPowerSwitchRow;
	ToggleSwitch RightCOASPowerSwitch;

	SwitchRow RightUtilityPowerSwitchRow;
	ToggleSwitch RightUtilityPowerSwitch;

	SwitchRow RightDockingTargetSwitchRow;
	ThreePosSwitch RightDockingTargetSwitch;

	//////////////////////
	// Panel 5 switches //
	//////////////////////

	SwitchRow GNPowerSwitchRow;
	ThreePosSwitch GNPowerSwitch;
	
	SwitchRow MainBusTieSwitchesRow;
	ThreePosSwitch MainBusTieBatAcSwitch;
	ThreePosSwitch MainBusTieBatBcSwitch;

	SwitchRow BatCHGRSwitchRow;
	ToggleSwitch BatCHGRSwitch;

	SwitchRow NonessBusSwitchRow;
	ThreePosSwitch NonessBusSwitch;

	SwitchRow InteriorLightsFloodSwitchesRow;
	ToggleSwitch InteriorLightsFloodDimSwitch;
	ToggleSwitch InteriorLightsFloodFixedSwitch;

	//////////////////////
	// Panel 5 rotaries //
	//////////////////////
	
	SwitchRow RightInteriorLightRotariesRow;
	RotationalSwitch RightIntegralRotarySwitch;
	RotationalSwitch RightFloodRotarySwitch;

	//////////////////////
	// Panel 4 switches //
	//////////////////////

	SwitchRow SPSGaugingSwitchRow;
	ThreePosSwitch SPSGaugingSwitch;

	SwitchRow TelcomSwitchesRow;
	ThreePosSwitch TelcomGroup1Switch;
	ThreePosSwitch TelcomGroup2Switch;

	////////////////////////
	// Right window cover //
	////////////////////////

	//SwitchRow RightWindowCoverRow;
	//ToggleSwitch RightWindowCoverSwitch;

	/////////////////////////////
	// G&N lower equipment bay //
	/////////////////////////////

	SwitchRow ModeSwitchRow;
	ThreePosSwitch ModeSwitch;

	SwitchRow ControllerSpeedSwitchRow;
	ThreePosSwitch ControllerSpeedSwitch;

	SwitchRow ControllerCouplingSwitchRow;
	ToggleSwitch ControllerCouplingSwitch;

	SwitchRow ControllerSwitchesRow;
	ThreePosSwitch ControllerTrackerSwitch;
	ThreePosSwitch ControllerTelescopeTrunnionSwitch;

	SwitchRow ConditionLampsSwitchRow;
	ThreePosSwitch ConditionLampsSwitch;

	SwitchRow UPTLMSwitchRow;
	ToggleSwitch UPTLMSwitch;

	///////////////////////
	// Panel 15 switches //
	///////////////////////

	SwitchRow LeftCOASPowerSwitchRow;
	ToggleSwitch LeftCOASPowerSwitch;

	SwitchRow LeftUtilityPowerSwitchRow;
	ToggleSwitch LeftUtilityPowerSwitch;

	SwitchRow PostLandingBCNLTSwitchRow;
	ThreePosSwitch PostLandingBCNLTSwitch;

	SwitchRow PostLandingDYEMarkerSwitchRow;
	GuardedToggleSwitch PostLandingDYEMarkerSwitch;

	SwitchRow PostLandingVentSwitchRow;
	ThreePosSwitch PostLandingVentSwitch;

	/////////////////////////
	// Panel 9 thumbwheels //
	/////////////////////////

	SwitchRow LeftModeIntercomVOXSensThumbwheelSwitchRow;
	ThumbwheelSwitch LeftModeIntercomVOXSensThumbwheelSwitch;

	SwitchRow LeftPowerMasterVolumeThumbwheelSwitchRow;
	VolumeThumbwheelSwitch LeftPowerMasterVolumeThumbwheelSwitch;

	SwitchRow LeftPadCommVolumeThumbwheelSwitchRow;
	ThumbwheelSwitch LeftPadCommVolumeThumbwheelSwitch;

	SwitchRow LeftIntercomVolumeThumbwheelSwitchRow;
	ThumbwheelSwitch LeftIntercomVolumeThumbwheelSwitch;

	SwitchRow LeftSBandVolumeThumbwheelSwitchRow;
	ThumbwheelSwitch LeftSBandVolumeThumbwheelSwitch;

	SwitchRow LeftVHFAMVolumeThumbwheelSwitchRow;
	ThumbwheelSwitch LeftVHFAMVolumeThumbwheelSwitch;

	//////////////////////
	// Panel 9 switches //
	//////////////////////

	SwitchRow LeftModeIntercomSwitchRow;
	ThreePosSwitch LeftModeIntercomSwitch;

	SwitchRow LeftAudioPowerSwitchRow;
	ThreePosSwitch LeftAudioPowerSwitch;

	SwitchRow LeftPadCommSwitchRow;
	ThreePosSwitch LeftPadCommSwitch;

	SwitchRow LeftIntercomSwitchRow;
	ThreePosSwitch LeftIntercomSwitch;

	SwitchRow LeftSBandSwitchRow;
	ThreePosSwitch LeftSBandSwitch;

	SwitchRow LeftVHFAMSwitchRow;
	ThreePosSwitch LeftVHFAMSwitch;

	SwitchRow LeftAudioControlSwitchRow;
	ThreePosSwitch LeftAudioControlSwitch;

	SwitchRow LeftSuitPowerSwitchRow;
	ToggleSwitch LeftSuitPowerSwitch;

	SwitchRow VHFRNGSwitchRow;
	ToggleSwitch VHFRNGSwitch;

	SwitchRow FloatBagSwitchRow;
	ToggleSwitch FloatBagSwitch1;
	ToggleSwitch FloatBagSwitch2;
	ToggleSwitch FloatBagSwitch3;

	SwitchRow SeqEventsContSystemSwitchesRow;
	TwoSourceSwitch Logic1Switch;
	TwoSourceSwitch Logic2Switch;
	TwoSourceSwitch PyroArmASwitch;
	TwoSourceSwitch PyroArmBSwitch;

	//////////////////////////////
	// Panel 8 circuit breakers //
	//////////////////////////////

	SwitchRow StabContSystemCircuitBrakerRow;
	CircuitBrakerSwitch StabContSystemTVCAc1CircuitBraker;
	CircuitBrakerSwitch StabContSystemAc1CircuitBraker;
	CircuitBrakerSwitch StabContSystemAc2CircuitBraker;

	SwitchRow StabilizationControlSystemCircuitBrakerRow;
	CircuitBrakerSwitch ECATVCAc2CircuitBraker;
	CircuitBrakerSwitch DirectUllMnACircuitBraker;
	CircuitBrakerSwitch DirectUllMnBCircuitBraker;
	CircuitBrakerSwitch ContrDirectMnA1CircuitBraker;
	CircuitBrakerSwitch ContrDirectMnB1CircuitBraker;
	CircuitBrakerSwitch ContrDirectMnA2CircuitBraker;
	CircuitBrakerSwitch ContrDirectMnB2CircuitBraker;
	CircuitBrakerSwitch ACRollMnACircuitBraker;
	CircuitBrakerSwitch ACRollMnBCircuitBraker;
	CircuitBrakerSwitch BDRollMnACircuitBraker;
	CircuitBrakerSwitch BDRollMnBCircuitBraker;
	CircuitBrakerSwitch PitchMnACircuitBraker;
	CircuitBrakerSwitch PitchMnBCircuitBraker;
	CircuitBrakerSwitch YawMnACircuitBraker;
	CircuitBrakerSwitch YawMnBCircuitBraker;

	SwitchRow StabilizationControlSystem2CircuitBrakerRow;
	CircuitBrakerSwitch OrdealAc2CircuitBraker;
	CircuitBrakerSwitch OrdealMnBCircuitBraker;
	CircuitBrakerSwitch ContrAutoMnACircuitBraker;
	CircuitBrakerSwitch ContrAutoMnBCircuitBraker;
	CircuitBrakerSwitch LogicBus12MnACircuitBraker;
	CircuitBrakerSwitch LogicBus34MnACircuitBraker;
	CircuitBrakerSwitch LogicBus14MnBCircuitBraker;
	CircuitBrakerSwitch LogicBus23MnBCircuitBraker;
	CircuitBrakerSwitch SystemMnACircuitBraker;
	CircuitBrakerSwitch SystemMnBCircuitBraker;

	SwitchRow ReactionControlSystemCircuitBrakerRow;
	CircuitBrakerSwitch CMHeater1MnACircuitBraker;
	CircuitBrakerSwitch CMHeater2MnBCircuitBraker;
	CircuitBrakerSwitch SMHeatersAMnBCircuitBraker;
	CircuitBrakerSwitch SMHeatersCMnBCircuitBraker;
	CircuitBrakerSwitch SMHeatersBMnACircuitBraker;
	CircuitBrakerSwitch SMHeatersDMnACircuitBraker;
	CircuitBrakerSwitch PrplntIsolMnACircuitBraker;
	CircuitBrakerSwitch PrplntIsolMnBCircuitBraker;
	CircuitBrakerSwitch RCSLogicMnACircuitBraker;
	CircuitBrakerSwitch RCSLogicMnBCircuitBraker;
	CircuitBrakerSwitch EMSMnACircuitBraker;
	CircuitBrakerSwitch EMSMnBCircuitBraker;
	CircuitBrakerSwitch DockProbeMnACircuitBraker;
	CircuitBrakerSwitch DockProbeMnBCircuitBraker;

	SwitchRow ServicePropulsionSysCircuitBrakerRow;
	CircuitBrakerSwitch GaugingMnACircuitBraker;
	CircuitBrakerSwitch GaugingMnBCircuitBraker;
	CircuitBrakerSwitch GaugingAc1CircuitBraker;
	CircuitBrakerSwitch GaugingAc2CircuitBraker;
	CircuitBrakerSwitch HeValveMnACircuitBraker;
	CircuitBrakerSwitch HeValveMnBCircuitBraker;
	CircuitBrakerSwitch PitchBatACircuitBraker;
	CircuitBrakerSwitch PitchBatBCircuitBraker;
	CircuitBrakerSwitch YawBatACircuitBraker;
	CircuitBrakerSwitch YawBatBCircuitBraker;
	CircuitBrakerSwitch PilotValveMnACircuitBraker;
	CircuitBrakerSwitch PilotValveMnBCircuitBraker;

	SwitchRow FloatBagCircuitBrakerRow;
	CircuitBrakerSwitch FloatBag1BatACircuitBraker;
	CircuitBrakerSwitch FloatBag2BatBCircuitBraker;
	CircuitBrakerSwitch FloatBag3FLTPLCircuitBraker;

	SwitchRow SeqEventsContSysCircuitBrakerRow;
	CircuitBrakerSwitch LogicBatACircuitBraker;
	CircuitBrakerSwitch LogicBatBCircuitBraker;
	CircuitBrakerSwitch ArmBatACircuitBraker;
	CircuitBrakerSwitch ArmBatBCircuitBraker;

	SwitchRow EDSCircuitBrakerRow;
	CircuitBrakerSwitch EDS1BatACircuitBraker;
	CircuitBrakerSwitch EDS2BatBCircuitBraker;
	CircuitBrakerSwitch EDS3BatCCircuitBraker;

	SwitchRow ELSCircuitBrakerRow;
	CircuitBrakerSwitch ELSBatACircuitBraker;
	CircuitBrakerSwitch ELSBatBCircuitBraker;

	SwitchRow PLVentCircuitBrakerRow;
	CircuitBrakerSwitch FLTPLCircuitBraker;

	//////////////////////
	// Panel 8 switches //
	//////////////////////
	
	SwitchRow AutoRCSSelectSwitchesRow;
	ThreeSourceSwitch AcRollA1Switch;
	ThreeSourceSwitch AcRollC1Switch;
	ThreeSourceSwitch AcRollA2Switch;
	ThreeSourceSwitch AcRollC2Switch;
	ThreeSourceSwitch BdRollB1Switch;
	ThreeSourceSwitch BdRollD1Switch;
	ThreeSourceSwitch BdRollB2Switch;
	ThreeSourceSwitch BdRollD2Switch;
	ThreeSourceSwitch PitchA3Switch;
	ThreeSourceSwitch PitchC3Switch;
	ThreeSourceSwitch PitchA4Switch;
	ThreeSourceSwitch PitchC4Switch;
	ThreeSourceSwitch YawB3Switch;
	ThreeSourceSwitch YawD3Switch;
	ThreeSourceSwitch YawB4Switch;
	ThreeSourceSwitch YawD4Switch;

	SwitchRow FloodDimSwitchRow;
	ToggleSwitch FloodDimSwitch;

	SwitchRow FloodFixedSwitchRow;
	ThreePosSwitch FloodFixedSwitch;

	//////////////////////
	// Panel 7 switches //
	//////////////////////

	SwitchRow EDSPowerSwitchRow;
	ToggleSwitch EDSPowerSwitch;

	SwitchRow TVCServorPowerSwitchesRow;
	ThreePosSwitch TVCServorPower1Switch;
	ThreePosSwitch TVCServorPower2Switch;

	SwitchRow LogicPowerSwitchRow;
	ToggleSwitch LogicPowerSwitch;

	SwitchRow SIGCondDriverBiasPowerSwitchesRow;
	ThreeSourceSwitch SIGCondDriverBiasPower1Switch;
	ThreeSourceSwitch SIGCondDriverBiasPower2Switch;

	//////////////////////
	// Panel 7 rotaries //
	//////////////////////

	SwitchRow LeftInteriorLightRotariesRow;
	RotationalSwitch NumericRotarySwitch;
	RotationalSwitch FloodRotarySwitch;
	RotationalSwitch IntegralRotarySwitch;

	SwitchRow FDAIPowerRotaryRow;
	FDAIPowerRotationalSwitch FDAIPowerRotarySwitch;

	SwitchRow SCSElectronicsPowerRotaryRow;
	RotationalSwitch SCSElectronicsPowerRotarySwitch;

	SwitchRow BMAGPowerRotary1Row;
	BMAGPowerRotationalSwitch BMAGPowerRotary1Switch;

	SwitchRow BMAGPowerRotary2Row;
	BMAGPowerRotationalSwitch BMAGPowerRotary2Switch;

	SwitchRow DirectO2RotaryRow;
	DirectO2RotationalSwitch DirectO2RotarySwitch;

	//////////////////////
	// Panel 325/326    //
	//////////////////////

	SwitchRow GlycolToRadiatorsLeverRow; 	
	CircuitBrakerSwitch GlycolToRadiatorsLever;

	SwitchRow GlycolReservoirRotariesRow;
	RotationalSwitch GlycolReservoirInletRotary;
	RotationalSwitch GlycolReservoirBypassRotary;
	RotationalSwitch GlycolReservoirOutletRotary;

	SwitchRow OxygenRotariesRow;
	RotationalSwitch OxygenSurgeTankRotary;
	RotationalSwitch OxygenSMSupplyRotary;
	RotationalSwitch OxygenRepressPackageRotary;

	//
	// OLD Switches: delete these as and when we can do so.
	//
	// old stuff begin
	//

	bool RPswitch17;

	bool CMCswitch;
	bool SCswitch;

	// old stuff end

	//
	// stage is the main stage of the flight. StageState is the current state within
	// that stage.
	//

	int stage;
	int StageState;

	//
	// Saturn type.
	//

	int SaturnType;

	#define SATSYSTEMS_NONE				  0
	#define SATSYSTEMS_PRELAUNCH		100
	#define SATSYSTEMS_CREWINGRESS_1	200
	#define SATSYSTEMS_CREWINGRESS_2	210
	#define SATSYSTEMS_CABINCLOSEOUT	300
	#define SATSYSTEMS_GSECONNECTED		400
	#define SATSYSTEMS_READYTOLAUNCH    500
	#define SATSYSTEMS_CABINVENTING		600
	#define SATSYSTEMS_FLIGHT			700

	int systemsState;
	bool firstSystemsTimeStepDone;
	double lastSystemsMissionTime;

	//
	// Stage masses: should really be saved, but probably aren't at the
	// moment.
	//

	double CM_Mass;
	double CM_EmptyMass;
	double CM_FuelMass;
	double SM_Mass;
	double SM_EmptyMass;
	double SM_FuelMass;
	double S4PL_Mass;
	double Abort_Mass;
	double Interstage_Mass;
	double S4B_Mass;
	double S4B_EmptyMass;
	double S4B_FuelMass;
	double SII_Mass;
	double SII_EmptyMass;
	double SII_FuelMass;
	double SI_Mass;
	double SI_EmptyMass;
	double SI_FuelMass;

	bool SI_MassLoaded;
	bool SII_MassLoaded;
	bool S4B_MassLoaded;

	bool S1_ThrustLoaded;
	bool S2_ThrustLoaded;
	bool S3_ThrustLoaded;

	//
	// Calculated total stage mass.
	//

	double Stage1Mass;
	double Stage2Mass;
	double Stage3Mass;

	//
	// Engine numbers.
	//

	int SI_EngineNum;
	int SII_EngineNum;
	int SIII_EngineNum;

	//
	// Indicator lights.
	//

	bool ENGIND[9];
	bool LAUNCHIND[8];
	bool LVGuidLight;
	bool LVRateLight;

	//
	// And state that doesn't need to be saved.
	//

	double aVAcc;
	double aVSpeed;
	double aHAcc;
	double aZAcc;

	double actualVEL;
	double actualALT;
	double actualFUEL;

	#define LASTVELOCITYCOUNT 50
	VECTOR3 LastVelocity[LASTVELOCITYCOUNT];
	double LastVerticalVelocity[LASTVELOCITYCOUNT];
	double LastSimt[LASTVELOCITYCOUNT];
	int LastVelocityFilled;

	double ThrustAdjust;
	double MixtureRatio;

	bool KEY1;
	bool KEY2;
	bool KEY3;
	bool KEY4;
	bool KEY5;
	bool KEY6;
	bool KEY7;
	bool KEY8;
	bool KEY9;

	//
	// State variables that must be initialised but not saved.
	//

	bool FirstTimestep;
	bool GenericFirstTimestep;

	int CurrentTimestep;
	int LongestTimestep;
	double LongestTimestepLength;
	VECTOR3 normal;

	PanelSwitches MainPanel;
	PanelSwitchScenarioHandler PSH;

	SwitchRow SequencerSwitchesRow;
	SwitchRow SeparationSwitchesRow;
	SwitchRow CryoTankSwitchesRow;
	SwitchRow FuelCellPhRadTempIndicatorsRow;
	SwitchRow FuelCellRadiatorsIndicatorsRow;
	SwitchRow FuelCellRadiatorsSwitchesRow;
	SwitchRow FuelCellIndicatorsSwitchRow;
	SwitchRow FuelCellHeatersSwitchesRow;
	SwitchRow FuelCellPurgeSwitchesRow;
	SwitchRow FuelCellReactantsIndicatorsRow;
	SwitchRow FuelCellReactantsSwitchesRow;
	SwitchRow FuelCellLatchSwitchesRow;
	SwitchRow FuelCellPumpsSwitchesRow;
	SwitchRow SuitCompressorSwitchesRow;
	SwitchRow MainBusAIndicatorsRow;

	SwitchRow SBandNormalSwitchesRow;

	//
	// Internal systems devices.
	//

	FCell *FuelCells[3];

	//
	// O2 tanks.
	//

	h_Tank *O2Tanks[2];

	//
	// Main bus A and B.
	//

	DCbus *MainBusA;
	DCbus *MainBusB;

	//
	// Non-essential buses... oddly, these are for non-essential systems.
	//

	DCbus NonEssBus1;
	DCbus NonEssBus2;


	ThreeWayPowerMerge DCBusASource;
	ThreeWayPowerMerge DCBusBSource;

	//
	// Inverters.
	//

	ACInverter *Inverter1;
	ACInverter *Inverter2;
	ACInverter *Inverter3;

	//
	// AC bus 1 and 2, which are three-phase.
	//

	ThreeWayPowerMerge ACBus1Source;
	ThreeWayPowerMerge ACBus2Source;

	ACbus ACBus1PhaseA;
	ACbus ACBus1PhaseB;
	ACbus ACBus1PhaseC;

	ACbus ACBus2PhaseA;
	ACbus ACBus2PhaseB;
	ACbus ACBus2PhaseC;

	ThreeWayPowerMerge ACBus1;
	ThreeWayPowerMerge ACBus2;

	Battery *EntryBatteryA;
	Battery *EntryBatteryB;
	Battery *EntryBatteryC;

	Battery *PyroBatteryA;
	Battery *PyroBatteryB;

	ThreeWayPowerMerge BatteryBusA;
	ThreeWayPowerMerge BatteryBusB;

	PowerMerge BatteryRelayBus;

	PowerMerge PyroBusA;
	PowerMerge PyroBusB;

	PowerMerge SECSLogicPower;
	PowerMerge PyroPower;

	PowerMerge SwitchPower;

	h_HeatExchanger *PrimCabinHeatExchanger;
	h_HeatExchanger *SecCabinHeatExchanger;
	h_HeatExchanger *PrimEcsRadiatorExchanger1;
	h_HeatExchanger *PrimEcsRadiatorExchanger2;
	Boiler *CabinHeater;
	AtmRegen *SuitCompressor1;
	AtmRegen *SuitCompressor2;

	double LastACVoltDisplay;
	double LastDCVoltDisplay;
	double LastDCAmpDisplay;
	double LastThrustDisplay;

	//
	// LM PAD
	//

	int LMPadCount;
	unsigned int *LMPad;

	//
	// Do we have a crew, or is this an unmanned flight?
	//

	bool Crewed;

	//
	// Unmanned flight parameters.
	//

	bool AutoSlow;

	int SIVBPayload;

	//
	// CSM seperation info for unmanned flights.
	//

	bool CSMSepSet;
	double CSMSepTime;
	bool CMSepSet;
	double CMSepTime;

	//
	// SIVB burn info for unmanned flights.
	//

	double SIVBBurnStart;
	double SIVBApogee;

	//
	// CSM burn information in unmanned flights.
	//

	bool CSMBurn;
	double CSMBurnStart;
	double CSMApogee;
	double CSMPerigee;

	//
	// Pre-entry CSM acceleration and end time for unmanned flights.
	//

	bool CSMAccelSet;
	double CSMAccelTime;
	double CSMAccelEnd;
	double CSMAccelPitch;

	bool TLICapableBooster;
	bool SkylabSM;
	bool NoHGA;
	bool SkylabCM;
	bool S1bPanel;
	bool bAbort;
	bool bAbtlocked;
	bool bRecovery;

	bool ActivateLEM;
	bool ActivateS4B;
	bool ToggleEva;

	#define SATVIEW_CDR		0
	#define SATVIEW_DMP		1
	#define SATVIEW_CMP		2
	#define SATVIEW_DOCK	3
	#define SATVIEW_ENG1	4
	#define SATVIEW_ENG2	5
	#define SATVIEW_ENG3	6

	unsigned int	viewpos;

	UINT probeidx;
	
	bool ActivateASTP;
	//bool ProbeExtended;
	bool FIRSTCSM;
	bool bManualSeparate;
	bool bManualUnDock;
	bool ASTPMission;
	bool ReadyAstp;
	bool bToggleHatch;
	bool SMSep;
	bool bStartS4B;
	bool Abort_Locked;

	double DockAngle;

	double AtempP;
	double AtempY;
	double AtempR;

	double release_time;
	double abortTimer;

	ELEMENTS elemSaturn1B;
	double refSaturn1B;
	ELEMENTS elemPREV;
	double refPREV;
	double AltitudePREV;

	double 	Offset1st;

	bool StopRot;
	bool ProbeJetison;
	bool RCS_Full;
	bool LEMdatatransfer;

#define SATPANEL_MAIN				0
#define SATPANEL_LOWER				1
#define SATPANEL_LEFT				2
#define SATPANEL_RIGHT				3
#define SATPANEL_LEFT_RNDZ_WINDOW	4
#define SATPANEL_RIGHT_RNDZ_WINDOW	5
#define SATPANEL_HATCH_WINDOW		6
#define SATPANEL_CABIN_PRESS_PANEL	7

	int  PanelId;
	bool InVC;
	bool InPanel;
	bool CheckPanelIdInTimestep;

	bool KranzPlayed;
	bool PostSplashdownPlayed;

	OBJHANDLE hEVA;

	SoundLib soundlib;

	//
	// Surfaces.
	//

	SURFHANDLE srf[nsurf + 1];  // handles for panel bitmaps. +1 for safety :).
	SURFHANDLE SMExhaustTex;
	SURFHANDLE SMMETex;
	SURFHANDLE CMTex;
	//TODO SURFHANDLEs for VC

	//
	// Hardware support.
	//

	//
	// CSM has two DSKYs: one is in the main panel, the other is below. For true realism we should support
	// both.
	//

	DSKY dsky;
	DSKY dsky2;
	CSMcomputer agc;
	IMU imu;
	IU iu;
	CSMCautionWarningSystem cws;
	DockingProbe dockingprobe;
	SECS secs;

	Pyro CMSMPyros;

	//
	// Vessel handles.
	//

	OBJHANDLE hLMV;
	OBJHANDLE hstg1;
	OBJHANDLE hstg2;
	OBJHANDLE hintstg;
	OBJHANDLE hesc1;
	OBJHANDLE hPROBE;
	OBJHANDLE hs4bM;
	OBJHANDLE hs4b1;
	OBJHANDLE hs4b2;
	OBJHANDLE hs4b3;
	OBJHANDLE hs4b4;
	OBJHANDLE habort;
	OBJHANDLE hMaster;
	OBJHANDLE hSMJet;
	OBJHANDLE hVAB;
	OBJHANDLE hCrawler;
	OBJHANDLE hML;

	//
	// ISP and thrust values, which vary depending on vehicle number.
	//

	double ISP_FIRST_SL;
	double ISP_FIRST_VAC;
	double ISP_SECOND_SL;//300*G;
	double ISP_SECOND_VAC;//421*G;
	double ISP_THIRD_VAC;//421*G;

	double THRUST_FIRST_VAC;
	double THRUST_SECOND_VAC;//115200*G;
	double THRUST_THIRD_VAC;

	//
	// Generic functions shared between SaturnV and Saturn1B
	//

	void ToggelHatch();
	void ToggelHatch2();
	void AddRCSJets(double TRANZ,double MaxThrust);
	void AddRCS_S4B();
	void ToggleEVA();
	void SetupEVA();
	void SetRecovery();
	void InitPanel(int panel);
	void SetSwitches(int panel);
	void ReleaseSurfaces();
	void KillDist(OBJHANDLE &hvessel, double kill_dist = 5000.0);
	void KillAlt(OBJHANDLE &hvessel,double altVS);
	void RedrawPanel_Thrust (SURFHANDLE surf);
	void RedrawPanel_Alt (SURFHANDLE surf);
	void RedrawPanel_Horizon (SURFHANDLE surf);
	void RedrawPanel_MFDButton (SURFHANDLE surf, int mfd, int side, int xoffset, int yoffset, int ydist);
	void RedrawPanel_ElectricMeter (SURFHANDLE surf, double fraction, int srf_id, double &last_val);
	void CryoTankHeaterSwitchToggled(ToggleSwitch *s, int *pump);
	void FuelCellHeaterSwitchToggled(ToggleSwitch *s, int *pump);
	void FuelCellPurgeSwitchToggled(ToggleSwitch *s, int *start);
	void FuelCellReactantsSwitchToggled(ToggleSwitch *s, int *start);
	void CabinTempAutoSwitchToggled();
	void MousePanel_MFDButton(int mfd, int event, int mx, int my);
	double SetPitchApo();
	void SetStage(int s);
	void initSaturn();
	void SwitchClick();
	void ProbeSound();
	void CabinFanSound();
	void StopCabinFanSound();
	void CabinFansSystemTimestep();
	void ButtonClick();
	void GuardClick();
	void FuelCell();
	void SetView();
	void SetView(double offset);
	void SetView(bool update_direction);
	void SetView(double offset, bool update_direction);
	void MasterAlarm();
	void StopMasterAlarm();
	void GenericTimestep(double simt, double simdt);
	void SystemsInit();
	void SystemsTimestep(double simt, double simdt);
	void SystemsInternalTimestep(double simdt);
	void JoystickTimestep();
	void SetSIVBThrusters(bool active);
	void LimitSetThrusterDir (THRUSTER_HANDLE th, const VECTOR3 &dir);
	void AttitudeLaunchSIVB();
	virtual void AutoPilot(double autoT) = 0;
	virtual void SeparateStage (int stage) = 0;
	void StageOrbitSIVB(double simt, double simdt);
	void JostleViewpoint(double amount);
	double CalculateApogeeTime();
	void UpdatePayloadMass();
	double GetCPitch(double t);
	double GetJ2ISP(double ratio);
	void StartAbort();
	void GetLEMName(char *s);
	void GetApolloName(char *s);
	void AddSM(double offet, bool showSPS);

	//
	// Systems functions.
	//

	bool AutopilotActive();
	bool CabinFansActive();
	bool CabinFan1Active();
	bool CabinFan2Active();
	void ActivateCSMRCS();
	void DeactivateCSMRCS();
	void ActivateCMRCS();
	void DeactivateCMRCS();
	// bool CMRCSActive();
	bool SMRCSActive();
	bool SMRCSAActive();
	bool SMRCSBActive();
	bool SMRCSCActive();
	bool SMRCSDActive();
	void ActivateSPS();
	void DeactivateSPS();
	void FuelCellCoolingBypass(int fuelcell, bool bypassed);
	bool FuelCellCoolingBypassed(int fuelcell);
	void SetRandomFailures();
	virtual void ActivatePrelaunchVenting() = 0;
	virtual void DeactivatePrelaunchVenting() = 0;

	//
	// Save/Load support functions.
	//

	int GetCSwitchState();
	void SetCSwitchState(int s);
	int GetSSwitchState();
	void SetSSwitchState(int s);
	int GetLPSwitchState();
	void SetLPSwitchState(int s);
	int GetRPSwitchState();
	void SetRPSwitchState(int s);
	int GetCP6SwitchState();
	void SetCP6SwitchState(int s);
	int GetMainState();
	void SetMainState(int s);
	int GetAttachState();
	void SetAttachState(int s);
	int GetLaunchState();
	void SetLaunchState(int s);
	int GetA13State();
	void SetA13State(int s);
	int GetLightState();
	void SetLightState(int s);
	void GenericLoadStateSetup();

	virtual void SetVehicleStats() = 0;
	virtual void CalculateStageMass () = 0;
	virtual void SaveVehicleStats(FILEHANDLE scn) = 0;

	void GetScenarioState (FILEHANDLE scn, void *status);
	bool ProcessConfigFileLine (FILEHANDLE scn, char *line);

	void ClearPanelSDKPointers();

	//
	// Mission stage functions.
	//

	void DoLaunch(double simt);

	void LaunchCountdown(double simt);
	void StageSeven(double simt);
	void StageEight(double simt);
	void SetChuteStage1();
	void SetChuteStage2();
	void SetChuteStage3();
	void SetChuteStage4();
	void SetSplashStage();
	void SetAbortStage ();
	void SetCSMStage ();
	void SetCSM2Stage ();
	void SetReentryStage ();
	void AddRCS_CM(double MaxThrust);
	void SetRCS_CM();
	void GenericTimestepStage(double simt, double simdt);
	bool CheckForLaunchShutdown();
	void SetGenericStageState();
	void DestroyStages(double simt);

	void FireSeperationThrusters(THRUSTER_HANDLE *pth);

	void LoadDefaultSounds();

	//
	// Sounds
	//

	Sound Sclick;
	Sound Bclick;
	Sound Gclick;
	Sound SMasterAlarm;
	Sound LaunchS;
	Sound Scount;
	Sound SplashS;
	Sound Swater;
	Sound PostSplashdownS;
	Sound TowerJS;
	Sound StageS;
	Sound Sctdw;
	Sound SeparationS;
	Sound SMJetS;
	Sound S4CutS;
	Sound SShutS;
	Sound S2ShutS;
	Sound SepS;
	Sound CrashBumpS;
	Sound Psound;
	Sound CabinFans;
	Sound SwindowS;
	Sound SKranz;
	Sound SExploded;
	Sound SApollo13;
	Sound SSMSepExploded;
	Sound SPUShiftS;
	Sound SDockingCapture;
	Sound SDockingLatch;
	Sound SDockingExtend;
	Sound SUndock;

	//
	// General engine resources.
	//

	PROPELLANT_HANDLE ph_1st, ph_2nd, ph_3rd, ph_rcs0, ph_rcs1, ph_rcs2, ph_rcs3, ph_rcs_cm_1,ph_rcs_cm_2, ph_sps, ph_sep, ph_sep2; // handles for propellant resources
	PROPELLANT_HANDLE ph_o2_vent;

	THGROUP_HANDLE thg_main,thg_ull,thg_ver;		          // handles for thruster groups
	THGROUP_HANDLE thg_retro1, thg_retro2, thg_aps;

	THRUSTER_HANDLE th_main[5], th_ull[8], th_ver[3], th_att_cm[12];               // handles for orbiter main engines
	THRUSTER_HANDLE th_sps[1], th_att_rot[24], th_att_lin[24];                 // handles for SPS engines
	THRUSTER_HANDLE	th_aps[3];
	THRUSTER_HANDLE	th_sep[8], th_sep2[8];
	THRUSTER_HANDLE th_rcs_a[8], th_rcs_b[8], th_rcs_c[8], th_rcs_d[8];		// RCS quads. Entry zero is not used, to match Apollo numbering
	THRUSTER_HANDLE th_o2_vent;

	PSTREAM_HANDLE prelaunchvent[3];
	PSTREAM_HANDLE stagingvent[8];
	PSTREAM_HANDLE contrail[5];
	double contrailLevel;

	CMRCSPropellant CMRCS1;
	CMRCSPropellant CMRCS2;
	SMRCSPropellant SMQuadARCS;
	SMRCSPropellant SMQuadBRCS;
	SMRCSPropellant SMQuadCRCS;
	SMRCSPropellant SMQuadDRCS;

	//
	// LEM data.
	//

	double LMLandingLatitude;
	double LMLandingLongitude;
	double LMLandingAltitude;

	//
	// Earth landing data.
	//

	double EarthLandingLatitude;
	double EarthLandingLongitude;

	//
	// Random motion.
	//

	double ViewOffsetx;
	double ViewOffsety;
	double ViewOffsetz;

	//
	// Save the last view offset.
	//

	double CurrentViewOffset;

	//
	// Time of last timestep call.
	//

	double LastTimestep;

	//
	// Panel flash.
	//

	double NextFlashUpdate;
	bool PanelFlashOn;

	//
	// Audio language.
	//

	char AudioLanguage[64];

	//
	// LEM name
	//

	char LEMName[64];

	//
	// GPFPI Values
	//
	bool initialized;
	int PitchClusterCurrent;
	int YawClusterCurrent;
	int PitchClusterActual;
	int YawClusterActual;
	int dPC;
	int dYC;


//	FILE *outstr;


	//
	// PanelSDK pointers.
	//

	double *pCO2Level;
	double *pCabinCO2Level;
	double *pCabinPressure;
	double *pCabinTemp;
	double *pSuitTemp;
	double *pSuitPressure;
	double *pSuitReturnPressure;
	double *pCabinRegulatorFlow;
	double *pO2DemandFlow;
	double *pDirectO2Flow;
	double *pO2Tank1Press;
	double *pO2Tank2Press;
	double *pH2Tank1Press;
	double *pH2Tank2Press;
	double *pO2SurgeTankPress;
	double *pO2Tank1Quantity;
	double *pO2Tank2Quantity;
	double *pH2Tank1Quantity;
	double *pH2Tank2Quantity;
	double *pFCH2Flow[4];
	double *pFCO2Flow[4];
	double *pFCTemp[4];
	double *pFCCondenserTemp[4];
	double *pFCCoolingTemp[4];
	double *pPrimECSRadiatorInletPressure;
	double *pPrimECSRadiatorInletTemp;
	double *pPrimECSRadiatorOutletTemp;
	double *pPrimECSEvaporatorOutletTemp;
	double *pPrimECSEvaporatorSteamPressure;
	double *pPrimECSAccumulatorQuantity;
	double *pSecECSRadiatorInletPressure;
	double *pSecECSRadiatorInletTemp;
	double *pSecECSRadiatorOutletTemp;
	double *pSecECSEvaporatorOutletTemp;
	double *pSecECSEvaporatorSteamPressure;
	double *pSecECSAccumulatorQuantity;
	double *pPotableH2oTankQuantity;
	double *pWasteH2oTankQuantity;

	int *pCSMValves[N_CSM_VALVES];
	bool ValveState[N_CSM_VALVES];

	// InitSaturn is called twice, but some things must run only once
	bool InitSaturnCalled;

	int LMPadLoadCount;
	int LMPadValueCount;
	
	// DS20060305 Friend Class List Added for SCS objects
	friend class GDC;
	friend class BMAG;
	friend class ASCP;
	friend class EDA;
	friend class RJEC;
	friend class ECA;
	friend class CSMcomputer; // I want this to be able to see the GDC	
	friend class PCM;         // Otherwise reading telemetry is a pain
};

extern void BaseInit();
extern void SaturnInitMeshes();
extern void StageTransform(VESSEL *vessel, VESSELSTATUS *vs, VECTOR3 ofs, VECTOR3 vel);

const double STG2O = 8;
const double SMVO = 0.0;//-0.14;
const double CREWO = 0.0;
const VECTOR3 OFS_MAINCHUTE =  { 0, -2, 9};

extern MESHHANDLE hSM;
extern MESHHANDLE hCM;
extern MESHHANDLE hCMInt;
extern MESHHANDLE hCMVC;
extern MESHHANDLE hFHC;
extern MESHHANDLE hCMP;
extern MESHHANDLE hCREW;
extern MESHHANDLE hSMhga;
extern MESHHANDLE hprobe;
extern MESHHANDLE hprobeext;
extern MESHHANDLE hsat5tower;
extern MESHHANDLE hFHO2;

extern void SetupgParam(HINSTANCE hModule);
extern void DeletegParam();

#endif