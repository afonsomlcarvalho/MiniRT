#include "../../inc/minirt.h"

/* Returns the closest object in LST */
t_aux	*get_closest_object(t_aux **lst)
{
	double	min;
	t_aux	*tmp;
	t_aux	*closest;

	if (!lst || !*lst)
		return (NULL);
	tmp = *lst;
	closest = tmp;
	min = tmp->t;
	
	while (tmp)
	{
		if (tmp->t < min)
		{
			min = tmp->t;
			closest = tmp;
		}
		tmp = tmp->next;
	}
	return (closest);
}

/* Adds a node with the value T to t_aux LST */
void	add_to_list(double t, int color, t_shape *shape, t_aux **lst)
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
	new->self = shape;
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
	free(lst);
}
