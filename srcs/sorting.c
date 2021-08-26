#include "pushswap.h"

static void	sort_a(t_list_int **actual, t_global *global, int nbr_sorting)
{
	long int	big;
	long int	small;

	// printf("content avant a 0 :%ld\n", *((*actual)->content));
	// printf("content avant a 1 :%ld\n", *((*actual)->next->content));
	if (nbr_sorting == 2)
	{
		if (*((*actual)->content) > *((*actual)->next->content))
			swap(actual, global);
		return ;
	}
	// printf("content avant a 2 :%ld\n", *((*actual)->next->next->content));
	if (!is_sorted_s_to_b(*actual, nbr_sorting))
	{
		big = find_biggest(*actual);
		small = find_smallest(*actual);
		if (small == *((*actual)->next->content) && big == *((*actual)->next->next->content))
		{
			swap(actual, global);
			return ;
		}
		if (big == *((*actual)->content))
			swap(actual, global);
		rotate(actual, global);
		swap(actual, global);
		rev_rotate(actual, global);
		if (small != *((*actual)->content))
			swap(actual, global);
	}
	// printf("content apres a 0 :%ld\n", *((*actual)->content));
	// printf("content apres a 1 :%ld\n", *((*actual)->next->content));
	// if (nbr_sorting > 2)
	// 	printf("content apres a 2 :%ld\n", *((*actual)->next->next->content));
}

static void	sort_b(t_list_int **actual, t_global *global, int nbr_sorting)
{
	long int	big;
	long int	small;

	// printf("content avant b 0 :%ld\n", *((*actual)->content));
	// printf("content avant b 1 :%ld\n", *((*actual)->next->content));
	if (nbr_sorting == 2)
	{
		if (*((*actual)->content) < *((*actual)->next->content))
			swap(actual, global);
		return ;
	}
	// printf("content avant b 2 :%ld\n", *((*actual)->next->next->content));
	if (!is_sorted_b_to_s(*actual, nbr_sorting))
	{
	printf("L\n");
		big = find_biggest(*actual);
		small = find_smallest(*actual);
		if (big == *((*actual)->next->content) && small == *((*actual)->next->next->content))
		{
			swap(actual, global);
			return ;
		}
		if (small == *((*actual)->content))
			swap(actual, global);
		rotate(actual, global);
		swap(actual, global);
		rev_rotate(actual, global);
		if (big != *((*actual)->content))
			swap(actual, global);
	}
	// printf("content apres b 0 :%ld\n", *((*actual)->content));
	// printf("content apres b 1 :%ld\n", *((*actual)->next->content));
	// if (nbr_sorting > 2)
	// 	printf("content apres b 2 :%ld\n", *((*actual)->next->next->content));
}

static void	stack_on(t_list_int **actual, t_list_int **other, int nbr_sorting, t_global *global)
{
	int	i;

	i = 0;
	while (i < nbr_sorting)
	{
		push(other, actual, global);
		i++;
	}
}

int sorting(int nbr_sorting, t_list_int **actual, t_list_int **other, t_global *global, int stack)
{
	global->stack = stack;
	printf("\033[36mnbr_sorting :%d\033[0m\n", nbr_sorting);
	if (!(stack % 2))
	{
	printf("LIST A++ : ");
	printlst_int(*actual);
	

	printf("LIST B : ");
	printlst_int(*other);
	}
	else
	{
	printf("LIST A : ");
	printlst_int(*other);
	

	printf("LIST B++ : ");
	printlst_int(*actual);
	}
	if (nbr_sorting <= 3)
	{
	printf("A\n");
		if (stack % 2 == 1)
		{
	printf("B\n");
			sort_b(actual, global, nbr_sorting);
		}
		else
		{
	printf("C\n");
			sort_a(actual, global, nbr_sorting);
		}
	printf("D\n");
		if (stack == 2)
			stack_on(actual, other, nbr_sorting, global);
	printf("E\n");
		if (stack == 3)
			stack_on(actual, other, nbr_sorting, global);
		return (1);
	}
	if (!(find_median(nbr_sorting, *actual, global, &(global->str), stack)))
		return (0);
	printf("median %d\n", global->median);
	seperate(actual, other, global, nbr_sorting, stack);

	// nbr_sorting -= global->changed;
	if (!(stack % 2))
	{
		// printf("\033[35mnfirst. br_sorting before %d\n\033[0m", nbr_sorting);
		// nbr_sorting += change_nbr(*actual, nbr_sorting, global);
		// printf("\033[35mfirst. nbr_sorting after %d\n\033[0m", nbr_sorting);
		sorting(nbr_sorting / 2 + nbr_sorting % 2, actual, other, global, 0);
		sorting(nbr_sorting / 2, other, actual, global, 3);
	}
	else
	{
		// printf("\033[34mfirst. nbr_sorting before %d\n\033[0m", nbr_sorting);
		// nbr_sorting += change_nbr(*other, nbr_sorting, global);
		// printf("\033[34mfirst. nbr_sorting after %d\n\033[0m", nbr_sorting);
		sorting(nbr_sorting / 2 + nbr_sorting % 2, actual, other, global, 1);
		sorting(nbr_sorting / 2, other, actual, global, 2);
	}
	if (stack == 2)
		stack_on(actual, other, nbr_sorting, global);
	if (stack == 3)
		stack_on(actual, other, nbr_sorting, global);
	return (1);
}