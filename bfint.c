#include <stdio.h>

int main(int argc, char *argv[]) {

    char* filename = argv[1];
    FILE* fp;

    char program[1000]; // 1000 chars is max program size

    fp = fopen(filename, "r"); // Open program file
    
    int i = 0;
    int depth_limit = 0; // Loop depth limit
    while (1) {
        // Read each character from file into program array

        char inchar = fgetc(fp);
        
        program[i] = inchar;

        // -1 istruction indicates program finish
        if (inchar != -1) {
            i++;
            if (inchar == *"[") {
                depth_limit++;
            }
        }
        else {
            break;
        }
    }
    
    fclose(fp); // Close program file

    int mem[30000] = {0}; // Program memory
    int *ptr = mem; // Beginning of memory

    int stack[depth_limit]; // depth_limit is number of '[', indicates maximum stack size
    int stack_depth = 0; // Current stack layer
    int skip = 0; // Skip to end of loop

    i = 0;

    while (1) {
        char instruction = program[i];

        if (instruction == -1) {
            break;
        }
        else if (instruction == *"]") {
            if (skip) {
                // The loop never executed
                stack_depth--;
                skip = 0;
            }
            else if (*ptr) {
                // Loop again
                i = stack[stack_depth - 1];
            }
            else {
                // Finished looping
                stack_depth--;
            }
        }
        else if (skip) {
            // Skipping to end of loop
        }
        else if (instruction == *"[") {                
            stack[stack_depth] = i;
            // record start position of loop

            if (*ptr) {
                // execute loop
                stack_depth++;
            }
            else {
                // ptr False, skip loop
                skip = 1;
            }
        }
        else if (instruction == *">") {
            // Move pointer up
            ptr++;
        }
        else if (instruction == *"<") {
            // Move pointer down
            ptr--;
        }
        else if (instruction == *"+") {
            // Increment value at pointer
            ++*ptr;
        }
        else if (instruction == *"-") {
            // Decrement value at pointer
            --*ptr;
        }
        else if (instruction == *".") {
            // Print value at pointer          
            putchar(*ptr);
        }
        else if (instruction == *",") {
            // Read value to pointer
            *ptr = getchar();
        }

        i++; // Next instruction
    }

    return 0;
}
