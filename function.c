#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"

// int order = ORDER;
node *queue = NULL;
bool verbose_output = false;


//Enqueue
void enqueue(node *new_node){
    node *c;
    if (queue == NULL){
        queue = new_node;
        queue -> next = NULL;
    }
 else{
    c = queue;
    while(c -> next != NULL){
        c = c-> next;
    }
    c->next = new_node;
    new_node -> next = NULL;
 }
}

// Dequeue -last in first out
node *dequeue(void){  
    node *n = queue;
    queue = queue -> next;
    n -> next = NULL;
    return n;
}

//Print the key in the leaves
void printLeaves( node *const root){
    if (root == NULL){
        printf("Empty tree. \n");
        return;
    }
    int i;
    node *c = root;
    while (!c -> is_leaf){
        c = c-> pointers[0]; 
    }

    while(true){
        for (i = 0; i < c -> num_keys; i++){
            printf("%d  ", c-> keys[i]);
        }
        if (c->pointers[order - 1]!= NULL){
            printf(" | ");
            c = c -> pointers[order -1]; 
        }else{
            break;
        }
    }
    printf("\n");
}
 // calculate the height
int height(node * const root){
    int h = 0;
    node *c = root;
    while (!c -> is_leaf){
        c = c-> pointers[0];
        h++;
    }
    return h;
}

// get length of the path to root
int pathToLeaves(node *const root, node *child){
    int length = 0;
    node *c = child;
    while (c != root){
        c = c -> parent;
        length ++;
    }
    return length;
}

// print the tree
void printTree(node *const root){ 
    node *n = NULL;
    int i = 0;
    int rank = 0;
    int new_rank = 0;
    node *parent = NULL;

    if(root == NULL){
        printf("EMPTY TREE.");
        return;

    }
    queue = NULL;
    enqueue(root);
    while (queue != NULL){
        n = dequeue();
        if (parent != n->parent){
            printf("||");
            parent = n->parent;
        };
        if (n-> parent != NULL && n == n->parent->pointers[0]){
            new_rank = pathToLeaves(root, n);
            if (new_rank != rank){
                rank = new_rank;
                printf("\n");
            }
        }
        // if (verbose_output){
        //     printf("(%p)", n);
        // }
        for (i = 0; i < n -> num_keys; i++){
            // if (verbose_output){
            //     printf("%p", n->pointers[i]); 
            // }
            printf("%d  ", n->keys[i]);
        }
        if (!n -> is_leaf){
            for (i = 0; i<= n->num_keys; i++){
                enqueue(n->pointers[i]);
            }
        }
        // if (verbose_output){
        //     if (n -> is_leaf){
        //         printf("%p", n->pointers[order-1]); //这个print的是啥
        //     }
        //     else{
        //         printf("%p", n->pointers[n -> num_keys]);
        //     }
        // }
        printf("|");

    }
    printf("\n");
}
// find the node and print it
void findAndPrint(node *const root, int key){
    // node *leaf = NULL;
    llNode *tmp;
    llNode *r = find (root,key, NULL);
    if (r == NULL){
        printf("Record not found under key %d. \n", key);
    }else{
        printf("\nRecord at %p -- key %d:\n", r, key);
        tmp = r; 
        // int count = 0;
        
        while (tmp != NULL){
            // printf("findandprinttest %s\n", tmp->next->courseID);
            // if (tmp->next == NULL){
            //     // printf("here");
            //     printf("courseID: %s, courseName: %s, grade: %s \n", tmp->courseID, tmp->courseName, tmp->grade);
            //     break;
            // }
            
            // else{
                printf("courseID: %s, courseName: %s,", tmp->courseID, tmp->courseName);
                printf("grade: %s\n", tmp->grade);
            // }
                // count ++;
            tmp = tmp -> next;
            // printf("count: %d", count);
            // printf("findandprinttest1%s\n",tmp->courseID);
        }
    }
}

