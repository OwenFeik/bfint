#include <stdlib.h>
#include <stdio.h>

#define MAX_PROGRAM_SIZE 30000
#define MAX_MEMORY_SIZE 30000

typedef struct StackNode {
    void *prev;
    int val;
} StackNode;

int is_instruction(char c);
void read_program(char *filename, char *program);
StackNode* get_stack_base();
void push_to_stack(StackNode** head, int val);
int pop_from_stack(StackNode** head);

int main(int argc, char *argv[]) {
    char program[MAX_PROGRAM_SIZE];
    read_program(argv[1], program);

    StackNode* head = get_stack_base();

    int mem[MAX_MEMORY_SIZE] = {0};
    int *ptr = mem;

    int skip = 0;
    int i = 0;

    char instruction;

    while ((instruction = program[i++]) != '\0') {
        if (instruction == ']') {
            if (skip)
                skip--;
            else if (*ptr)
                i = (*head).val;
            else
                pop_from_stack(&head);
        }
        else if (instruction == '[') {
            if (*ptr)
                push_to_stack(&head, i);
            else
                skip++;
        }
        else if (skip)
            {}
        else if (instruction == '>')
            ++ptr;
        else if (instruction == '<')
            --ptr;
        else if (instruction == '+')
            ++*ptr;
        else if (instruction == '-')
            --*ptr;
        else if (instruction == '.')
            putchar(*ptr);
        else if (instruction == ',')
            *ptr = getchar();
    }

    return EXIT_SUCCESS;
}

int is_instruction(char c) {
    switch (c) {
        case '>':
        case '<':
        case '+':
        case '-':
        case '.':
        case ',':
        case '[':
        case ']':
            return 1;
        default:
            return 0;
    }
}

void read_program(char *filename, char *program) {
    FILE* f;
    f = fopen(filename, "r"); // Open program file
    
    int i = 0, c;
    while ((c = getc(f)) != EOF) {
        if (is_instruction(c)) {
            program[i++] = c;
        }
    }
    program[i] = '\0';
    
    fclose(f); // Close program file
}

StackNode* get_stack_base() {
    StackNode* base = malloc(sizeof(StackNode));
    base->prev = NULL;
    base->val = 0;
    return base;
}

void push_to_stack(StackNode** head, int val) {
    StackNode* new = malloc(sizeof(StackNode));
    new->val = val;
    new->prev = *head;
    *head = new; 
}

int pop_from_stack(StackNode** head) {
    StackNode* prev = (StackNode*) (*head)->prev;

    if (prev == NULL) {
        printf("Tried to pop stack base. Exiting.\n");
        exit(EXIT_FAILURE);
    }

    int val = (*head)->val;
    free(*head);
    *head = prev;
    return val;
}
