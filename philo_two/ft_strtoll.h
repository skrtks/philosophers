/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: samkortekaas <samkortekaas@student.codam.nl> +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 12:40:00 by skorteka      #+#    #+#                 */
/*   Updated: 2020/05/02 15:41:44 by samkortekaas  ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRTOLL_H
#define FT_STRTOLL_H

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

typedef struct			s_info
{
	int					any;
	int					neg;
	int					base;
	unsigned long long	cutlim;
	unsigned long long	cutoff;
}						t_info;

#endif


#endif //FT_STRTOLL_H
