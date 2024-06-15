#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define STACK_SIZE 100

char stack[STACK_SIZE][PATH_MAX];  // Assuming PATH_MAX is large enough
int top = -1;

void pushd(const char *dir) {
    if (top == STACK_SIZE - 1) {
        fprintf(stderr, "Stack overflow\n");
        return;
    }
    
    top++;
    strncpy(stack[top], dir, PATH_MAX - 1);
    stack[top][PATH_MAX - 1] = '\0';
    
    // Change directory
    if (chdir(dir) != 0) {
        fprintf(stderr, "Error: Cannot change directory to %s\n", dir);
        top--;
    }
}

void popd() {
    if (top == -1) {
        fprintf(stderr, "Stack underflow\n");
        return;
    }
    
    // Change directory to the top of the stack
    if (chdir(stack[top]) != 0) {
        fprintf(stderr, "Error: Cannot change directory to %s\n", stack[top]);
    }
    
    top--;
}

void print_stack() {
    printf("Directory stack:\n");
    for (int i = top; i >= 0; i--) {
        printf("%s\n", stack[i]);
    }
}

int main() {
    char command[100];
    char dir[PATH_MAX];
    
    while (1) {
        printf("Enter command (pushd, popd, dirs, quit): ");
        scanf("%s", command);
        
        if (strcmp(command, "pushd") == 0) {
            scanf("%s", dir);
            pushd(dir);
        } else if (strcmp(command, "popd") == 0) {
            popd();
        } else if (strcmp(command, "dirs") == 0) {
            print_stack();
        } else if (strcmp(command, "quit") == 0) {
            break;
        } else {
            printf("Invalid command\n");
        }
        
        // Clear stdin buffer
        while (getchar() != '\n');
    }
    
    return 0;
}

