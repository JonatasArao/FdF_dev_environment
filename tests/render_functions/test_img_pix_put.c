/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_img_pix_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:37:46 by jarao-de          #+#    #+#             */
/*   Updated: 2024/11/25 15:35:55 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "minunit.h"

MU_TEST(test_img_pix_put_red)
{
	// ARRANGE
	t_img img;
	t_point point;
	char buffer[WINDOW_WIDTH * WINDOW_HEIGHT * 4] = {0};

	img.img = NULL;
	img.addr = buffer;
	img.bits_per_pixel = 32;
	img.line_len = WINDOW_WIDTH * 4;
	img.endian = 0;

	point.color = 0xFF0000; // Red color
	point.x = 50;
	point.y = 50;
	point.z = 0;

	// ACT
	img_pix_put(&img, point);

	// ASSERT
	mu_assert_int_eq(0xFF, (unsigned char)buffer[50 * img.line_len + 50 * 4 + 2]); // Red channel
	mu_assert_int_eq(0x00, (unsigned char)buffer[50 * img.line_len + 50 * 4 + 1]); // Green channel
	mu_assert_int_eq(0x00, (unsigned char)buffer[50 * img.line_len + 50 * 4 + 0]); // Blue channel
}

MU_TEST(test_img_pix_put_green)
{
	// ARRANGE
	t_img img;
	t_point point;
	char buffer[WINDOW_WIDTH * WINDOW_HEIGHT * 4] = {0};

	img.img = NULL;
	img.addr = buffer;
	img.bits_per_pixel = 32;
	img.line_len = WINDOW_WIDTH * 4;
	img.endian = 0;

	point.color = 0x00FF00; // Green color
	point.x = 60;
	point.y = 60;
	point.z = 0;

	// ACT
	img_pix_put(&img, point);

	// ASSERT
	mu_assert_int_eq(0x00, (unsigned char)buffer[60 * img.line_len + 60 * 4 + 2]); // Red channel
	mu_assert_int_eq(0xFF, (unsigned char)buffer[60 * img.line_len + 60 * 4 + 1]); // Green channel
	mu_assert_int_eq(0x00, (unsigned char)buffer[60 * img.line_len + 60 * 4 + 0]); // Blue channel
}

MU_TEST(test_img_pix_put_blue)
{
	// ARRANGE
	t_img img;
	t_point point;
	char buffer[WINDOW_WIDTH * WINDOW_HEIGHT * 4] = {0};

	img.img = NULL;
	img.addr = buffer;
	img.bits_per_pixel = 32;
	img.line_len = WINDOW_WIDTH * 4;
	img.endian = 0;

	point.color = 0x0000FF; // Blue color
	point.x = 30;
	point.y = 30;
	point.z = 0;

	// ACT
	img_pix_put(&img, point);

	// ASSERT
	mu_assert_int_eq(0x00, (unsigned char)buffer[30 * img.line_len + 30 * 4 + 2]); // Red channel
	mu_assert_int_eq(0x00, (unsigned char)buffer[30 * img.line_len + 30 * 4 + 1]); // Green channel
	mu_assert_int_eq(0xFF, (unsigned char)buffer[30 * img.line_len + 30 * 4 + 0]); // Blue channel
}

MU_TEST(test_img_pix_put_white)
{
	// ARRANGE
	t_img img;
	t_point point;
	char buffer[WINDOW_WIDTH * WINDOW_HEIGHT * 4] = {0};

	img.img = NULL;
	img.addr = buffer;
	img.bits_per_pixel = 32;
	img.line_len = WINDOW_WIDTH * 4;
	img.endian = 0;

	point.color = 0xFFFFFF; // White color
	point.x = 40;
	point.y = 40;
	point.z = 0;

	// ACT
	img_pix_put(&img, point);

	// ASSERT
	mu_assert_int_eq(0xFF, (unsigned char)buffer[40 * img.line_len + 40 * 4 + 2]); // Red channel
	mu_assert_int_eq(0xFF, (unsigned char)buffer[40 * img.line_len + 40 * 4 + 1]); // Green channel
	mu_assert_int_eq(0xFF, (unsigned char)buffer[40 * img.line_len + 40 * 4 + 0]); // Blue channel
}

MU_TEST(test_img_pix_put_red_big_endian)
{
	// ARRANGE
	t_img img;
	t_point point;
	char buffer[WINDOW_WIDTH * WINDOW_HEIGHT * 4] = {0};

	img.img = NULL;
	img.addr = buffer;
	img.bits_per_pixel = 32;
	img.line_len = WINDOW_WIDTH * 4;
	img.endian = 1;

	point.color = 0xFF0000; // Red color
	point.x = 50;
	point.y = 50;
	point.z = 0;

	// ACT
	img_pix_put(&img, point);

	// ASSERT
	mu_assert_int_eq(0xFF, (unsigned char)buffer[50 * img.line_len + 50 * 4 + 1]); // Red channel
	mu_assert_int_eq(0x00, (unsigned char)buffer[50 * img.line_len + 50 * 4 + 2]); // Green channel
	mu_assert_int_eq(0x00, (unsigned char)buffer[50 * img.line_len + 50 * 4 + 3]); // Blue channel
}

MU_TEST(test_img_pix_put_green_big_endian)
{
	// ARRANGE
	t_img img;
	t_point point;
	char buffer[WINDOW_WIDTH * WINDOW_HEIGHT * 4] = {0};

	img.img = NULL;
	img.addr = buffer;
	img.bits_per_pixel = 32;
	img.line_len = WINDOW_WIDTH * 4;
	img.endian = 1;

	point.color = 0x00FF00; // Green color
	point.x = 60;
	point.y = 60;
	point.z = 0;

	// ACT
	img_pix_put(&img, point);

	// ASSERT
	mu_assert_int_eq(0x00, (unsigned char)buffer[60 * img.line_len + 60 * 4 + 1]); // Red channel
	mu_assert_int_eq(0xFF, (unsigned char)buffer[60 * img.line_len + 60 * 4 + 2]); // Green channel
	mu_assert_int_eq(0x00, (unsigned char)buffer[60 * img.line_len + 60 * 4 + 3]); // Blue channel
}

MU_TEST(test_img_pix_put_blue_big_endian)
{
	// ARRANGE
	t_img img;
	t_point point;
	char buffer[WINDOW_WIDTH * WINDOW_HEIGHT * 4] = {0};

	img.img = NULL;
	img.addr = buffer;
	img.bits_per_pixel = 32;
	img.line_len = WINDOW_WIDTH * 4;
	img.endian = 1;

	point.color = 0x0000FF; // Blue color
	point.x = 30;
	point.y = 30;
	point.z = 0;

	// ACT
	img_pix_put(&img, point);

	// ASSERT
	mu_assert_int_eq(0x00, (unsigned char)buffer[30 * img.line_len + 30 * 4 + 1]); // Red channel
	mu_assert_int_eq(0x00, (unsigned char)buffer[30 * img.line_len + 30 * 4 + 2]); // Green channel
	mu_assert_int_eq(0xFF, (unsigned char)buffer[30 * img.line_len + 30 * 4 + 3]); // Blue channel
}

MU_TEST(test_img_pix_put_white_big_endian)
{
	// ARRANGE
	t_img img;
	t_point point;
	char buffer[WINDOW_WIDTH * WINDOW_HEIGHT * 4] = {0};

	img.img = NULL;
	img.addr = buffer;
	img.bits_per_pixel = 32;
	img.line_len = WINDOW_WIDTH * 4;
	img.endian = 1;

	point.color = 0xFFFFFF; // White color
	point.x = 40;
	point.y = 40;
	point.z = 0;

	// ACT
	img_pix_put(&img, point);

	// ASSERT
	mu_assert_int_eq(0xFF, (unsigned char)buffer[40 * img.line_len + 40 * 4 + 1]); // Red channel
	mu_assert_int_eq(0xFF, (unsigned char)buffer[40 * img.line_len + 40 * 4 + 2]); // Green channel
	mu_assert_int_eq(0xFF, (unsigned char)buffer[40 * img.line_len + 40 * 4 + 3]); // Blue channel
}

MU_TEST_SUITE(test_img_pix_put_suite)
{
	MU_RUN_TEST(test_img_pix_put_red);
	MU_RUN_TEST(test_img_pix_put_green);
	MU_RUN_TEST(test_img_pix_put_blue);
	MU_RUN_TEST(test_img_pix_put_white);
	MU_RUN_TEST(test_img_pix_put_red_big_endian);
	MU_RUN_TEST(test_img_pix_put_green_big_endian);
	MU_RUN_TEST(test_img_pix_put_blue_big_endian);
	MU_RUN_TEST(test_img_pix_put_white_big_endian);
}

int	test_img_pix_put(void)
{
	MU_RUN_SUITE(test_img_pix_put_suite);
	MU_REPORT();
	return (MU_EXIT_CODE);
}
