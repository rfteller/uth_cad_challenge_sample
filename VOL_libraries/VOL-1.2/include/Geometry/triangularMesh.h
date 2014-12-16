/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		triangularMesh.h:	triangular mesh


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/

#ifndef TRIANGULARMESH_H

typedef struct VolTriangularMesh
{
	int		maxTriangles;			// buffer size must be initially determined
	int		maxVertices;

	int		nTriangles;				//	number of registered triangles	<= maxTriangles
	int		nVertices;				//	number of registered vertices	<= maxVertices

	int*	triangleVertices;		//	maxTriangles x 3 (v1,v2,v3)
	float*	triangleNormals;		//	maxTriangles x 3 (v1,v2,v3)

	float*	vertexCoordinates;		//	maxVertices x 3 (x,y,z)
	float*	vertexNormals;			//	maxVertices x 3 (u,v,w)
	float*	vertexColors;			//	maxVertices x 4 (r,g,b,a)

	int*	neighbourTriangles;		// (option) maxTriangles x 3 (nt1,nt2,nt3)

	int		maxTrianglesPerVertex;	// (option)
	int*	vertexTriangles;		// (option) maxVertices x maxTrianglesPerVertex

} VOL_TRIANGULARMESH;



#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

VOL_TRIANGULARMESH*		VOL_NewTriangularMesh(int triangleBufferSize,int vertexBufferSize);
VOL_TRIANGULARMESH*		VOL_DuplicateTriangularMesh(VOL_TRIANGULARMESH* triangularMesh);
int						VOL_MinimizeBufferOfTriangularMesh(VOL_TRIANGULARMESH* triangularMesh);
void					VOL_DeleteTriangularMesh(VOL_TRIANGULARMESH* triangularMesh);

int			VOL_AddColorToTriangularMesh(VOL_TRIANGULARMESH* triangularMesh);

int			VOL_CalculateTriangleNormalsOfTriangularMesh(VOL_TRIANGULARMESH* triangularMesh);

int			VOL_GetNeighbourTrianglesOfTriangularMesh(VOL_TRIANGULARMESH* triangularMesh);
int			VOL_GetVertexTrianglesOfTriangularMesh(VOL_TRIANGULARMESH* triangularMesh,int maxTrianglesPerVertex);
int			VOL_GetVertexNormalsFromTriangleNormalsOfTriangularMesh(VOL_TRIANGULARMESH* triangularMesh);

VOL_BOX3D*	VOL_GetBoundingBoxOfTriangularMesh(VOL_TRIANGULARMESH* triangularMesh);

void		VOL_MakeTriangularMeshInsideOut(VOL_TRIANGULARMESH* triangularMesh);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define TRIANGULARMESH_H







