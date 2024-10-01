#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 1000

char originalString[SIZE] = "";
char *commandAndArguements[SIZE];

void readFromSTDIN();
void parseInput();

int main(int argc, char const *argv[]) {
    bool running = true;

    while (running) {
        // Read input
        readFromSTDIN();

        // Check if the input is empty or exit command
        if (strlen(originalString) == 0) continue;
        if (strcmp(originalString, "exit") == 0) break;

        // Parse the input command
        parseInput();

        // Fork a new process
        pid_t pid = fork();

        if (pid == -1) {
            printf("Failed to create a child process\n");
        } else if (pid == 0) {
            // In the child process, execute the command
            if (execvp(commandAndArguements[0], commandAndArguements) == -1) {
                perror("Error executing command");
            }
            return 1;  // Exit child process if exec fails
        } else {
            // Parent process handling
            int background = 0;

            // Check if the last argument is "&"
            int lastIndex = 0;
            while (commandAndArguements[lastIndex] != NULL) lastIndex++;
            if (lastIndex > 0 && strcmp(commandAndArguements[lastIndex - 1], "&") == 0) {
                background = 1;
                commandAndArguements[lastIndex - 1] = NULL;  // Remove "&" from arguments
            }

            // Wait for the child if it's not a background process
            if (!background) {
                int status;
                waitpid(pid, &status, 0);
            }
        }
    }

    return 0;
}

void readFromSTDIN() {
    printf(">>>\t");
    fgets(originalString, SIZE, stdin);

    // Remove the newline character from the input string
    if ((strlen(originalString) > 0) && (originalString[strlen(originalString) - 1] == '\n')) {
        originalString[strlen(originalString) - 1] = '\0';
    }
}

void parseInput() {
    int argumentIndex = 0;
    char *token = strtok(originalString, " ");  // Split by space

    // Tokenize the input string and store the tokens in the argument array
    while (token != NULL) {
        commandAndArguements[argumentIndex++] = token;
        token = strtok(NULL, " ");
    }

    // NULL-terminate the argument array for execvp
    commandAndArguements[argumentIndex] = NULL;
}
