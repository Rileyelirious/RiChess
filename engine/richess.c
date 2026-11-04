#include <stdio.h>
#include <string.h>
#include "logger.c"

#define BUFFER_SIZE 4096

void uci_loop() {
    char line[BUFFER_SIZE];

    setbuf(stdout, NULL);

    while (1) {
        // If there is no input, skip
        if (!fgets(line, BUFFER_SIZE, stdin)) {
            break;
        }

        line[strcspn(line, "\r\n")] = 0;

        log_message("IN", line);

        if (strcmp(line, "uci") == 0) {
            printf("id name RiChess v1\n");
            printf("id author Rileyelirious\n");
            printf("uciok\n");
        }
        else if (strcmp(line, "isready") == 0) {
            printf("readyok\n");
        }
        else if (strcmp(line, "ucinewgame") == 0) {
            // reset game state stuff to default
        }
        else if (strncmp(line, "position", 8) == 0) {
            // put in board position
        }
        else if (strncmp(line, "go", 2) == 0) {
            // search function
            printf("bestmove e2e4\n");
        }
        else if (strcmp(line, "quit") == 0) {
            break;
        }
    }
}

int main() {
    uci_loop();
    return 0;
}