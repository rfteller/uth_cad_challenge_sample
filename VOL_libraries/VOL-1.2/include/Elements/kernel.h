/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		kernel.h:	kernel for 3D processing such as filters


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/

#ifndef KERNEL_H

#define VOL_KERNELTYPE_SPHERICAL	0
#define VOL_KERNELTYPE_CUBIC		1
#define VOL_KERNELTYPE_FREEFORM		2

#define VOL_NEIGHBOURTYPE_4		4	// in-plane connectivity only
#define VOL_NEIGHBOURTYPE_6		6
#define VOL_NEIGHBOURTYPE_8		8	// in-plane connectivity only
#define VOL_NEIGHBOURTYPE_10	10
#define VOL_NEIGHBOURTYPE_18	18
#define VOL_NEIGHBOURTYPE_26	26


typedef struct VolKernel
{
	int		type;
	
	float	radius, radiusMax;
	int		intRad;
	
	VOL_LOCATIONARRAY*	locationArray;

	float	*distance;

	float	*weight;
	float	weightSum;

} VOL_KERNEL;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

VOL_KERNEL*	VOL_NewSphericalKernel(float radius);
VOL_KERNEL*	VOL_NewCubicKernel(int size);
VOL_KERNEL*	VOL_NewFreeFormKernel(int maxElements);
VOL_KERNEL*	VOL_NewFreeFormKernelFromRawVolumeData(VOL_RAWVOLUMEDATA* volume,int c,VOL_INTVECTOR3D* origin);

VOL_KERNEL*	VOL_NewNeighbourKernel(int neighbourType);

void		VOL_DeleteKernel(VOL_KERNEL *kernel);

void		VOL_SetKernelRadius(VOL_KERNEL* kernel, float radius);
void		VOL_SetRasterPositionOfKernelElements(VOL_KERNEL* kernel,VOL_INTSIZE3D*	matrixSize);

int			VOL_AddFreeFormKernelElement(VOL_KERNEL* kernel,VOL_INTVECTOR3D* position,float weight);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define KERNEL_H
