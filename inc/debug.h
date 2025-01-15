/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:40:17 by shurtado          #+#    #+#             */
/*   Updated: 2025/01/15 13:12:05 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "miniRT.h"

// debug_info
void		print_t_rgb(const char *label, t_rgb rgb);
void		print_t_v3(const char *label, t_v3 vec);
long long	current_timestamp(void);

#endif
