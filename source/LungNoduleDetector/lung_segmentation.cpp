////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Sample codes for UTH CAD Challenge
//
//	      lung_segmentation.cpp : Lung are segmentation from CT images
//
//    [CAUTION 1] The sample codes are permitted to use only for research purposes.
//
//    [CAUTION 2] If you use this algorithm, you should cite the paper: 
//                   Nomura Y et al., "Reduction of false positives at vessel bifurcations in
//                   omputerized detection of lung nodules," Journal of Biomedical Graphics and
//                   Computing, vol.4, no.3, pp.36-46, 2014.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "VOL.h"
#include "VOLbinary.h"
#include "VOLfilter.h"
#include "LibCircusCS.h"

#include "lung_segmentation.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

// fixed params (modified to be adaptive)
#define BONE_THRESHOLD                    100
#define BODY_TRUNK_THRESHOLD             -150
#define LUNG_THRESHOLD_JOIN              -600

#define SECOND_THRESHOLD_OFFSET           100

#define AIRWAY_SEARCH_OFFSET               10
#define	CROPPING_MARGIN						8

#define BRONCHI_CUT_RADIUS					2.5f 
#define BRONCHI_CUT_ITERATIONS				1

#define FINAL_LUNG_SMOOTHING_RADIUS			5.0f  
#define FINAL_LUNG_SMOOTHING_ITERATIONS		1

////////////////////////////////////////////////////////////////////////////////////////////////////

static int
search_peak(unsigned int* histo_array, int length)
{
	unsigned int max_cnt   = 0;
	int			 max_index = 0;

	for(int i = 0; i < length; i++)
	{
		if(histo_array[i] > max_cnt)
		{
			max_cnt   = histo_array[i];
			max_index = i;
		}
	}

	return max_index;
}


// get air peak, and lung peak
void
get_calibration(VOL_RAWVOLUMEDATA* volume, VOL_RAWVOLUMEDATA* labels, short* lung_level)
{
	short           lung_histo_min = -1000;
	short           lung_histo_max = -800;
	unsigned int    lung_histo[200];
	short*			signal_ptr = (short*)volume->data[0];
	unsigned char*	label_ptr  = (unsigned char*)labels->data[0];
	int				length     = VOL_GetNumberOfVoxels(volume);

	for(int i = 0; i < 200; i++)  lung_histo[i] = 0;

	for(int i = 0; i < length; i++)
	{
		unsigned char	label  = *label_ptr++;
		short			signal = *signal_ptr++;

		if(label == 1 
			&& signal >= lung_histo_min
			&& signal < lung_histo_max)
		{
			lung_histo[(int)(signal - lung_histo_min)]++;
		}
	}

	*lung_level = search_peak(lung_histo, 200) + lung_histo_min;
}



// replace all "label" value with 1 (foreground)
void
make_uint8_volume_binary(VOL_RAWVOLUMEDATA* volume)
{
	VOL_VOLVALUERANGE range;

	range.min.uint8 = 1;
	range.max.uint8 = 255;

	VOL_ThresholdingMinMax(volume, 0, &range);
}


// general purpose label extractor (max label value <= 255)
void
extract_components(
	VOL_RAWVOLUMEDATA* volume,
	int extracted_cc_cnt,
	unsigned int* component_ids,
	int connectivity_type)
{
	int	cmps_num = VOL_ConnectedComponentAnalysis(
						volume,
						0,
						connectivity_type);
	
	VOL_COMPONENTDATA* cc_data = VOL_NewComponentData(volume, 0, cmps_num);

	if(cmps_num == 0 || cc_data == NULL)	return;

	VOL_SortComponentsByProperty(cc_data, VOL_CC_PROPERTY_ID_VOXELCOUNT);
	
	VOL_ExtractComponents(cc_data, extracted_cc_cnt, component_ids);

	VOL_DeleteComponentData(cc_data);
}


