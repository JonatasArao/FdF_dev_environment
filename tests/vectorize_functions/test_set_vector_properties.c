/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set_vector_properties.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:04:25 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/05 17:28:10 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include "minunit.h"
#include "fdf.h"

int capture_segfault_set_vector_properties(void (*f)(void *), void *vector_ptr)
{
	pid_t pid = fork();
	if (pid == 0)
	{
		// Child process executes the test
		f(vector_ptr);
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

MU_TEST(test_set_vector_properties_valid_points)
{
	t_vector vector;
	t_point	a = {0, 0, 0, 0};
	t_point	b = {0, 3, 4, 0};

	vector.a = &a;
	vector.b = &b;

	set_vector_properties(&vector);

	mu_assert_int_eq(0, vector.a->x);
	mu_assert_int_eq(0, vector.a->y);
	mu_assert_int_eq(3, vector.b->x);
	mu_assert_int_eq(4, vector.b->y);
	mu_assert_int_eq(3, vector.delta_x);
	mu_assert_int_eq(4, vector.delta_y);
	mu_assert_int_eq(1, vector.direction_x);
	mu_assert_int_eq(1, vector.direction_y);
}

MU_TEST(test_set_vector_properties_negative_delta)
{
	t_vector vector;
	t_point	a = {0, 3, 4, 0};
	t_point	b = {0, 0, 0, 0};

	vector.a = &a;
	vector.b = &b;

	set_vector_properties(&vector);

	mu_assert_int_eq(3, vector.a->x);
	mu_assert_int_eq(4, vector.a->y);
	mu_assert_int_eq(0, vector.b->x);
	mu_assert_int_eq(0, vector.b->y);
	mu_assert_int_eq(-3, vector.delta_x);
	mu_assert_int_eq(-4, vector.delta_y);
	mu_assert_int_eq(-1, vector.direction_x);
	mu_assert_int_eq(-1, vector.direction_y);
}

MU_TEST(test_set_vector_properties_null_vector)
{
	int segfaulted = capture_segfault_set_vector_properties(set_vector_properties, NULL);
	if (!segfaulted)
		set_vector_properties(NULL);

	if (segfaulted)
		mu_fail("Function should not cause a segmentation fault when head is NULL.");
}

MU_TEST(test_set_vector_properties_null_a_and_b)
{
	t_vector vector;
	vector.a = NULL;
	vector.b = NULL;

	int segfaulted = capture_segfault_set_vector_properties(set_vector_properties, NULL);
	if (!segfaulted)
		set_vector_properties(&vector);

	if (segfaulted)
		mu_fail("Function should not cause a segmentation fault when points are NULL.");
}

MU_TEST(test_set_vector_properties_multiple_vectors)
{
	t_vector vector1;
	t_vector vector2;
	t_point	a1 = {0, 0, 0, 0};
	t_point	b1 = {0, 3, 4, 0};
	t_point	a2 = {0, 1, 1, 0};
	t_point	b2 = {0, 4, 5, 0};

	vector1.a = &a1;
	vector1.b = &b1;
	vector2.a = &a2;
	vector2.b = &b2;

	set_vector_properties(&vector1);
	set_vector_properties(&vector2);

	mu_assert_int_eq(0, vector1.a->x);
	mu_assert_int_eq(0, vector1.a->y);
	mu_assert_int_eq(3, vector1.b->x);
	mu_assert_int_eq(4, vector1.b->y);
	mu_assert_int_eq(3, vector1.delta_x);
	mu_assert_int_eq(4, vector1.delta_y);
	mu_assert_int_eq(1, vector1.direction_x);
	mu_assert_int_eq(1, vector1.direction_y);

	mu_assert_int_eq(1, vector2.a->x);
	mu_assert_int_eq(1, vector2.a->y);
	mu_assert_int_eq(4, vector2.b->x);
	mu_assert_int_eq(5, vector2.b->y);
	mu_assert_int_eq(3, vector2.delta_x);
	mu_assert_int_eq(4, vector2.delta_y);
	mu_assert_int_eq(1, vector2.direction_x);
	mu_assert_int_eq(1, vector2.direction_y);
}

MU_TEST_SUITE(test_set_vector_properties_suite)
{
	MU_RUN_TEST(test_set_vector_properties_valid_points);
	MU_RUN_TEST(test_set_vector_properties_negative_delta);
	MU_RUN_TEST(test_set_vector_properties_null_vector);
	MU_RUN_TEST(test_set_vector_properties_null_a_and_b);
	MU_RUN_TEST(test_set_vector_properties_multiple_vectors);
}

int test_set_vector_properties(void)
{
	MU_RUN_SUITE(test_set_vector_properties_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
