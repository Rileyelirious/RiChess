#ifndef BOARD_H
#define BOARD_H

enum {
    EMPTY = 0,
    wP, wN, wB, wR, wQ, wK,
    bP, bN, bB, bR, bQ, bK,
    OFFBOARD
};

enum { WHITE, BLACK };

#define NO_SQUARE 0

typedef struct Board {
    int squares[120];
    int side;
    int castle_rights;
    int ep_square;
    int halfmove;
    int fullmove;
    int king_sq[2];
} Board;

void board_clear(Board *b);
void board_print(const Board *b);

#endif