// may be used only for bronchi(+airway)
void
extract_component_of_minimum_Z(VOL_RAWVOLUMEDATA* bin_volume, int search_offset_z)
{
	int width  = bin_volume->matrixSize->width;
	int	height = bin_volume->matrixSize->height;
	int	depth  = bin_volume->matrixSize->depth;

	unsigned int cmp_num = VOL_ConnectedComponentAnalysis(
								bin_volume,
								0,
								VOL_NEIGHBOURTYPE_26);

	VOL_COMPONENTDATA*	cc_data = VOL_NewComponentData(bin_volume, 0, cmp_num);

	if(cmp_num == 0 || cc_data == NULL)	return;

	unsigned long  found  = 0;
	unsigned long* voxels = (unsigned long*)bin_volume->data[0]
							+ search_offset_z * width * height;

	for(int k = search_offset_z; k < depth  && found == 0; k++)
	for(int j = 0;               j < height && found == 0; j++)
	for(int i = 0;               i < width  && found == 0; i++)
	{
		if((found = *voxels) == 0)	voxels++;
	}

	VOL_ExtractComponent(cc_data, found);	// only 1 component

	VOL_DeleteComponentData(cc_data);
}



void
replace_sint16value_in_uint8mask(
	VOL_RAWVOLUMEDATA* signal_volume,
	short replace_value,
	VOL_RAWVOLUMEDATA* mask,
	unsigned char mask_value)
{
	short*		   signal_ptr = (short*)signal_volume->data[0];
	unsigned char* mask_ptr   = (unsigned char*)mask->data[0];
	int	           length     = VOL_GetNumberOfVoxels(signal_volume);

	for(int i = 0; i < length; i++)
	{
		if( *mask_ptr == mask_value )	*signal_ptr = replace_value;
		
		signal_ptr++;
		mask_ptr++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class VARTYPE>
static void
initiaize_label(VARTYPE* src_ptr, VARTYPE max_value, int length)
{
	for(int i = 0; i < length; i++)
	{
		*src_ptr = (*src_ptr != 0) ? max_value : 0;
		src_ptr++;
	}
}

template void initiaize_label(unsigned char*  src_ptr, unsigned char  max_value, int length);
template void initiaize_label(unsigned short* src_ptr, unsigned short max_value, int length);
template void initiaize_label(unsigned int*   src_ptr, unsigned int   max_value, int length);

template <class VARTYPE>
static void
re_binarize_label(VARTYPE* src_ptr, VARTYPE threshold, int length)
{
	for(int i = 0; i < length; i++)
	{
		*src_ptr = (*src_ptr >= threshold) ? 1 : 0;
		src_ptr++;
	}
}

template void re_binarize_label(unsigned char*  src_ptr, unsigned char  threshold, int length);
template void re_binarize_label(unsigned short* src_ptr, unsigned short threshold, int length);
template void re_binarize_label(unsigned int*   src_ptr, unsigned int   threshold, int length);


void
rescale_binary_volume(VOL_RAWVOLUMEDATA* volume, VOL_INTSIZE3D* dst_size)
{
	unsigned char* srcPtr = (unsigned char*)volume->data[0];
	int length = VOL_GetNumberOfVoxels(volume);

	switch(volume->voxelUnit[0])
	{
		case VOL_VALUEUNIT_UINT8:
					initiaize_label(
						(unsigned char*)volume->data[0],
						VOL_MAX_OF_UINT8,
						length);
					break;

		case VOL_VALUEUNIT_UINT16:
					initiaize_label(
						(unsigned short*)volume->data[0],
						VOL_MAX_OF_UINT16,
						length);
					break;
		
		case VOL_VALUEUNIT_UINT32:
					initiaize_label(
						(unsigned int*)volume->data[0],
						VOL_MAX_OF_UINT32,
						length);
					break;
	}

	VOL_ScaleRawVolumeData(volume, dst_size, VOL_SCALING_METHOD_LINEAR);
	
	length = VOL_GetNumberOfVoxels(volume);

	switch(volume->voxelUnit[0])
	{
		case VOL_VALUEUNIT_UINT8:
					re_binarize_label(
						(unsigned char*)volume->data[0],
						(unsigned char)128,
						length);
					break;

		case VOL_VALUEUNIT_UINT16:
					re_binarize_label(
						(unsigned short*)volume->data[0],
						(unsigned short)32768,
						length);
					break;

		case VOL_VALUEUNIT_UINT32:
					re_binarize_label(
						(unsigned int*)volume->data[0],
						(unsigned int)2147483648,
						length);
					break;
	}

	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

VOL_RAWVOLUMEDATA*
body_trunk_extraction(VOL_RAWVOLUMEDATA* volume, short threshold)
{
	VOL_RAWVOLUMEDATA* ret = VOL_DuplicateRawVolumeData(volume);

	VOL_VOLVALUERANGE	range;

	range.min.sint16 = threshold;
	range.max.sint16 = VOL_MAX_OF_SINT16;

	VOL_ThresholdingMinMax(ret, 0, &range);

	VOL_ConvertVoxelUnit(
		ret,
		0,
		VOL_VALUEUNIT_UINT16,
		NULL,
		NULL,
		VOL_CONVERTUNIT_TYPE_DIRECT);

	VOL_INTSIZE3D* org_size  = VOL_GetIntSize3DFromIntSize4D(ret->matrixSize);
	VOL_INTSIZE3D* half_size = VOL_NewIntSize3D(
									org_size->width/2,
									org_size->height/2,
									org_size->depth/2);

	rescale_binary_volume(ret, half_size);

	VOL_AttachOffsetXY(ret, 1, VOL_RESIZE_BACKGROUNDTYPE_ZERO);

	unsigned short*** mask_data = (unsigned short***)ret->array4D[0];

	VOL_INTSIZE3D label_slice_size;
	label_slice_size.width  = half_size->width;
	label_slice_size.height = half_size->height;
	label_slice_size.depth  = 1;
	
	unsigned int component_ids[1] = {1};

	for(int k = 0; k < half_size->depth; k++)
	{
		VOL_RAWVOLUMEDATA* tmp_volume = VOL_NewSingleChannelRawVolumeData(
											&label_slice_size,
											VOL_VALUEUNIT_UINT16,
											VOL_VALUETYPE_SINGLE);

		{
			unsigned short*** tmp_data = (unsigned short***)tmp_volume->array4D[0];

			for(int j = 0; j < label_slice_size.height; j++)
			for(int i = 0; i < label_slice_size.width;  i++)
			{
				tmp_data[0][j][i] = mask_data[k][j][i];
			}
		}

		extract_components(tmp_volume, 1, component_ids, VOL_NEIGHBOURTYPE_18);

		VOL_RemoveCavity(tmp_volume, 0);

		{
			unsigned int*** tmp_data = (unsigned int***)tmp_volume->array4D[0];

			for(int j=0; j<label_slice_size.height; j++)
			for(int i=0; i<label_slice_size.width;  i++)
			{
				mask_data[k][j][i] = tmp_data[0][j][i];
			}
		}

		VOL_DeleteRawVolumeData(tmp_volume);
	}

	VOL_ConvertVoxelUnit(ret, 0, VOL_VALUEUNIT_UINT8, NULL, NULL, VOL_CONVERTUNIT_TYPE_DIRECT);
	
	VOL_RemoveOffsetXY(ret, 1);

	rescale_binary_volume(ret, org_size);

	VOL_DeleteIntSize3D(org_size);
	VOL_DeleteIntSize3D(half_size);

	return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static VOL_RAWVOLUMEDATA*
simple_bronchi_segmentation(VOL_RAWVOLUMEDATA* volume, VOL_RAWVOLUMEDATA* lung_shape, short threshold)
{
	VOL_RAWVOLUMEDATA*	bronchi_shape = VOL_DuplicateRawVolumeData(lung_shape);

	short*         src_ptr     = (short*)volume->data[0];
	unsigned char* lung_ptr    = (unsigned char*)lung_shape->data[0];
	unsigned char* bronchi_ptr = (unsigned char*)bronchi_shape->data[0];
	int            length      = VOL_GetNumberOfVoxels(volume);

	// included in the input, but lower than BRONCHI_THRESHOLD
	for(int i = 0; i < length; i++)
	{
		*bronchi_ptr = ( *lung_ptr != 0 && *src_ptr < threshold ) ? 1 : 0;

		src_ptr++;
		lung_ptr++;
		bronchi_ptr++;
	}

	// opening to cut air within lungs
	{
		for(int i = 0; i < BRONCHI_CUT_ITERATIONS; i++)
		{
			VOL_ErodeBinaryVolumeBySphere(bronchi_shape, 0, BRONCHI_CUT_RADIUS);
		}

		for(int i = 0; i < BRONCHI_CUT_ITERATIONS; i++)
		{
			VOL_DilateBinaryVolumeBySphere(bronchi_shape, 0, BRONCHI_CUT_RADIUS);
		}
	}

	// should be so
	extract_component_of_minimum_Z(bronchi_shape, AIRWAY_SEARCH_OFFSET);

	VOL_ConvertVoxelUnit(
		bronchi_shape,
		0,
		VOL_VALUEUNIT_UINT8,
		NULL,
		NULL,
		VOL_CONVERTUNIT_TYPE_DIRECT);
	
	make_uint8_volume_binary(bronchi_shape);

	return bronchi_shape;
}

static VOL_RAWVOLUMEDATA*
simple_bone_segmentation(VOL_RAWVOLUMEDATA* volume, short threshold)
{
	VOL_INTSIZE3D*     org_matrix = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);
	VOL_RAWVOLUMEDATA* bone_shape = VOL_NewSingleChannelRawVolumeData(
										org_matrix,
										VOL_VALUEUNIT_UINT8,
										VOL_VALUETYPE_SINGLE);

	short*         src_ptr  = (short*)volume->data[0];
	unsigned char* bone_ptr = (unsigned char*)bone_shape->data[0];
	int            length   = VOL_GetNumberOfVoxels(volume);

	// simple thresholding
	for(int i = 0; i < length; i++)
	{
		*bone_ptr = (*src_ptr > threshold ) ? 1 : 0;

		bone_ptr++;
		src_ptr++;
	}

	VOL_ErodeBinaryVolumeBySphere(bone_shape,  0, 1.0f);
	VOL_DilateBinaryVolumeBySphere(bone_shape, 0, 1.0f);

	// extract the largest area
	{
		unsigned int component_ids[1] = {1};
		extract_components(bone_shape, 1, component_ids, VOL_NEIGHBOURTYPE_26);

		VOL_ConvertVoxelUnit(
			bone_shape,
			0,
			VOL_VALUEUNIT_UINT8,
			NULL,
			NULL,
			VOL_CONVERTUNIT_TYPE_DIRECT);
	}

	// closing
	VOL_DilateBinaryVolumeBySphere(bone_shape, 0, 5.0f);
	VOL_ErodeBinaryVolumeBySphere(bone_shape,  0, 5.0f);

	return bone_shape;
}



static VOL_RAWVOLUMEDATA*
lung_resegmentation(VOL_RAWVOLUMEDATA* signal_volume,
					VOL_RAWVOLUMEDATA* other_lung_shape,
					VOL_RAWVOLUMEDATA* body_trunk,
					VOL_RAWVOLUMEDATA* brochi_shape)
{
	VOL_RAWVOLUMEDATA* ret = VOL_DuplicateRawVolumeData(signal_volume);

	// initial thresholding
	{
		VOL_VOLVALUERANGE	range;

		range.min.sint16 = VOL_MIN_OF_SINT16;
		range.max.sint16 = LUNG_THRESHOLD_JOIN;

		VOL_ThresholdingMinMax(ret, 0, &range);

		VOL_ConvertVoxelUnit(ret,0,VOL_VALUEUNIT_UINT8,NULL,NULL,VOL_CONVERTUNIT_TYPE_DIRECT);

		VOL_BooleanOperationOfBinaryVolume(ret, 0, body_trunk, 0, "AND");
	}
	
	// remove bronchi and other lung
	VOL_BooleanOperationOfBinaryVolume(ret, 0, other_lung_shape, 0, "NAND");
	VOL_BooleanOperationOfBinaryVolume(ret, 0, brochi_shape, 0, "NAND");


	// largest
	{
		unsigned int component_ids[1] = {1};

		extract_components(ret, 1, component_ids, VOL_NEIGHBOURTYPE_26);

		VOL_ConvertVoxelUnit(ret, 0, VOL_VALUEUNIT_UINT8, NULL, NULL, VOL_CONVERTUNIT_TYPE_DIRECT);
		make_uint8_volume_binary(ret);
	}


	// closing
	for(int i = 0; i < FINAL_LUNG_SMOOTHING_ITERATIONS; i++)
	{
		VOL_DilateBinaryVolumeBySphere(ret, 0, FINAL_LUNG_SMOOTHING_RADIUS);
	}

	for(int i = 0; i < FINAL_LUNG_SMOOTHING_ITERATIONS; i++)
	{
		VOL_ErodeBinaryVolumeBySphere(ret, 0, FINAL_LUNG_SMOOTHING_RADIUS);
	}

	// remove bubbles
	VOL_RemoveCavity(ret, 0);

	return ret;
}


static void
complete_each_lung(VOL_RAWVOLUMEDATA* signal_volume,
				   VOL_RAWVOLUMEDATA* dilated_lung_labels,
				   VOL_RAWVOLUMEDATA* body_trunk,
				   VOL_RAWVOLUMEDATA* brochi_shape)
{
	VOL_RAWVOLUMEDATA *largest_first  = VOL_ExtractSingleChannelRawVolumeData(dilated_lung_labels, 0);
	VOL_RAWVOLUMEDATA *largest_second = VOL_ExtractSingleChannelRawVolumeData(dilated_lung_labels, 0);
	
	// extract each
	{
		VOL_VOLVALUERANGE	range;

		range.min.uint8 = 1;
		range.max.uint8 = 1;
		VOL_ThresholdingMinMax(largest_first, 0, &range );
		VOL_DilateBinaryVolumeBySphere(largest_first, 0, 1.0f);

		range.min.uint8 = 2;
		range.max.uint8 = 2;
		VOL_ThresholdingMinMax(largest_second, 0, &range );
		VOL_DilateBinaryVolumeBySphere(largest_second, 0, 1.0f);
	}

	// with precision
	VOL_RAWVOLUMEDATA* largest_first_prec  = lung_resegmentation(
												signal_volume,
												largest_second,
												body_trunk,
												brochi_shape);
	VOL_RAWVOLUMEDATA* largest_second_prec = lung_resegmentation(
												signal_volume,
												largest_first,
												body_trunk,
												brochi_shape);

	VOL_DeleteRawVolumeData(largest_first);
	VOL_DeleteRawVolumeData(largest_second);

	// boolean operation
	VOL_ClearRawVolumeData(dilated_lung_labels,0);

	VOL_BooleanOperationOfBinaryVolume(dilated_lung_labels, 0, largest_first_prec,  0, "OR");
	VOL_BooleanOperationOfBinaryVolume(dilated_lung_labels, 0, largest_second_prec, 0, "OR");

	VOL_DeleteRawVolumeData(largest_first_prec);
	VOL_DeleteRawVolumeData(largest_second_prec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void
lung_segmentation(VOL_RAWVOLUMEDATA* volume)
{
	VOL_RAWVOLUMEDATA* lung_shape = VOL_DuplicateRawVolumeData(volume);
	VOL_RAWVOLUMEDATA* bronchi_shape;
	VOL_RAWVOLUMEDATA* bone_shape;
	
	//----------------------------------------------------------------------------------------------
	// extract body trunk and bone region
	//----------------------------------------------------------------------------------------------
	fprintf(stderr,">body trunk extraction\n");
	VOL_RAWVOLUMEDATA* body_trunk = body_trunk_extraction(volume, BODY_TRUNK_THRESHOLD);
	//----------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------
	// initial segmentation
	//----------------------------------------------------------------------------------------------
	fprintf(stderr, ">initial thresholding\n");
	{
		short*         src_ptr  = (short*)lung_shape->data[0];
		unsigned char* body_ptr = (unsigned char*)body_trunk->data[0];
		int            length   = VOL_GetNumberOfVoxels(lung_shape);

		for(int i = 0; i < length; i++)
		{
			*src_ptr = (*body_ptr == 1 && *src_ptr <= LUNG_THRESHOLD_JOIN) ? 1 : 0;

			src_ptr++;
			body_ptr++;
		}
		
		VOL_ConvertVoxelUnit(
			lung_shape,
			0,
			VOL_VALUEUNIT_UINT32,
			NULL,
			NULL,
			VOL_CONVERTUNIT_TYPE_DIRECT);

		unsigned int component_ids[1] = {1};
		extract_components(lung_shape, 1, component_ids, VOL_NEIGHBOURTYPE_26);

		VOL_ConvertVoxelUnit(
			lung_shape,
			0,
			VOL_VALUEUNIT_UINT8,
			NULL,
			NULL,
			VOL_CONVERTUNIT_TYPE_DIRECT);
	}
	//----------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------
	// cropping
	//----------------------------------------------------------------------------------------------
	fprintf(stderr,">cropping\n");	

	VOL_INTSIZE3D*	org_matrix = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);
	VOL_INTBOX3D*	crop_box   = VOL_GetBoundingBoxOfBinaryVolume(lung_shape, 0);

	crop_box->size->width  += (CROPPING_MARGIN*2);		
	crop_box->size->height += (CROPPING_MARGIN*2);		
	crop_box->size->depth   = volume->matrixSize->depth;
	crop_box->origin->x    -= CROPPING_MARGIN;
	crop_box->origin->y    -= CROPPING_MARGIN;
	crop_box->origin->z     = 0;

	VOL_ResizeRawVolumeData(body_trunk, crop_box, VOL_RESIZE_BACKGROUNDTYPE_ZERO);
	VOL_ResizeRawVolumeData(lung_shape, crop_box, VOL_RESIZE_BACKGROUNDTYPE_ZERO);
	VOL_ResizeRawVolumeData(volume,     crop_box, VOL_RESIZE_BACKGROUNDTYPE_ZERO);
	//----------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------
	// second segmentation
	//----------------------------------------------------------------------------------------------
	fprintf(stderr,">second thresholding\n");

	short lung_level;
	{
		// get air level, lung level
		get_calibration(volume, lung_shape, &lung_level);
		fprintf(stderr, "lung_level:%d\n", lung_level);

		VOL_RAWVOLUMEDATA* tmp_volume = VOL_DuplicateRawVolumeData(volume);
	
	
		VOL_VOLVALUERANGE range;
	
		range.min.sint16 = VOL_MIN_OF_SINT16;
		range.max.sint16 = lung_level + SECOND_THRESHOLD_OFFSET;
	
		fprintf(stderr, "... (min,max)=(%d,%d)\n", range.min.sint16, range.max.sint16);
	
		VOL_ThresholdingMinMax(tmp_volume, 0, &range);
	
		VOL_ConvertVoxelUnit(
			tmp_volume,
			0,
			VOL_VALUEUNIT_UINT8,
			NULL,
			NULL,
			VOL_CONVERTUNIT_TYPE_DIRECT);
	
		VOL_BooleanOperationOfBinaryVolume(tmp_volume, 0, lung_shape, 0, "AND");
	
		VOL_SwapContentsOfRawVolumeData(tmp_volume, lung_shape);
	
		VOL_DeleteRawVolumeData(tmp_volume);
	}
	//----------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------
	// Remove bronchi
	// NOTE: At this phase, smaller noise components may be included in lung_shape (mostly airway
	//       surface). In the subsequent section, only 2 largest will be extracted and be smoothed
	//       independently.
	//----------------------------------------------------------------------------------------------
	fprintf(stderr,">simple bronchi segmentation \n");

	// simple segmentation (should be modified later)
	bronchi_shape = simple_bronchi_segmentation(volume, lung_shape, lung_level + 50);

	// plus partial volume
	VOL_DilateBinaryVolumeBySphere(bronchi_shape, 0, 1.5f);
		
	// remove
	VOL_BooleanOperationOfBinaryVolume(lung_shape, 0, bronchi_shape, 0, "NAND");
	//----------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------
	// bone segmentation
	//----------------------------------------------------------------------------------------------
	fprintf(stderr,">simple bone segmentation \n");

	// simple segmentation
	bone_shape = simple_bone_segmentation(volume, 100);

	// plus partial volume
	VOL_DilateBinaryVolumeBySphere(bone_shape, 0 , 1.5f);
	//----------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------
	// precise segmentation
	//----------------------------------------------------------------------------------------------
	fprintf(stderr,">complete each lung\n");
	{
		unsigned int component_ids[2] = {1,2};

		extract_components(lung_shape, 2, component_ids, VOL_NEIGHBOURTYPE_26);

		VOL_DilateLabeledVolume(lung_shape, 0, 5);

		VOL_ConvertVoxelUnit(
			lung_shape,
			0,
			VOL_VALUEUNIT_UINT8,
			NULL,
			NULL,
			VOL_CONVERTUNIT_TYPE_DIRECT);

		{
			unsigned char* lung_ptr = (unsigned char*)lung_shape->data[0];
			unsigned char* body_ptr = (unsigned char*)body_trunk->data[0];
			int            length   = VOL_GetNumberOfVoxels(lung_shape);

			for(int i = 0; i < length; i++)
			{
				if(*body_ptr == 0)  *lung_ptr = 0;

				lung_ptr++;
				body_ptr++;
			}
		}

		// final processing
		complete_each_lung(volume, lung_shape, body_trunk, bronchi_shape);
	}
	//----------------------------------------------------------------------------------------------

	// remove bone region
	fprintf(stderr,">remove bone region\n");
	VOL_BooleanOperationOfBinaryVolume(lung_shape, 0, bone_shape, 0, "NAND");

	// useless hereafter
	VOL_DeleteRawVolumeData(bronchi_shape);
	VOL_DeleteRawVolumeData(body_trunk);
	VOL_DeleteRawVolumeData(bone_shape);

	// output binary shape only
	VOL_SwapContentsOfRawVolumeData(volume, lung_shape);
	
	// useless hereafter
	VOL_DeleteRawVolumeData(lung_shape);

	// restore original size
	{
		VOL_RAWVOLUMEDATA* tmp_volume = VOL_NewSingleChannelRawVolumeData(
											org_matrix,
											volume->voxelUnit[0],
											volume->voxelType[0]);

		VOL_DeleteIntSize3D(org_matrix);

		VOL_INTVECTOR3D	dst_origin;

		dst_origin.x = crop_box->origin->x;
		dst_origin.y = crop_box->origin->y;	
		dst_origin.z = crop_box->origin->z;

		crop_box->origin->x = 0;
		crop_box->origin->y = 0;
		crop_box->origin->z = 0;

		// paste into new
		VOL_CopyRawVolumeData(volume, 0, tmp_volume, 0, crop_box, &dst_origin);

		VOL_DeleteIntBox3D(crop_box);

		// swap contents
		VOL_SwapContentsOfRawVolumeData(volume, tmp_volume);

		VOL_DeleteRawVolumeData(tmp_volume);
	}
}