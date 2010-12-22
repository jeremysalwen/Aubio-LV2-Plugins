/*
 * onset-plugin.h
 *
 * Copyright (C) 2010 - Jeremy  Salwen
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ONSET_PLUGIN_H
#define ONSET_PLUGIN_H

#include <lv2.h>
#include <aubio.h>
#include <stdlib.h>
#include <string.h>

#define ONSET_URI "urn:aubio:plugins:onset"
#define AT_INPUT 0
#define AT_OUTPUT 1
#define AT_DETECTION_TYPE 2
#define AT_PTHRESH 3
#define AT_STHRESH 4
#define AT_INTERVAL 5
#define AT_LATENCY 6

#define BUFFSIZE 1024
#define HOP_SIZE 256

typedef struct _onset_t {
	float* in_p;
	float* out_p;
	float* pthresh_p;
	float* sthresh_p;
	float* interval_p;
	float* latency_p;
	float* detectiontype_p;
	
	unsigned int current_onset_type;
	aubio_onset_t* onset;
	
	fvec_t* inbuff;
	fvec_t* outbuff;
	unsigned int index;
} onset_t;
LV2_Descriptor* get_onset_descriptor ();

#endif /* ONSET_PLUGIN_H */
