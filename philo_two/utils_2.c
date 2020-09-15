/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Philosophers                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: samkortekaas <samkortekaas@student.codam.nl> +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/31 09:50:34 by samkortekaas  #+#    #+#                 */
/*   Updated: 2020/05/08 13:50:58 by samkortekaas  ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <zconf.h>

size_t	ft_strlen(const char *str)
{
	size_t l;

	l = 0;
	while (str[l])
		l++;
	return (l);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void		ft_putnbr_fd(uint64_t n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd((char)(n % 10 + '0'), fd);
}
