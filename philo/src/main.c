#include "../include/philosopher.h"

int main(int ac, char **av)
{
	int num;
	t_geral *geral;

	geral = NULL;
	if(ac != 5)
		exit_erro();
	num = atoi(av[1]);
	create_lista(&geral,num,av);
	create_threads(&geral);
	join_threads(&geral);
	destroy_all_mutex(&geral);
	return 0;
}
