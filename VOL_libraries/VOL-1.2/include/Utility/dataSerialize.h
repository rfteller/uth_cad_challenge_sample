/************************************************************************************************

	VOLUME-ONE Library (VOL):

		dataSerialize.h:	data serialization


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/


//////////////////////////////////////////////////////
// Serializing Raw Volume Data
//////////////////////////////////////////////////////


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


// whole volume
int					VOL_GetSerializedSizeOfRawVolumeData(VOL_RAWVOLUMEDATA* volume);
int					VOL_SerializeRawVolumeData(VOL_RAWVOLUMEDATA* volume,void* serializedData);
VOL_RAWVOLUMEDATA*	VOL_GetRawVolumeDataFromSerializedData(void* serializedData);

// a channel of volume
int					VOL_GetSerializedSizeOfChannelOfRawVolumeData(VOL_RAWVOLUMEDATA* volume,int c);
int					VOL_SerializeChannelOfRawVolumeData(VOL_RAWVOLUMEDATA* volume,int c,void* serializedData);
int					VOL_ReplaceChannelOfRawVolumeDataBySerializedData(VOL_RAWVOLUMEDATA* volume,int c,void* serializedData);
VOL_RAWVOLUMEDATA*	VOL_GetSingleChannelRawVolumeDataFromSerializedData(void* serializedData);


// whole image
int					VOL_GetSerializedSizeOfRawImageData(VOL_RAWIMAGEDATA* image);
int					VOL_SerializeRawImageData(VOL_RAWIMAGEDATA* image,void* serializedData);
VOL_RAWIMAGEDATA*	VOL_GetRawImageDataFromSerializedData(void* serializedData);

// a channel of image
int					VOL_GetSerializedSizeOfChannelOfRawImageData(VOL_RAWIMAGEDATA* image,int c);
int					VOL_SerializeChannelOfRawImageData(VOL_RAWIMAGEDATA* image,int c,void* serializedData);
VOL_RAWIMAGEDATA*	VOL_GetSingleChannelRawImageDataFromSerializedData(void* serializedData);


// parametric objects

int					VOL_GetSerializedSizeOfSphere(VOL_SPHERE* object);
int					VOL_SerializeSphere(VOL_SPHERE* object,void* serializedData);
VOL_SPHERE*			VOL_GetSphereFromSerializedData(void* serializedData);

int					VOL_GetSerializedSizeOfEllipsoid(VOL_ELLIPSOID* object);
int					VOL_SerializeEllipsoid(VOL_ELLIPSOID* object,void* serializedData);
VOL_ELLIPSOID*		VOL_GetEllipsoidFromSerializedData(void* serializedData);

int					VOL_GetSerializedSizeOfDiamond(VOL_DIAMOND* object);
int					VOL_SerializeDiamond(VOL_DIAMOND* object,void* serializedData);
VOL_DIAMOND*		VOL_GetDiamondFromSerializedData(void* serializedData);

int					VOL_GetSerializedSizeOfCone(VOL_CONE* object);
int					VOL_SerializeCone(VOL_CONE* object,void* serializedData);
VOL_CONE*			VOL_GetConeFromSerializedData(void* serializedData);

int					VOL_GetSerializedSizeOfTube(VOL_TUBE* object);
int					VOL_SerializeTube(VOL_TUBE* object,void* serializedData);
VOL_TUBE*			VOL_GetTubeFromSerializedData(void* serializedData);

int					VOL_GetSerializedSizeOfVessel(VOL_VESSEL* object);
int					VOL_SerializeVessel(VOL_VESSEL* object,void* serializedData);
VOL_VESSEL*			VOL_GetVesselFromSerializedData(void* serializedData);

int					VOL_GetSerializedSizeOfParallelogram(VOL_PARALLELOGRAM* object);
int					VOL_SerializeParallelogram(VOL_PARALLELOGRAM* object,void* serializedData);
VOL_PARALLELOGRAM*	VOL_GetParallelogramFromSerializedData(void* serializedData);

int					VOL_GetSerializedSizeOfBox(VOL_BOX* object);
int					VOL_SerializeBox(VOL_BOX* object,void* serializedData);
VOL_BOX*			VOL_GetBoxFromSerializedData(void* serializedData);

int					VOL_GetSerializedSizeOfPolygon3D(VOL_POLYGON3D* object);
int					VOL_SerializePolygon3D(VOL_POLYGON3D* object,void* serializedData);
VOL_POLYGON3D*		VOL_GetPolygon3DFromSerializedData(void* serializedData);

int						VOL_GetSerializedSizeOfTexturedPolygon3D(VOL_TEXTUREDPOLYGON3D* object);
int						VOL_SerializeTexturedPolygon3D(VOL_TEXTUREDPOLYGON3D* object,void* serializedData);
VOL_TEXTUREDPOLYGON3D*	VOL_GetTexturedPolygon3DFromSerializedData(void* serializedData);

int					VOL_GetSerializedSizeOfPolyLine(VOL_POLYLINE* object);
int					VOL_SerializePolyLine(VOL_POLYLINE* object,void* serializedData);
VOL_POLYLINE*		VOL_GetPolyLineFromSerializedData(void* serializedData);

int					VOL_GetSerializedSizeOfLineStrip(VOL_LINESTRIP* object);
int					VOL_SerializeLineStrip(VOL_LINESTRIP* object,void* serializedData);
VOL_LINESTRIP*		VOL_GetLineStripFromSerializedData(void* serializedData);

int					VOL_GetSerializedSizeOfTubeStrip(VOL_TUBESTRIP* object);
int					VOL_SerializeTubeStrip(VOL_TUBESTRIP* object,void* serializedData);
VOL_TUBESTRIP*		VOL_GetTubeStripFromSerializedData(void* serializedData);


int					VOL_GetSerializedSizeOfTriangularMesh(VOL_TRIANGULARMESH* triangularMesh);
int					VOL_SerializeTriangularMesh(VOL_TRIANGULARMESH* triangularMesh,void* serializedData);
VOL_TRIANGULARMESH*	VOL_GetTriangularMeshFromSerializedData(void* serializedData);



int					VOL_GetSerializedSizeOfObjectGroup(VOL_OBJECTGROUP* objectGroup);
int					VOL_SerializeObjectGroup(VOL_OBJECTGROUP* objectGroup,void* serializedData);
VOL_OBJECTGROUP*	VOL_GetObjectGroupFromSerializedData(void* serializedData);




#ifdef __cplusplus
}
#endif /* __cplusplus */
