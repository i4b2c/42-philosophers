#include "../include/philosopher.h"

long int calculo(struct timeval time_start, struct timeval time_end)
{
	long int temp;

	temp = ((time_end.tv_sec * 1000 + time_end.tv_usec / 1000) -
    		(time_start.tv_sec * 1000 + time_start.tv_usec / 1000));
	return temp;
}
