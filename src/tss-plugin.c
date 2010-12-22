/*
 * tss-plugin.c
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

#include "tss-plugin.h"

static LV2_Descriptor* tssDescriptor=NULL;

static void connectPortTss(LV2_Handle instance, uint32_t port, void *data) {
	tss_t* plugin = (tss_t *)instance;

	switch (port) {
		case TSS_IN:
			plugin->in_p = data;
			break;
		case TSS_STEADY:
			plugin->steady_p = data;
			break;
		case TSS_THRESH:
			plugin->thresh_p = data;
			break;
		case TSS_TRANS:
			plugin->trans_p= data;
			break;
		case TSS_LATENCY:
			plugin->latency_p=data;
			break;
		default:
			fprintf(stderr,"Warning, port %i not connected\n",port);
	}
}

static void cleanupTss(LV2_Handle instance)
{
	tss_t* t=(tss_t*)instance;
	del_fvec(t->inbuff);
	del_fvec(t->transbuff);
	del_fvec(t->steadybuff);
	del_cvec (t->ci);
	del_cvec (t->ct);
	del_cvec (t->cs);
	del_aubio_tss(t->tss);
	del_aubio_pvoc(t->pv);
	del_aubio_pvoc(t->pvs);
	del_aubio_pvoc(t->pvt);

	free(instance);
	aubio_cleanup();	//Not sure if I should do this.
}

static LV2_Handle instantiateTss(const LV2_Descriptor *descriptor,
                                 double s_rate, const char *path,
                                 const LV2_Feature *  const * features)
{
	tss_t *plugin_data = (tss_t *)malloc(sizeof(tss_t));

	plugin_data->inbuff=new_fvec (HOP_SIZE,1);
	plugin_data->steadybuff=new_fvec (HOP_SIZE,1);
	plugin_data->transbuff=new_fvec(HOP_SIZE,1);
	memset(plugin_data->steadybuff->data[0],0,HOP_SIZE*sizeof(float));
	memset(plugin_data->transbuff->data[0],0,HOP_SIZE*sizeof(float));
	

	plugin_data->tss=new_aubio_tss (0.01, 3, 4, BUFFSIZE,  HOP_SIZE, 1);
	plugin_data->pv = new_aubio_pvoc (BUFFSIZE,HOP_SIZE,1);
	plugin_data->pvt = new_aubio_pvoc(BUFFSIZE,HOP_SIZE,1);
	plugin_data->pvs = new_aubio_pvoc(BUFFSIZE,HOP_SIZE,1);

	plugin_data->ci=new_cvec (BUFFSIZE, 1);
	plugin_data->cs=new_cvec (BUFFSIZE, 1);
	plugin_data->ct=new_cvec (BUFFSIZE, 1);

	plugin_data->index=0;
	
	return (LV2_Handle)plugin_data;
}
static void runTss(LV2_Handle instance, uint32_t sample_count) {
	tss_t* t=(tss_t*) instance;

	aubio_tss_set_thres(t->tss,*t->thresh_p);

	float * readptr=t->in_p;
	float * transwrite=t->trans_p;
	float * steadywrite=t->steady_p;
	while(sample_count) {
		unsigned int num_copy=HOP_SIZE-t->index;
		if(num_copy> sample_count) {
			num_copy=sample_count;
		}
		memcpy(transwrite,t->transbuff->data[0]+t->index, sizeof(float) *num_copy);
		memcpy(steadywrite,t->steadybuff->data[0]+t->index, sizeof(float) * num_copy);	
		memcpy(t->inbuff->data[0] +t->index,readptr,num_copy*sizeof(float));
		steadywrite+=num_copy;
		transwrite+=num_copy;
		sample_count-=num_copy;
		readptr+=num_copy;
		t->index+=num_copy;
		if(t->index==HOP_SIZE) {
			t->index=0;
			aubio_pvoc_do(t->pv,t->inbuff,t->ci);
			aubio_tss_do(t->tss,t->ci,t->ct,t->cs);
			aubio_pvoc_rdo(t->pvt,t->ct,t->transbuff);
			aubio_pvoc_rdo(t->pvs,t->cs,t->steadybuff);
		}
	}
	if(t->latency_p){
		*t->latency_p=HOP_SIZE;
	}
}
	LV2_Descriptor* get_tss_descriptor() {
		if(!tssDescriptor) {
			tssDescriptor =
				(LV2_Descriptor *)malloc(sizeof(LV2_Descriptor));
			tssDescriptor->URI = TSS_URI;
			tssDescriptor->activate = NULL;
			tssDescriptor->cleanup = cleanupTss;
			tssDescriptor->connect_port = connectPortTss;
			tssDescriptor->deactivate = NULL;
			tssDescriptor->instantiate = instantiateTss;
			tssDescriptor->run = runTss;
			tssDescriptor->extension_data = NULL;
		}
		return tssDescriptor;
	}