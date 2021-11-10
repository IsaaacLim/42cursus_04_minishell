#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#include <unistd.h>
#include <limits.h>


#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>

#include <dirent.h>

void	ft_sigint()
{
	printf("Cya\n");
	exit (0);
}

void	ft_sigquit()
{
	printf("Bye\n");
	exit (0);
}

void	ft_tty()
{
	int	i;
	int	t;

	i = 0;
	while (i < 100)
	{
		t = isatty(i);
		printf("%d ", t);
		i++;
	}
	printf("\n");
	printf("ttyname(0): %s\n", ttyname(0));
	printf("ttyname(1): %s\n", ttyname(1));
	printf("ttyname(2): %s\n", ttyname(2));
	printf("ttyname(3): %s\n", ttyname(3));
}
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
	if (fstat(fd, buf) == 0)
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

void	ft_execve()
{
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("Current working dir: %s\n", cwd);

	char *args[] = {"ls", "-l", "-a", (char *)0};
	char	*env_args[] = {"PATH=/Users/jinlim/Documents/42Projects/42-minishell", (char *)0};
	execve(args[0], args, env_args);

	printf("Error\n");
}

//https://www.geeksforgeeks.org/dup-dup2-linux-system-call/
void	ft_dup()
{
	int	fd;
	int	dup_fd;

	fd = open("dup.txt", O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (fd < 0)
		perror("open");
	dup_fd = dup(fd);
	write(fd, "This will be output to the file named dup.txt\n", 46);
	write(dup_fd, "This will also be output to the file named dup.txt\n", 51);

	int	fd2;
	int	dup_fd2;

	fd2 = open("dup2.txt", O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (fd2 < 0)
		perror("open2");
	printf("Still prints in STDOUT but not for long\n");
	dup_fd2 = dup2(fd2, STDOUT_FILENO);
	printf("I will be printed in the file dup2.txt\n");
}

void	ft_pipe()
{
	int		pipefd1[2]; //C => P
	int		pipefd2[2]; //P => C
	pid_t	cpid;
	int		x;
	int		y;

	if (pipe(pipefd1) != 0)
		perror("pipe1");
	if (pipe(pipefd2) != 0)
		perror("pipe2");
	cpid = fork();
	if (cpid == -1)
		perror("fork");
	if (cpid == 0) //child process
	{
		close(pipefd1[0]); //close unused C => P read end
		close(pipefd2[1]); //close unused P => C write end
		// x = readline("Enter text: ");
		scanf("Child num input: %d", &x);
		if (write(pipefd1[1], &x, 10) == -1)
			perror("child write");
		printf("Child wrote: %d\n", x);
		if (read(pipefd2[0], &x, 10) == -1)
			perror("child read");
		printf("Child read: %d\n", x);
		close(pipefd1[1]);
		close(pipefd2[0]);
	}
	else //parent process
	{
		close(pipefd1[1]);
		close(pipefd2[0]);
		scanf("Parent num input: %d", &y);
		if (write(pipefd2[1], &y, 10) == -1)
			perror("parent write");
		printf("Parent write: %d\n", y);
		if (read(pipefd1[0], &y, 10) == -1)
			perror("parent read");
		printf("Parent read: %d\n", y);
		close(pipefd1[0]); //child reads from pipe
		close(pipefd2[1]);
		wait(NULL);
	}
}

void	ft_dir()
{
	struct dirent *pDirent;
	DIR	*pDir;

	pDir = opendir ("../42-minishell");
	if (pDir == NULL)
	{
		printf("Cannot open directory\n");
		exit (0);
	}
	while ((pDirent = readdir(pDir)) != NULL)
		printf ("[%s]\n", pDirent->d_name);
	closedir(pDir);
}

int	main()
{
	signal(SIGINT, ft_sigint);	//ctrl - C
	signal(SIGQUIT, ft_sigquit); //ctrl - \ /
	// ft_tty();
	// ft_readline();
	// ft_getpath();
	// ft_changepath();
	// ft_getpath();
	// ft_stat();
	// ft_fstat();
	// ft_unlink();
	// ft_execve();
	// ft_dup();
	ft_pipe(); //got issues with 2 way communication
	// ft_dir();
}
