#include <stdio.h>

FILE *debug_log = NULL;

void log_message(const char *direction, const char *msg) {
    if (!debug_log) {
        debug_log = fopen("engine_debug.txt", "w");
    }
    fprintf(debug_log, "%s: %s\n", direction, msg);
    fflush(debug_log);
}

// Inside your main loop where you read input:
// log_message("IN", line);

// Inside your main loop where you print/respond:
// log_message("OUT", "bestmove e2e4");