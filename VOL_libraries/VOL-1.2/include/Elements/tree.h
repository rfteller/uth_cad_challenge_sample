/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		tree.h:	tree structure


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

			memo:	will be refined by using STL
					"There is no tree without root."
					"There exist trees with many root nodes"

************************************************************************************************/


#ifndef TREE_H


#define VOL_TREENODE_TYPE_NONE				100
#define VOL_TREENODE_TYPE_ROOT				211
#define VOL_TREENODE_TYPE_ROOT_OF_SUBTREE	212
#define VOL_TREENODE_TYPE_EDGE				311
#define VOL_TREENODE_TYPE_EDGE_TO_SUBTREE	312
#define VOL_TREENODE_TYPE_ON_BRANCH			411
#define VOL_TREENODE_TYPE_BIFURCATION		511



typedef struct VolTreeNode
{
	VOL_LIST*	connectedNodeList;

	int		type;

	// Optional. Valid if only one root exists
	int		distanceFromRoot;
	int		bifurcationLevelFromRoot;

	int		flag;

	// user data attachment
	void*	data;

} VOL_TREENODE;


typedef struct VolTreeNodeList VOL_TREENODELIST;


#define VOL_TREEBRANCH_DIRECTIONTYPE_NONE		125
#define VOL_TREEBRANCH_DIRECTIONTYPE_1_TO_2		353
#define VOL_TREEBRANCH_DIRECTIONTYPE_2_TO_1		151
#define VOL_TREEBRANCH_DIRECTIONTYPE_NEUTRAL	747


typedef struct VolTreeBranch
{
	VOL_TREENODE*	node1;
	VOL_TREENODE*	node2;

	int		directionType;

	int		flag;

	// user data attachment
	void*	data;

} VOL_TREEBRANCH;


typedef struct VolTree
{
	VOL_LIST*	nodeList;		// list of node

	VOL_LIST*	branchList;		// list of branch

	VOL_LIST*	rootNodeList;

	VOL_LIST*	subTreeList;		// array of pointer

	int		flag;

	// user data attachment
	void*	data;

} VOL_TREE;




#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

VOL_TREENODE*		VOL_NewTreeNode();
VOL_TREEBRANCH*		VOL_NewTreeBranch();
VOL_TREE*			VOL_NewTree();

VOL_TREENODE*		VOL_NewNodeAddedToTree(VOL_TREE* tree);
VOL_TREEBRANCH*		VOL_NewBranchAddedToTree(VOL_TREE* tree);

void	VOL_DeleteTree(VOL_TREE* tree);
void	VOL_DeleteTreeBranch(VOL_TREEBRANCH* treeBranch);
void	VOL_DeleteTreeNode(VOL_TREENODE* treeNode);


VOL_TREEBRANCH*		VOL_AddNodeToTree(VOL_TREE* tree,VOL_TREENODE* connectedNode,VOL_TREENODE* addedNode);
int					VOL_RemoveNodeOfTree(VOL_TREE* tree,VOL_TREENODE* node,void** nodeData,void** branchData);
int					VOL_SubdivideTreeBranch(VOL_TREE* tree,VOL_TREEBRANCH* branch,VOL_TREENODE** newNode,VOL_TREEBRANCH** newBranch);

int					VOL_CheckIfNodeIsMemberOfTree(VOL_TREENODE* node,VOL_TREE* tree);
int					VOL_CheckIfNodeIsRootOfTree(VOL_TREENODE* node,VOL_TREE* tree);
int					VOL_CheckIfBranchIsMemberOfTree(VOL_TREEBRANCH* branch,VOL_TREE* tree);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define TREE_H




