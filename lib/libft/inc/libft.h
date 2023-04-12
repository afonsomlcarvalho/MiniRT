/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:23:18 by gda-cruz          #+#    #+#             */
/*   Updated: 2023/03/09 15:09:03 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*************** EXTERNAL **************
*************** LIBRARIES *************/
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <wait.h>
# include <err.h>

/************** CHARACTER **************
**************** RELATED **************/
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);

/**************** PUT ******************
**************** STUFF ****************/
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);

/************ FROM SOMETHING ***********
*********** TO SOMETHING ELSE *********/
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);

/*************** STRING ****************
************* MANIPULATION ************/
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);

/*************** MEMORY ****************
************* MANIPULATION ************/
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/**************** LIST *****************
************* MANIPULATION ************/
typedef struct s_list
{
	char			*value;
	struct s_list	*next;
}				t_list;

t_list	*ft_lstnew(char *value);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
int		ft_lstsize(t_list *lst);

/************** GET NEXT ***************
***************** LINE ****************/
# define BUFFER_SIZE 10

# define OPEN_MAX 256

char	*get_next_line(int fd);

/***************** FT ******************
**************** PRINTF ***************/
int		ft_printf(const char *s, ...);
int		ft_putchar(char c);
char	*ft_strchr(const char *s, int c);
void	*ft_redirect(char c);
void	*ft_redirect_flags(char c, char d);
int		ft_print_c(char c);
int		ft_print_i(int n);
int		ft_print_d(int n);
int		ft_print_s(char *s);
int		ft_print_p(unsigned long int mem);
int		ft_print_x(unsigned int num);
int		ft_print_ux(unsigned int num);
int		ft_print_u(unsigned int n);

int		ft_flag_plus(int n);
int		ft_flag_space(int n);
int		ft_flag_hash_l(unsigned int n);
int		ft_flag_hash_u(unsigned int n);

#endif