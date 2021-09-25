extern int order;
// A linked list node

typedef struct llNode
{
    char courseID[32];
    char courseName[32];
    char grade[32];
    struct llNode *next;
} llNode;

//define a node
typedef struct node{
    void **pointers;
    struct llNode (**record);
    int *keys;
    struct node *parent;
    bool is_leaf;
    int num_keys;
    struct node *next;
}node;

typedef struct h_node{
    char courseID[32];
    int frequency;
    struct h_node *next;
}h_node;

// Enqueue
void enqueue(node *new_node);
// Dequeue
node *dequeue(void);
int height(node *const root);
int pathToLeaves(node *const root, node *child);
void printLeaves(node *const root);
void printTree(node *const root);
void findAndPrint(node *const root, int key);
// void findAndPrintRange(node *const root, int range1, int range2);
// int findRange(node *const root, int key_start, int key_end);
void findRangeandPrint(node *const root, int key_start, int key_end);
node *findLeaf(node *const root, int key);
llNode *find(node *root, int key, node **leaf_out);
int addLast(llNode *head_ref, struct llNode *newNode);
int cut(int length);
node *makeNode(void);
node *makeLeaf(void);
int getLeftIndex(node *parent, node *left);
node *insertIntoLeaf( node *leaf, int key, llNode *newRecord);
node *insertIntoLeafAfterSplitting(node *root, node *leaf, int key, llNode *newRecord);
node *insertIntoNode(node *root, node *parent,
           int left_index, int key, node *right);
node *insertIntoNodeAfterSplitting(node *root, node *parent,
                   int left_index,
                   int key, node *right);
node *insertIntoParent(node *root, node *left, int key, node *right);
node *insertIntoNewRoot(node *left, int key, node *right);
node *startNewTree(int key, llNode *newRecord);
node *insert(node *root, int key, llNode *newRecord);
void deletellNode(node *root, char* courseID, int key);
int freell(struct llNode *head);
int free_tree(struct node* node);
float compute_GPA_single(node *root, int studentID);
float compute_GPA_many(node *root,int key_start, int key_end);
float GPA_calculater(char* grade);
void verify(node *root);
h_node *addValueToDic(h_node *start, char* courseID);
void MergeSort(struct h_node** headRef);
struct h_node * SortedMerge(struct h_node * a, struct h_node * b);
void FrontBackSplit(struct h_node* source,
                    struct h_node** frontRef, struct h_node** backRef);
void returnTopKCourse(struct h_node *root, int k);
void print_list(struct h_node *list);
int free_list(struct h_node *list);