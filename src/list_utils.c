#include "../inc/minirt.h"

/* Returns the color of the smalles float of LST */
int	get_list_min(t_aux **lst)
{
	float	min;
	int		color;
	t_aux	*tmp;

	if (!lst || !*lst)
		return (0);	//TODO: Error Handling
	tmp = *lst;
	min = tmp->t;
	color = tmp->color;
	while (tmp)
	{
		if (tmp->t < min)
		{
			min = tmp->t;
			color = tmp->color;
		}
		tmp = tmp->next;
	}
	return (color);
}

/* Adds a node with the value T to t_aux LST */
void	add_to_list(float t, int color, t_aux **lst)
{
	t_aux	*new;
	t_aux	*tmp;

	if (!lst)
		return ;	//TODO: Error Handling
	new = (t_aux *)malloc(sizeof(t_aux));
	if (!new)
		return ;	//TODO: Error Handling
	new->t = t;
	new->color = color;
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

/* Frees the contents of the list pointed to by LST */
void	delete_list(t_aux **lst)
{
	t_aux	*tmp;

	if (!lst)
		return ;	//TODO: Error Handling
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}

