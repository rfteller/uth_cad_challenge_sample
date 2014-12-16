/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		basicPrimitive.h:	for basic primitives such as "value"


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/

#ifndef BASICPRIMITIVE_H


#define VOL_VALUEUNIT_UINT8		0		// unsigned char
#define VOL_VALUEUNIT_SINT8		1		// (signed) char
#define VOL_VALUEUNIT_UINT16	2		// unsigned short
#define VOL_VALUEUNIT_SINT16	3		// (signed) short
#define VOL_VALUEUNIT_UINT32	4		// unsigned int
#define VOL_VALUEUNIT_SINT32	5		// (signed) int
#define VOL_VALUEUNIT_FLOAT32	6		// float
#define VOL_VALUEUNIT_FLOAT64	7		// double

#define VOL_VALUEUNIT_TYPESTRING_UINT8		"unsigned 8 bits"				// unsigned char
#define VOL_VALUEUNIT_TYPESTRING_SINT8		"signed 8 bits"				// (signed) char
#define VOL_VALUEUNIT_TYPESTRING_UINT16		"unsigned 16 bits"				// unsigned short
#define VOL_VALUEUNIT_TYPESTRING_SINT16		"signed 16 bits"				// (signed) short
#define VOL_VALUEUNIT_TYPESTRING_UINT32		"unsigned 32 bits"			// unsigned int
#define VOL_VALUEUNIT_TYPESTRING_SINT32		"signed 32 bits"			// (signed) int
#define VOL_VALUEUNIT_TYPESTRING_FLOAT32	"floating-point 32 bits"		// float
#define VOL_VALUEUNIT_TYPESTRING_FLOAT64	"floating-point 64 bits"		// double

#define VOL_INTERLEAVE_TYPE_3D	0
#define VOL_INTERLEAVE_TYPE_2D	1
#define VOL_INTERLEAVE_TYPE_1D	2
#define VOL_INTERLEAVE_TYPE_0D	3

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int				VOL_GetByteSizeOfValueUnit(int unit);
void			VOL_GetTypeStringOfValueUnit(int unit,char* string_32bytes_needed);
char*			VOL_GetValueUnitNameString(int unit);
int				VOL_CheckIfUnitIsValid(int unit);

float			VOL_LargerOf2Values(float value1,float value2);
float			VOL_SmallerOf2Values(float value1,float value2);
float			VOL_MinimumOf3Values(float value1,float value2,float value3);
float			VOL_MaximumOf3Values(float value1,float value2,float value3);

int				VOL_LargerOf2IntValues(int value1,int value2);
int				VOL_SmallerOf2IntValues(int value1,int value2);
int				VOL_MinimumOf3IntValues(int value1,int value2,int value3);
int				VOL_MaximumOf3IntValues(int value1,int value2,int value3);

#ifdef __cplusplus
}
#endif /* __cplusplus */

typedef union VolValue
{
	unsigned char	uint8;
	char			sint8;
	unsigned short	uint16;
	short			sint16;
	unsigned int	uint32;
	int				sint32;
	float			float32;
	double			float64;
} VOL_VALUE;

typedef struct VolValueRange {		float		min, max;	}	VOL_VALUERANGE;
typedef struct VolIntValueRange {	int		min, max;	}	VOL_INTVALUERANGE;

typedef struct VolVolValueRange {	VOL_VALUE	min, max;	}	VOL_VOLVALUERANGE;


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

VOL_VALUERANGE*		VOL_NewValueRange(float min,float max);
VOL_VALUERANGE*		VOL_DuplicateValueRange(VOL_VALUERANGE* valueRange);
VOL_VALUERANGE*		VOL_GetValueRangeOfValueUnit(int unit);
void				VOL_DeleteValueRange(VOL_VALUERANGE* valueRange);
int					VOL_CheckIfValueIsWithinRange(float value,VOL_VALUERANGE* range);
float				VOL_ForceWithinRange(float value,VOL_VALUERANGE* range);

float				VOL_ScaleValue(float value,VOL_VALUERANGE* oldRange,VOL_VALUERANGE* newRange);
float				VOL_ScaleValueWithRangeCheck(float value,VOL_VALUERANGE* srcRange,VOL_VALUERANGE* dstRange);


VOL_VALUE*			VOL_ConvertFloatValueToVolValue(float value, int unit);
VOL_VOLVALUERANGE*	VOL_ConvertValueRangeToVolValueRange(VOL_VALUERANGE* valueRange, int unit);



VOL_VALUERANGE*		VOL_GetValueRangeOfArray(void* array,int length,int unit);

VOL_VALUERANGE*		VOL_AddRanges(VOL_VALUERANGE* range1,VOL_VALUERANGE* range2);


VOL_INTVALUERANGE*	VOL_NewIntValueRange(int min,int max);
VOL_INTVALUERANGE*	VOL_DuplicateIntValueRange(VOL_INTVALUERANGE* valueRange);
void				VOL_DeleteIntValueRange(VOL_INTVALUERANGE* valueRange);
int					VOL_CheckIfValueIsWithinIntRange(int value,VOL_INTVALUERANGE* range);
int					VOL_ForceWithinIntRange(int value,VOL_INTVALUERANGE* range);

int					VOL_AutoScaleWithinIntRange(int value,VOL_INTVALUERANGE* oldRange,VOL_INTVALUERANGE* newRange);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif

#define BASICPRIMITIVE_H

