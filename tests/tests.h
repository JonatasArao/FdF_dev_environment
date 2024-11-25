/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:09:35 by jarao-de          #+#    #+#             */
/*   Updated: 2024/11/26 14:51:33 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H
# include <stdio.h>
# include "fdf.h"
# define PRINTCYAN(X) "\033[1;36m"X"\033[0m"

int	test_img_pix_put(void);

int	test_parse_cell_data(void);

#endif
