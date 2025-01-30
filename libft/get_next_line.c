/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:47:36 by jvarila           #+#    #+#             */
/*   Updated: 2024/12/13 15:51:35 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		initialize(t_buffer *buffers, t_buffer **buffer, int fd);
static void		read_into_buffer(t_buffer *buffer);
static ssize_t	get_newline_index(t_buffer *buffer);
static char		*flush_and_combine(t_buffer *buff, size_t to_flush, char *line);

// If buffer is uninitialized assign it a filedescriptor and fill it's static
// character array with read. If a newline is found, flush the line from the 
// buffer and return it. If no newlines are found, eof has been found (the
// buffer couldn't be filled by read) and the buffer has unflushed bytes, 
// flush all unflushed bytes and return. If eof and the buffer is empty return
// NULL. If buffer is full and no newlines are found, store buffer in line by
// appending and read new data into the buffer memory, starting the loop anew.
char	*get_next_line(int fd)
{
	static t_buffer	buffers[FILE_LIMIT];
	char			*line;
	t_buffer		*buffer;
	ssize_t			newline_index;

	line = NULL;
	initialize(buffers, &buffer, fd);
	if (!buffer)
		return (NULL);
	while (1)
	{
		newline_index = get_newline_index(buffer);
		if (newline_index >= 0)
			return (flush_and_combine(buffer, newline_index + 1, line));
		if (buffer->eof && buffer->unflushed_bytes > 0)
			return (flush_and_combine(buffer, buffer->unflushed_bytes, line));
		if (buffer->eof && buffer->unflushed_bytes == 0)
		{
			if (line == NULL)
				ft_memset(buffer, 0, sizeof(t_buffer));
			return (line);
		}
		line = flush_and_combine(buffer, buffer->unflushed_bytes, line);
		read_into_buffer(buffer);
	}
}

// Check if a buffer with fd already exists, initialize if necessary. If it
// doesn't exist find an unitialized member, link it to buffer and initialize.
static void	initialize(t_buffer *buffers, t_buffer **buffer, int fd)
{
	size_t	i;

	*buffer = NULL;
	i = 0;
	while (i < FILE_LIMIT)
	{
		if (buffers[i].fd == fd)
			break ;
		if (buffers[i].flushed_bytes == 0 && buffers[i].unflushed_bytes == 0)
		{
			buffers[i].fd = fd;
			break ;
		}
		i++;
	}
	if (i == FILE_LIMIT)
		return ;
	(*buffer) = &buffers[i];
	if ((*buffer)->unflushed_bytes == 0 && (*buffer)->flushed_bytes == 0)
		read_into_buffer(*buffer);
}

// Attempts to fill buffer. If read fails or goes past eof mark buffer as
// completely flushed and assign eof. If read succeeds assign bytes_read,
// set unflushed_bytes to 0 and assign eof if less bytes than BUFFER_SIZE
// were read from file, in case of stdin don't set eof for partial fills.
static void	read_into_buffer(t_buffer *buffer)
{
	ssize_t	bytes_read;

	bytes_read = read(buffer->fd, buffer->memory, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		buffer->eof = 1;
		buffer->unflushed_bytes = 0;
		buffer->flushed_bytes = BUFFER_SIZE;
		return ;
	}
	buffer->unflushed_bytes = bytes_read;
	buffer->flushed_bytes = 0;
	if (bytes_read < BUFFER_SIZE && buffer->fd != STDIN_FILENO)
		buffer->eof = 1;
}

// Start search in unflushed bytes by using flushed_bytes as an offset.
static ssize_t	get_newline_index(t_buffer *buffer)
{
	size_t	offset;
	size_t	i;

	offset = buffer->flushed_bytes;
	i = 0;
	while (i < buffer->unflushed_bytes)
	{
		if (buffer->memory[offset + i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

// This function mallocs to_flush + 1 bytes, memmoves to_flush bytes from
// buffer->memory + offset (skips the already flushed bytes) to the mallocated
// temp, updates the buffer's flushed and uflushed bytes, appends temp to line
// and returns the new combined string.
static char	*flush_and_combine(t_buffer *buff, size_t to_flush, char *line)
{
	char	*temp;
	size_t	offset;

	if (!buff || buff->unflushed_bytes == 0 || to_flush == 0)
		return (NULL);
	if (to_flush > buff->unflushed_bytes)
		to_flush = buff->unflushed_bytes;
	temp = malloc((to_flush + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	offset = buff->flushed_bytes;
	ft_memmove(temp, buff->memory + offset, to_flush);
	temp[to_flush] = '\0';
	buff->unflushed_bytes -= to_flush;
	buff->flushed_bytes += to_flush;
	line = strjoin_and_free(line, temp);
	return (line);
}