// find the range 
void findRangeandPrint(node *const root, int key_start, int key_end){
    // printf("start calculate");
    int i, key;
    llNode *r;
    node *tmp;
    struct node *start = findLeaf(root, key_start);

    if (start == NULL){
        printf("None found. \n");
    }

    for (i = 0; i < start->num_keys && start->keys[i] < key_start; i++){ // get the index of the start point as i
        // printf("start->keys[i]  %d\n", start->keys[i] );
        if (i == start-> num_keys){ 
            printf("None found. \n");
        }
    }
    tmp = start;
    // printf("%d\n",i);
    while (tmp != NULL){
    for (; i < tmp -> num_keys && tmp-> keys[i] <= key_end; i++){ //assign value to returned_keys
        r = tmp -> record[i];
        key = tmp -> keys[i];
        printf("\nRecord at %p -- key %d:\n", r, key);
        llNode *cur = r; 
        // printf("findandprinttest%s\n",r->courseID);
        while (cur != NULL){
         
                printf("courseID: %s, courseName: %s, grade: %s \n", cur->courseID, cur->courseName, cur->grade);
            
            cur = cur -> next;
            // printf("findandprinttest1%s\n",tmp->courseID);
        }
    }
        tmp = tmp -> pointers[order-1]; // order - 1 = 3, the last pointer
    //finishes the whole node and walk through the link list to the next node
        i = 0;
    }
}

node *findLeaf(node *const root, int key){ //given the key we want to find and find the corresponidng record in leaf
    if (root == NULL){
            printf("Empty tree. /n");
        return root;
    }

    int i = 0;
    node *c = root; 
    // printf("find leaf inside %s", root->record[0]->courseID);
    while (!c -> is_leaf){

        i = 0;
        while (i < c -> num_keys){
            if (key >= c-> keys[i]){
                i++;
            }else{
                break;
            }
        } // loop to the key which is >= the key we want



        c = (node *) c-> pointers[i];  

    }
        // printf("%d] -> \n", c-> keys[i]);
    
    return c;
} 

llNode *find(node *root, int key, node **leaf_out){ 
    if (root == NULL){
        if (leaf_out != NULL){
            *leaf_out = NULL;
        }
        return NULL;
    }

    int i = 0;
    node *leaf = NULL;

    leaf = findLeaf(root, key); 
    // printf("leaf %s\n", leaf->record[0]->courseID);

    for (i = 0; i< leaf->num_keys; i++){ //loop to find the key
        if (leaf -> keys[i] == key){ 
            break;
        }
    }
    if (leaf_out != NULL){
        *leaf_out = leaf; // set the leaf_out to be the leaf we want to find
    }
    if (i == leaf -> num_keys){
        return NULL; //record not find
    }else{
        // printf("find, %s\n", root->record[0]->courseID);
        // if()
        // printf("find next %s\n",leaf->record[i]->next->courseID);
        return leaf ->record[i];
    }
}
//for split the node
int cut(int length){
    if (length % 2 == 0){
        return length / 2;
    }else{
        return length / 2 + 1;
    }
}

// create a new record to the record list
int addLast(struct llNode *head_ref, struct llNode *newNode){
    // newNode->next = NULL;

    //if head is NULL, it is an empty list
        struct llNode *lastNode = head_ref;
        // printf("%s\n",previous->courseID);
        while(lastNode -> next != NULL){
            lastNode = lastNode->next;
        }

        // printf("headref %s",head_ref->courseID);
        struct llNode *tmp = (struct llNode *)malloc(sizeof(llNode));
        strcpy(tmp->courseID, newNode->courseID);
    // tmp->courseID = newNode->courseID;
        strcpy(tmp->courseName, newNode->courseName);
        strcpy(tmp->grade, newNode->grade);
        // printf("add last %s\n", tmp->courseID);
        lastNode -> next = tmp;
        tmp -> next = NULL;
        // printf("addlast %s", head_ref->next->courseID);
        // previous->next = newNode;

    return 0;
}

node *makeNode(void){
    node *new_node = (node *)malloc(sizeof(node));
    if(new_node == NULL){
        perror("NODE creation");
        exit(EXIT_FAILURE);
    }
    new_node -> keys = malloc ((order - 1) * sizeof(int)); //key比pointer少一个
    if( new_node -> keys == NULL){
        perror("New node keys array.");
        exit(EXIT_FAILURE);
    }

    new_node -> pointers = malloc(order*sizeof(void *)); 
    if (new_node->pointers == NULL) {
    perror("New node pointers array.");
    exit(EXIT_FAILURE);
  }

    new_node -> record = malloc(order*sizeof(void *)); 
    if (new_node->record == NULL) {
    perror("New node pointers array.");
    exit(EXIT_FAILURE);
  }
    new_node->parent = NULL;
    new_node->is_leaf = false;
    new_node->num_keys = 0;
    new_node->next = NULL;
    return new_node;
}

