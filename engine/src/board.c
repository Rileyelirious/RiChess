#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "board.h"

static const int EMPTY_BOARD[120] = {
    OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD,
    OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD,
    OFFBOARD, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, OFFBOARD,
    OFFBOARD, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, OFFBOARD,
    OFFBOARD, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, OFFBOARD,
    OFFBOARD, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, OFFBOARD,
    OFFBOARD, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, OFFBOARD,
    OFFBOARD, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, OFFBOARD,
    OFFBOARD, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, OFFBOARD,
    OFFBOARD, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, OFFBOARD,
    OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD,
    OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD, OFFBOARD,
};

void board_clear(Board *b) {
    *b = (Board){0};

    // set to the empty board template
    for (int i = 0; i<120; i++) {
        b->squares[i] = EMPTY_BOARD[i];
    }

    // init en passant square and king squares
    b->ep_square = NO_SQUARE;
    b->king_sq[WHITE] = NO_SQUARE;
    b->king_sq[BLACK] = NO_SQUARE;
}

void board_print(const Board *b) {
    for (int i = 0; i<120; i++) {
        if (i%10==0) printf("\n");
        printf("%d ", b->squares[i]);
    }
    printf("\n");
}

void check_board_values(const Board *b) {
    board_print(b);
    printf("Side: %d\n", b->side);
    printf("Castle Rights: %d\n", b->castle_rights);
    printf("En Passant Square: %d\n", b->ep_square);
    printf("Halfmove: %d\n", b->halfmove);
    printf("Fullmove: %d\n", b->fullmove);
    printf("King Squares: %d %d\n", b->king_sq[0], b->king_sq[1]);
}

void make_move(Board *b, int from, int to) {
    b->squares[to] = b->squares[from];
    b->squares[from] = EMPTY;
}

void fen_to_board(Board *b, char fen[]) {
    int board_pointer = 21; // first square on 8th rank for fen
    char *token = strtok(fen, " "); // this becomes the position part of the string (ideally)
    if (token == NULL) return;
    
    // turn 8 ranks notation on fen string to pieces on the board
    int rank_offset = 0;
    for (int i = 0; token[i] != '\0'; i++) {
        if (token[i] == '/') {
            board_pointer += 10; // to next rank!
            rank_offset = 0;
            continue;
        }

        int num = (int)(token[i] - '0');
        if (num > 0 && num < 9) {
            for (int j = 0; j<num; j++) {
                b->squares[board_pointer+rank_offset] = EMPTY;
                rank_offset++;
            }
        }
        else {
            switch (token[i]) { // translate fen pieces to boardrep pieces
                case 'P':
                    b->squares[board_pointer+rank_offset] = wP;
                    break;
                case 'p':
                    b->squares[board_pointer+rank_offset] = bP;
                    break;
                case 'N':
                    b->squares[board_pointer+rank_offset] = wN;
                    break;
                case 'n':
                    b->squares[board_pointer+rank_offset] = bN;
                    break;
                case 'B':
                    b->squares[board_pointer+rank_offset] = wB;
                    break;
                case 'b':
                    b->squares[board_pointer+rank_offset] = bB;
                    break;
                case 'R':
                    b->squares[board_pointer+rank_offset] = wR;
                    break;
                case 'r':
                    b->squares[board_pointer+rank_offset] = bR;
                    break;
                case 'Q':
                    b->squares[board_pointer+rank_offset] = wQ;
                    break;
                case 'q':
                    b->squares[board_pointer+rank_offset] = bQ;
                    break;
                case 'K':
                    b->squares[board_pointer+rank_offset] = wK;
                    b->king_sq[0] = board_pointer+rank_offset;
                    break;
                case 'k':
                    b->squares[board_pointer+rank_offset] = bK;
                    b->king_sq[1] = board_pointer+rank_offset;
                    break;
            }
            rank_offset++;
        }
    }

    token = strtok(NULL, " "); // current side's turn
    if (token == NULL) return;
    b->side = token[0] == 'b';

    token = strtok(NULL, " "); // castling rights
    if (token == NULL) return;
    for (int i = 0; token[i] != '\0'; i++) {
        switch (token[i]) {
            case 'K':
                b->castle_rights |= WHITE_OO;
                break;
            case 'Q':
                b->castle_rights |= WHITE_OOO;
                break;
            case 'k':
                b->castle_rights |= BLACK_OO;
                break;
            case 'q':
                b->castle_rights |= BLACK_OOO;
                break;
        }
    }

    token = strtok(NULL, " "); // en passant square
    if (token == NULL) return;
    if (token[0] != '-') b->ep_square = 21 + (token[0] - 'a') + (10 * ('8' - token[1]));

    token = strtok(NULL, " "); // halfmove
    if (token == NULL) return;
    b->halfmove = atoi(token);

    token = strtok(NULL, " "); // fullmove
    if (token == NULL) return;
    b->fullmove = atoi(token);
}

void parse_position(Board *b, char input[]) {
    char *moves = strstr(input, "moves"); // i would just use token for moves but fen_to_board uses strtok 'till its null, so saving now
    char *token = strtok(input + 9, " ");
    if (strcmp(token, "fen") == 0) {
        char fen_buffer[128] = "";
        for (int i = 0; i < 6; i++) {
            token = strtok(NULL, " ");
            strcat(fen_buffer, token);
            if (i < 5) strcat(fen_buffer, " ");
        }
        printf("%s", fen_buffer);
        fen_to_board(b, fen_buffer);
    }
    else if (strcmp(token, "startpos") == 0) {
        char start[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"; // have to make this because string literals can't be tokenized
        fen_to_board(b, start); // set to start position
    }

    token = strtok(moves, " ");
    if (token != NULL && strcmp(token, "moves") == 0) {
        while (token != NULL) {
            token = strtok(NULL, " ");
            if (token == NULL) break;
            int from = 21 + (token[0] - 'a') + (10 * ('8' - token[1]));
            int to = 21 + (token[2] - 'a') + (10 * ('8' - token[3]));
            make_move(b, from, to);
        }
    }
}