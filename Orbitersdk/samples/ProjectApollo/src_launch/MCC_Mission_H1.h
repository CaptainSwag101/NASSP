/****************************************************************************
This file is part of Project Apollo - NASSP
Copyright 2022

MCC for Mission H1 (Header)

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

// MISSION STATES: MISSION H1

//Ground liftoff time update to TLI Simulation
#define MST_H1_INSERTION		10
//TLI Simulation to TLI+90 PAD
#define MST_H1_EPO1			11
//TLI+90 Maneuver PAD to TLI+5h P37 PAD
#define MST_H1_EPO2			12
#define MST_H1_EPO3			13
#define MST_H1_EPO4			14
#define MST_H1_TRANSLUNAR_DAY1_1	20
#define MST_H1_TRANSLUNAR_DAY1_2	21
#define MST_H1_TRANSLUNAR_DAY1_3	22
#define MST_H1_TRANSLUNAR_DAY1_4	23
#define MST_H1_TRANSLUNAR_DAY1_5	24
#define MST_H1_TRANSLUNAR_DAY1_6	25
#define MST_H1_TRANSLUNAR_DAY1_7	26
#define MST_H1_TRANSLUNAR_DAY1_8	27
#define MST_H1_TRANSLUNAR_DAY1_9	28
#define MST_H1_TRANSLUNAR_DAY1_10	29
#define MST_H1_TRANSLUNAR_DAY1_11	30
#define MST_H1_TRANSLUNAR_DAY1_12	31
#define MST_H1_TRANSLUNAR_DAY2_1	40
#define MST_H1_TRANSLUNAR_DAY2_2	41
#define MST_H1_TRANSLUNAR_DAY2_3	42
#define MST_H1_TRANSLUNAR_DAY2_4	43
#define MST_H1_TRANSLUNAR_DAY3_1	50
#define MST_H1_TRANSLUNAR_DAY3_2	51
#define MST_H1_TRANSLUNAR_NO_MCC4_1 60
#define MST_H1_TRANSLUNAR_NO_MCC4_2 61
#define MST_H1_TRANSLUNAR_NO_MCC4_3 62
#define MST_H1_TRANSLUNAR_DAY4_1	70
#define MST_H1_TRANSLUNAR_DAY4_2	71
#define MST_H1_TRANSLUNAR_DAY4_3	72
#define MST_H1_TRANSLUNAR_DAY4_4	73
#define MST_H1_TRANSLUNAR_DAY4_5	74
#define MST_H1_TRANSLUNAR_DAY4_6	75
#define MST_H1_TRANSLUNAR_DAY4_7	76
#define MST_H1_TRANSLUNAR_DAY4_8	77
#define MST_H1_TRANSLUNAR_DAY4_9	78

#define MST_H1_LUNAR_ORBIT_LOI_DAY_1 100
#define MST_H1_LUNAR_ORBIT_LOI_DAY_2 101
#define MST_H1_LUNAR_ORBIT_LOI_DAY_3 102
#define MST_H1_LUNAR_ORBIT_LOI_DAY_4 103
#define MST_H1_LUNAR_ORBIT_LOI_DAY_5 104
#define MST_H1_LUNAR_ORBIT_LOI_DAY_6 105
#define MST_H1_LUNAR_ORBIT_LOI_DAY_7 106
#define MST_H1_LUNAR_ORBIT_LOI_DAY_8 107
#define MST_H1_LUNAR_ORBIT_LOI_DAY_9 108
#define MST_H1_LUNAR_ORBIT_LOI_DAY_10 109

#define MST_H1_LUNAR_ORBIT_PDI_DAY_1 110
#define MST_H1_LUNAR_ORBIT_PDI_DAY_2 111
#define MST_H1_LUNAR_ORBIT_PDI_DAY_3 112
#define MST_H1_LUNAR_ORBIT_PDI_DAY_4 113
#define MST_H1_LUNAR_ORBIT_PDI_DAY_5 114
#define MST_H1_LUNAR_ORBIT_PDI_DAY_6 115
#define MST_H1_LUNAR_ORBIT_PDI_DAY_7 116
#define MST_H1_LUNAR_ORBIT_PDI_DAY_8 117
#define MST_H1_LUNAR_ORBIT_PDI_DAY_9 118
#define MST_H1_LUNAR_ORBIT_PDI_DAY_10 119
#define MST_H1_LUNAR_ORBIT_PDI_DAY_11 120
#define MST_H1_LUNAR_ORBIT_PDI_DAY_12 121
#define MST_H1_LUNAR_ORBIT_PDI_DAY_13 122
#define MST_H1_LUNAR_ORBIT_PDI_DAY_14 123
#define MST_H1_LUNAR_ORBIT_PDI_DAY_15 124
#define MST_H1_LUNAR_ORBIT_PDI_DAY_16 125
#define MST_H1_LUNAR_ORBIT_PDI_DAY_17 126

#define MST_H1_LUNAR_ORBIT_PRE_DOI_1 130
#define MST_H1_LUNAR_ORBIT_PRE_DOI_2 131
#define MST_H1_LUNAR_ORBIT_PRE_DOI_3 132
#define MST_H1_LUNAR_ORBIT_PRE_DOI_4 133
#define MST_H1_LUNAR_ORBIT_PRE_PDI_1 134
#define MST_H1_LUNAR_ORBIT_PRE_PDI_2 135
#define MST_H1_LUNAR_ORBIT_PRE_PDI_3 136

#define MST_H1_LUNAR_ORBIT_PRE_LANDING_1 137
#define MST_H1_LUNAR_ORBIT_NO_PDI        138

#define MST_H1_LUNAR_ORBIT_POST_LANDING_1 140
#define MST_H1_LUNAR_ORBIT_POST_LANDING_2 141
#define MST_H1_LUNAR_ORBIT_POST_LANDING_3 142
#define MST_H1_LUNAR_ORBIT_POST_LANDING_4 143
#define MST_H1_LUNAR_ORBIT_POST_LANDING_5 144
#define MST_H1_LUNAR_ORBIT_POST_LANDING_6 145
#define MST_H1_LUNAR_ORBIT_POST_LANDING_7 146
#define MST_H1_LUNAR_ORBIT_POST_LANDING_8 147
#define MST_H1_LUNAR_ORBIT_POST_LANDING_9 148
#define MST_H1_LUNAR_ORBIT_POST_LANDING_10 149
#define MST_H1_LUNAR_ORBIT_POST_LANDING_11 150
#define MST_H1_LUNAR_ORBIT_POST_LANDING_12 151
#define MST_H1_LUNAR_ORBIT_POST_LANDING_13 152

#define MST_H1_LUNAR_ORBIT_PLANE_CHANGE_1 153
#define MST_H1_LUNAR_ORBIT_PLANE_CHANGE_2 154
#define MST_H1_LUNAR_ORBIT_NO_PLANE_CHANGE_1 155

#define MST_H1_LUNAR_ORBIT_EVA_DAY_1 160
#define MST_H1_LUNAR_ORBIT_EVA_DAY_2 161
#define MST_H1_LUNAR_ORBIT_EVA_DAY_3 162
#define MST_H1_LUNAR_ORBIT_EVA_DAY_4 163
#define MST_H1_LUNAR_ORBIT_EVA_DAY_5 164
#define MST_H1_LUNAR_ORBIT_EVA_DAY_6 165
#define MST_H1_LUNAR_ORBIT_EVA_DAY_7 166
#define MST_H1_LUNAR_ORBIT_EVA_DAY_8 167
#define MST_H1_LUNAR_ORBIT_EVA_DAY_9 168
#define MST_H1_LUNAR_ORBIT_EVA_DAY_10 169
#define MST_H1_LUNAR_ORBIT_EVA_DAY_11 170
#define MST_H1_LUNAR_ORBIT_EVA_DAY_12 171
#define MST_H1_LUNAR_ORBIT_EVA_DAY_13 172
#define MST_H1_LUNAR_ORBIT_EVA_DAY_14 173
#define MST_H1_LUNAR_ORBIT_EVA_DAY_15 174
#define MST_H1_LUNAR_ORBIT_EVA_DAY_16 175
#define MST_H1_LUNAR_ORBIT_EVA_DAY_17 176
#define MST_H1_LUNAR_ORBIT_EVA_DAY_18 177

#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_1 180
#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_2 181
#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_3 182
#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_4 183
#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_5 184
#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_6 185
#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_7 186
#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_8 187
#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_9 188
#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_10 189
#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_11 190
#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_12 191
#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_13 192
#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_14 193
#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_15 194
#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_16 195
#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_17 196
#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_18 197
#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_19 198
#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_20 199
#define MST_H1_LUNAR_ORBIT_ASCENT_DAY_21 200

#define MST_H1_LUNAR_ORBIT_PC2_DAY_1 210
#define MST_H1_LUNAR_ORBIT_PC2_DAY_2 211
#define MST_H1_LUNAR_ORBIT_PC2_DAY_3 212
#define MST_H1_LUNAR_ORBIT_PC2_DAY_4 213
#define MST_H1_LUNAR_ORBIT_PC2_DAY_5 214
#define MST_H1_LUNAR_ORBIT_PC2_DAY_6 215
#define MST_H1_LUNAR_ORBIT_PC2_DAY_7 216
#define MST_H1_LUNAR_ORBIT_PC2_DAY_8 217
#define MST_H1_LUNAR_ORBIT_PC2_DAY_9 218
#define MST_H1_LUNAR_ORBIT_PC2_DAY_10 219
#define MST_H1_LUNAR_ORBIT_PC2_DAY_11 220
#define MST_H1_LUNAR_ORBIT_PC2_DAY_12 221
#define MST_H1_LUNAR_ORBIT_PC2_DAY_13 222
#define MST_H1_LUNAR_ORBIT_PC2_DAY_14 223
#define MST_H1_LUNAR_ORBIT_PC2_DAY_15 224
#define MST_H1_LUNAR_ORBIT_PC2_DAY_16 225
#define MST_H1_LUNAR_ORBIT_PC2_DAY_17 226
#define MST_H1_LUNAR_ORBIT_PC2_DAY_18 227
#define MST_H1_LUNAR_ORBIT_PC2_DAY_19 228
#define MST_H1_LUNAR_ORBIT_PC2_DAY_20 229
#define MST_H1_LUNAR_ORBIT_PC2_DAY_21 230
#define MST_H1_LUNAR_ORBIT_PC2_DAY_22 231
#define MST_H1_LUNAR_ORBIT_PC2_DAY_23 232
#define MST_H1_LUNAR_ORBIT_PC2_DAY_24 233
#define MST_H1_LUNAR_ORBIT_PC2_DAY_25 234
#define MST_H1_LUNAR_ORBIT_PC2_DAY_26 235
#define MST_H1_LUNAR_ORBIT_PC2_DAY_27 236
#define MST_H1_LUNAR_ORBIT_PC2_DAY_28 237

#define MST_H1_TRANSEARTH_DAY1_1 300
#define MST_H1_TRANSEARTH_DAY1_2 301
#define MST_H1_TRANSEARTH_DAY1_3 302
#define MST_H1_TRANSEARTH_DAY2_1 310
#define MST_H1_TRANSEARTH_DAY2_2 311
#define MST_H1_TRANSEARTH_DAY2_3 312
#define MST_H1_TRANSEARTH_DAY3_1 320
#define MST_H1_TRANSEARTH_DAY3_2 321
#define MST_H1_TRANSEARTH_DAY3_3 322
#define MST_H1_TRANSEARTH_DAY3_4 323
#define MST_H1_TRANSEARTH_DAY3_5 324
#define MST_H1_TRANSEARTH_DAY3_6 325
#define MST_H1_TRANSEARTH_DAY4_1 330
#define MST_H1_TRANSEARTH_DAY4_2 331
#define MST_H1_TRANSEARTH_DAY4_3 332
#define MST_H1_TRANSEARTH_DAY4_4 333
#define MST_H1_TRANSEARTH_DAY4_5 334

//ABORTS
// Ends at entry interface, goes to entry.
#define MST_H1_ABORT_ORBIT	500
// Abort from earth orbit, goes to MST_ORBIT_ENTRY
#define MST_H1_ABORT		501
// post-TLI abort, ends at abort burn (if any)
// goes to MST_CP_TRANSEARTH with an abort flag.