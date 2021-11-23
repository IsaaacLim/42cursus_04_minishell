#include "environment.h"

int main(int argc, char *argv[], char *envp[])
{
	t_list *env;

	env = initialise_env(envp);

	// unset(&env, "XDG_DATA_DIRS");
	unset(&env, "PWD");
	// unset(&env, "WSL_DISTRO_NAME");
	// export_add(&env, "TERM=WRONGCOLOR!");
    export_add(&env, "PWD=BACK");
	// env_command(env);
	export_command(env);

	// to free -> include towards end of main
	ft_lstclear(&env, free_envar);
	return (0);
}
