/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 10:41:17 by epresa-c          #+#    #+#             */
/*   Updated: 2022/08/13 14:59:30 by Emiliano         ###   ########.fr       */
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
# define ERROR_NUM_ARGS 1
# define ERROR_NON_NUMERICAL_ARG 2
# define ERROR_INT_OVERFLOW 3
# define ERROR_NUM_PHILOS 4
# define ERROR_MALLOC 5
# define ERROR_PTHREAD_CREATE 6
# define ERROR_PTHREAD_JOIN 7

/* ****************************** STRUCTURES ******************************** */

typedef struct s_philosopher
{
	size_t			id;
	size_t			t_last_meal;
	size_t			n_meals_to_eat;
	size_t			n_meals_eaten;
	size_t			t_to_die;
	size_t			t_to_eat;
	size_t			t_to_sleep;
	size_t			start_simu;
	int				*end_simu;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*print;
}	t_philosopher;

typedef struct s_var
{
	pthread_t		*th;
	pthread_t		check_end;
	t_philosopher	**philosophers;
	size_t			n_of_phil;
	size_t			t_to_die;
	size_t			t_to_eat;
	size_t			t_to_sleep;
	size_t			n_meals_to_eat;
	size_t			t_start_simu;
	int				exit_status;
	int				end_simu;
	pthread_mutex_t	print;
}	t_var;

/* ******************************* FUNCTIONS ******************************** */

// print.c

int				print_error(int exit_status);

// main.c

void			init_var(int argc, char **argv, t_var *v);

// check_args.c

long long int	fn_atoll(char *s);
int				check_int_overflow(char *argv);
int				check_single_arg(char *argv_i, int k);
int				check_args(int argc, char **argv, t_var *var);

// utiles.c

int				ft_isdigit(int c);
size_t			ft_strlen(const char *s);
void			print_var(t_var var);

#endif
