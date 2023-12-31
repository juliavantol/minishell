/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fras <fras@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/11 14:52:11 by fras          #+#    #+#                 */
/*   Updated: 2023/12/01 16:39:33 by fras          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lexer(t_tokens *tokens);

int	main(int argc, char **argv, char **envp)
{
	t_exe		executor;
	t_tokens	*tokens;

	if (!proper_start(argc, argv))
		return (EXIT_FAILURE);
	init_executor(&executor, envp);
	while (1)
	{
		init_signal_handler();
		executor.input = init_prompt("minishell$ ");
		restore_signals();
		if (!executor.input)
			return (ctrl_d(&executor));
		tokens = lexer(executor.input);
		if (!tokens)
		{
			executor.exit_code = 2;
			continue ;
		}
		run_parser(&executor, tokens, 1);
		run_executor(&executor);
		clear_tokens(&tokens);
		free(executor.input);
	}
	empty_executor(&executor);
}

bool	proper_start(int argc, char **argv)
{
	if (argc == 1 && *argv)
		return (true);
	return (false);
}
