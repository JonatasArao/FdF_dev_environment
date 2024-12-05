/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_generate_vector_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:04:25 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/05 17:42:16 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include "minunit.h"
#include "fdf.h"

void dummy_del(void *content)
{
	(void)content;
}

MU_TEST(test_generate_vector_list_single_point)
{
	t_list	*points = NULL;
	t_list	*vectors;

	t_point a = {0, 0, 0, 0};
	ft_lstadd_back(&points, ft_lstnew(&a));

	vectors = generate_vector_list(points);

	mu_assert(vectors == NULL, "The vector list should be NULL for a single point");

	ft_lstclear(&points, dummy_del);
}

MU_TEST(test_generate_vector_list_two_connected_points)
{
	t_list	*points = NULL;
	t_list	*vectors;
	t_vector *vector;

	t_point a = {0, 1, 0, 0};
	t_point b = {0, 0, 0, 0};
	ft_lstadd_back(&points, ft_lstnew(&a));
	ft_lstadd_back(&points, ft_lstnew(&b));

	vectors = generate_vector_list(points);

	mu_assert(vectors != NULL, "The vector list should not be NULL");
	vector = (t_vector *)vectors->content;
	mu_assert_int_eq(1, vector->a->x);
	mu_assert_int_eq(0, vector->a->y);
	mu_assert_int_eq(0, vector->b->x);
	mu_assert_int_eq(0, vector->b->y);
	mu_assert_int_eq(-1, vector->delta_x);
	mu_assert_int_eq(0, vector->delta_y);
	mu_assert_int_eq(-1, vector->direction_x);
	mu_assert_int_eq(1, vector->direction_y);

	ft_lstclear(&points, dummy_del);
	ft_lstclear(&vectors, free);
}

MU_TEST(test_generate_vector_list_no_connected_points)
{
	t_list	*points = NULL;
	t_list	*vectors;

	t_point a = {0, 0, 0, 0};
	t_point b = {2, 2, 0, 0};
	ft_lstadd_back(&points, ft_lstnew(&a));
	ft_lstadd_back(&points, ft_lstnew(&b));

	vectors = generate_vector_list(points);

	mu_assert(vectors == NULL, "The vector list should be NULL for no connected points");

	ft_lstclear(&points, dummy_del);
}

MU_TEST(test_generate_vector_list_multiple_connected_points)
{
	t_list	*points = NULL;
	t_list	*vectors;
	t_vector *vector;

	t_point a = {0, 1, 1, 0};
	t_point b = {0, 0, 1, 0};
	t_point c = {0, 1, 0, 0};
	ft_lstadd_back(&points, ft_lstnew(&a));
	ft_lstadd_back(&points, ft_lstnew(&b));
	ft_lstadd_back(&points, ft_lstnew(&c));

	vectors = generate_vector_list(points);

	mu_assert(vectors != NULL, "The vector list should not be NULL");

	vector = (t_vector *)vectors->content;
	mu_assert_int_eq(1, vector->a->x);
	mu_assert_int_eq(1, vector->a->y);
	mu_assert_int_eq(1, vector->b->x);
	mu_assert_int_eq(0, vector->b->y);
	mu_assert_int_eq(0, vector->delta_x);
	mu_assert_int_eq(-1, vector->delta_y);
	mu_assert_int_eq(1, vector->direction_x);
	mu_assert_int_eq(-1, vector->direction_y);

	vector = (t_vector *)vectors->next->content;
	mu_assert_int_eq(1, vector->a->x);
	mu_assert_int_eq(1, vector->a->y);
	mu_assert_int_eq(0, vector->b->x);
	mu_assert_int_eq(1, vector->b->y);
	mu_assert_int_eq(-1, vector->delta_x);
	mu_assert_int_eq(0, vector->delta_y);
	mu_assert_int_eq(-1, vector->direction_x);
	mu_assert_int_eq(1, vector->direction_y);

	ft_lstclear(&points, dummy_del);
	ft_lstclear(&vectors, free);
}

MU_TEST(test_generate_vector_list_disconnected_points)
{
	t_list	*points = NULL;
	t_list	*vectors;

	t_point a = {0, 0, 0, 0};
	t_point b = {0, 1, 1, 0};
	t_point c = {0, 2, 3, 0};
	ft_lstadd_back(&points, ft_lstnew(&a));
	ft_lstadd_back(&points, ft_lstnew(&b));
	ft_lstadd_back(&points, ft_lstnew(&c));

	vectors = generate_vector_list(points);

	mu_assert(vectors == NULL, "The vector list should be NULL for disconnected points");

	ft_lstclear(&points, dummy_del);
}

MU_TEST(test_generate_vector_list_mixed_connected_and_disconnected_points)
{
	t_list	*points = NULL;
	t_list	*vectors;
	t_vector *vector;

	t_point a = {0, 2, 3, 0};
	t_point b = {0, 1, 1, 0};
	t_point c = {0, 3, 2, 0};
	t_point d = {0, 0, 1, 0};
	t_point e = {0, 1, 0, 0};
	ft_lstadd_back(&points, ft_lstnew(&a));
	ft_lstadd_back(&points, ft_lstnew(&b));
	ft_lstadd_back(&points, ft_lstnew(&c));
	ft_lstadd_back(&points, ft_lstnew(&d));
	ft_lstadd_back(&points, ft_lstnew(&e));

	vectors = generate_vector_list(points);

	mu_assert(vectors != NULL, "The vector list should not be NULL");

	vector = (t_vector *)vectors->content;
	mu_assert_int_eq(1, vector->a->x);
	mu_assert_int_eq(1, vector->a->y);
	mu_assert_int_eq(1, vector->b->x);
	mu_assert_int_eq(0, vector->b->y);
	mu_assert_int_eq(0, vector->delta_x);
	mu_assert_int_eq(-1, vector->delta_y);
	mu_assert_int_eq(1, vector->direction_x);
	mu_assert_int_eq(-1, vector->direction_y);

	vector = (t_vector *)vectors->next->content;
	mu_assert_int_eq(1, vector->a->x);
	mu_assert_int_eq(1, vector->a->y);
	mu_assert_int_eq(0, vector->b->x);
	mu_assert_int_eq(1, vector->b->y);
	mu_assert_int_eq(-1, vector->delta_x);
	mu_assert_int_eq(0, vector->delta_y);
	mu_assert_int_eq(-1, vector->direction_x);
	mu_assert_int_eq(1, vector->direction_y);

	mu_assert(vectors->next->next == NULL, "The next vector should be NULL");

	ft_lstclear(&points, dummy_del);
	ft_lstclear(&vectors, free);
}

MU_TEST_SUITE(test_generate_vector_list_suite)
{
	MU_RUN_TEST(test_generate_vector_list_single_point);
	MU_RUN_TEST(test_generate_vector_list_two_connected_points);
	MU_RUN_TEST(test_generate_vector_list_no_connected_points);
	MU_RUN_TEST(test_generate_vector_list_multiple_connected_points);
	MU_RUN_TEST(test_generate_vector_list_disconnected_points);
	MU_RUN_TEST(test_generate_vector_list_mixed_connected_and_disconnected_points);
}

int test_generate_vector_list(void)
{
	MU_RUN_SUITE(test_generate_vector_list_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