node *makeLeaf(void){
    node *leaf = makeNode();
    leaf->is_leaf = true;
    return leaf;
}

//find the index of the left node
int getLeftIndex(node *parent, node *left){ 
    int left_index = 0;
    while(left_index <= parent->num_keys && parent -> pointers[left_index] != left){
        left_index ++;
    }
    return left_index;
}

node *insertIntoLeaf( node *leaf, int key, llNode *newRecord){ //在leaf_node里面加一个record //是只有正好满足条件才能用？
    int i, insertion_point;
    
    insertion_point = 0;

    struct llNode *tmp = (struct llNode *)malloc(sizeof(llNode));
    strcpy(tmp->courseID, newRecord->courseID);
    // tmp->courseID = newNode->courseID;
    strcpy(tmp->courseName, newRecord->courseName);
    strcpy(tmp->grade, newRecord->grade);

    while (insertion_point < leaf -> num_keys && leaf->keys[insertion_point] < key){  
        insertion_point ++;
    }

    leaf -> pointers[leaf -> num_keys] = leaf -> pointers[leaf -> num_keys - 1];

    for( i = leaf -> num_keys; i > insertion_point; i--){ //move everthing after insertion_point one step backward
        leaf -> keys[i] = leaf -> keys[i-1];
        leaf -> record[i] = leaf ->record[i-1];
    } 
    
    leaf -> keys[insertion_point] = key;

    leaf -> record[insertion_point] = tmp;
    leaf -> num_keys++;
    return leaf;
}

node *insertIntoLeafAfterSplitting(node *root, node *leaf, int key, llNode *newRecord){
    node *new_leaf;
    int *temp_keys; 
    llNode **temp_records;  
    void **temp_pointers;
    int insertion_index, split, new_key, i, j;

    struct llNode *tmp = (struct llNode *)malloc(sizeof(llNode));
    strcpy(tmp->courseID, newRecord->courseID);
// tmp->courseID = newNode->courseID;
    strcpy(tmp->courseName, newRecord->courseName);
    strcpy(tmp->grade, newRecord->grade);

    new_leaf = makeLeaf();
    temp_keys = malloc(order *sizeof(int)); // alloc an integer array with size of #order

    if(temp_keys == NULL){
        perror("Temporary keys array.");
        exit(EXIT_FAILURE);
    }

    temp_records = malloc((order) *sizeof(llNode *));
    if (temp_records == NULL) {
        perror("Temporary records array.");
        exit(EXIT_FAILURE);
    }

    temp_pointers = malloc((order)*sizeof(void *)); 
    if (temp_pointers == NULL) {
    perror("New node pointers array.");
    exit(EXIT_FAILURE);
  }

    insertion_index = 0;
    while( insertion_index < order - 1 && leaf -> keys[insertion_index] < key){
        insertion_index ++;
    }

    for (i = 0, j = 0; i < leaf -> num_keys; i++, j++){
        if (j == insertion_index){
            j++;
        }
        temp_keys[j] = leaf->keys[i];
        temp_records[j] = leaf -> record[i];
        temp_pointers[j] = leaf -> pointers[i];
    }

    temp_keys[insertion_index] = key;
    temp_records[insertion_index] = tmp;
    temp_pointers[insertion_index] = NULL;

    leaf -> num_keys = 0;

    split = cut(order-1);

    for(i = 0; i< split; i++){
        leaf -> record[i] = temp_records[i];
        leaf ->keys[i] = temp_keys[i];
        leaf -> pointers[i] = temp_pointers[i];
        leaf -> num_keys++;
    }

    for (i = split, j = 0; i< order; i++, j++){
        new_leaf -> record[j] = temp_records[i];
        new_leaf -> keys[j] = temp_keys[i];
        new_leaf -> pointers[j] = temp_pointers[j];
        new_leaf -> num_keys++;
    }

    free(temp_records);
    free(temp_keys);
    free(temp_pointers);

    new_leaf -> pointers[order - 1] = leaf -> pointers[order - 1]; //原本leaf 结尾指的东西现在变成new leaf 指向它
    leaf -> pointers[order - 1] = new_leaf;// 第一个leaf指向第二个leaf

    for(i = leaf->num_keys; i< order - 1; i++){ //没有被assign record 的部分指针指向null
        leaf ->pointers[i] =NULL;
        leaf -> record[i] = NULL;
    }
    for(i = new_leaf -> num_keys; i< order - 1; i++){
        new_leaf -> pointers[i] = NULL;
        new_leaf -> record[i] = NULL;
    }
    new_leaf -> parent = leaf -> parent;
    new_key = new_leaf->keys[0];

    return insertIntoParent(root, leaf, new_key, new_leaf);

}

