/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:17:04 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/04 09:57:22 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "minunit.h"

MU_TEST(test_parse_line_single_value)
{
	// ARRANGE
	int	expected_return;
	int	actual_return;
	t_list	*points = NULL;
	char input[] = "42";

	// ACT
	expected_return = 1;
	actual_return = parse_line(84, input, &points);

	// ASSERT
	mu_assert_int_eq(expected_return, actual_return);
	mu_assert_int_eq(0, ((t_point *)points->content)->x);
	mu_assert_int_eq(84, ((t_point *)points->content)->y);
	mu_assert_int_eq(42, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);
	ft_lstclear(&points, free);
}

MU_TEST(test_parse_line_multiple_values)
{
	// ARRANGE
	int	expected_return;
	int	actual_return;
	t_list	*points = NULL;
	char input[] = "42 -42 0";

	// ACT
	expected_return = 3;
	actual_return = parse_line(84, input, &points);

	// ASSERT
	mu_assert_int_eq(expected_return, actual_return);
	mu_assert_int_eq(2, ((t_point *)points->content)->x);
	mu_assert_int_eq(84, ((t_point *)points->content)->y);
	mu_assert_int_eq(0, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	mu_assert_int_eq(1, ((t_point *)points->next->content)->x);
	mu_assert_int_eq(84, ((t_point *)points->next->content)->y);
	mu_assert_int_eq(-42, ((t_point *)points->next->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->next->content)->color);

	mu_assert_int_eq(0, ((t_point *)points->next->next->content)->x);
	mu_assert_int_eq(84, ((t_point *)points->next->next->content)->y);
	mu_assert_int_eq(42, ((t_point *)points->next->next->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->next->next->content)->color);
	ft_lstclear(&points, free);
}

MU_TEST(test_parse_line_with_colors)
{
	// ARRANGE
	int	expected_return;
	int	actual_return;
	t_list	*points = NULL;
	char input[] = "42,0xFFFFFF -42,0x000000 0,0x123456";

	// ACT
	expected_return = 3;
	actual_return = parse_line(84, input, &points);

	// ASSERT
	mu_assert_int_eq(2, ((t_point *)points->content)->x);
	mu_assert_int_eq(84, ((t_point *)points->content)->y);
	mu_assert_int_eq(0, ((t_point *)points->content)->z);
	mu_assert_int_eq(0x123456, ((t_point *)points->content)->color);

	mu_assert_int_eq(1, ((t_point *)points->next->content)->x);
	mu_assert_int_eq(84, ((t_point *)points->next->content)->y);
	mu_assert_int_eq(-42, ((t_point *)points->next->content)->z);
	mu_assert_int_eq(0x000000, ((t_point *)points->next->content)->color);

	mu_assert_int_eq(expected_return, actual_return);
	mu_assert_int_eq(0, ((t_point *)points->next->next->content)->x);
	mu_assert_int_eq(84, ((t_point *)points->next->next->content)->y);
	mu_assert_int_eq(42, ((t_point *)points->next->next->content)->z);
	mu_assert_int_eq(0xFFFFFF, ((t_point *)points->next->next->content)->color);
	ft_lstclear(&points, free);
}

MU_TEST(test_parse_line_invalid_input)
{
	// ARRANGE
	int	expected_return;
	int	actual_return;
	t_list	*points = NULL;
	char input[] = "invalid";

	// ACT
	expected_return = -1;
	actual_return = parse_line(0, input, &points);

	// ASSERT
	mu_assert_int_eq(expected_return, actual_return);
	mu_assert(points == NULL, "Points list should be NULL");
}

MU_TEST(test_parse_line_empty_input)
{
	// ARRANGE
	int	expected_return;
	int	actual_return;
	t_list	*points = NULL;
	char input[] = "";

	// ACT
	expected_return = 0;
	actual_return = parse_line(84, input, &points);

	// ASSERT
	mu_assert_int_eq(expected_return, actual_return);
	mu_assert(points == NULL, "Points list should be NULL");
}

MU_TEST(test_parse_line_with_mixed_valid_invalid_values)
{
	// ARRANGE
	int	expected_return;
	int	actual_return;
	t_list	*points = NULL;
	char input[] = "42 invalid -42";

	// ACT
	expected_return = -1;
	actual_return = parse_line(84, input, &points);

	// ASSERT
	mu_assert_int_eq(expected_return, actual_return);
	mu_assert(points == NULL, "Points list should be NULL");
}

MU_TEST(test_parse_line_with_extra_spaces)
{
	// ARRANGE
	int	expected_return;
	int	actual_return;
	t_list	*points = NULL;
	char input[] = "  42   -42  0  ";

	// ACT
	expected_return = 3;
	actual_return = parse_line(84, input, &points);

	// ASSERT
	mu_assert_int_eq(expected_return, actual_return);
	mu_assert_int_eq(2, ((t_point *)points->content)->x);
	mu_assert_int_eq(84, ((t_point *)points->content)->y);
	mu_assert_int_eq(0, ((t_point *)points->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->content)->color);

	mu_assert_int_eq(1, ((t_point *)points->next->content)->x);
	mu_assert_int_eq(84, ((t_point *)points->next->content)->y);
	mu_assert_int_eq(-42, ((t_point *)points->next->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->next->content)->color);

	mu_assert_int_eq(0, ((t_point *)points->next->next->content)->x);
	mu_assert_int_eq(84, ((t_point *)points->next->next->content)->y);
	mu_assert_int_eq(42, ((t_point *)points->next->next->content)->z);
	mu_assert_int_eq(DEFAULT_COLOR, ((t_point *)points->next->next->content)->color);
	ft_lstclear(&points, free);
}

MU_TEST(test_parse_line_with_negative_coordinates)
{
	// ARRANGE
	int	expected_return;
	int	actual_return;
	t_list	*points = NULL;
	char input[] = "-42,-0xFFFFFF 42,0x000000";

	// ACT
	expected_return = 2;
	actual_return = parse_line(-84, input, &points);

	// ASSERT
	mu_assert_int_eq(expected_return, actual_return);
	mu_assert_int_eq(1, ((t_point *)points->content)->x);
	mu_assert_int_eq(-84, ((t_point *)points->content)->y);
	mu_assert_int_eq(42, ((t_point *)points->content)->z);
	mu_assert_int_eq(0x000000, ((t_point *)points->content)->color);

	mu_assert_int_eq(0, ((t_point *)points->next->content)->x);
	mu_assert_int_eq(-84, ((t_point *)points->next->content)->y);
	mu_assert_int_eq(-42, ((t_point *)points->next->content)->z);
	mu_assert_int_eq(0xFFFFFF, ((t_point *)points->next->content)->color);
	ft_lstclear(&points, free);
}

MU_TEST_SUITE(parse_line_test_suite)
{
	MU_RUN_TEST(test_parse_line_single_value);
	MU_RUN_TEST(test_parse_line_multiple_values);
	MU_RUN_TEST(test_parse_line_with_colors);
	MU_RUN_TEST(test_parse_line_invalid_input);
	MU_RUN_TEST(test_parse_line_empty_input);
	MU_RUN_TEST(test_parse_line_with_mixed_valid_invalid_values);
	MU_RUN_TEST(test_parse_line_with_extra_spaces);
	MU_RUN_TEST(test_parse_line_with_negative_coordinates);
}

int	test_parse_line(void) {
	MU_RUN_SUITE(parse_line_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
