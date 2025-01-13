/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:18:36 by erigonza          #+#    #+#             */
/*   Updated: 2025/01/13 11:02:49 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_end(t_data *data, char *str, int i)
{
	while (str[i] && ft_isspace(str[i]))
		i++;
	i = skip_color(data, str, i, 0);
	i = skip_color(data, str, i, 0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && str[i] != '\n')
		if (!ft_isspace(str[i++]))
			exit(er(data, "error: check_end: char after last num", str));
}

void	check_light(t_data *data, t_alight *aL, t_slight *sL)
{
	if (aL)
	{
		if (aL->br < 0)
			exit(er(data,  "error: check_lihgt: brightness < 0", NULL));
		if (aL->rgb.r < 0 || aL->rgb.r > 255)
			exit(er(data,  "error: check_lihgt: aL rgb.r 0-255", NULL));
		else if (aL->rgb.g < 0 || aL->rgb.g > 255)
			exit(er(data,  "error: check_lihgt: aL rgb.g 0-255", NULL));
		else if (aL->rgb.b < 0 || aL->rgb.b > 255)
			exit(er(data,  "error: check_lihgt: aL rgb.b 0-255", NULL));
	}
	while (sL)
	{
		if (sL->br < 0)
			exit(er(data,  "error: ACL left", NULL));
		else if (sL->rgb.r < 0 || sL->rgb.r > 255)
			exit(er(data,  "error: sL rgb.r 0-255", NULL));
		else if (sL->rgb.g < 0 || sL->rgb.g > 255)
			exit(er(data,  "error: sL rgb.g 0-255", NULL));
		else if (sL->rgb.b < 0 || sL->rgb.b > 255)
			exit(er(data,  "error: sL rgb.b 0-255", NULL));
		sL = sL->next;
	}
}

void	check_params_acl(t_data *data, t_alight *aL, t_slight *sL, t_cam *cam)
{
	if (!cam)
		exit(er(data,  "error: check_params_acl: ACL left", NULL));
	check_light(data, aL, sL);
	if (cam->axis.x < -1 || cam->axis.x > 1)
		exit(er(data,  "error: check_params_acl: cam axis.x 0-1", NULL));
	else if (cam->axis.y < -1 || cam->axis.y > 1)
		exit(er(data,  "error: check_params_acl: cam axis.y 0-1", NULL));
	else if (cam->axis.z < -1 || cam->axis.z > 1)
		exit(er(data,  "error: check_params_acl: cam axis.z 0-1", NULL));
	else if (cam->fov < 0)
		exit(er(data,  "error: check_params_acl: cam fov <0", NULL));
}

void	check_obj_normi(t_obj *obj)
{
	if (obj->axis.x < -1 || obj->axis.x > 1)
		exit(er(obj->data,"error: check_obj_normi: axis.x 0-1", NULL));
	else if (obj->axis.y < -1 || obj->axis.y > 1)
		exit(er(obj->data,"error: check_obj_normi: axis.y 0-1", NULL));
	else if (obj->axis.z < -1 || obj->axis.z > 1)
		exit(er(obj->data, "error: check_obj_normi: axis.z 0-1", NULL));
	else if ((obj->type == CY || obj->type == CO) && obj->height < 1)
		exit(er(obj->data,"error: check_obj_normi: height <1", NULL));
	else if (obj->type == CO && (obj->size > 90 || obj->size < 1))
		exit(er(obj->data, "error: check_obj_normi: size <1", NULL));
	if (obj->type == CU)
	{
		if (obj->cube_size.x < 1)
			exit(er(obj->data,"error: check_obj_normi: size x <1", NULL));
		else if (obj->cube_size.x < 1)
			exit(er(obj->data,"error: check_obj_normi: size y <1", NULL));
		else if (obj->cube_size.x < 1)
			exit(er(obj->data, "error: check_obj_normi: size z <1", NULL));
	}
}

void	check_obj(t_obj *obj)
{
	while (obj)
	{
		if (obj->rgb.r < 0 || obj->rgb.r > 255)
			exit(er(obj->data,  "error: check_obj: rgb.r 0-255", NULL));
		else if (obj->rgb.g < 0 || obj->rgb.g > 255)
			exit(er(obj->data,  "error: check_obj: rgb.g 0-255", NULL));
		else if (obj->rgb.b < 0 || obj->rgb.b > 255)
			exit(er(obj->data,  "error: check_obj: rgb.b 0-255", NULL));
		else if (obj->type != PL && obj->type != CO && obj->size <= 0)
			exit(er(obj->data,  "error: check_obj: sp/cy size <=0", NULL));
		else if (obj->type != SP)
			check_obj_normi(obj);
		if (obj->type == CO && (obj->size < 0 || obj->size > 54))
			exit(er(obj->data,  "error: check_obj: co size 0-54", NULL));
		else if (obj->type == CO)
			obj->size += 35;
		obj = obj->next;
	}
}
