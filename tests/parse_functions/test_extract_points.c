/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_extract_points.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:39:11 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/04 07:32:59 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "minunit.h"

MU_TEST(test_extract_points_simple_file)
{
	// ARRANGE
	t_list	*points;
	int		fd;
	char	*filename = "simple_file.fdf";
	char	*file_content = "42";

	// Create a temporary file with the test content
	fd = open(filename, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
	{
		perror("Cannot create test file.");
		return;
	}
	write(fd, file_content, strlen(file_content));
	close(fd);

	// ACT
	points = extract_points(filename);

	// ASSERT
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(0, ((t_point *)points->content)->y);
	mu_assert_int_eq(42, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);
	ft_lstclear(&points, free);

	// Clean up the temporary file
	remove(filename);
}

MU_TEST(test_extract_points_multiple_points)
{
	// ARRANGE
	t_list	*points;
	int		fd;
	char	*filename = "multiple_points.fdf";
	char	*file_content = "0 1 2\n3 4 5";

	// Create a temporary file with the test content
	fd = open(filename, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
	{
		perror("Cannot create test file.");
		return;
	}
	write(fd, file_content, strlen(file_content));
	close(fd);

	// ACT
	points = extract_points(filename);

	// ASSERT
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(2, ((t_point *)points->content)->y);
	mu_assert_int_eq(5, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(1, ((t_point *)points->content)->y);
	mu_assert_int_eq(4, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(0, ((t_point *)points->content)->y);
	mu_assert_int_eq(3, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(2, ((t_point *)points->content)->y);
	mu_assert_int_eq(2, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(1, ((t_point *)points->content)->y);
	mu_assert_int_eq(1, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(0, ((t_point *)points->content)->y);
	mu_assert_int_eq(0, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	ft_lstclear(&points, free);

	// Clean up the temporary file
	remove(filename);
}

MU_TEST(test_extract_points_empty_file)
{
	// ARRANGE
	t_list	*points;
	int		fd;
	char	*filename = "empty_file.fdf";
	char	*file_content = "";

	// Create a temporary file with the test content
	fd = open(filename, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
	{
		perror("Cannot create test file.");
		return;
	}
	write(fd, file_content, strlen(file_content));
	close(fd);

	// ACT
	points = extract_points(filename);

	// ASSERT
	mu_assert(points == NULL, "Points should be NULL for an empty file.");

	// Clean up the temporary file
	remove(filename);
}

MU_TEST(test_extract_points_invalid_file)
{
	// ARRANGE
	t_list	*points;
	char	*filename = "non_existent_file.fdf";

	// ACT
	points = extract_points(filename);

	// ASSERT
	mu_assert(points == NULL, "Points should be NULL for a non-existent file.");
}

MU_TEST(test_extract_points_no_extension_file)
{
	// ARRANGE
	t_list	*points;
	int		fd;
	char	*filename = "no_extension";
	char	*file_content = "1 2 3\n4 5 6";

	// Create a temporary file with the test content
	fd = open(filename, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
	{
		perror("Cannot create test file.");
		return;
	}
	write(fd, file_content, strlen(file_content));
	close(fd);

	// ACT
	points = extract_points(filename);

	// ASSERT
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(2, ((t_point *)points->content)->y);
	mu_assert_int_eq(6, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(1, ((t_point *)points->content)->y);
	mu_assert_int_eq(5, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(0, ((t_point *)points->content)->y);
	mu_assert_int_eq(4, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(2, ((t_point *)points->content)->y);
	mu_assert_int_eq(3, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(1, ((t_point *)points->content)->y);
	mu_assert_int_eq(2, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(0, ((t_point *)points->content)->y);
	mu_assert_int_eq(1, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	ft_lstclear(&points, free);

	// Clean up the temporary file
	remove(filename);
}

MU_TEST_SUITE(parse_mapfile_test_suite)
{
	MU_RUN_TEST(test_extract_points_simple_file);
	MU_RUN_TEST(test_extract_points_multiple_points);
	MU_RUN_TEST(test_extract_points_empty_file);
	MU_RUN_TEST(test_extract_points_invalid_file);
	MU_RUN_TEST(test_extract_points_no_extension_file);
}

int	test_extract_points(void) {
	MU_RUN_SUITE(parse_mapfile_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
