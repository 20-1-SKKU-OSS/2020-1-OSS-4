#include<stdio.h>
#define NUM_KEYS 10

enum NodeType {
	ROOT,
	INTERNAL,
	LEAF
};

typedef struct _BTreeNode{

	NodeType type;
    int Tindex;
    long long keys[NUM_KEYS];
	BTreeNode* child[NUM_KEYS+1];

} BTreeNode;


void insertKey(BTreeNode*, int, long long);
void deleteKey(BTreeNode*, int);


typedef struct _BStack{
    BTreeNode* bstack[1000];
	int bstack_c[1000];
	int top;
	int top_c;
} BStack;


typedef struct _BTree{
    BTreeNode* root = NULL;


} BTree;

void push(BStack* stackb, BTreeNode* ptr){
    stackb->top++;
    stackb->bstack[top] = ptr;

}
BTreeNode* pop(BStack* stackb){
    stackb->top--;
    return stackb->bstack[top+1]; 
}
void push_c(BStack* stackb, int c_index){
    stackb->top_c++;
    stackb->bstack_c[top_c] = c_index;

}
int pop_c(BStack* stackb){
    top_c--;
    return bstack_c[top_c+1]; 
}



void insert(BTree* btree, long long value);
void insert(BTree* btree, long long value){


    BTreeNode* ins_Node;
    long long smst;

    BStack* search_Stack = (BStack*)malloc(sizeof(BStack));
    search_Stack->top = -1;
    search_Stack->top_c = -1;

    if(root == NULL){
        BTreeNode* new_Node = (BTreeNode*)malloc(sizeof(BTreeNode));
        new_Node->type = ROOT;
        insert_in_leaf(new_Node, value);
        btree->root = new_Node;
        only_root_flag = 1;
        count++;
        return;
    }


}
