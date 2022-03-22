#include "Floyd_Warshall.h"

#ifdef Floyd_Warshall_debug_print
#include <stdio.h>
char debug_print_dp_file_format[256] = "\0";
char debug_print_next_node_file_format[256] = "\0";
#endif /#ifdef Floyd_Warshall_debug_print

int vertices_num = (int)VERTICES_NUM;
int fake_infinity = (int)FAKE_INFINITY;

uint16_t graph[VERTICES_NUM][VERTICES_NUM] = {
	{0,   4,   1,   FAKE_INFINITY},
	{FAKE_INFINITY,    0,   6,   FAKE_INFINITY},
	{4,   1,   0,   2},
	{FAKE_INFINITY,   FAKE_INFINITY,   FAKE_INFINITY,   0}
};

uint16_t dp[VERTICES_NUM][VERTICES_NUM] = {
	{FAKE_INFINITY,   FAKE_INFINITY,   FAKE_INFINITY,   FAKE_INFINITY},
	{FAKE_INFINITY,   FAKE_INFINITY,   FAKE_INFINITY,   FAKE_INFINITY},
	{FAKE_INFINITY,   FAKE_INFINITY,   FAKE_INFINITY,   FAKE_INFINITY},
	{FAKE_INFINITY,   FAKE_INFINITY,   FAKE_INFINITY,   FAKE_INFINITY},
};

uint16_t next_node[VERTICES_NUM][VERTICES_NUM] = {
	{FAKE_INFINITY,   FAKE_INFINITY,   FAKE_INFINITY,   FAKE_INFINITY},
	{FAKE_INFINITY,   FAKE_INFINITY,   FAKE_INFINITY,   FAKE_INFINITY},
	{FAKE_INFINITY,   FAKE_INFINITY,   FAKE_INFINITY,   FAKE_INFINITY},
	{FAKE_INFINITY,   FAKE_INFINITY,   FAKE_INFINITY,   FAKE_INFINITY}
};

///////

void floyd_warshall_init()
{
	int i, j;
	for (i = 0; i < vertices_num; i++)
	{
		for (j = 0; j < vertices_num; j++)
		{
			dp[i][j] = graph[i][j];
			if (dp[i][j] < fake_infinity)
				next_node[i][j] = j;
		}
			
	}
}

///////

void floyd_warshall_run()
{
	int k, i, j;
	for (k = 0; k < vertices_num; k++)
	{
		for (i = 0; i < vertices_num; i++)
		{
			for (j = 0; j < vertices_num; j++)
			{
				if (dp[i][j] > dp[i][k] + dp[k][j])
				{
					dp[i][j] = dp[i][k] + dp[k][j];
					next_node[i][j] = next_node[i][k];
				}
			}
		}
#ifdef Floyd_Warshall_debug_print
		sprintf_s(debug_print_dp_file_format, 256, "debug_print/dp_k_%d.txt", k);
		sprintf_s(debug_print_next_node_file_format, 256, "debug_print/next_node_k_%d.txt", k);
		floyd_warshall_print_SP_and_next(
			debug_print_dp_file_format,
			debug_print_next_node_file_format
		);
#endif //Floyd_Warshall_debug_print
	}
}

////////
#ifdef Floyd_Warshall_debug_print
void floyd_warshall_print_SP_and_next(char* filename_sp, char* filename_next)
{
	errno_t err;
	FILE* fp_sp; 
	err = fopen_s(&fp_sp, filename_sp, "w");
	FILE* fp_next;
	err = fopen_s(&fp_next, filename_next, "w");
	int i, j;

	fprintf(fp_sp, "dp:\n");
	for (i = 0; i < vertices_num; i++) {
		for (j = 0; j < vertices_num; j++)
			fprintf(fp_sp, "%d ", dp[i][j]);
		fprintf(fp_sp, "\n");
	}

	fprintf(fp_next, "next_node:\n");
	for (i = 0; i < vertices_num; i++) {
		for (j = 0; j < vertices_num; j++)
			fprintf(fp_next, "%d ", next_node[i][j]);
		fprintf(fp_next, "\n");
	}

	fclose(fp_sp);
	fclose(fp_next);	
}
#endif /#ifdef Floyd_Warshall_debug_print