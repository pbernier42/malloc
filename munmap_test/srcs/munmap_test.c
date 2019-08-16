#include <sys/mman.h>
#include <unistd.h>

int		main()
{
	int		i;
	char 	*ptr;

	i = 0;
	while (i++ < 500)
	{
		if ((ptr = mmap(NULL, 16, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		 	write(1, "FAIL M\n", 7);
		ptr[0] = 'a';
		if (munmap(ptr, 16) != 0)
			write(1, "FAIL MUN\n", 9);
	}
	return (1);
}
