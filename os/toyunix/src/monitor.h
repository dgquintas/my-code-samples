#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"

//write a single character out to the screen
void monitor_put(char c);

// clear the screen to all black
void monitor_clear();

//output a null-terminated ascii string 
void monitor_write(char* c);


#endif
