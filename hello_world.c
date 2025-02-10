#include <unistd.h>

int	main(void)
{
	write(STDOUT_FILENO, "Hello world!\n", 13);
	return (0);
}
