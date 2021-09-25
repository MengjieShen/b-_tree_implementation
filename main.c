#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"
int order;

int main(int argc, char *argv[]){
    FILE * fp;
    char getcourseID[32];
    char getcourseName[32];
    char getgrade[32];
    // char addValueCourseID[32];
    node *root;
    char* file;
    bool isFile = false;
    char input[100];
    root = NULL;
    struct h_node *h_root = NULL;
    bool exit = false;
    for (int i = 1; i < argc; i++)
    {  
        if (i + 1 != argc)
        {
            if (strcmp(argv[i], "-k") == 0) // This is your parameter name
            {
                // printf("here");                 
                order = atoi(argv[i+1]);
                // printf("order: %d", order);

            }
            if(strcmp(argv[i], "-f") == 0) {
                file = argv[i+1];
                isFile = true;
                // printf("file: %s ", file);
                
            }
        }
    }
    while (!exit){
        //initialize all structures of your program.
        printf("in: initialize all structures of your program.\n"); 
        printf("i <studID><courseID><courseName><Grade>: insert all pertitnent data for a specific course that a student (with <studID>) has taken.\n");
        printf("f <studID>: find all information found on the B+ tree-based structure regarding student with <studID>.\n");
        printf("r <studIDa> <studIDb>: fetch and display all information for students whose IDs range from <studIDa> to <studIDb>.\n");
        printf("g <studID> or g <studIDa> <studIDb>: compute the gpa of a specific student or the average gpa of students in the range <studIDa> to <studIDb>.\n");
        printf("t k:compute the top-k (number) more popular courses taken by all students in the semester.\n");
        printf("v:verify all nodes of the indexing structure comply with B+ tree properties.\n");
        printf("d <studID><courseID>: delete the specific course for the student indicated by <studID>.\n");
        printf("o: output the content of the B+ tree in a readable text format.\n");
        printf("e: free all space allocated gracefully and exit the application.\n");
        printf("Please input a command:\n");

        scanf("%[^\n]%*c", &input);

        char * cur = strtok(&input, " ");
        // printf("cur: %s", cur);
        if (strcmp(cur, "in") == 0){
            // order = atoi(argv[2]);
            // char* file = strtok(NULL, " ");
            // char * file = argv[4];
            if (isFile){
            FILE * fp = fopen(file, "r");
            if (!fp){
                    printf("Can't open file\n");
                }
            else {
                char buffer[1024];
                int row = 0;
                while((fscanf(fp, "%[^\n]\n", buffer))!= EOF){
                    struct llNode *student = (struct llNode *)malloc(sizeof(llNode));
                    // printf("student: %p",student);
                    if (student == NULL){
                        printf("error of allocation\n");
                    }
                    int key = atoi(strtok(buffer, ","));
                    char *getcourseID = strtok(NULL, ",");
                    strcpy(student->courseID, getcourseID);
                    char *getcourseName = strtok(NULL, ",");
                    strcpy(student->courseName, getcourseName);
                    char *getgrade = strtok(NULL, ",");
                    strcpy(student->grade, getgrade);
                    h_root = addValueToDic(h_root, getcourseID);
                    root = insert(root, key, student);
                    free(student);
                    student = NULL;
                    row++;
                }
            fclose(fp);
            }
            // exit = true;
        }
        printf("Successfully initiated!\n");
        }
            // printf("cur: %s", cur);

        else if(strcmp(cur, "i") == 0){
                struct llNode *student = (struct llNode *)malloc(sizeof(llNode));
                if (student == NULL){
                    printf("error of allocation\n");
                }
                int key = atoi(strtok(NULL, " "));
                char *getcourseID = strtok(NULL, " ");
                strcpy(student->courseID, getcourseID);
                char *getcourseName = strtok(NULL, " ");
                strcpy(student->courseName, getcourseName);
                char *getgrade = strtok(NULL, " ");
                strcpy(student->grade, getgrade);
                h_root = addValueToDic(h_root, getcourseID);
                root = insert(root, key, student);
                free(student);
                student = NULL;
                printf("successfully inserted!\n");
            }
            // find all information found on the B+ tree-based structure regarding student with <studID>.
            // f <studID>
            else if(strcmp(cur, "f") == 0){
                // char* input;
                char * student = strtok(NULL, " ");
                findAndPrint(root, atoi(student));
            }
            //r <studIDa> <studIDb>
            //fetch and display all information for students whose IDs range from <studIDa> to <studIDb>.
            else if(strcmp(cur, "r") == 0){
                int studIDa = atoi(strtok(NULL, " "));
                int studIDb = atoi(strtok(NULL, " "));
                printf("%d, %d", studIDa, studIDb);
                findRangeandPrint(root, studIDa, studIDb);
            } 

            //g <studID> or g <studIDa> <studIDb>
            //compute GPA
            else if(strcmp(cur, "g") == 0){
                float GPA;
                char* studIDa = strtok(NULL, " ");
                char* studIDb = strtok(NULL, " ");
                int start = atoi(studIDa);

                if(studIDb != NULL){
                    int end = atoi(studIDb);
                    GPA = compute_GPA_many(root,start,end);
                    printf("Average GPA: %f\n", GPA);
                    // float GPA;
                }
                else{
                    GPA = compute_GPA_single(root, start);
                    printf("Average GPA: %f\n", GPA);
                }
            }
            //return top k
            else if(strcmp(cur, "t") == 0){
                char* k = strtok(NULL, " ");
                // printf("here");
                MergeSort(&h_root);
                // printf("%d", h_root->frequency);
                returnTopKCourse(h_root, atoi(k));
            }
            
            //verify 
            else if(strcmp(cur, "v") == 0){
                verify(root);
            }
            //delete
            else if(strcmp(cur, "d") == 0){
                char* studID = strtok(NULL, " ");
                char* courseID = strtok(NULL, " ");
                deletellNode(root, courseID, atoi(studID));
                printf("successfully delete\n");
            }
            //output the content of the tree
            else if(strcmp(cur, "o") == 0){
                printTree(root);
            }
            
            else if(strcmp (cur, "e") == 0){
                free_list(h_root);
                free_tree(root);
                exit = true;
                return 0;
            }

        
    }
    }