//在node 中加入一个
node *insertIntoNode(node *root, node *n, int left_index, int key, node *right){ //在n这个node插入 //啥意思？？？

    int i;

    for( i = n-> num_keys; i > left_index; i--){
        n ->pointers[i +1] = n->pointers[i];
        n -> keys[i] = n-> keys[i-1];
    }
    n -> pointers[left_index + 1] = right;
    n -> keys[left_index] = key;
    n -> num_keys ++;
    return root;
}

//?
node *insertIntoNodeAfterSplitting( node *root, node *old_node, int left_index, int key, node *right){
    int i, j, split, k_prime;
    node *new_node, *child;
    int *temp_keys;
    node **temp_pointers;

    temp_pointers = malloc((order+1) * sizeof(node *));
    if (temp_pointers == NULL){
        exit(EXIT_FAILURE);
    }
    temp_keys = malloc(order * sizeof(int));
    if (temp_keys == NULL){
        exit(EXIT_FAILURE);
    }

    for(i = 0, j = 0; i< old_node -> num_keys + 1; i++, j++){
        if (j == left_index + 1){
            j++;
        }
        temp_pointers[j] = old_node -> pointers[i];
    }

    for(i = 0, j = 0; i< old_node -> num_keys; i++, j++){
        if (j == left_index){
            j++;
        }
        temp_keys[j] = old_node -> keys[i];
    }

    temp_pointers[left_index + 1] = right; //insert after the left node
    temp_keys[left_index] = key;

    split = cut(order);
    new_node = makeNode();
    old_node -> num_keys = 0;
    for (i = 0; i< split - 1; i++){
        old_node -> pointers[i] = temp_pointers[i]; //为什么不需要把old node没有用到的pointer设成null
        old_node -> keys[i] = temp_keys[i];
        old_node -> num_keys ++;
    }
    old_node -> pointers[i] = temp_pointers[i];
    k_prime = temp_keys[split - 1]; 
    for (++i, j = 0; i < order; i++, j++){ //++i 返回the result of i+1
        new_node -> pointers[j] = temp_pointers[i];
        new_node -> keys[j] = temp_keys[i];
        new_node -> num_keys ++;
    }
    new_node -> pointers[j] = temp_pointers[i];
    free(temp_pointers);
    free(temp_keys);
    new_node -> parent = old_node -> parent;
    for (i = 0; i<= new_node -> num_keys; i++){ //change the parent of the leaf node
        child = new_node -> pointers[i];
        child -> parent = new_node;
    }
    return insertIntoParent(root, old_node, k_prime, new_node);
}

node *insertIntoParent(node *root, node *left, int key, node *right){
    int left_index;
    node *parent;

    parent = left-> parent;
    if (parent == NULL){
        return insertIntoNewRoot(left, key, right);
    }
    left_index = getLeftIndex(parent, left);

    if(parent -> num_keys < order - 1){ //如果还有位置直接insert
        return insertIntoNode(root, parent, left_index, key, right);
    }
    return insertIntoNodeAfterSplitting(root, parent, left_index, key, right); //如果没有位置 split 后insert

}

node *insertIntoNewRoot(node *left, int key, node *right){
    node *root = makeNode();
    root -> keys[0] = key;
    root -> pointers[0] = left;
    root -> pointers[1] = right;
    root -> num_keys ++;
    root -> parent = NULL;
    left -> parent = root;
    right -> parent = root;
    return root;

}

node *startNewTree(int key, llNode *newRecord){
    node *root = makeLeaf();
    root -> keys[0] = key;
    struct llNode *tmp = (struct llNode *)malloc(sizeof(llNode));
    strcpy(tmp->courseID, newRecord->courseID);
// tmp->courseID = newNode->courseID;
    strcpy(tmp->courseName, newRecord->courseName);
    strcpy(tmp->grade, newRecord->grade);
    root -> record[0] = tmp;
    root -> pointers[0] = NULL;
    root -> pointers[order - 1] = NULL;
    root -> parent = NULL;
    root -> num_keys++;
    // printf("start new tree%s\n",root -> record[0]->courseID);
    return root;
}


