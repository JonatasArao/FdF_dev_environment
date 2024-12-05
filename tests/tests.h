/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:09:35 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/05 17:28:10 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H
# include <stdio.h>
# include "fdf.h"
# define PRINTCYAN(X) "\033[1;36m"X"\033[0m"

int	test_img_pix_put(void);

int	test_parse_cell(void);

int	test_add_point(void);

int	test_parse_line(void);

int	test_parse_mapfile(void);

int	test_extract_points(void);

int	test_set_vector_properties(void);

int	test_add_vector(void);

int test_generate_vector_list(void);

#endif
