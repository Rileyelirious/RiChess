#include "board.h"
#include "uci.h"

int main() {
    Board b;
    board_clear(&b);
    uci_loop(&b);
    return 0;
}