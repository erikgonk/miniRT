/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:28:28 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/19 12:08:27 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

# include <pthread.h>
# include <stdint.h>


# define NUM_THREADS 6

typedef struct s_thread_data
{
	int			thread_id;
	t_ray		**rays;
	t_data		*scene;
	uint32_t	**image;
}	t_thread_data;

#endif
