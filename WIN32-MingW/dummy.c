#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "portable.h"

#include <stdio.h>
#define TR printf("%s, #%d\n", __func__, __LINE__)

void * pvPortMalloc(size_t xWantedSize) { TR; return NULL; }
void vPortFree( void * pv ) {TR;}
void vPortGetHeapStats( HeapStats_t * pxHeapStats ) {TR;}
size_t xPortGetMinimumEverFreeHeapSize( void ) { TR; return 0; }
void vPortDefineHeapRegions( const HeapRegion_t * const pxHeapRegions ) {TR;}
size_t xPortGetFreeHeapSize( void ) {TR;}
void _getch() {TR;}
