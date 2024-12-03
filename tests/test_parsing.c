/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:41:43 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/03 11:59:31 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	main(void)
{
	printf(PRINTCYAN("\nTesting: parse_cell\n"));
	test_parse_cell();
	printf(PRINTCYAN("\nTesting: add_point\n"));
	test_add_point();
}
