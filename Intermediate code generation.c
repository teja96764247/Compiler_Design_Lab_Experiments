#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a quadruple (operation, operand1, operand2, result)
typedef struct Quadruple {
    char operation[20];
    char operand1[20];
    char operand2[20];
    char result[20];
} Quadruple;

// Function to generate intermediate code for if statement
void generateIfIntermediateCode(char *condition, Quadruple *quadruples, int *quadIndex) {
    // Evaluate the condition
    sprintf(quadruples[*quadIndex].operation, "evaluate");
    strcpy(quadruples[*quadIndex].operand1, condition);
    quadruples[*quadIndex].operand1[strlen(condition)] = '\0'; // Ensure proper string termination
    (*quadIndex)++;

    // Jump to else part if condition is false
    sprintf(quadruples[*quadIndex].operation, "ifFalse");
    strcpy(quadruples[*quadIndex].operand1, condition);
    quadruples[*quadIndex].operand1[strlen(condition)] = '\0'; // Ensure proper string termination
    sprintf(quadruples[*quadIndex].result, "L%d", *quadIndex + 2); // Jump to end_if
    quadruples[*quadIndex].result[strlen("L")+1] = '\0'; // Ensure proper string termination
    (*quadIndex)++;
}

// Function to generate intermediate code for while statement
void generateWhileIntermediateCode(char *condition, Quadruple *quadruples, int *quadIndex) {
    // Start of the loop
    int loopStart = *quadIndex;

    // Evaluate the condition
    sprintf(quadruples[*quadIndex].operation, "evaluate");
    strcpy(quadruples[*quadIndex].operand1, condition);
    quadruples[*quadIndex].operand1[strlen(condition)] = '\0'; // Ensure proper string termination
    (*quadIndex)++;

    // Jump out of the loop if condition is false
    sprintf(quadruples[*quadIndex].operation, "ifFalse");
    strcpy(quadruples[*quadIndex].operand1, condition);
    quadruples[*quadIndex].operand1[strlen(condition)] = '\0'; // Ensure proper string termination
    sprintf(quadruples[*quadIndex].result, "L%d", *quadIndex + 2); // Jump to loop_end
    quadruples[*quadIndex].result[strlen("L")+1] = '\0'; // Ensure proper string termination
    (*quadIndex)++;

    // End of the loop
    int loopEnd = *quadIndex;

    // Statements inside the loop
    // (You can add statements here by generating intermediate code for them)

    // Jump back to the start of the loop
    sprintf(quadruples[*quadIndex].operation, "goto");
    strcpy(quadruples[*quadIndex].result, "L");
    quadruples[*quadIndex].result[strlen("L")+1] = '\0'; // Ensure proper string termination
    (*quadIndex)++;

    // Set the target for jumping out of the loop
    sprintf(quadruples[loopEnd].result, "L%d", *quadIndex);
    quadruples[loopEnd].result[strlen("L")+1] = '\0'; // Ensure proper string termination
}

int main() {
    // Example if statement
    char ifCondition[] = "x > y";
    Quadruple quadruples[20]; // Assuming a maximum of 20 quadruples
    int quadIndex = 0;

    generateIfIntermediateCode(ifCondition, quadruples, &quadIndex);

    // Example while statement
    char whileCondition[] = "i < n";
    generateWhileIntermediateCode(whileCondition, quadruples, &quadIndex);

    // Printing generated quadruples
    printf("Intermediate Code:\n");
    for (int i = 0; i < quadIndex; i++) {
        printf("%d: %s %s %s %s\n", i + 1, quadruples[i].operation, quadruples[i].operand1,
               quadruples[i].operand2, quadruples[i].result);
    }

    return 0;
}