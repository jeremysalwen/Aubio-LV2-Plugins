/*
 * tss-plugin.h
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

#ifndef TSS_PLUGIN_H
#define TSS_PLUGIN_H

#include "lv2.h"
#include <stdlib.h>
#include <stdio.h>
#include <aubio.h>
#include <string.h>

#define TSS_THRESH 0
#define TSS_IN 1
#define TSS_TRANS 2
#define TSS_STEADY 3
#define TSS_LATENCY 4
#define TSS_URI "urn:aubio:plugins:tss"

#define BUFFSIZE 1024
#define HOP_SIZE 256
typedef struct {
	float* in_p;
	float* steady_p;
	float* trans_p;
	float* thresh_p;
	float* latency_p;
	//input values
	fvec_t* inbuff;
	fvec_t* steadybuff;
	fvec_t* transbuff;
	
	aubio_tss_t* tss;

	//phase vocoders
	aubio_pvoc_t * pv;
    aubio_pvoc_t * pvt;
    aubio_pvoc_t * pvs;

	//complex values
	cvec_t* ci;
	cvec_t* cs;
	cvec_t* ct;

	unsigned int index;
} tss_t;

LV2_Descriptor* get_tss_descriptor();

#endif /* TSS_PLUGIN_H */

