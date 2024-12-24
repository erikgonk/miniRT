/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:37:48 by shurtado          #+#    #+#             */
/*   Updated: 2024/12/24 17:45:59 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/render.h"
#include "../lib/libvector/libvct.h"

float	vlength(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_obj	*find_closest_object(t_ray *ray, t_obj *objs, float *t_min)
{
	t_obj	*closest_obj;
	t_obj	*obj;
	float	t;

	closest_obj = NULL;
	obj = objs;
	while (obj)
	{
		t = *t_min;
		if ((obj->type == SP && hit_sp(ray, obj, &t)) \
		|| (obj->type == PL && hit_pl(ray, obj, &t)) \
		|| (obj->type == CY && hit_cy(ray, obj, &t, NULL) \
			))
		{
			if (t > 0 && t < *t_min)
			{
				*t_min = t;
				closest_obj = obj;
			}
		}
		obj = obj->next;
	}
	return (closest_obj);
}

t_v3	get_normal(t_obj *obj, t_v3 point)
{
	t_v3	proj;

	if (obj->type == SP)
		return (normalize(vsub(point, obj->pos)));
	else if (obj->type == PL)
		return (obj->axis);
	else if (obj->type == CY)
	{
		proj = vmul(dot(vsub(point, obj->pos), obj->axis), \
										obj->axis);
		return (normalize(vsub(vsub(point, obj->pos), proj)));
	}
	return ((t_v3){0, 0, 0});
}

#define MAX_DEPTH 2

t_rgb	combine_colors(t_rgb c_local, t_rgb c_global)
{
	t_rgb	c_final;

	c_final.r = fminf((c_global.r * G_WEIGHT) + (c_local.r * L_WEIGHT), 255.0f);
	c_final.g = fminf((c_global.g * G_WEIGHT) + (c_local.g * L_WEIGHT), 255.0f);
	c_final.b = fminf((c_global.b * G_WEIGHT) + (c_local.b * L_WEIGHT), 255.0f);
	return (c_final);
}

t_v3 scalar_mult(t_v3 v, float scalar)
{
	t_v3 result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return result;
}

t_v3 reflect(t_ray *ray)
{
	float	dot_product;
	t_v3	scaled_normal;
	t_v3	reflected;

	// Calcular el producto escalar entre el rayo incidente y la normal
	dot_product = dot(ray->direction, ray->normal);

	// Escalar la normal por 2 * dot_product
	scaled_normal = scalar_mult(ray->normal, 2 * dot_product);

	// Calcular la dirección reflejada
	reflected = vsub(ray->direction, scaled_normal);

	// Normalizar el vector reflejado
	return normalize(reflected);
}

float get_reflection_ratio(t_v3 incident, t_v3 normal, float n1, float n2)
{
    float cos_theta_i;  // Coseno del ángulo de incidencia
    float sin_theta_t2; // Cuadrado del seno del ángulo de transmisión
    float cos_theta_t;  // Coseno del ángulo de transmisión
    float r_perpendicular;
    float r_parallel;
    float reflection_ratio;

    // Calcular el coseno del ángulo de incidencia
    cos_theta_i = fabs(dot(incident, normal)); // Asegurarse de que sea positivo

    // Usar la Ley de Snell para calcular el seno del ángulo de transmisión
    sin_theta_t2 = (n1 / n2) * (n1 / n2) * (1.0f - cos_theta_i * cos_theta_i);

    // Verificar si ocurre reflexión total interna
    if (sin_theta_t2 > 1.0f)
        return 1.0f; // Reflexión total interna: todo se refleja

    // Calcular el coseno del ángulo de transmisión
    cos_theta_t = sqrtf(1.0f - sin_theta_t2);

    // Reflectancia para el componente perpendicular
    r_perpendicular = (n1 * cos_theta_i - n2 * cos_theta_t) /
                      (n1 * cos_theta_i + n2 * cos_theta_t);

    // Reflectancia para el componente paralelo
    r_parallel = (n2 * cos_theta_i - n1 * cos_theta_t) /
                 (n2 * cos_theta_i + n1 * cos_theta_t);

    // Cuadrado de las reflectancias
    r_perpendicular = r_perpendicular * r_perpendicular;
    r_parallel = r_parallel * r_parallel;

    // Promediar para obtener el reflection ratio total
    reflection_ratio = (r_perpendicular + r_parallel) / 2.0f;

    return reflection_ratio;
}

t_rgb blend_colors(t_rgb color1, t_rgb color2, float weight1, float weight2)
{
    t_rgb result;

	    float total_weight;

    // Calcular la suma de los pesos
    total_weight = weight1 + weight2;

    // Normalizar los pesos si la suma no es cero
    if (total_weight > 0)
    {
        weight1 /= total_weight;
        weight2 /= total_weight;
    }
    else
    {
        weight1 = 0.5f; // Asignar pesos iguales si la suma es cero
        weight2 = 0.5f;
    }
    // Mezclar los colores según los pesos
    result.r = fmin(255, fmax(0, color1.r * weight1 + color2.r * weight2));
    result.g = fmin(255, fmax(0, color1.g * weight1 + color2.g * weight2));
    result.b = fmin(255, fmax(0, color1.b * weight1 + color2.b * weight2));

    return result;
}

float get_reflection_ratio_non_metallic(float cos_theta_i)
{
    float R_0 = 0.04; // Reflectancia típica en ángulo normal para dieléctricos
    return R_0 + (1 - R_0) * pow(1 - cos_theta_i, 5);
}

t_rgb checkerboard_color(t_v3 point, t_rgb color1, t_rgb color2, float scale)
{
    int x, y;

    // Escalar las coordenadas del punto para determinar el tamaño del patrón
    x = (int)floor(point.x * scale);
    y = (int)floor(point.z * scale); // Usamos Z para la otra dimensión en el plano

    // Alternar colores según la posición
    if ((x + y) % 2 == 0)
        return color1; // Color para las celdas "blancas"
    else
        return color2; // Color para las celdas "negras"
}

t_rgb	path_tracer(t_data *data, t_ray ray, t_obj *obj, int m_depth)
{
	t_obj	*closest_obj;
	t_ray	new_ray;
	t_rgb	color = {0, 0, 0};
	t_rgb	reflected_color = {0, 0, 0};
	t_rgb	diffuse_color = {0, 0, 0};
	float	reflection_ratio = 0;
	float	t_min = INFINITY;
	int		flag = 0;

	if (m_depth <= 0)
		return ((t_rgb){0, 0, 0});

	closest_obj = find_closest_object(&ray, obj, &t_min);
	if (!closest_obj)
		return ((t_rgb){0, 0, 0});
	// Iluminación difusa
	diffuse_color = phong(data, &ray, closest_obj, 0);

	// Reflexión especular
	if (closest_obj->metallic > EPSILON)
	{
		// Calcular el ratio de reflexión dinámico con Fresnel
		reflection_ratio = get_reflection_ratio(ray.direction, ray.normal, 1.0f, 1.5f); // Índices: aire (1.0) y material (1.5)
		reflection_ratio *= closest_obj->metallic; // Escalar según la propiedad del material

		// Calcular el rayo reflejado
		new_ray.origin = vadd(ray.point, vmul(EPSILON, ray.normal));
		new_ray.direction = reflect(&ray);
		reflected_color = path_tracer(data, new_ray, obj, m_depth - 1);
		if (obj->metallic == 1)
				diffuse_color = reflected_color;
		color = blend_colors(diffuse_color, reflected_color, 1 - reflection_ratio, reflection_ratio);
	}
else
{
    // Reflexión para objetos no metálicos (opcional)
    reflection_ratio = get_reflection_ratio_non_metallic(dot(ray.direction, ray.normal));
    color = diffuse_color;
}
	// Mezclar los colores difuso y reflejado según el ratio de reflexión
	if (obj->type == PL)
		color = checkerboard_color(ray.point, obj->rgb, (t_rgb){0, 0, 0}, 0.5f);
	return (color);
}

uint32_t	trace_ray(t_ray ray, t_data *data)
{
	float	t_min;
	t_obj	*closest_obj;
	t_rgb	c_global;

	t_min = INFINITY;
	closest_obj = find_closest_object(&ray, data->obj, &t_min);
	if (!closest_obj)
		return (BLACK);
	c_global = path_tracer(data, ray, closest_obj, 120);
	return (get_colour(c_global));
}
