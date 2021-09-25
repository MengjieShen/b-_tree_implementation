#######################################################################
This is the list of files in this project
#######################################################################

Makefile: for compilation
main.c: The main function with interface to run my program
dictionary.c: compute the top-k (number) more popular courses taken by all students in the semester.
insertion.c: The function used for inserting single value to the b+ tree.
function.c: All the basic implementation function for b+ tree. 
tree.h: including all the struct and function defined.

To start the program:
Step 1: Go to the directory
Step 2(optional): You can change the size and input file on line 18 in the form of 
                                ./main -k <size> -f <fileName>
Step 3: Run command line to start: "make run"
        After the program starts to run, besure to type in "in" to initiate the program
Step 4: To finish the program: type in "e" to exit
        Besure to run command line: "make clean" to remove the output file