void deletellNode(node *root, char* courseID, int key){
    // struct llNode *record_pointer = NULL;
    struct llNode *tmp;
    int i;
    llNode *record;
    struct node *leaf;
    struct llNode *afterNode;
    struct llNode *prevNode;

    leaf = findLeaf(root, key); 
    // printf("leaf %s\n", leaf->record[0]->courseID);

    for (i = 0; i< leaf->num_keys; i++){ //loop to find the key
        if (leaf -> keys[i] == key){ 
            break;
        }
}
    if (i == leaf -> num_keys){
        return; //record not find
    }else{
        record = leaf -> record[i];
    }

    tmp = record;
    // head = *n;
    while ( tmp!= NULL && strcmp(tmp->courseID, courseID) == 0){
        afterNode = tmp -> next;
        free(tmp);
        tmp = NULL;
        tmp = afterNode;
    }
    leaf ->record[i] = tmp;
    prevNode = tmp;
    tmp = tmp -> next;
    while(tmp != NULL){

        if(strcmp(tmp->courseID, courseID) != 0){
            prevNode = tmp;
            tmp = tmp->next;
        }
        else{
            prevNode->next = tmp->next;
            free(tmp);
            tmp = NULL;
            tmp = prevNode->next;
        }
    }
}

int free_tree(struct node* node)
{
    int i = 0;
    if (node == NULL) 
        return 0;
    
    if(!node->is_leaf){
        for (i = 0; i<= node->num_keys; i++){
            free_tree(node->pointers[i]);
        }
        free(node);
        node = NULL;
    }
    else{
        // printf("%d\n",node->num_keys);
        for (i = 0; i< node->num_keys; i++){
            // printf("%d\n",node->num_keys);
            freell(node->record[i]);
        }
        free(node);
        node = NULL;
    }
    // free(node);
    // printf("All space is free.");
    return 0;
}

int freell(struct llNode *head)
{
    struct llNode *current = NULL;
    current = head;
    while (current != NULL)
    {
        // printf("free%s\n",current->courseID);
        head = head->next;
        // current = head;
        free(current);
        current = head;
    }
    return 0;
}

void verify(node *root){
    node *n = NULL;
    node *left_childn = NULL;
    node *right_childn = NULL;
    int i = 0;
    int j = 0;
    int rank = height(root);

    if(root == NULL){
        printf("Tree is null");
        return;

    }
    queue = NULL;
    enqueue(root);
    while (queue != NULL){
        n = dequeue();
        // if (n-> parent != NULL && n == n->parent->pointers[0]){
        //     new_rank = pathToLeaves(root, n);
        //     if (new_rank != rank){
        //         rank = new_rank;
        //         printf("\n");
        //     }
        // }
        // verify that it can host at most k-1 key.
        if (n ->num_keys > order - 1){
            printf("it should host at most k-1 key.");
            return;
        }
        for (i = 0; i < n -> num_keys; i++){
            if (!n->is_leaf){
                //verify that the pointer to the right of α takes us to to keys whose values are greater or equal to α.
                right_childn = n->pointers[i+1];
                if (n->keys[i] > right_childn->keys[0]){
                    printf("the pointer to the right of α should takes us to to keys whose values are greater or equal to α.\n");
                    return;
                }
                //verify that for root and internal nodes, a pointer to the left of a specific key value α 
                //leads to other keys whose value is smaller than α
                left_childn = n->pointers[i];
                for (j = 0; j < left_childn->num_keys; j++){
                    if (n->keys[i] < left_childn->keys[j]){
                        printf("a pointer to the left of a specific key value α should lead to other keys whose value is smaller than α.\n");
                        return;
                    }
                }
            }

            //verify that for each node, there is at least a 50% utilization.
            if (n->parent != NULL && !n->is_leaf){
                for(i = 0; i < (order + 1)/2; i++){
                    if(n->pointers[i] == NULL){
                        printf("for each node, there should be at least half utilization.\n");
                        return;
                    }
            }   
            }else if(n->parent ==NULL){
                if(n->pointers[0] == NULL || n->pointers[1] ==NULL){
                    printf("At the very minimum, the root node should maintains at least 2 outgoing pointers.\n");
                    return;
                }
            }
            // else{
            //     for(i = 0; i < (order + 1)/2; i++){
            //         if(n->record[i] == NULL){
            //             // printf("i: %d\n", i);
            //             // printf("%d\n", n->keys[i]);
            //             // printf("%s", n->record[i-1]->courseID);
            //             printf("for each leaf node, there should be at least half utilization.");
            //             return;
            //         }
            //     }   
            // }
            //verify that all leaf nodes are found at the same level. The distance of this level from root is the height of the B+ tree.
            if(n->is_leaf){
                if (rank != pathToLeaves(root, n)){
                    printf("leaf nodes should be found at the same level.\n");
                    return;
                }
            }
        }
        if (!n -> is_leaf){
            for (i = 0; i<= n->num_keys; i++){
                enqueue(n->pointers[i]);
            }
        }
    }
    printf("B+ Tree properties are fullfilled\n");
    return;

}

