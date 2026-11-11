#include "board.h"

void parse_legal_moves_for_side(Board *b, int side, Move moves[]) {
    int move_index = 0;
    if (side == WHITE) {
        for (int i = 21; i<99; i++) {
            switch (b->squares[i]) {
                case wP:
                    // jump one
                    if (b->squares[i-10] == EMPTY) {
                        if ((i-10)/10 == 2) { // promotion check
                            moves[move_index++] = (Move){.from=i,.to=i-10,.promote_to=wN};
                            moves[move_index++] = (Move){.from=i,.to=i-10,.promote_to=wB};
                            moves[move_index++] = (Move){.from=i,.to=i-10,.promote_to=wR};
                            moves[move_index++] = (Move){.from=i,.to=i-10,.promote_to=wQ};
                        }
                        else moves[move_index++] = (Move){.from=i,.to=i-10}; // normal jump one if can't promote
                        // jump two if can jump one (promote or not, doesn't matter)
                        if (i/10 == 8 && b->squares[i-20] == EMPTY) {
                            moves[move_index++] = (Move){.from=i,.to=i-20};
                        }
                    }
                    // take diagonally right
                    if (IS_BLACK(b->squares[i-9]) || i-9 == b->ep_square) {
                        if ((i-9)/10 == 2) { // promotion check
                            moves[move_index++] = (Move){.from=i,.to=i-9,.promote_to=wN};
                            moves[move_index++] = (Move){.from=i,.to=i-9,.promote_to=wB};
                            moves[move_index++] = (Move){.from=i,.to=i-9,.promote_to=wR};
                            moves[move_index++] = (Move){.from=i,.to=i-9,.promote_to=wQ};
                        }
                        else moves[move_index++] = (Move){.from=i,.to=i-9};
                    }
                    // take diagonally left
                    if (IS_BLACK(b->squares[i-11]) || i-11 == b->ep_square) {
                        if ((i-11)/10 == 2) { // promotion check
                            moves[move_index++] = (Move){.from=i,.to=i-11,.promote_to=wN};
                            moves[move_index++] = (Move){.from=i,.to=i-11,.promote_to=wB};
                            moves[move_index++] = (Move){.from=i,.to=i-11,.promote_to=wR};
                            moves[move_index++] = (Move){.from=i,.to=i-11,.promote_to=wQ};
                        }
                        else moves[move_index++] = (Move){.from=i,.to=i-11};
                    }
                    break;
                case wN:
                    break;
                case wB:
                    break;
                case wR:
                    break;
                case wQ:
                    break;
                case wK:
                    break;
            }
        }
    }
    else { // side is black

    }
}