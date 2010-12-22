/*
 * onset-plugin.c
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

#include "onset-plugin.h"


static void connectPortOnset(LV2_Handle instance, uint32_t port, void *data) {
	onset_t* plugin = (onset_t *)instance;

	switch (port) {
		case AT_INPUT:
			plugin->in_p = data;
			break;
		case AT_OUTPUT:
			plugin->out_p = data;
			break;
		case AT_DETECTION_TYPE:
			plugin->detectiontype_p = data;
			break;
		case AT_PTHRESH:
			plugin->pthresh_p = data;
			break;
		case AT_STHRESH:
			plugin->sthresh_p= data;
			break;
		case AT_INTERVAL:
			plugin->interval_p=data;
			break;
		case AT_LATENCY:
			plugin->latency_p=data;
			break;
		default:
			fprintf(stderr,"Warning, port %i not connected\n",port);
	}
}
static void cleanupOnset(LV2_Handle instance)
{
	onset_t* onset=(onset_t*)instance;
	del_fvec (	onset->inbuff);
	del_fvec (onset->outbuff);
	del_aubio_onset (onset->onset);
	free(onset);
	aubio_cleanup();	//Not sure if I should do this.
}

static aubio_onsetdetection_type detection_types[]={
	aubio_onset_energy,
	aubio_onset_specdiff ,
	aubio_onset_hfc,
	aubio_onset_complex,
	aubio_onset_phase,
	aubio_onset_kl ,
	aubio_onset_mkl };

static LV2_Handle instantiateOnset(const LV2_Descriptor *descriptor,
                                 double s_rate, const char *path,
                                 const LV2_Feature *  const * features)
{
	onset_t *plugin_data = (onset_t *)malloc(sizeof(onset_t));

	plugin_data->inbuff=new_fvec (HOP_SIZE,1);
	plugin_data->outbuff=new_fvec (HOP_SIZE,1);
	plugin_data->index=0;

	plugin_data->current_onset_type=0;
	plugin_data->onset=new_aubio_onset (detection_types[0],BUFFSIZE,HOP_SIZE,1);
	return plugin_data;
}

static void runOnset(LV2_Handle instance, uint32_t sample_count) {
	onset_t* o=(onset_t*) instance;

	unsigned int detectiontype=(unsigned int)(*o->detectiontype_p);
	if(0<=detectiontype && 6>=detectiontype && detectiontype!=o->current_onset_type) {
		del_aubio_onset (o->onset);
		o->onset=new_aubio_onset (detection_types[detectiontype],BUFFSIZE,HOP_SIZE,1);
		o->current_onset_type=detectiontype;
	}
	
	aubio_onset_set_threshold(o->onset,*o->pthresh_p);
	aubio_onset_set_silence(o->onset,*o->sthresh_p);
	aubio_onset_set_minioi(o->onset,*o->interval_p);
	
	float * readptr=o->in_p;
	float * writeptr=o->out_p;
	while(sample_count) {
		unsigned int num_copy=HOP_SIZE-o->index;
		if(num_copy> sample_count) {
			num_copy=sample_count;
		}
		memcpy(writeptr,o->outbuff->data[0]+o->index,num_copy*sizeof(float));	
		memcpy(o->inbuff->data[0] +o->index,readptr,num_copy*sizeof(float));
		writeptr+=num_copy;
		sample_count-=num_copy;
		readptr+=num_copy;
		o->index+=num_copy;
		if(o->index==HOP_SIZE) {
			o->index=0;
			aubio_onset(o->onset,o->inbuff,o->outbuff);
		}
	}
	if(o->latency_p){
		*o->latency_p=HOP_SIZE;
	}
}

static LV2_Descriptor* onsetDescriptor;
LV2_Descriptor* get_onset_descriptor () {
	if(!onsetDescriptor) {
		onsetDescriptor =
			(LV2_Descriptor *)malloc(sizeof(LV2_Descriptor));
		onsetDescriptor->URI = ONSET_URI;
		onsetDescriptor->activate = NULL;
		onsetDescriptor->cleanup = cleanupOnset;
		onsetDescriptor->connect_port = connectPortOnset;
		onsetDescriptor->deactivate = NULL;
		onsetDescriptor->instantiate = instantiateOnset;
		onsetDescriptor->run = runOnset;
		onsetDescriptor->extension_data = NULL;
	}
	return onsetDescriptor;
}