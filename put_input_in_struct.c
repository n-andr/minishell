/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_input_in_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:05:17 by nandreev          #+#    #+#             */
/*   Updated: 2024/07/04 16:45:25 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//WIP add to makefile when ready

// all functions are drafts

void add_command(t_minishell *shell, char **args, char **redir, bool is_redir, bool is_pipe) {
    t_args *new_command = malloc(sizeof(t_args));
    if (!new_command)
        return;

    new_command->args = args;
    new_command->redir = redir;
    new_command->is_redir = is_redir;
    new_command->is_pipe = is_pipe;
    new_command->next = NULL;

    // Append to the end of the list
    if (shell->commands == NULL) {
        shell->commands = new_command;
    } else {
        t_args *temp = shell->commands;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_command;
    }
}
