#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"tree.h"

// merge_sort reference :https://www.geeksforgeeks.org/merge-sort-for-linked-list/
h_node *addValueToDic(h_node *start, char* courseID){
    h_node * tmp;
    tmp = start;
    if(start == NULL){
        h_node *new_entry = (h_node *)malloc(sizeof(h_node));
        strcpy(new_entry -> courseID,courseID);
        new_entry -> frequency =1;
        new_entry -> next =NULL;
        start = new_entry;
        return start;
    }
    while(true){
        if (strcmp(tmp->courseID, courseID) == 0){
            tmp->frequency ++;
            return start;
        }
        if(tmp -> next == NULL){
            break;
        }
        tmp = tmp->next;
    }
    h_node *new_entry = (h_node *)malloc(sizeof(h_node));
    strcpy(new_entry -> courseID,courseID);
    new_entry -> frequency = 1;
    new_entry -> next =NULL;
    tmp ->next = new_entry;
    return start;
}

void MergeSort(struct h_node** headRef)
{
    struct h_node* head = *headRef;
    struct h_node* a;
    struct h_node* b;
 
    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
 
    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);
 
    /* Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);
 
    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}

struct h_node * SortedMerge(struct h_node * a, struct h_node * b)
{
    struct h_node * result = NULL;
 
    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
 
    /* Pick either a or b, and recur */
    if (a->frequency >= b->frequency) {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}

void FrontBackSplit(struct h_node* source,
                    struct h_node** frontRef, struct h_node** backRef)
{
    struct h_node* fast;
    struct h_node* slow;
    slow = source;
    fast = source->next;
 
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

void returnTopKCourse(struct h_node *root, int k){
    struct h_node *tmp;
    int count;
    count = 1;
    tmp = root;
    // printf("outside %d", root->frequency);
    if( root == NULL){
        printf("No course found");
    }

    while(count <= k && tmp != NULL){
        // printf("inside");
        printf("Top %d course: %s \n", count, tmp->courseID);
        tmp = tmp->next;
        count ++;
    }
    // return 0;
}

int free_list(struct h_node *list){
    struct h_node *nextcellptr;
    while (list != NULL){ 
        nextcellptr = list; //point to the first element of the list
        list = list -> next;   //list pointer points to the next element   
        free(nextcellptr); 
    }
    return 0;
}

void print_list(struct h_node *list){
    struct h_node *tmp;
    tmp = list;
    if (tmp == NULL){ //the case when list is empty
        printf("List is empty.\n");
        return;
    }
    while (tmp != NULL){
        printf("%s, %d ->",tmp->courseID, tmp->frequency);
        tmp = tmp->next; //print element one by one
    }
}