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

#define WHITE_OO  1 // Binary: 0001 (Decimal: 1)
#define WHITE_OOO 2 // Binary: 0010 (Decimal: 2)
#define BLACK_OO  4 // Binary: 0100 (Decimal: 4)
#define BLACK_OOO 8 // Binary: 1000 (Decimal: 8)

#define IS_BLACK(p) ((p) >= bP && (p) <= bK)
#define IS_WHITE(p) ((p) >= wP && (p) <= wK)

typedef struct {
    int squares[120];
    int side;
    int castle_rights;
    int ep_square;
    int halfmove;
    int fullmove;
    int king_sq[2];
} Board;

typedef struct {
    int from;
    int to;
    int promote_to;
} Move;

void board_clear(Board *b);
void check_board_values(const Board *b);
void parse_position(Board *b, char input[]);

#endif