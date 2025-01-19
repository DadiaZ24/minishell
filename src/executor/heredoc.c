#include "minishell.h"

char	*enum_heredoc(void)
{
	static int	i = -1;
	char		*num;
	char		*file;

	num = ft_itoa(++i);
	file = ft_strjoin(".746D70", num);
	free(num);
	return (file);
}

bool	handle_heredoc(t_cmds *cmds)
{
	char	*line;
	char	*eof;
	int		fd;

	eof = ft_strdup(cmds->redir->info);
	free(cmds->redir->info);
	cmds->redir->info = enum_heredoc();
	fd = open(cmds->redir->info, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (false);
	line = readline("> ");
	while (line && ft_strcmp(line, eof))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(eof);
	close(fd);
	return (true);
}
