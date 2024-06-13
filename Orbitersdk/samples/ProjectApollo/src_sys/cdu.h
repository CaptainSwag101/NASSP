/***************************************************************************
This file is part of Project Apollo - NASSP
Copyright 2017

Coupling Data Unit (Header)

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

#include "apolloguidance.h"
#include "powersource.h"

#define CDU_STEP 9.587379924285257e-05

class CDU
{
public:
	CDU(ApolloGuidance &comp, int l, int err, int cdutype);
	void Timestep(double simdt);
	void ChannelOutput(int address, ChannelValue val);
	void SetReadCounter(double angle);
	int GetErrorCounter();
	int GetAltOutput();

	void SaveState(FILEHANDLE scn, char *start_str, char *end_str);
	void LoadState(FILEHANDLE scn, char *end_str);
protected:
	void DoZeroCDU();

	uint16_t ReadCounter;
	int ErrorCounter;
	double NewReadCounter;

	int AltOutput;

	bool ZeroCDU;
	bool ErrorCounterEnabled;

	//0 = ICDU, 1 = RR CDU, 2 = OCDU
	int CDUType;
	//Address of AGC CDU counter
	int loc;
	//Channel for error counter commands
	int err_channel;

	//Output channel bit for CDU Zeroing
	int CDUZeroBit;
	//Output channel bit for error counter enabled
	int ErrorCounterBit;

	int AltOutBit;

	//Mode switches
	bool CA;

	ApolloGuidance &agc;
};