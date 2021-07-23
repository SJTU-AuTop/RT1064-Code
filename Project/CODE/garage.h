#ifndef GARAGE_H
#define GARAGE_H

enum garage_type_e{
    GARAGE_NONE,
    GARAGE_OUT_LEFT, GARAGE_OUT_RIGHT,
    GARAGE_FOUND_LEFT, GARAGE_FOUND_RIGHT,
    GARAGE_IN_LEFT, GARAGE_IN_RIGHT,
    GARAGE_STOP,
};

extern enum garage_type_e garage_type;

void check_garage();

void run_garage();

void draw_garage();

#endif // GARAGE_H