/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:01:10 by jnguyen           #+#    #+#             */
/*   Updated: 2023/03/28 17:37:41 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"
#include "get_next_line.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 32
#endif

typedef struct s_list
{
	void *content;
	struct s_list *next;
} t_list;

int ft_atoi(const char *str);
size_t ft_strlen(const char *str);
void ft_bzero(void *str, size_t n);
void *ft_calloc(size_t nmemb, size_t size);
int ft_isalnum(int c);
int ft_isalpha(int c);
int ft_isascii(int c);
int ft_isdigit(int c);
int ft_isprint(int c);
void *ft_memchr(const void *str, int c, size_t n);
void *ft_memccpy(void *dst, const void *src, int c, size_t n);
int ft_memcmp(const void *s1, const void *s2, size_t n);
void *ft_memcpy(void *dst, const void *src, size_t n);
void *ft_memmove(void *dst, const void *src, size_t n);
void *ft_memset(void *str, int c, size_t n);
char *ft_strchr(const char *str, int c);
char *ft_strdup(const char *str);
char *ft_strcat(char *dest, const char *src);
size_t ft_strlcat(char *dest, char const *src, size_t size);
size_t ft_strlcpy(char *dest, char const *src, size_t size);
int ft_strncmp(char const *s1, char const *s2, size_t n);
char *ft_strnstr(const char *haystack,
				 const char *needle, size_t len);
char *ft_strrchr(const char *str, int c);
int ft_tolower(int c);
int ft_toupper(int c);

char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strtrim(char const *s1, char const *set);
char *ft_itoa(int n);
void ft_putchar_fd(char c, int fd);
void ft_putstr_fd(char *s, int fd);
void ft_putendl_fd(char *s, int fd);
void ft_putnbr_fd(int n, int fd);
char *ft_strmapi(char const *s, char (*f)(unsigned int, char));
char **ft_split(char const *str, char c);

t_list *ft_lstnew(void *content);
void ft_lstadd_front(t_list **alst, t_list *new);
int ft_lstsize(t_list *lst);
t_list *ft_lstlast(t_list *lst);
void ft_lstadd_back(t_list **alst, t_list *new);
void ft_lstdelone(t_list *lst, void (*del)(void *));
void ft_lstclear(t_list **lst, void (*del)(void *));
void ft_lstiter(t_list *lst, void (*f)(void *));
t_list *ft_lstmap(t_list *lst, void *(*f)(void *),
				  void (*del)(void *));
char *ft_strnew(size_t size);
void ft_strdel(char **str);
int get_next_line(int fd, char **line);
char *ft_strnjoin(char *s1, char const *s2, size_t n);
char *ft_strcpy(char *dest, const char *src);

#endif
