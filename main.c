#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

#include <unistd.h>
#include <limits.h>


#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>

void	ft_readline()
{
	char	*inpt;

	while (1)
	{
		inpt = readline("Enter text: ");
		if(strlen(inpt) > 0)
			add_history(inpt);
		if (!strcmp(inpt, "exit"))
			exit(0);
		else if(!strcmp(inpt, "ls"))
			system("ls");
		free(inpt);
	}
}

void	ft_getpath()
{
	//https://stackoverflow.com/questions/298510/how-to-get-the-current-directory-in-a-c-program
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("Current working dir: %s\n", cwd);
	else
		perror("getcwd() error");	
}

void	ft_changepath()
{
	//https://www.geeksforgeeks.org/chdir-in-c-language-with-examples/
	chdir("..");
}

void	ft_stat()
{
	//https://stackoverflow.com/questions/3138600/correct-use-of-stat-on-c
	char *file = "myfile.txt";
	int	dev;
	int ino;
	int uid;
	int size;

	struct stat *buf = malloc(sizeof(struct stat));
	if (stat(file, buf) == 0)
	{
		dev = buf->st_dev; //use man to know that structs are there
		ino = buf->st_ino;
		uid = buf->st_uid;
		size = buf->st_size;
		printf("\"%s\" info:\n", file);
		printf("\tDevide ID:\t %d.\n", dev);
		printf("\tInode Number:\t %d.\n", ino);
		printf("\tUser ID:\t %d.\n", uid);
		printf("\tSize:\t\t %d bytes.\n", size);
	}
	else
		perror(file);
	free(buf);
	//lstat used to describe information of a symbolic link
}

void	ft_fstat()
{
	int		fd;
	char	*file = "myfile.txt";
	int		size;

	struct stat *buf = malloc(sizeof(struct stat));
	fd = open("myfile.txt", O_RDONLY);
	if (stat(file, buf) == 0)
	{
		size = buf->st_size;
		printf("\"%s\" info:\n", file);
		printf("\tSize:\t\t %d bytes.\n", size);
	}
	else
		perror(file);
	free(buf);
	close(fd);
}

void	ft_unlink()
{
	char	*file = "myfile.txt";
	unlink(file); //deletes file
}

int	main()
{
	// ft_readline();
	ft_getpath();
	// ft_changepath();
	// ft_getpath();
	ft_stat();
	ft_fstat();
	// ft_unlink();
}