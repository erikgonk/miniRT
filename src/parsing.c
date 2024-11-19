/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:53:01 by erigonza          #+#    #+#             */
/*   Updated: 2024/11/19 12:45:07 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	correct_file(char *name)
{
	int	i;

	i = 0;
	while (name[i] != '.' && name[i])
		i++;
	if (name[i + 3] || !name[i - 1])
		exit(er("error: wrong file name -> ", name));
	else if (name[i] == '.' && name[i + 1] == 'r' && name[i + 2] == 't')
		return ;
	exit (er("error: wrong file name -> ", name));
}

// int	ft_builtins(t_exec *exec)
// {
	// static char		*bts[] = {"t_cam", "t_lihgt", "t_plane", 
	// 	"t_sphere", "t_cylinder", NULL};
// 	static char		*bts[] = {"pwd", "echo", "cd", "export",
// 		"unset", "env", "exit", NULL};
// 	static int		(*builtins[])(t_exec *) = {ft_pwd, ft_echo,
// 		ft_cd, ft_export, ft_unset, ft_env, ft_exit};
// 	int				i;

// 	i = 0;
// 	while (bts[i] && !ft_strcmp(bts[i], exec->cmd_t->cmd[0]))
// 		i++;
// 	if (bts[i])
// 		builtins[i](exec);
// 	else
// 		return (127);
// 	return (exec->g_exit);
// }

int	newNode(t_data *data, char *str)
{
	static char		*bts[] = {"A", "C", "L", "sp", "pl", "cy", NULL};
	int				i;

	i = 0;
	while (bts[i] && !ft_strncmp(bts[i], str, 2))
		i++;
	if (bts[i])
		return (0);
	return (1);
}

void	parse(t_data *data, char **av)
{
	int		fd;
	char	*str;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		exit(er("error: fd filed", NULL));
	while (true)
	{
		if (str)
			free(str);
		str = get_next_line(fd);
		if (!str)
			break ;
		printf("%s\n", str);
	}
	exit (er("salio bien", NULL));

	data->sp->ray_start = vDefine(0.0, 0.0, 0.0);		// Camera position (where our rays start from)	
	data->sp->sphere_radius = 1.4;						// Radius (size) of the sphere
    data->sp->sphere_center = vDefine(
        atof(av[1]),
        atof(av[2]),
        atof(av[3]));

    data->sp->sphere_radius = atof(av[4]);  // Sphere radius
    data->sp->color = ((atoi(av[5]) << 16) | (atoi(av[6]) << 8) | atoi(av[7]));

    // Initialize light source
    data->light->pos = vDefine(
        atof(av[8]),  // X
        atof(av[9]),  // Y
        atof(av[10])  // Z
    );
    data->light->br = atof(av[11]);  // Light brightness ratio
    if (data->light->br < 0.0f || data->light->br > 1.0f)
        er("error: %s: brightness must be in range [0.0, 1.0]", av[11]);
}
