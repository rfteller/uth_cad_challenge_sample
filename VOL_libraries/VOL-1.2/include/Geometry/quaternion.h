////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	This is a sample code for VOLUME-ONE client development
//
//
//	Copyright (C) VOLUME-ONE developpers group 2003-
//
////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef QUATERNION_H

typedef struct VolQuaternion
{
	float	a0, a1, a2, a3;

} VOL_QUATERNION;




#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


VOL_QUATERNION*	VOL_MultiplyQuaternions(VOL_QUATERNION* a,VOL_QUATERNION* b);
VOL_QUATERNION*	VOL_GetRotationQuaternion(VOL_VECTOR3D* shaft,float angle_rad);
VOL_MATRIX*	VOL_GetRotationMatrixFromQuaternion(VOL_QUATERNION* q);



#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif


#define QUATERNION_H





