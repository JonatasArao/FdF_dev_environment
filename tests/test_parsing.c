/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:41:43 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/03 17:40:16 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	main(void)
{
	printf(PRINTCYAN("\nTesting: parse_cell\n"));
	test_parse_cell();
	printf(PRINTCYAN("\nTesting: add_point\n"));
	test_add_point();
	printf(PRINTCYAN("\nTesting: parse_line\n"));
	test_parse_line();
	printf(PRINTCYAN("\nTesting: parse_mapfile\n"));
	test_parse_mapfile();
	printf(PRINTCYAN("\nTesting: extract_points\n"));
	test_extract_points();
}
