#ifndef TIMER_H
#define TIMER_H

#define PIT_FREQUENCY 1193180U  // ← ADD THIS CONSTANT

void init_timer();
void sleep(int ms);           // Keep as int ms
unsigned long get_ticks();    // Keep as unsigned long

#endif
