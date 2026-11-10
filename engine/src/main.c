#include <stdio.h>
#include <string.h>
#include "logger.h"
#include "board.h"

#define BUFFER_SIZE 4096

void uci_loop(Board *b) {
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
            printf("id name RiChess eng-c-v1\n"); // type-lang-version (this is the engine, written in c, first version)
            printf("id author Rileyelirious\n");
            printf("uciok\n");
        }
        else if (strcmp(line, "isready") == 0) {
            printf("readyok\n");
        }
        else if (strcmp(line, "ucinewgame") == 0) {
            board_clear(b);
        }
        else if (strncmp(line, "position", 8) == 0) {
            parse_position(b, line);
        }
        else if (strncmp(line, "go", 2) == 0) {
            // search function
            printf("bestmove e2e4\n");
        }
        else if (strcmp(line, "quit") == 0) {
            break;
        }

        // non-uci testing commands
        else if (strcmp(line, "checkboard") == 0) {
            check_board_values(b);
        }
    }
}

int main() {
    Board b;
    board_clear(&b);
    uci_loop(&b);
    return 0;
}