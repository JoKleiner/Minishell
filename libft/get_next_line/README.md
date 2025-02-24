
This is how the function **get_next_line** can be used.

	int	main(void)
	{
		int	fd;
		char	*str;

		fd = open("text.txt", O_RDONLY);
		str = get_next_line(fd);
		if (str != NULL)
		{
			printf("%s", str);
			free(str);
		}
		close(fd);
		return (0);
	}
