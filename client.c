/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadlane <cadlane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:49:43 by cadlane           #+#    #+#             */
/*   Updated: 2024/05/13 18:13:30 by cadlane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
static long	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	if (result > 2147483647)
		return (-1);
	return (sign * result);
}

static void	send_signal(pid_t id, char *message)
{
    int		i;
    int		j;
    char	result;

    i = 0;
    while (message[i] != '\0')
    {
	    j = 7;
	    while (j >= 0)
	    {
			result = (message[i] >> j) & 1;
			if (result == 1)
				kill(id, SIGUSR1);
			else if (result == 0)
				kill(id, SIGUSR2);
			usleep(600);
			j--;
	    }
		i++;
	}
}

int	main(int argc, char *argv[])
{
	pid_t	 server_id;

	if (argc == 3)
    {
	    server_id = ft_atoi(argv[1]);
	    if (server_id <= 0 || kill(server_id, 0) == -1)
	    {
		    write(2, "Server Id error\n", 17);
		    return (1);
	    }
	    send_signal(server_id, argv[2]);
    }
    else
	    write(1, "the requested number of arguments was not entered", 50);
    return (0);
}
   