/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 10:41:17 by epresa-c          #+#    #+#             */
/*   Updated: 2022/08/12 14:32:30 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ***************************** LIBRARIES ********************************** */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/* ******************************* MACROS *********************************** */

# define FALSE 0
# define TRUE 1
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define NO 0
# define YES 1

/* ****************************** STRUCTURES ******************************** */

typedef struct s_philosopher
{
	size_t			id;
	size_t			t_last_meal;
	size_t			n_meals_eaten;
	size_t			t_to_die;
	size_t			t_to_eat;
	size_t			t_to_sleep;
	int				*end_simu;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork_right;
}	t_phillosopher;

typedef struct s_var
{
	pthread_t		*th;
	pthread_t		check_end;
	t_phillosopher	**philosophers;
	size_t			n_of_phil;
	size_t			t_to_die;
	size_t			t_to_eat;
	size_t			t_to_sleep;
	size_t			n_meals_to_eat;
	int				exit_status;
	size_t			t_start_simu;
	int				end_simu;
	pthread_mutex_t	print;
}	t_var;

/* ******************************* FUNCTIONS ******************************** */

// main.c

int				print_error(int exit_status);
void			init_var(int argc, char **argv, t_var *v);

// check_args.c

long long int	fn_atoll(char *s);
int				check_int_overflow(char *argv);
int				check_single_arg(char *argv_i);
int				check_args(int argc, char **argv, t_var *var);

// utiles.c

int				ft_isdigit(int c);
size_t			ft_strlen(const char *s);
void			print_var(t_var var);

#endif
