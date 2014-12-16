/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		draw.h:	drawing on volume (= set intensities in various shapes)


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/

#ifndef DRAW_H

#define VOL_VOXELDRAWINGTYPE_REPLACE			0
#define VOL_VOXELDRAWINGTYPE_REPLACE_IF_HIGHER	1
#define VOL_VOXELDRAWINGTYPE_BLEND				2

typedef struct VolVoxelDrawingContext
{
	VOL_VALUE	foreground;
	VOL_VALUE	background;
	int			drawing_type;

} VOL_VOXELDRAWINGCONTEXT;


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


void	VOL_PaintVoxel(VOL_RAWVOLUMEDATA* volume, int c, VOL_INTVECTOR3D* position, VOL_VALUE* level);
void	VOL_PaintVoxelSecure(VOL_RAWVOLUMEDATA* volume, int c, VOL_INTVECTOR3D* position, VOL_VALUE* level);

void	VOL_DrawObjectGroupInVolume(VOL_RAWVOLUMEDATA* volume, int c, VOL_OBJECTGROUP* objects, VOL_VOXELDRAWINGCONTEXT* vdc);

void	VOL_DrawBoxInVolume(VOL_RAWVOLUMEDATA* volume, int c, VOL_BOX* box, VOL_VOXELDRAWINGCONTEXT* vdc);
void	VOL_DrawSphereInVolume(VOL_RAWVOLUMEDATA* volume, int c, VOL_SPHERE* sphere, VOL_VOXELDRAWINGCONTEXT* vdc);
void	VOL_DrawEllipsoidInVolume(VOL_RAWVOLUMEDATA* volume, int c, VOL_ELLIPSOID* ellipsoid, VOL_VOXELDRAWINGCONTEXT* vdc);
void	VOL_DrawTubeInVolume(VOL_RAWVOLUMEDATA* volume, int c, VOL_TUBE* tube, VOL_VOXELDRAWINGCONTEXT* vdc);
void	VOL_DrawVesselInVolume(VOL_RAWVOLUMEDATA* volume, int c, VOL_VESSEL* vessel, VOL_VOXELDRAWINGCONTEXT* vdc);

VOL_INTBOX3D* 	VOL_GetBoundingBoxOfBox(VOL_BOX* box);
VOL_INTBOX3D* 	VOL_GetBoundingBoxOfSphere(VOL_SPHERE* sphere);
VOL_INTBOX3D* 	VOL_GetBoundingBoxOfEllipsoid(VOL_ELLIPSOID* ellipsoid);
VOL_INTBOX3D* 	VOL_GetBoundingBoxOfTube(VOL_TUBE* tube);
VOL_INTBOX3D* 	VOL_GetBoundingBoxOfVessel(VOL_VESSEL* vessel);


float	VOL_GetPartialVolumeRatioForBox(VOL_INTVECTOR3D* voxel_location,VOL_BOX* box);
float	VOL_GetPartialVolumeRatioForSphere(VOL_INTVECTOR3D* voxel_location,VOL_SPHERE* sphere);
float	VOL_GetPartialVolumeRatioForEllipsoid(VOL_INTVECTOR3D* voxel_location,VOL_ELLIPSOID* ellipsoid);
float	VOL_GetPartialVolumeRatioForTube(VOL_INTVECTOR3D* voxel_location,VOL_TUBE* tube);
float	VOL_GetPartialVolumeRatioForVessel(VOL_INTVECTOR3D* voxel_location,VOL_VESSEL* vessel);


int		VOL_CheckIfPointIsWithinBox(VOL_VECTOR3D* voxel_location,VOL_BOX* box);
int		VOL_CheckIfPointIsWithinSphere(VOL_VECTOR3D* voxel_location,VOL_SPHERE* sphere);
int		VOL_CheckIfPointIsWithinEllipsoid(VOL_VECTOR3D* voxel_location,VOL_ELLIPSOID* ellipsoid);
int		VOL_CheckIfPointIsWithinTube(VOL_VECTOR3D* voxel_location,VOL_TUBE* tube);
int		VOL_CheckIfPointIsWithinVessel(VOL_VECTOR3D* voxel_location,VOL_VESSEL* vessel);





#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif

#define DRAW_H

