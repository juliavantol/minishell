/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fras <fras@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:15:51 by fras          #+#    #+#                 */
/*   Updated: 2023/11/09 14:20:04 by fras          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	quote_is_closed(const char *str)
{
	char	quote_type;
	size_t	i;

	quote_type = *str;
	i = 1;
	while (str[i])
	{
		if (str[i] == quote_type)
			return (i);
		i++;
	}
	return (0);
}

size_t	get_string_literal(char *string, char *dest)
{
	char	quote_type;
	size_t	size;

	size = 0;
	quote_type = *string;
	while (*string != quote_type)
	{
		*dest++ = *string++;
		size++;
	}
	*dest = '\0';
	return (size);
}

int	assign_quote(char *line, char **dest)
{
	int	i;

	i = 0;
	*dest = malloc(quote_is_closed(line[i]) * sizeof(char) + 1);
	if (!*dest)
		return (-1);
	i += get_quoted_string_literal(line[i + 1], *dest);
	return (i);
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}
