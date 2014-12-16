/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		colormap.h:	for color-look-up tables


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/

#ifndef COLORMAP_H

#define VOL_COLORLIST_INDEXTYPE_INT		0
#define VOL_COLORLIST_INDEXTYPE_FLOAT	1

#define VOL_COLORMAP_TYPE_DIRECT		0
#define VOL_COLORMAP_TYPE_INDIRECT		1


typedef struct VolColor
{
	float	r;
	float	g;
	float	b;
	float	a;

} VOL_COLOR;

typedef struct VolColorList
{
	int		nColors;
	int		nColorsMax;			// may be private in C++

	int		indexType;

	void*		indices;
	VOL_COLOR**	colors;

} VOL_COLORLIST;



typedef struct VolDirectColormap		// for integer index value
{
	int		nColors;					// number of colors

	VOL_INTVALUERANGE*	indexRange;		// index value can be negative for signed index value
	VOL_VALUERANGE*		rRange;			// range: 0-255, 0-1, etc.
	VOL_VALUERANGE*		gRange;			// range: 0-255, 0-1, etc.
	VOL_VALUERANGE*		bRange;			// range: 0-255, 0-1, etc.
	VOL_VALUERANGE*		aRange;			// range: 0-255, 0-1, etc.

	float*	r;							// (an indexing trick by address shifting)
	float*	g;							//		+ indexMin is the top of the original array
	float*	b;							//		r(,g,b,a)[index] = value
	float*	a;							//			index = [indexRange->min, ..., indexRange->max+nColors-1]

} VOL_DIRECTCOLORMAP;



typedef struct VolIndirectColormap		// for integer/floating point index value
{
	int		nColors;					// number of colors

	VOL_VALUERANGE*		indexRange;		// can be negative or floating point value

	float	scale, shift;				// should be private member in C++
										// index' = (int)( scale*index + shift )
										// scale*indexRange->min + shift = 0, scale*indexRange->max + shift = nColors-1
							
	float*	r;							// no indexing trick
	float*	g;
	float*	b;
	float*	a;

} VOL_INDIRECTCOLORMAP;

typedef union VolColormapPointer
{
	VOL_DIRECTCOLORMAP*		directColormap;
	VOL_INDIRECTCOLORMAP*	indirectColormap;

} VOL_COLORMAPPOINTER;

typedef struct VolColormap
{
	int		colormapType;

	VOL_COLORMAPPOINTER*	colormap;

} VOL_COLORMAP;


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


VOL_COLOR*		VOL_NewColor(float r,float g,float b,float a);
VOL_COLOR*		VOL_DuplicateColor(VOL_COLOR* color);
void			VOL_DeleteColor(VOL_COLOR* color);

VOL_COLORLIST*	VOL_NewColorList(int nColorsMax,int indexType);
VOL_COLORLIST*	VOL_DuplicateColorList(VOL_COLORLIST* colorList);
void			VOL_DeleteColorList(VOL_COLORLIST* colorList);

int				VOL_AddColorToColorList(VOL_COLORLIST* colorList,VOL_COLOR* color,void* index);
int				VOL_RemoveColorFromColorList(VOL_COLORLIST* colorList,void* index);
void			VOL_SortColorListByIndex(VOL_COLORLIST* colorList);


VOL_DIRECTCOLORMAP*		VOL_NewDirectColormap(int indexMin,int nColors);
VOL_DIRECTCOLORMAP* 	VOL_NewDirectColormapFromColorList(VOL_COLORLIST* colorList);
VOL_DIRECTCOLORMAP*		VOL_NewDirectColormapOfPrimaryColors(int indexMin,int nColors);
VOL_DIRECTCOLORMAP* 	VOL_DuplicateDirectColormap(VOL_DIRECTCOLORMAP* colormap);
void					VOL_DeleteDirectColormap(VOL_DIRECTCOLORMAP* colormap);

void					VOL_GetColorInDirectColormap(VOL_DIRECTCOLORMAP* colormap,int index,VOL_COLOR* color);
void					VOL_GetColorInDirectColormapSecure(VOL_DIRECTCOLORMAP* colormap,int index,VOL_COLOR* color);
void					VOL_GetRGBInDirectColormap(VOL_DIRECTCOLORMAP* colormap,int index,float* r,float* g,float* b);
void					VOL_GetRGBInDirectColormapSecure(VOL_DIRECTCOLORMAP* colormap,int index,float* r,float* g,float* b);
void					VOL_GetRGBAInDirectColormap(VOL_DIRECTCOLORMAP* colormap,int index,float* r,float* g,float* b,float* a);
void					VOL_GetRGBAInDirectColormapSecure(VOL_DIRECTCOLORMAP* colormap,int index,float* r,float* g,float* b,float* a);





VOL_INDIRECTCOLORMAP*	VOL_NewIndirectColormap(VOL_VALUERANGE* indexRange,int nColors);
VOL_INDIRECTCOLORMAP*	VOL_NewIndirectColormapFromColorList(VOL_COLORLIST* colorList,int nColors);
VOL_INDIRECTCOLORMAP* 	VOL_DuplicateIndirectColormap(VOL_INDIRECTCOLORMAP* colormap);
void					VOL_DeleteIndirectColormap(VOL_INDIRECTCOLORMAP* colormap);

void					VOL_GetColorInIndirectColormap(VOL_INDIRECTCOLORMAP* colormap,float index,VOL_COLOR* color);
void					VOL_GetColorInIndirectColormapSecure(VOL_INDIRECTCOLORMAP* colormap,float index,VOL_COLOR* color);
void					VOL_GetRGBInIndirectColormap(VOL_INDIRECTCOLORMAP* colormap,float index,float* r,float* g,float* b);
void					VOL_GetRGBInIndirectColormapSecure(VOL_INDIRECTCOLORMAP* colormap,float index,float* r,float* g,float* b);
void					VOL_GetRGBAInIndirectColormap(VOL_INDIRECTCOLORMAP* colormap,float index,float* r,float* g,float* b,float* a);
void					VOL_GetRGBAInIndirectColormapSecure(VOL_INDIRECTCOLORMAP* colormap,float index,float* r,float* g,float* b,float* a);


VOL_COLORMAP*			VOL_NewColormap(int colormapType);
VOL_COLORMAP*			VOL_DuplicateColormap(VOL_COLORMAP* colormap);
void					VOL_DeleteColormap(VOL_COLORMAP* colormap);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define COLORMAP_H
