/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		list.h:	list structure


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

			memo:	will be refined by using STL

************************************************************************************************/

#ifndef LIST_H


typedef struct VolListNode
{
	struct VolListNode* next;
	struct VolListNode* previous;

	// user data attachment
	void*	data;

} VOL_LISTNODE;

typedef struct VolList
{
	int				nNodes;
	VOL_LISTNODE*	firstNode;
	VOL_LISTNODE*	endNode;

	// user data attachment
	void*	data;

} VOL_LIST;


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

VOL_LIST*		VOL_NewList();
VOL_LISTNODE*	VOL_NewListNode();
VOL_LISTNODE*	VOL_NewNodeAddedToList(VOL_LIST* list);		// as last
VOL_LISTNODE*	VOL_NewNodeAppendedToList(VOL_LIST* list);	// as first

void	VOL_DeleteListNode(VOL_LISTNODE* listNode);
void	VOL_DeleteList(VOL_LIST* list);

VOL_LIST*		VOL_NewListWithNodes(int numNodes);

int		VOL_AddNodeToList(VOL_LISTNODE* node,VOL_LIST* list);		// as last
int		VOL_AppendNodeToList(VOL_LISTNODE* node,VOL_LIST* list);	// as first
int		VOL_InsertNodeToList(VOL_LISTNODE* node,VOL_LIST* list,VOL_LISTNODE* insertedNextToThis);
int		VOL_RemoveNodeFromList(VOL_LISTNODE* node,VOL_LIST* list);
int		VOL_DeleteNodeInList(VOL_LISTNODE* node,VOL_LIST* list);

int		VOL_CheckIfNodeIsMemberOfList(VOL_LISTNODE* node,VOL_LIST* list);



VOL_LISTNODE*	VOL_SearchListNodeByData(void* data,VOL_LIST* list);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif



#define LIST_H
