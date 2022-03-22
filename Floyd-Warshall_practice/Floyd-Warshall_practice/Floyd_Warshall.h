#ifndef __FLOYD_WARSHALL_H__
#define __FLOYD_WARSHALL_H__

#include<stdint.h>

#define VERTICES_NUM 4
#define FAKE_INFINITY 65535

#define Floyd_Warshall_debug_print

extern uint16_t graph[VERTICES_NUM][VERTICES_NUM];

void floyd_warshall_init();

void floyd_warshall_run();

#ifdef Floyd_Warshall_debug_print
void floyd_warshall_print_SP_and_next(char* filename_sp, char* filename_next);
#endif /#ifdef Floyd_Warshall_debug_print

#endif /*__FLOYD_WARSHALL_H__*/

