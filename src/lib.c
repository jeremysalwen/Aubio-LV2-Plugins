/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * lib.c
 * Copyright (C) Jeremy  Salwen 2010 <jas2312@columbia.edu>
	 * 
 * aubiolv2 is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
	 * 
 * aubiolv2 is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include "tss-plugin.h"
#include "onset-plugin.h"
#include "pitch-plugin.h"

#include <lv2.h>


LV2_SYMBOL_EXPORT
const LV2_Descriptor *lv2_descriptor(uint32_t index)
{

	switch (index) {
		case 0:
			return get_tss_descriptor ();
		case 1:
			return get_onset_descriptor();
		case 2:
			return get_pitch_descriptor();
		default:
			return NULL;
	}
}
