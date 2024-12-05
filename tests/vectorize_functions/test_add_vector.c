/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_add_vector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:04:25 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/05 17:37:36 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include "minunit.h"
#include "fdf.h"

int capture_segfault_add_vector(t_list *(*f)(t_list **, t_point *, t_point *), t_list **head, t_point *a, t_point *b)
{
	pid_t pid = fork();
	if (pid == 0)
	{
		// Child process executes the test
		f(head, a, b);
		exit(0);
	}
	else if (pid > 0)
	{
		// Parent process waits for the child
		int status;
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV)
		{
			return 1;
		}
		return 0;
	}
	else
	{
		perror("fork");
		exit(1);
	}
}
MU_TEST(test_add_vector_valid_points)
{
	t_list	*head = NULL;
	t_vector *vector;
	t_point	a = {0, 0, 0, 0};
	t_point	b = {0, 3, 4, 0};

	add_vector(&head, &a, &b);

	mu_assert(head != NULL, "The list should not be NULL");
	vector = (t_vector *)head->content;
	mu_assert_int_eq(0, vector->a->x);
	mu_assert_int_eq(0, vector->a->y);
	mu_assert_int_eq(3, vector->b->x);
	mu_assert_int_eq(4, vector->b->y);
	mu_assert_int_eq(3, vector->delta_x);
	mu_assert_int_eq(4, vector->delta_y);
	mu_assert_int_eq(1, vector->direction_x);
	mu_assert_int_eq(1, vector->direction_y);
	mu_assert_int_eq(0, vector->a->z);
	mu_assert_int_eq(0, vector->b->z);
	mu_assert_int_eq(0, vector->a->color);
	mu_assert_int_eq(0, vector->b->color);
	mu_assert(head->next == NULL, "The next node should be NULL");

	free(vector);
	free(head);
}

MU_TEST(test_add_vector_negative_delta)
{
	t_list	*head = NULL;
	t_vector *vector;
	t_point	a = {0, 3, 4, 0};
	t_point	b = {0, 0, 0, 0};

	add_vector(&head, &a, &b);

	mu_assert(head != NULL, "The list should not be NULL");
	vector = (t_vector *)head->content;
	mu_assert_int_eq(3, vector->a->x);
	mu_assert_int_eq(4, vector->a->y);
	mu_assert_int_eq(0, vector->b->x);
	mu_assert_int_eq(0, vector->b->y);
	mu_assert_int_eq(-3, vector->delta_x);
	mu_assert_int_eq(-4, vector->delta_y);
	mu_assert_int_eq(-1, vector->direction_x);
	mu_assert_int_eq(-1, vector->direction_y);
	mu_assert_int_eq(0, vector->a->z);
	mu_assert_int_eq(0, vector->b->z);
	mu_assert_int_eq(0, vector->a->color);
	mu_assert_int_eq(0, vector->b->color);
	mu_assert(head->next == NULL, "The next node should be NULL");

	free(vector);
	free(head);
}

MU_TEST(test_add_vector_null_head)
{
	t_list	*head = NULL;
	t_point	a = {0, 0, 0, 0};
	t_point	b = {0, 3, 4, 0};

	int segfaulted = capture_segfault_add_vector(add_vector, &head, &a, &b);
	if (!segfaulted)
		add_vector(&head, &a, &b);

	if (segfaulted)
		mu_fail("Function should not cause a segmentation fault when head is NULL.");
}

MU_TEST(test_add_vector_null_points)
{
	t_list	*head = NULL;
	t_point	*a = NULL;
	t_point	*b = NULL;

	int segfaulted = capture_segfault_add_vector(add_vector, &head, a, b);
	if (!segfaulted)
		add_vector(&head, a, b);

	if (segfaulted)
		mu_fail("Function should not cause a segmentation fault when points are NULL.");
}

MU_TEST(test_add_vector_multiple_vectors)
{
	t_list	*head = NULL;
	t_vector *vector1;
	t_vector *vector2;
	t_point	a1 = {0, 0, 0, 0};
	t_point	b1 = {0, 3, 4, 0};
	t_point	a2 = {0, 1, 1, 0};
	t_point	b2 = {0, 4, 5, 0};

	add_vector(&head, &a1, &b1);
	add_vector(&head, &a2, &b2);

	mu_assert(head != NULL, "The list should not be NULL");
	vector2 = (t_vector *)head->content;
	mu_assert_int_eq(1, vector2->a->x);
	mu_assert_int_eq(1, vector2->a->y);
	mu_assert_int_eq(4, vector2->b->x);
	mu_assert_int_eq(5, vector2->b->y);
	mu_assert_int_eq(3, vector2->delta_x);
	mu_assert_int_eq(4, vector2->delta_y);
	mu_assert_int_eq(1, vector2->direction_x);
	mu_assert_int_eq(1, vector2->direction_y);
	mu_assert_int_eq(0, vector2->a->z);
	mu_assert_int_eq(0, vector2->b->z);
	mu_assert_int_eq(0, vector2->a->color);
	mu_assert_int_eq(0, vector2->b->color);

	mu_assert(head->next != NULL, "The next node should not be NULL");
	vector1 = (t_vector *)head->next->content;
	mu_assert_int_eq(0, vector1->a->x);
	mu_assert_int_eq(0, vector1->a->y);
	mu_assert_int_eq(3, vector1->b->x);
	mu_assert_int_eq(4, vector1->b->y);
	mu_assert_int_eq(3, vector1->delta_x);
	mu_assert_int_eq(4, vector1->delta_y);
	mu_assert_int_eq(1, vector1->direction_x);
	mu_assert_int_eq(1, vector1->direction_y);
	mu_assert_int_eq(0, vector1->a->z);
	mu_assert_int_eq(0, vector1->b->z);
	mu_assert_int_eq(0, vector1->a->color);
	mu_assert_int_eq(0, vector1->b->color);

	mu_assert(head->next->next == NULL, "The next node of the second vector should be NULL");

	free(vector1);
	free(head->next);
	free(vector2);
	free(head);
}

MU_TEST_SUITE(test_add_vector_suite)
{
	MU_RUN_TEST(test_add_vector_valid_points);
	MU_RUN_TEST(test_add_vector_negative_delta);
	MU_RUN_TEST(test_add_vector_null_head);
	MU_RUN_TEST(test_add_vector_null_points);
	MU_RUN_TEST(test_add_vector_multiple_vectors);
}

int test_add_vector(void)
{
	MU_RUN_SUITE(test_add_vector_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
