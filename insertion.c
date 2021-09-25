#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"

node *insert(node *root, int key, llNode *newRecord){
    // printf("here");

    llNode *record_pointer = NULL;
    node *leaf = NULL;

    record_pointer = find(root, key, NULL); //return one record
    
    if (record_pointer != NULL){

        addLast(record_pointer, newRecord);
        return root;
    }
    if(root == NULL){ 
        return startNewTree(key, newRecord);
    }


    leaf = findLeaf(root, key);
    
    if(leaf -> num_keys < order - 1){
        leaf = insertIntoLeaf(leaf, key, newRecord);
        return root;
    }
    return insertIntoLeafAfterSplitting(root, leaf, key, newRecord);
}
