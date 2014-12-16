/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		parametricPrimitive.h:	various shapes


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/

#ifndef PARAMETRICPRIMITIVE_H


#define VOL_PRIMITIVETYPE_NONE						0

#define VOL_PRIMITIVETYPE_SPHERE					11
#define VOL_PRIMITIVETYPE_ELLIPSOID					12
#define VOL_PRIMITIVETYPE_TUBE						13
#define VOL_PRIMITIVETYPE_VESSEL					14
#define VOL_PRIMITIVETYPE_PARALLELOGRAM				15
#define VOL_PRIMITIVETYPE_BOX						16
#define VOL_PRIMITIVETYPE_DIAMOND					17
#define VOL_PRIMITIVETYPE_CONE						18

#define VOL_PRIMITIVETYPE_TORUS						19	// new

#define VOL_PRIMITIVETYPE_POLYGON3D					21
#define VOL_PRIMITIVETYPE_TEXTUREDPOLYGON3D			22

#define VOL_PRIMITIVETYPE_VOLTEXPOLYGONS3D			25

#define VOL_PRIMITIVETYPE_POLYLINE					31


#define VOL_PRIMITIVETYPE_LINESTRIP					61	// w color
#define VOL_PRIMITIVETYPE_TUBESTRIP					62	// w color

#define VOL_PRIMITIVETYPE_TRIANGULARMESH			71	// w color


#define VOL_PRIMITIVETYPE_OBJECTGROUP				99


#define VOL_GRAPHICOBJECT_RENDERTYPE_WIRE				187
#define VOL_GRAPHICOBJECT_RENDERTYPE_SOLID				142
#define VOL_GRAPHICOBJECT_RENDERTYPE_WIRE_AND_SOLID		121


#define VOL_GRAPHICOBJECT_MINIMUM_PRECISION				3
#define VOL_GRAPHICOBJECT_DEFAULT_PRECISION				8
#define VOL_GRAPHICOBJECT_MAXIMUM_PRECISION				64




typedef struct VolSphere
{
	VOL_VECTOR3D*	center;
	float			r;
	int				precision;
	int				renderType;

} VOL_SPHERE;


typedef struct VolEllipsoid
{
	VOL_VECTOR3D*	center;
	VOL_VECTOR3D*	e1;
	VOL_VECTOR3D*	e2;
	VOL_VECTOR3D*	e3;
	float			r1, r2, r3;
	int				precision;
	int				renderType;

} VOL_ELLIPSOID;



typedef struct VolTube
{
	VOL_VECTOR3D*	node1;
	VOL_VECTOR3D*	node2;
	float			r1, r2;
	int				precision;
	int				renderType;

} VOL_TUBE;

typedef struct VolVessel
{
	VOL_VECTOR3D*	node1;	// position
	VOL_VECTOR3D*	node2;	// position
	float			uR1, vR1;
	float			uR2, vR2;
	VOL_VECTOR3D	*u1, *v1;
	VOL_VECTOR3D	*u2, *v2;
	int				precision;
	int				renderType;

} VOL_VESSEL;

typedef struct VolParallelogram
{
	VOL_VECTOR3D*	origin;
	VOL_VECTOR3D*	v1;
	VOL_VECTOR3D*	v2;
	int				renderType;

} VOL_PARALLELOGRAM;

typedef struct VolBox
{
	VOL_VECTOR3D*	origin;
	VOL_VECTOR3D*	v1;
	VOL_VECTOR3D*	v2;
	VOL_VECTOR3D*	v3;
	int				renderType;

} VOL_BOX;

typedef struct VolDiamond
{
	VOL_VECTOR3D*	center;
	VOL_VECTOR3D*	e1;
	VOL_VECTOR3D*	e2;
	VOL_VECTOR3D*	e3;
	float			s1, s2, s3;
	int				precision;
	int				renderType;

} VOL_DIAMOND;

typedef struct VolCone
{
	VOL_VECTOR3D*	center;
	VOL_VECTOR3D*	normal;
	float			r, h;
	int				precision;
	int				renderType;

} VOL_CONE;


typedef struct VolTorus
{
	VOL_VECTOR3D*	center;
	VOL_VECTOR3D*	normal;
	float			R, r;
	int				precision;
	int				renderType;

} VOL_TORUS;


typedef struct VolPolygon2D
{
	int				nVertices;
	VOL_VECTOR2D**	vertices;

	VOL_BOX2D*		boundingBox;

	int				renderType;

} VOL_POLYGON2D;

typedef struct VolPolygon3D
{
	int				nVertices;
	VOL_VECTOR3D**	vertices;

	VOL_BOX3D*		boundingBox;

	int				renderType;

} VOL_POLYGON3D;

typedef struct VolTexturedPolygon3D
{
	VOL_POLYGON3D*	polygon3D;

	VOL_POLYGON2D*	polygon2D;

	VOL_VECTOR3D*	uvOrigin;

	VOL_VECTOR3D*	u;
	VOL_VECTOR3D*	v;

	VOL_RAWIMAGEDATA*	textureImage;			// 2D
	int					textureSerialID;
	VOL_INTSIZE2D*		textureTruncatedSize;

	int				renderType;

} VOL_TEXTUREDPOLYGON3D;

typedef struct VolVolumeTexturedPolygons3D
{
	int				nPolygons;

	VOL_POLYGON3D**	polygon3D;

	VOL_POLYGON3D**	texCoords3D;

	VOL_VECTOR3D*	uvwOrigin;

	VOL_VECTOR3D*	u;
	VOL_VECTOR3D*	v;
	VOL_VECTOR3D*	w;

	VOL_RAWVOLUMEDATA*	textureVolume;			// 2D
	int					textureSerialID;
	VOL_INTSIZE3D*		textureTruncatedSize;

	int				renderType;

} VOL_VOLTEXPOLYGONS3D;


