/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vectorize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:09:58 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/06 17:40:22 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	main(void)
{
	printf(PRINTCYAN("\nTesting: add_vector\n"));
	test_add_vector();
	printf(PRINTCYAN("\nTesting: generate_vector_list\n"));
	test_generate_vector_list();
}
