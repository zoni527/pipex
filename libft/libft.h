/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:42:55 by jvarila           #+#    #+#             */
/*   Updated: 2025/01/20 11:55:11 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>

# ifndef CONVERSION_SET
#  define CONVERSION_SET "cspdiuxX%"
# endif

# ifndef HEX_BASE_LOWER_CASE
#  define HEX_BASE_LOWER_CASE "0123456789abcdef"
# endif

# ifndef HEX_BASE_UPPER_CASE
#  define HEX_BASE_UPPER_CASE "0123456789ABCDEF"
# endif

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);

int				ft_islower(int c);
int				ft_isupper(int c);

size_t			ft_strlen(const char *s);

void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);

size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);

int				ft_toupper(int c);
int				ft_tolower(int c);

char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);

int				ft_strncmp(const char *s1, const char *s2, size_t n);

void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);

char			*ft_strnstr(const char *big, const char *little, size_t len);

int				ft_atoi(const char *nptr);
long int		ft_atol(const char *nptr);

void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strdup(const char *s);

char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));

int				ft_putchar_fd(char c, int fd);
int				ft_putstr_fd(const char *s, int fd);
int				ft_putendl_fd(const char *s, int fd);
int				ft_putnbr_fd(int n, int fd);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new_lst);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new_lst);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

int				ft_putstr(const char *s);
int				ft_putchar(char c);
int				ft_putendl(const char *s);
int				ft_putnbr(int n);
int				ft_putnbr_base(unsigned int n, const char *base);

char			*ft_longtoa(long int n);
char			*ft_hextoa(unsigned long n, unsigned char mode);
char			*ft_utoa(unsigned int n);
char			*ft_ulongtoa(unsigned long n);

int				ft_int_digits(int n);
int				ft_long_digits(long int n);
int				ft_uint_digits(unsigned int n);
int				ft_ulong_digits(unsigned long n);
int				ft_ulong_hex_digits(unsigned long n);

int				free_ptr_return_int(void **ptr_to_ptr, int i);
void			free_null_ended_array(void ***ptr_to_array);
void			*free_null_ended_array_return_null(void ***ptr_to_array);
int				free_null_ended_array_return_int(void ***ptr_to_array, int num);
int				write_error_return_int(char *error_message, int return_value);
void			*write_error_return_null(char *error_message);

//------------------------------------------------------------------------------
// get_next_line

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef FILE_LIMIT
#  define FILE_LIMIT 10
# endif

typedef struct s_buffer
{
	int			fd;
	int			eof;
	size_t		flushed_bytes;
	size_t		unflushed_bytes;
	char		memory[BUFFER_SIZE];
}	t_buffer;

char			*get_next_line(int fd);
size_t			ft_strlen(const char *str);
void			*ft_memmove(void *dest, const void *src, size_t n);
char			*strjoin_and_free(char *s1, char *s2);
//------------------------------------------------------------------------------
// ft_printf

int				ft_printf(const char *format_str, ...);
int				handle_c(const char **format_str_ptr, va_list ap);
int				handle_s(const char **format_str_ptr, va_list ap);
int				handle_p(const char **format_str_ptr, va_list ap);
int				handle_d(const char **format_str_ptr, va_list ap);
int				handle_i(const char **format_str_ptr, va_list ap);
int				handle_u(const char **format_str_ptr, va_list ap);
int				handle_hex_lowercase(const char **format_str_ptr, va_list ap);
int				handle_hex_uppercase(const char **format_str_ptr, va_list ap);
//------------------------------------------------------------------------------

int				isnumstr(const char *str);
int				word_count(const char *str);
char			*skip_whitespace(const char *str);
char			*skip_char(const char *str, char c);

int				larger_int(int a, int b);
int				smaller_int(int a, int b);

int				first_int_larger(int a, int b);
int				first_int_smaller(int a, int b);

int				ft_iabs(int num);

int				valid_multinumberstring(char *str);

int				contains_duplicate_char(const char *str);

int				char_index(const char *str, int c);

int				valid_hex_string(const char *str);
unsigned int	atou_base(const char *str, const char *base);
unsigned int	atohex(const char *str);

#endif