typedef struct VolPolyLine
{
	int				nLines;
	VOL_VECTOR3D**	from;
	VOL_VECTOR3D**	to;

} VOL_POLYLINE;


typedef struct VolLineStrip
{
	int				nVertices;
	int				maxVertices;
	VOL_VECTOR3D	*vertices;
	VOL_COLOR		*colors;

} VOL_LINESTRIP;


typedef struct VolTubeStrip
{
	int				nNodes;
	int				maxNodes;
	VOL_VECTOR3D	*nodes;
	float			*r;
	VOL_COLOR		*colors;
	int				precision;
	int				renderType;

} VOL_TUBESTRIP;

typedef struct VolObjectGroup
{
	int			nObjects;
	int			maxObjects;
	void**		objects;
	int*		objectTypes;
	int*		objectVisibility;
	VOL_COLOR**	objectColors;

} VOL_OBJECTGROUP;







#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


// sphere
VOL_SPHERE*				VOL_NewSphere(VOL_VECTOR3D* center,float r);
void					VOL_DeleteSphere(VOL_SPHERE* sphere);

// ellipsoid
VOL_ELLIPSOID*			VOL_NewEllipsoid(VOL_VECTOR3D* center,VOL_VECTOR3D* e1,VOL_VECTOR3D* e2,VOL_VECTOR3D* e3,float r1,float r2,float r3);
void					VOL_DeleteEllipsoid(VOL_ELLIPSOID* ellipsoid);

// tube
VOL_TUBE*				VOL_NewTube(VOL_VECTOR3D* node1,VOL_VECTOR3D* node2,float r1,float r2);
VOL_TUBE*				VOL_NewTubeBetween2Spheres(VOL_SPHERE* sphere1,VOL_SPHERE* sphere2);
void					VOL_DeleteTube(VOL_TUBE* tube);

// vessel
VOL_VESSEL*				VOL_NewVessel(	VOL_VECTOR3D* node1, VOL_VECTOR3D* node2,
										float ur1, float vr1, float ur2, float vr2,
										VOL_VECTOR3D* u1, VOL_VECTOR3D* v1,
										VOL_VECTOR3D* u2, VOL_VECTOR3D* v2);
void					VOL_DeleteVessel(VOL_VESSEL* vessel);

// parallelogram
VOL_PARALLELOGRAM*		VOL_NewParallelogram(VOL_VECTOR3D* origin,VOL_VECTOR3D* v1,VOL_VECTOR3D* v2);
void					VOL_DeleteParallelogram(VOL_PARALLELOGRAM* parallelogram);

// box
VOL_BOX*				VOL_NewBox(VOL_VECTOR3D* origin,VOL_VECTOR3D* v1,VOL_VECTOR3D* v2,VOL_VECTOR3D* v3);
void					VOL_DeleteBox(VOL_BOX* box);

// diamond
VOL_DIAMOND*			VOL_NewDiamond(VOL_VECTOR3D* center,VOL_VECTOR3D* e1,VOL_VECTOR3D* e2,VOL_VECTOR3D* e3,float s1,float s2,float s3);
void					VOL_DeleteDiamond(VOL_DIAMOND* diamond);

// cone
VOL_CONE*				VOL_NewCone(VOL_VECTOR3D* center,VOL_VECTOR3D* normal,float r,float h);
void					VOL_DeleteCone(VOL_CONE* cone);

// torus
VOL_TORUS*				VOL_NewTorus(VOL_VECTOR3D* center,VOL_VECTOR3D* normal,float R,float r);
void					VOL_DeleteTorus(VOL_TORUS* torus);

// polygon2D
VOL_POLYGON2D*			VOL_NewPolygon2D(int nVertices);
void					VOL_DeletePolygon2D(VOL_POLYGON2D* polygon);

// polygon3D
VOL_POLYGON3D*			VOL_NewPolygon3D(int nVertices);
void					VOL_DeletePolygon3D(VOL_POLYGON3D* polygon);

// texpolygon 3D
VOL_TEXTUREDPOLYGON3D*	VOL_NewTexturedPolygon3D(int nVertices);
void					VOL_DeleteTexturedPolygon3D(VOL_TEXTUREDPOLYGON3D* polygon);



// VolTexPolygon3D
VOL_VOLTEXPOLYGONS3D*	VOL_NewVolumeTexturedPolygon3D(int nVertices,int nPolygons);
void					VOL_DeleteVolumeTexturedPolygon3D(VOL_VOLTEXPOLYGONS3D* polygon);



// polyline
VOL_POLYLINE*			VOL_NewPolyLine(int maxLines);
void					VOL_DeletePolyLine(VOL_POLYLINE* polyLine);

// line strip
VOL_LINESTRIP*			VOL_NewLineStrip(int maxVertices);
int						VOL_AddColorToLineStrip(VOL_LINESTRIP* lineStrip);
void					VOL_DeleteLineStrip(VOL_LINESTRIP* lineStrip);

// tube strip
VOL_TUBESTRIP*			VOL_NewTubeStrip(int maxNodes);
int						VOL_AddColorToTubeStrip(VOL_TUBESTRIP* tubeStrip);
void					VOL_DeleteTubeStrip(VOL_TUBESTRIP* tubeStrip);

// group
VOL_OBJECTGROUP*		VOL_NewObjectGroup(int maxObjects);
void					VOL_DeleteObjectGroup(VOL_OBJECTGROUP* objectGroup);
int						VOL_AddObjectToGroup(void* object,int type,VOL_COLOR* color,VOL_OBJECTGROUP* objectGroup);




#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif

#define PARAMETRICPRIMITIVE_H
