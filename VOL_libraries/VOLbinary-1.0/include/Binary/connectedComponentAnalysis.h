/***********************************************************************************

	Volume One Library (VOL):

		connectedComponentAnalysis.h

***********************************************************************************/

#ifndef CONNECTEDCOMPONENTANALYSIS_H



#define VOL_CC_PROPERTY_ID_VOXELCOUNT	-1


#define VOL_MAX_NUM_COMPONENT_PROPERTIES	256


typedef struct VolComponentData
{
	VOL_RAWVOLUMEDATA*	analyzedVolume;		// single channel uint32 volume

	int					componentChannel;

	unsigned int		nComponents;

	unsigned int*		nVoxelsOfComponents;

	// extra properties
	int					nProperties;
	float**				componentProperties;

} VOL_COMPONENTDATA;


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


VOL_COMPONENTDATA*	VOL_NewComponentData( VOL_RAWVOLUMEDATA* rawVolumeData, int c, unsigned int nComponents );
void				VOL_DeleteComponentData(VOL_COMPONENTDATA* componentData);

int		VOL_SortComponentsByProperty( VOL_COMPONENTDATA* componentData, int propertyID );
int		VOL_ExtractComponent(VOL_COMPONENTDATA* componentData,unsigned int componentID);
int		VOL_RemoveComponent(VOL_COMPONENTDATA* componentData,unsigned int componentID);
int		VOL_ExtractComponents(VOL_COMPONENTDATA* componentData,unsigned int nSelectedComponents,unsigned int* componentIDs);
int		VOL_RemoveComponents(VOL_COMPONENTDATA* componentData,unsigned int nRemovedComponents,unsigned int* componentIDs);

VOL_RAWVOLUMEDATA*	VOL_CopyComponentVolume(VOL_COMPONENTDATA* componentData,unsigned int nSelectedComponents,unsigned int* componentIDs);

unsigned int	VOL_ConnectedComponentAnalysis( VOL_RAWVOLUMEDATA* rawVolumeData, int c, int neighbourType );	// just labelling binary volume
unsigned int	VOL_ConnectedComponentAnalysisUINT32( VOL_RAWVOLUMEDATA* rawVolumeData, int c, int neighbourType );	// just labelling binary volume

void			VOL_RemoveCavity( VOL_RAWVOLUMEDATA* rawVolumeData, int c);							// utility

void			VOL_GetCenterOfGravityOfComponent( VOL_COMPONENTDATA* componentData, unsigned int componentID, VOL_VECTOR3D* cog);
void			VOL_GetBoundingBoxOfComponent( VOL_COMPONENTDATA* componentData, unsigned int componentID, VOL_INTBOX3D* box);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define CONNECTEDCOMPONENTANALYSIS_H