float GPA_calculater(char* grade){
    if (strncmp(grade, "A+", 2) == 0){
                return 4;
    }
    else if((strncmp(grade, "A-", 2) == 0)){
        return 3.7;
    }
    else if(strncmp(grade, "A", 1) == 0){
        return 4;
    }
    else if(strncmp(grade, "B+", 2) == 0){
        return 3.3;
    }
    else if((strncmp(grade, "B-", 2) == 0)){
        return 2.7;
    }
    else if((strncmp(grade, "B", 2) == 0)){
        return 3;
    }
    else if((strncmp(grade, "C+", 2) == 0)){
        return 2.3;
    }
    else if((strncmp(grade, "C-", 2) == 0)){
        return 1.7;
    }
    else if((strncmp(grade, "C", 1) == 0)){
        return 2;
    }
    else if((strncmp(grade, "D+", 2) == 0)){
        return 1.3;
    }
    else if((strncmp(grade, "D-", 2) == 0)){
        return 0.7;
    }
    else if((strncmp(grade, "D", 1) == 0)){
        return 1;
    }
    else if((strncmp(grade, "F", 1) == 0)){
        return 0;
    }
    else{
        return 0;
    }
}

float compute_GPA_single(node *root, int studentID){
    llNode *record_pointer;
    char* grade;
    float GPA;
    GPA = 0;
    int num = 0;
    float average_gpa;
    // printf("here %d", studentID);
    record_pointer = find(root, studentID, NULL); 

    //if head is NULL, it is an empty list
    if(record_pointer == NULL){
        printf("empty record list!");
        return 0;
    }

    else{
        struct llNode *lastNode = record_pointer;

        while(lastNode != NULL){
            num ++;
            grade = lastNode ->grade;
            GPA = GPA + GPA_calculater(grade);
            lastNode = lastNode->next;
        }
        average_gpa = GPA/num;
        return average_gpa;
    }
}

float compute_GPA_many(node *root,int key_start, int key_end){
    // printf("start calculate");
    int i;
    float GPA = 0; 
    float average_gpa;
    // bool verbose = false;
    char* grade;
    node *tmp;
    int num_found = 0;
    struct node *start = findLeaf(root, key_start);

    if (start == NULL){
        printf("None found. \n");
    }

    for (i = 0; i < start->num_keys && start->keys[i] < key_start; i++){ // get the index of the start point as i
        // printf("start->keys[i]  %d\n", start->keys[i] );
        if (i == start-> num_keys){ 
            return 0;
        }
    }
    tmp = start;
    // printf("%d\n",i);

    while (tmp != NULL){
    
    for (; i < tmp -> num_keys && tmp-> keys[i] <= key_end; i++){ //assign value to returned_keys
        struct llNode *lastNode = tmp->record[i];
        while(lastNode != NULL){
            num_found ++;
            grade = lastNode ->grade;
            GPA = GPA + GPA_calculater(grade);
            lastNode = lastNode->next;
            // printf("GPA: %s %f\n", grade, GPA);
        }
        average_gpa = GPA/num_found;
        // return average_gpa;
    }
        tmp = tmp -> pointers[order-1]; // order - 1 = 3, the last pointer
    //finishes the whole node and walk through the link list to the next node
        i = 0;
    }
    // printf("total average %f", GPA/num_found);
    return GPA/num_found;
}
