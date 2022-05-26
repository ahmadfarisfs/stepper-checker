#include "nonstd.h"
// #ifndef __INTELLISENSE__
void * operator new(size_t size, void * ptr) { return ptr; }
// #endif