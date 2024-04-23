/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:24:56 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/28 12:33:33 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <limits.h>

struct					s_cmd;
typedef struct s_cmd	t_cmd;

typedef enum s_token
{
	PIPE = 1,
	OUT,
	D_OUT,
	IN,
	D_IN,
}	t_token;

typedef struct s_chunk
{
	char			*str;
	t_token			token;
	int				idx;
	struct s_chunk	*next;
	struct s_chunk	*prev;
}	t_chunk;

typedef struct s_info
{
	char			*line;
	char			**paths;
	char			**ev;
	char			**not_ev;
	t_cmd			*cmds;
	t_chunk			*chunk_list;
	char			*pwd;
	char			*o_pwd;
	int				pipes;
	int				*pids;
	unsigned char	error_num;
	bool			heredoc;
	bool			reset;
}	t_info;

typedef struct s_cmd
{
	char			**strs;
	int				(*builtin)(t_info *, struct s_cmd *);
	int				num_redirs;
	char			*hd_file_name;
	t_chunk			*redirs;
	bool			is_outfile;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_parse_info
{
	t_chunk			*chunk_list;
	t_chunk			*redirs;
	bool			is_outfile;
	int				num_redirs;
	struct s_info	*info;
}	t_parse_info;

int						g_in_heredoc;

int		restart_minishell(t_info *info);

void	print_message(char *keyword, char *msg, int fd);
void	free_strs(char **strs);
char	**strdup_arr(char **strs);
int		print_error(int code, t_info *info, int is_child);

int		make_new_chunk(char *str, t_token token, t_chunk **chunk_list_addr);
t_chunk	*chunk_new(char *str, int token);
void	chunk_list_push(t_chunk **chunk_list_addr, t_chunk *new_chunk);
void	chunk_list_clear(t_chunk **chunk_list_addr);
void	chunk_list_erase(t_chunk **chunk_list_addr, int key);
void	chunk_clear_print_error(int code, t_info *info, t_chunk *chunk_list);
int		print_token_error(t_info *info, t_chunk *chunk_list, t_token token);

int		my_echo(t_info *info, t_cmd *cmd);
int		my_cd(t_info *info, t_cmd *cmd);
int		my_pwd(t_info *info, t_cmd *cmd);
int		my_export(t_info *info, t_cmd *cmd);
int		my_unset(t_info *info, t_cmd *cmd);
int		my_env(t_info *info, t_cmd *cmd);
int		my_exit(t_info *info, t_cmd *cmd);

#endif