/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_add_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:04:25 by jarao-de          #+#    #+#             */
/*   Updated: 2024/11/27 12:08:31 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include "minunit.h"
#include "fdf.h"

int capture_segfault_add_point(t_list *(*f)(t_list **, int, int, char *), t_list **points, int x, int y, char *cell)
{
	pid_t pid = fork();
	if (pid == 0)
	{
		// Child process executes the test
		f(points, x, y, cell);
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

MU_TEST(test_add_point_only_z_value)
{
	t_list	*points = NULL;
	t_point	*point;
	char	cell[] = "42";

	add_point(&points, 1, 2, cell);

	mu_assert(points != NULL, "The list should not be NULL");
	point = (t_point *)points->content;
	mu_assert_int_eq(1, point->x);
	mu_assert_int_eq(2, point->y);
	mu_assert_int_eq(42, point->z);
	mu_assert(points->next == NULL, "The next node should be NULL");

	free(point);
	free(points);
}

MU_TEST(test_add_point_zero_coordinates)
{
	t_list	*points = NULL;
	t_point	*point;
	char	cell[] = "0,0x000000";

	add_point(&points, 0, 0, cell);

	mu_assert(points != NULL, "The list should not be NULL");
	point = (t_point *)points->content;
	mu_assert_int_eq(0, point->x);
	mu_assert_int_eq(0, point->y);
	mu_assert_int_eq(0, point->z);
	mu_assert_int_eq(0x000000, point->color);
	mu_assert(points->next == NULL, "The next node should be NULL");

	free(point);
	free(points);
}

MU_TEST(test_add_point_negative_coordinates)
{
	t_list	*points = NULL;
	t_point	*point;
	char	cell[] = "-42,0xFFFFFF";

	add_point(&points, -1, -2, cell);

	mu_assert(points != NULL, "The list should not be NULL");
	point = (t_point *)points->content;
	mu_assert_int_eq(-1, point->x);
	mu_assert_int_eq(-2, point->y);
	mu_assert_int_eq(-42, point->z);
	mu_assert_int_eq(0xFFFFFF, point->color);
	mu_assert(points->next == NULL, "The next node should be NULL");

	free(point);
	free(points);
}

MU_TEST(test_add_point_large_coordinates)
{
	t_list	*points = NULL;
	t_point	*point;
	char	cell[] = "1000000,0xFFFFFF";

	add_point(&points, 1000000, 2000000, cell);

	mu_assert(points != NULL, "The list should not be NULL");
	point = (t_point *)points->content;
	mu_assert_int_eq(1000000, point->x);
	mu_assert_int_eq(2000000, point->y);
	mu_assert_int_eq(1000000, point->z);
	mu_assert_int_eq(0xFFFFFF, point->color);
	mu_assert(points->next == NULL, "The next node should be NULL");

	free(point);
	free(points);
}

MU_TEST(test_add_point_valid_data)
{
	t_list	*points = NULL;
	t_point	*point;
	char	cell[] = "42,0xFFFFFF";

	add_point(&points, 1, 2, cell);

	mu_assert(points != NULL, "The list should not be NULL");
	point = (t_point *)points->content;
	mu_assert_int_eq(1, point->x);
	mu_assert_int_eq(2, point->y);
	mu_assert_int_eq(42, point->z);
	mu_assert_int_eq(0xFFFFFF, point->color);
	mu_assert(points->next == NULL, "The next node should be NULL");

	free(point);
	free(points);
}

MU_TEST(test_add_point_invalid_data)
{
	t_list	*points = NULL;
	t_list	*expected_result;
	char	cell[] = "invalid";

	expected_result = add_point(&points, 1, 2, cell);

	mu_assert(expected_result == NULL, "The function should return NULL for invalid data");
	mu_assert(points == NULL, "The list should be NULL for invalid data");
}

MU_TEST(test_add_point_null_cell)
{
	t_list	*points = NULL;
	t_list	*expected_result;

	expected_result = add_point(&points, 1, 2, NULL);

	mu_assert(expected_result == NULL, "The function should return NULL for NULL cell");
	mu_assert(points == NULL, "The list should be NULL for NULL cell");
}

MU_TEST(test_add_point_multiple_points)
{
	t_list	*points = NULL;
	t_point	*point1;
	t_point	*point2;
	char	cell1[] = "42,0xFFFFFF";
	char	cell2[] = "84,0x000000";

	add_point(&points, 1, 2, cell1);
	add_point(&points, 3, 4, cell2);

	mu_assert(points != NULL, "The list should not be NULL");
	point1 = (t_point *)points->content;
	mu_assert_int_eq(1, point1->x);
	mu_assert_int_eq(2, point1->y);
	mu_assert_int_eq(42, point1->z);
	mu_assert_int_eq(0xFFFFFF, point1->color);

	mu_assert(points->next != NULL, "The next node should not be NULL");
	point2 = (t_point *)points->next->content;
	mu_assert_int_eq(3, point2->x);
	mu_assert_int_eq(4, point2->y);
	mu_assert_int_eq(84, point2->z);
	mu_assert_int_eq(0x000000, point2->color);

	mu_assert(points->next->next == NULL, "The next node of the second point should be NULL");

	free(point1);
	free(points->next);
	free(points);
}

MU_TEST(test_add_point_null_points)
{
	int		segfaulted;
	char	cell[] = "42,0xFFFFFF";

	segfaulted = capture_segfault_add_point(&add_point, NULL, 1, 2, cell);
	if (!segfaulted)
		add_point(NULL, 1, 2, cell);

	if (!segfaulted)
		mu_fail("Function should not cause a segmentation fault when points is NULL.");
}

MU_TEST(test_add_point_returns_head_pointer)
{
	t_list	*points = NULL;
	t_list	*head;
	char	cell[] = "42,0xFFFFFF";

	head = add_point(&points, 1, 2, cell);

	mu_assert(head == points, "The function should return a pointer to the head of the list");

	free(points->content);
	free(points);
}

MU_TEST(test_add_point_null_cell_segfault)
{
	t_list	*points = NULL;
	int		segfaulted;

	segfaulted = capture_segfault_add_point(&add_point, &points, 1, 2, NULL);
	if (!segfaulted)
		add_point(&points, 1, 2, NULL);

	// ASSERT
	if (!segfaulted)
	{
		mu_assert(points == NULL, "The list should be remain NULL for NULL cell");
	}
	if (segfaulted)
		mu_fail("Function should not cause a segmentation fault when cell is NULL.");
}

MU_TEST_SUITE(test_add_point_suite)
{
	MU_RUN_TEST(test_add_point_only_z_value);
	MU_RUN_TEST(test_add_point_zero_coordinates);
	MU_RUN_TEST(test_add_point_negative_coordinates);
	MU_RUN_TEST(test_add_point_large_coordinates);
	MU_RUN_TEST(test_add_point_valid_data);
	MU_RUN_TEST(test_add_point_invalid_data);
	MU_RUN_TEST(test_add_point_null_cell);
	MU_RUN_TEST(test_add_point_multiple_points);
	MU_RUN_TEST(test_add_point_null_points);
	MU_RUN_TEST(test_add_point_returns_head_pointer);
	MU_RUN_TEST(test_add_point_null_cell_segfault);
}

int test_add_point(void)
{
	MU_RUN_SUITE(test_add_point_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
