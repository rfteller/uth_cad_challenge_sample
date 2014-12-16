/************************************************************************************************

	VOLUME-ONE Library (VOL):

		VOL.h:	header file for very basic components (elements)


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/


/////////////////////////////////////////////////////////////////////////////////////////////////
// basic definitions
/////////////////////////////////////////////////////////////////////////////////////////////////

#define VOL_FALSE		0
#define VOL_TRUE		1
#define VOL_NEUTRAL		2

#define VOL_OK			 0
#define VOL_NG			-1


#define VOL_VALUETYPE_SINGLE		0		// ordinary
#define VOL_VALUETYPE_DUAL			1		// interleaved 2 uchar/ushort components
#define VOL_VALUETYPE_RGBA			2		// interleaved uchar 4 components

#define VOL_MAX_CHANNELS_OF_DATA	256

#define VOL_M_PI					((float)3.1415926535)
#define VOL_VIRTUAL_INFINITY		((float)10000000.0)



#define VOL_RANGE_OF_UINT8	(unsigned char)(256)
#define VOL_RANGE_OF_SINT8	(unsigned char)(256)
#define VOL_RANGE_OF_UINT16 (unsigned short)(65536)
#define VOL_RANGE_OF_SINT16	(unsigned short)(65536)
#define VOL_RANGE_OF_UINT32	(unsigned int)(4294967296UL)
#define VOL_RANGE_OF_SINT32	(unsigned int)(4294967296UL)

#define VOL_MAX_OF_UINT8	(unsigned char)(255)
#define VOL_MAX_OF_SINT8	(char)(127)
#define VOL_MAX_OF_UINT16	(unsigned short)(65535)
#define VOL_MAX_OF_SINT16	(short)(32767)
#define VOL_MAX_OF_UINT32	(unsigned int)(4294967295UL)
#define VOL_MAX_OF_SINT32	(int)(2147483647L)			// ? 2147483648
#define VOL_MAX_OF_FLOAT32	(float)(3.40282e+38)

#define VOL_MIN_OF_UINT8	(unsigned char)(0)
#define VOL_MIN_OF_SINT8	(char)(-128)
#define VOL_MIN_OF_UINT16	(unsigned short)(0)
#define VOL_MIN_OF_SINT16	(short)(-32768)
#define VOL_MIN_OF_UINT32	(unsigned int)(0UL)
#define VOL_MIN_OF_SINT32	(int)(-2147483647L)		// ? -2147483648
#define VOL_MIN_OF_FLOAT32	(float)(-3.40282e+38)



/////////////////////////////////////////////////////////////////////////////////////////////////
// include files
/////////////////////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#include "Elements/basicPrimitive.h"
#include "Elements/geometricPrimitive.h"		//	depends on    basicPrimitive.h
#include "Elements/array.h"						//  depends on    basicPrimitive.h, geometricPrimitive.h
#include "Elements/colormap.h"					//	depends on    array.h, basicPrimitive.h
#include "Elements/rawVolumeData.h"				//	depends on    array.h, geometricPrimitive.h
#include "Elements/rawImageData.h"				//	depends on    array.h, geometricPrimitive.h
#include "Elements/volumeData.h"				//	depends on    rawVolumeData.h, colormap.h
#include "Elements/imageData.h"					//	depends on    rawVolumeData.h, colormap.h
#include "Elements/locationArray.h"				//	depends on    array.h
#include "Elements/kernel.h"					//	depends on    locationArray.h
#include "Elements/list.h"
#include "Elements/tree.h"						//	depends on    list.h
#include "Elements/binaryVolume.h"				//	depends on    rawVolumeData.h


#include "Geometry/parametricPrimitive.h"
#include "Geometry/draw.h"						//  depends on    parametricPrimitive.h
#include "Geometry/matrix.h"
#include "Geometry/triangularMesh.h"			//  depends on    parametricPrimitive.h
#include "Geometry/quaternion.h"


#include "Transform/flip.h"						//	depends on    rawVolumeData.h
#include "Transform/rotate.h"					//	depends on    rawVolumeData.h
#include "Transform/scale.h"					//	depends on    rawVolumeData.h, rawImageData.h


#include "Utility/convertUnit.h"				//	depends on   rawVolumeData.h, rawImageData.h
#include "Utility/copyPaste.h"					//	depends on   rawVolumeData.h, rawImageData.h
#include "Utility/dataSerialize.h"				//	depends on   rawVolumeData.h, parametricPrimitive.h
#include "Utility/misc.h"						//	depends on   rawVolumeData.h, rawImageData.h
#include "Utility/overlay.h"					//	depends on   rawVolumeData.h
#include "Utility/reformat.h"					//	depends on   rawVolumeData.h, rawImageData.h
#include "Utility/resize.h"						//	depends on   rawVolumeData.h




/////////////////////////////////////////////////////////////////////////////////////////////////
// for debug
/////////////////////////////////////////////////////////////////////////////////////////////////


#define SHOW_OK	fprintf(stderr,"OK\n");
#define SHOW_NG	fprintf(stderr,"NG\n");

#define SHOW_0	fprintf(stderr,"0\n");
#define SHOW_1	fprintf(stderr,"1\n");
#define SHOW_2	fprintf(stderr,"2\n");
#define SHOW_3	fprintf(stderr,"3\n");
#define SHOW_4	fprintf(stderr,"4\n");
#define SHOW_5	fprintf(stderr,"5\n");
#define SHOW_6	fprintf(stderr,"6\n");
#define SHOW_7	fprintf(stderr,"7\n");
#define SHOW_8	fprintf(stderr,"8\n");
#define SHOW_9	fprintf(stderr,"9\n");




