/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:55:24 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/11 11:35:16 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <sys/stat.h>                                                                                                 
#include <stdlib.h>                                                                                                   
#include <string.h>                                                                                                   

#include "../lib/MLX42/include/MLX42/MLX42.h"

typedef struct {
    float x, y, z;
} Vector3;

#endif
