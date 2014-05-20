/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 20:02:10 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/17 20:58:38 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

char		*get_pwd(void)
{
	char		buf[1024];

	return (ft_strdup(getcwd(buf, 1024)));
}

void		ft_ls(int cs)
{
	DIR				*rep;
	struct dirent	*dir;
	char			*tmp;
	char			*res;

	res = NULL;
	rep = opendir(get_pwd());
	while ((dir = readdir(rep)))
	{
		if (!res && dir->d_name[0] != '.')
			res = ft_strdup(dir->d_name);
		else if (dir->d_name[0] != '.')
		{
			tmp = res;
			res = ft_strjoin(res, "\n");
			free(tmp);
			tmp = res;
			res = ft_strjoin(res, dir->d_name);
			free(tmp);
		}
	}
	closedir(rep);
	send_msg(cs, res, 0);
	if (res)
		free(res);
}

void		donothing()
{
	;
}

int		preparing_file(int cs, char *buff, int size)
{
	int		fd;
	int		len;
	char	*beg;
	char	*name;

	beg = buff;
	size -= 4;
	if (size <= 0)
	{
		size = read(cs, beg, B_SIZE);
		name = buff;
	}
	else
		name = buff + 4;
	len = ft_strlen(name) + 1;
	fd = open(name, O_WRONLY | O_CREAT, 00666);
	buff += len;
	size -= len;
	if (size <= 0)
	{
		size = read(cs, beg, B_SIZE);
		write(fd, beg, size);
	}
	else
		write(fd, buff, size);
	return (fd);
}

int			get_eof(int fd, int size, char *buff)
{
	int		i;

	i = 0;
	while (i < size)
	{
		printf("%d %c\n", buff[i], buff[i]);
		if (buff[i] == EOF)
		{
			printf("Gatcha !\n");
			break ;
		}
		i++;
	}
	write(fd, buff, i);
	if (i < size)
		return (1);
	return (0);
}

int			ft_putf(int cs, char *buff, int size)
{
	int		fd;

	fd = preparing_file(cs, buff, size);
	while ((size = read(cs, buff, B_SIZE)) > 0)
	{
		if (get_eof(fd, size, buff))
		{
			printf("End of transmission. Sleeping...\n");
			break ;
		}
	}
	close(fd);
	return (0);
}

// int			is_file(int fd)
// {
// 	struct stat		file_stat;

// 	if (fstat(fd, &file_stat))
// 		return (-1);
// 	return ((file_stat.st_mode & S_IFREG) == S_IFREG);
// }

int			is_dir(int fd)
{
	struct stat		file_stat;

	if (fstat(fd, &file_stat))
		return (-1);
	return ((file_stat.st_mode & S_IFDIR) == S_IFDIR);
}

int			ft_cd(int cs, char *dir, char *home)
{
	char			**tmp;
	char			*save;
	int				fd;

	tmp = ft_strsplit(dir, ' ');
	if (ft_tabsize((void **)tmp) == 2)
	{
		fd = open(dir, 0);
		if (is_dir(fd))
		{
			save = get_pwd();
			chdir(tmp[1]);
			if (ft_strncmp(home, get_pwd(), ft_strlen(home)) && chdir(save))
				return (send_error(cs, "error"));
		}
		else
			return (send_error(cs, "not a directory"));
		close(fd);
	}
	else if (ft_tabsize((void **)tmp) == 1)
		chdir(home);
	return (send_msg(cs, get_pwd(), 0));
}
