#include <windows.h>
#include <stdio.h>

typedef int bool;
#define true 1
#define false 0

#define foreach(item, array) \
    for(int keep = 1, \
            count = 0,\
            size = sizeof (array) / sizeof *(array); \
        keep && count != size; \
        keep = !keep, count++) \
      for(item = (array) + count; keep; keep = !keep)

void gotoXY(int x, int y);
int getArrowKey(void);