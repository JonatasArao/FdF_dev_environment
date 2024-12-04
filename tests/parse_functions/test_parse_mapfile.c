/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_mapfile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:06:14 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/03 17:18:40 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "minunit.h"

MU_TEST(test_parse_mapfile_single)
{
	// ARRANGE
	t_list	*points = NULL;
	char input[] = "42";
	int fd[2];

	// ACT
	pipe(fd);
	write(fd[1], input, sizeof(input));
	close(fd[1]);
	parse_mapfile(fd[0], &points);

	// ASSERT
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(0, ((t_point *)points->content)->y);
	mu_assert_int_eq(42, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);
	ft_lstclear(&points, free);
	close(fd[0]);
}

MU_TEST(test_parse_mapfile_multiple)
{
	// ARRANGE
	t_list	*points = NULL;
	char input[] = "42 21\n84 63";
	int fd[2];

	// ACT
	pipe(fd);
	write(fd[1], input, sizeof(input));
	close(fd[1]);
	parse_mapfile(fd[0], &points);

	// ASSERT
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(1, ((t_point *)points->content)->y);
	mu_assert_int_eq(63, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(0, ((t_point *)points->content)->y);
	mu_assert_int_eq(84, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(1, ((t_point *)points->content)->y);
	mu_assert_int_eq(21, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(0, ((t_point *)points->content)->y);
	mu_assert_int_eq(42, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	ft_lstclear(&points, free);
	close(fd[0]);
}

MU_TEST(test_parse_mapfile_negative_values)
{
	// ARRANGE
	t_list	*points = NULL;
	char input[] = "-42 -21\n-84 -63";
	int fd[2];

	// ACT
	pipe(fd);
	write(fd[1], input, sizeof(input));
	close(fd[1]);
	parse_mapfile(fd[0], &points);

	// ASSERT
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(1, ((t_point *)points->content)->y);
	mu_assert_int_eq(-63, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(0, ((t_point *)points->content)->y);
	mu_assert_int_eq(-84, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(1, ((t_point *)points->content)->y);
	mu_assert_int_eq(-21, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(0, ((t_point *)points->content)->y);
	mu_assert_int_eq(-42, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	ft_lstclear(&points, free);
	close(fd[0]);
}

MU_TEST(test_parse_mapfile_with_color)
{
	// ARRANGE
	t_list	*points = NULL;
	char input[] = "42,0xFFFFFF 21,0x000000\n84,0xFF0000 63,0x00FF00";
	int fd[2];

	// ACT
	pipe(fd);
	write(fd[1], input, sizeof(input));
	close(fd[1]);
	parse_mapfile(fd[0], &points);

	// ASSERT
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(1, ((t_point *)points->content)->y);
	mu_assert_int_eq(63, ((t_point *)points->content)->z);
	mu_assert_int_eq(0x00FF00, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(0, ((t_point *)points->content)->y);
	mu_assert_int_eq(84, ((t_point *)points->content)->z);
	mu_assert_int_eq(0xFF0000, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(1, ((t_point *)points->content)->y);
	mu_assert_int_eq(21, ((t_point *)points->content)->z);
	mu_assert_int_eq(0x000000, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(0, ((t_point *)points->content)->y);
	mu_assert_int_eq(42, ((t_point *)points->content)->z);
	mu_assert_int_eq(0xFFFFFF, ((t_point *)points->content)->color);

	ft_lstclear(&points, free);
	close(fd[0]);
}

MU_TEST(test_parse_mapfile_mixed_values_with_color)
{
	// ARRANGE
	t_list	*points = NULL;
	char input[] = "42,0xFFFFFF -21\n-84,0xFF0000 63,0x00FF00";
	int fd[2];

	// ACT
	pipe(fd);
	write(fd[1], input, sizeof(input));
	close(fd[1]);
	parse_mapfile(fd[0], &points);

	// ASSERT
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(1, ((t_point *)points->content)->y);
	mu_assert_int_eq(63, ((t_point *)points->content)->z);
	mu_assert_int_eq(0x00FF00, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(0, ((t_point *)points->content)->y);
	mu_assert_int_eq(-84, ((t_point *)points->content)->z);
	mu_assert_int_eq(0xFF0000, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(1, ((t_point *)points->content)->y);
	mu_assert_int_eq(-21, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(0, ((t_point *)points->content)->y);
	mu_assert_int_eq(42, ((t_point *)points->content)->z);
	mu_assert_int_eq(0xFFFFFF, ((t_point *)points->content)->color);

	ft_lstclear(&points, free);
	close(fd[0]);
}

MU_TEST(test_parse_mapfile_invalid_input)
{
	// ARRANGE
	t_list	*points = NULL;
	char input[] = "invalid input";
	int fd[2];

	// ACT
	pipe(fd);
	write(fd[1], input, sizeof(input));
	close(fd[1]);
	parse_mapfile(fd[0], &points);

	// ASSERT
	mu_assert(points == NULL, "Points list should be NULL for invalid input");

	close(fd[0]);
}

MU_TEST(test_parse_mapfile_invalid_numbers)
{
	// ARRANGE
	t_list	*points = NULL;
	char input[] = "42 abc\n84 63";
	int fd[2];

	// ACT
	pipe(fd);
	write(fd[1], input, sizeof(input));
	close(fd[1]);
	parse_mapfile(fd[0], &points);

	// ASSERT
	mu_assert(points == NULL, "Points list should be NULL for invalid numbers");

	close(fd[0]);
}

MU_TEST(test_parse_mapfile_invalid_colors)
{
	// ARRANGE
	t_list	*points = NULL;
	char input[] = "42,0xZZZZZZ 21,0x000000\n84,0xFF0000 63,0x00FF00";
	int fd[2];

	// ACT
	pipe(fd);
	write(fd[1], input, sizeof(input));
	close(fd[1]);
	parse_mapfile(fd[0], &points);

	// ASSERT
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(1, ((t_point *)points->content)->y);
	mu_assert_int_eq(63, ((t_point *)points->content)->z);
	mu_assert_int_eq(0x00FF00, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(0, ((t_point *)points->content)->y);
	mu_assert_int_eq(84, ((t_point *)points->content)->z);
	mu_assert_int_eq(0xFF0000, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(1, ((t_point *)points->content)->y);
	mu_assert_int_eq(21, ((t_point *)points->content)->z);
	mu_assert_int_eq(0x000000, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(0, ((t_point *)points->content)->y);
	mu_assert_int_eq(42, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	ft_lstclear(&points, free);
	close(fd[0]);
}

MU_TEST(test_parse_mapfile_empty)
{
	// ARRANGE
	t_list	*points = NULL;
	char input[] = "";
	int fd[2];

	// ACT
	pipe(fd);
	write(fd[1], input, sizeof(input));
	close(fd[1]);
	parse_mapfile(fd[0], &points);

	// ASSERT
	mu_assert(points == NULL, "Points list should be NULL for empty input");

	close(fd[0]);
}

MU_TEST(test_parse_mapfile_large_numbers)
{
	// ARRANGE
	t_list	*points = NULL;
	char input[] = "2147483647 -2147483648\n0 123456789";
	int fd[2];

	// ACT
	pipe(fd);
	write(fd[1], input, sizeof(input));
	close(fd[1]);
	parse_mapfile(fd[0], &points);

	// ASSERT
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(1, ((t_point *)points->content)->y);
	mu_assert_int_eq(123456789, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(0, ((t_point *)points->content)->y);
	mu_assert_int_eq(0, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(1, ((t_point *)points->content)->y);
	mu_assert_int_eq(-2147483648, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(0, ((t_point *)points->content)->y);
	mu_assert_int_eq(2147483647, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	ft_lstclear(&points, free);
	close(fd[0]);
}

MU_TEST(test_parse_mapfile_mixed_invalid_and_valid)
{
	// ARRANGE
	t_list	*points = NULL;
	char input[] = "42 abc\n84,0xFF0000 invalid";
	int fd[2];

	// ACT
	pipe(fd);
	write(fd[1], input, sizeof(input));
	close(fd[1]);
	parse_mapfile(fd[0], &points);

	// ASSERT
	mu_assert(points == NULL, "Points list should be NULL for mixed invalid and valid input");

	close(fd[0]);
}

MU_TEST(test_parse_mapfile_extra_spaces)
{
	// ARRANGE
	t_list	*points = NULL;
	char input[] = "  42,0xFFFFFF   21,0x000000  \n  84,0xFF0000  63,0x00FF00  ";
	int fd[2];

	// ACT
	pipe(fd);
	write(fd[1], input, sizeof(input));
	close(fd[1]);
	parse_mapfile(fd[0], &points);

	// ASSERT
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(1, ((t_point *)points->content)->y);
	mu_assert_int_eq(63, ((t_point *)points->content)->z);
	mu_assert_int_eq(0x00FF00, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(0, ((t_point *)points->content)->y);
	mu_assert_int_eq(84, ((t_point *)points->content)->z);
	mu_assert_int_eq(0xFF0000, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(1, ((t_point *)points->content)->y);
	mu_assert_int_eq(21, ((t_point *)points->content)->z);
	mu_assert_int_eq(0x000000, ((t_point *)points->content)->color);

	points = points->next;
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(0, ((t_point *)points->content)->y);
	mu_assert_int_eq(42, ((t_point *)points->content)->z);
	mu_assert_int_eq(0xFFFFFF, ((t_point *)points->content)->color);

	ft_lstclear(&points, free);
	close(fd[0]);
}

MU_TEST(test_parse_mapfile_spaces_between_comma)
{
	// ARRANGE
	t_list	*points = NULL;
	char input[] = "  42  ,  0xFFFFFF   21  ,  0x000000  \n  84  ,  0xFF0000  63  ,  0x00FF00  ";
	int fd[2];

	// ACT
	pipe(fd);
	write(fd[1], input, sizeof(input));
	close(fd[1]);
	parse_mapfile(fd[0], &points);

	// ASSERT
	mu_assert(points == NULL, "Points list should be NULL for mixed invalid and valid input");

	close(fd[0]);
}

MU_TEST_SUITE(parse_mapfile_test_suite)
{
	MU_RUN_TEST(test_parse_mapfile_single);
	MU_RUN_TEST(test_parse_mapfile_multiple);
	MU_RUN_TEST(test_parse_mapfile_empty);
	MU_RUN_TEST(test_parse_mapfile_negative_values);
	MU_RUN_TEST(test_parse_mapfile_invalid_input);
	MU_RUN_TEST(test_parse_mapfile_with_color);
	MU_RUN_TEST(test_parse_mapfile_mixed_values_with_color);
	MU_RUN_TEST(test_parse_mapfile_invalid_numbers);
	MU_RUN_TEST(test_parse_mapfile_invalid_colors);
	MU_RUN_TEST(test_parse_mapfile_large_numbers);
	MU_RUN_TEST(test_parse_mapfile_mixed_invalid_and_valid);
	MU_RUN_TEST(test_parse_mapfile_extra_spaces);
	MU_RUN_TEST(test_parse_mapfile_spaces_between_comma);
}

int	test_parse_mapfile(void) {
	MU_RUN_SUITE(parse_mapfile_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
