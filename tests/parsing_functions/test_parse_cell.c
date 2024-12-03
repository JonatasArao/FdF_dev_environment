/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_cell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:29:26 by jarao-de          #+#    #+#             */
/*   Updated: 2024/11/26 14:45:55 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "minunit.h"

MU_TEST(test_parse_cell_z_forty_two)
{
	// ARRANGE
	int	expected_return;
	int	actual_return;
	int	expected_z_value;
	int	actual_z_value;
	int	expected_color_value;
	int	actual_color_value;
	t_point point;
	char input[] = "42";

	// ACT
	expected_return = 1;
	actual_return = parse_cell(input, &point);
	expected_z_value = 42;
	actual_z_value = point.z;
	expected_color_value = DEFAULT_COLOR;
	actual_color_value = point.color;

	// ASSERT
	mu_assert_int_eq(expected_return, actual_return);
	mu_assert_int_eq(expected_z_value, actual_z_value);
	mu_assert_int_eq(expected_color_value, actual_color_value);
}

MU_TEST(test_parse_cell_z_minus_forty_two)
{
	// ARRANGE
	int	expected_return;
	int	actual_return;
	int	expected_z_value;
	int	actual_z_value;
	int	expected_color_value;
	int	actual_color_value;
	t_point point;
	char input[] = "-42";

	// ACT
	expected_return = 1;
	actual_return = parse_cell(input, &point);
	expected_z_value = -42;
	actual_z_value = point.z;
	expected_color_value = DEFAULT_COLOR;
	actual_color_value = point.color;

	// ASSERT
	mu_assert_int_eq(expected_return, actual_return);
	mu_assert_int_eq(expected_z_value, actual_z_value);
	mu_assert_int_eq(expected_color_value, actual_color_value);
}

MU_TEST(test_parse_cell_z_forty_two_white_lowercase)
{
	// ARRANGE
	int	expected_return;
	int	actual_return;
	int	expected_z_value;
	int	actual_z_value;
	int	expected_color_value;
	int	actual_color_value;
	t_point point;
	char input[] = "42,0xffffff";

	// ACT
	expected_return = 1;
	actual_return = parse_cell(input, &point);
	expected_z_value = 42;
	actual_z_value = point.z;
	expected_color_value = 0xffffff;
	actual_color_value = point.color;

	// ASSERT
	mu_assert_int_eq(expected_return, actual_return);
	mu_assert_int_eq(expected_z_value, actual_z_value);
	mu_assert_int_eq(expected_color_value, actual_color_value);
}

MU_TEST(test_parse_cell_z_forty_two_white_uppercase)
{
	// ARRANGE
	int	expected_return;
	int	actual_return;
	int	expected_z_value;
	int	actual_z_value;
	int	expected_color_value;
	int	actual_color_value;
	t_point point;
	char input[] = "42,0xFFFFFF";

	// ACT
	expected_return = 1;
	actual_return = parse_cell(input, &point);
	expected_z_value = 42;
	actual_z_value = point.z;
	expected_color_value = 0xFFFFFF;
	actual_color_value = point.color;

	// ASSERT
	mu_assert_int_eq(expected_return, actual_return);
	mu_assert_int_eq(expected_z_value, actual_z_value);
	mu_assert_int_eq(expected_color_value, actual_color_value);
}

MU_TEST(test_parse_cell_short_color_hex)
{
	// ARRANGE
	int	expected_return;
	int	actual_return;
	int	expected_z_value;
	int	actual_z_value;
	int	expected_color_value;
	int	actual_color_value;
	t_point point;
	char input[] = "42,0xFFF";

	// ACT
	expected_return = 1;
	actual_return = parse_cell(input, &point);
	expected_z_value = 42;
	actual_z_value = point.z;
	expected_color_value = 0xFFF;
	actual_color_value = point.color;

	// ASSERT
	mu_assert_int_eq(expected_return, actual_return);
	mu_assert_int_eq(expected_z_value, actual_z_value);
	mu_assert_int_eq(expected_color_value, actual_color_value);
}

MU_TEST(test_parse_cell_invalid_z_value)
{
	// ARRANGE
	int	expected_return;
	int	actual_return;
	t_point point;
	char input[] = "43invalid";

	// ACT
	expected_return = 0;
	actual_return = parse_cell(input, &point);

	// ASSERT
	mu_assert_int_eq(expected_return, actual_return);
}

MU_TEST(test_parse_cell_invalid_color)
{
	// ARRANGE
	int	expected_return;
	int	actual_return;
	int	expected_z_value;
	int	actual_z_value;
	int	expected_color_value;
	int	actual_color_value;
	t_point point;
	char input[] = "42,invalid";

	// ACT
	expected_return = 1;
	actual_return = parse_cell(input, &point);
	expected_z_value = 42;
	actual_z_value = point.z;
	expected_color_value = DEFAULT_COLOR;
	actual_color_value = point.color;

	// ASSERT
	mu_assert_int_eq(expected_return, actual_return);
	mu_assert_int_eq(expected_z_value, actual_z_value);
	mu_assert_int_eq(expected_color_value, actual_color_value);
}

MU_TEST(test_parse_cell_invalid_color_missing_value)
{
	// ARRANGE
	int	expected_return;
	int	actual_return;
	int	expected_z_value;
	int	actual_z_value;
	int	expected_color_value;
	int	actual_color_value;
	t_point point;
	char input[] = "42,0x";

	// ACT
	expected_return = 1;
	actual_return = parse_cell(input, &point);
	expected_z_value = 42;
	actual_z_value = point.z;
	expected_color_value = DEFAULT_COLOR;
	actual_color_value = point.color;

	// ASSERT
	mu_assert_int_eq(expected_return, actual_return);
	mu_assert_int_eq(expected_z_value, actual_z_value);
	mu_assert_int_eq(expected_color_value, actual_color_value);
}

MU_TEST(test_parse_cell_invalid_color_hex)
{
	// ARRANGE
	int	expected_return;
	int	actual_return;
	int	expected_z_value;
	int	actual_z_value;
	int	expected_color_value;
	int	actual_color_value;
	t_point point;
	char input[] = "42,0xZZZZZZ";

	// ACT
	expected_return = 1;
	actual_return = parse_cell(input, &point);
	expected_z_value = 42;
	actual_z_value = point.z;
	expected_color_value = DEFAULT_COLOR;
	actual_color_value = point.color;

	// ASSERT
	mu_assert_int_eq(expected_return, actual_return);
	mu_assert_int_eq(expected_z_value, actual_z_value);
	mu_assert_int_eq(expected_color_value, actual_color_value);
}

MU_TEST(test_parse_cell_invalid_color_format)
{
	// ARRANGE
	int	expected_return;
	int	actual_return;
	int	expected_z_value;
	int	actual_z_value;
	int	expected_color_value;
	int	actual_color_value;
	t_point point;
	char input[] = "42,#FFFFFF";

	// ACT
	expected_return = 1;
	actual_return = parse_cell(input, &point);
	expected_z_value = 42;
	actual_z_value = point.z;
	expected_color_value = DEFAULT_COLOR;
	actual_color_value = point.color;

	// ASSERT
	mu_assert_int_eq(expected_return, actual_return);
	mu_assert_int_eq(expected_z_value, actual_z_value);
	mu_assert_int_eq(expected_color_value, actual_color_value);
}

MU_TEST_SUITE(parse_cell_test_suite)
{
	MU_RUN_TEST(test_parse_cell_z_forty_two);
	MU_RUN_TEST(test_parse_cell_z_minus_forty_two);
	MU_RUN_TEST(test_parse_cell_z_forty_two_white_lowercase);
	MU_RUN_TEST(test_parse_cell_z_forty_two_white_uppercase);
	MU_RUN_TEST(test_parse_cell_short_color_hex);
	MU_RUN_TEST(test_parse_cell_invalid_z_value);
	MU_RUN_TEST(test_parse_cell_invalid_color);
	MU_RUN_TEST(test_parse_cell_invalid_color_missing_value);
	MU_RUN_TEST(test_parse_cell_invalid_color_hex);
	MU_RUN_TEST(test_parse_cell_invalid_color_format);
}

int	test_parse_cell(void) {
	MU_RUN_SUITE(parse_cell_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
