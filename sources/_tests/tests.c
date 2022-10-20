
# include "../_headers/cub3d.h"
# include "../_headers/colors.h"
# include <signal.h>
# include <sys/wait.h>

int test_number;
char *tested_func;

void sigsegv_exit()
{
	printf("%sSIGSEGV%s %s failed test:%d\n", BYEL, NC, tested_func, test_number);
	exit(1);
}

bool test_bool(bool expected, bool recieved)
{
	if (expected == recieved)
		return (true);
	return (false);
}

void t_is_valid_file()
{
	char *test_value;
	tested_func = "is_valid_file()";

	test_number = 0;
	test_value = "map.cub";
	if (test_bool(true, is_valid_file(test_value)) == false)
		return ((void)printf("%sX%s is_valid_file() failed test:%d\n",
			BRED, NC, test_number));

	test_number = 1;
	test_value = ".cub";
	if (test_bool(false, is_valid_file(test_value)) == false)
		return ((void)printf("%sX%s is_valid_file() failed test:%d\n",
			BRED, NC, test_number));

	test_number = 2;
	test_value = "";
	if (test_bool(false, is_valid_file(test_value)) == false)
		return ((void)printf("%sX%s is_valid_file() failed test:%d\n",
			BRED, NC, test_number));

	test_number = 3;
	test_value = "map";
	if (test_bool(false, is_valid_file(test_value)) == false)
		return ((void)printf("%sX%s is_valid_file() failed test:%d\n",
			BRED, NC, test_number));

	test_number = 4;
	test_value = NULL;
	if (test_bool(false, is_valid_file(test_value)) == false)
		return ((void)printf("%sX%s is_valid_file() failed test:%d\n",
			BRED, NC, test_number));

	printf("%sV%s is_valid_file() tests:%d\n", BGRN, NC, test_number + 1);
}

void t_is_valid_map()
{
	char	**test_map;
	tested_func = "is_valid_map()";

	test_number = 0;
	test_map = ft_calloc(4, sizeof(char *));
	test_map[0] = ft_strdup("1111");
	test_map[1] = ft_strdup("10S1");
	test_map[2] = ft_strdup("1111");
	if (test_bool(true, is_valid_map(test_map)) == false)
		return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
			BRED, NC, test_number));
	free_array(test_map);

	test_number = 1;
	test_map = ft_calloc(4, sizeof(char *));
	test_map[0] = ft_strdup("011");
	test_map[1] = ft_strdup("1S1");
	test_map[2] = ft_strdup("111");
	if (test_bool(false, is_valid_map(test_map)) == false)
		return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
			BRED, NC, test_number));
	free_array(test_map);

	test_number = 2;
	test_map = ft_calloc(4, sizeof(char *));
	test_map[0] = ft_strdup("N11");
	test_map[1] = ft_strdup("101");
	test_map[2] = ft_strdup("111");
	if (test_bool(false, is_valid_map(test_map)) == false)
		return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
			BRED, NC, test_number));
	free_array(test_map);

	test_number = 3;
	test_map = ft_calloc(4, sizeof(char *));
	test_map[0] = ft_strdup("11");
	test_map[1] = ft_strdup("1N1");
	test_map[2] = ft_strdup("111");
	if (test_bool(false, is_valid_map(test_map)) == false)
		return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
			BRED, NC, test_number));
	free_array(test_map);

	test_number = 4;
	test_map = ft_calloc(4, sizeof(char *));
	test_map[0] = ft_strdup("1 1");
	test_map[1] = ft_strdup("1N1");
	test_map[2] = ft_strdup("111");
	if (test_bool(false, is_valid_map(test_map)) == false)
		return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
			BRED, NC, test_number));
	free_array(test_map);

	test_number = 5;
	test_map = ft_calloc(4, sizeof(char *));
	test_map[0] = ft_strdup("111");
	test_map[1] = ft_strdup(" S1");
	test_map[2] = ft_strdup("111");
	if (test_bool(false, is_valid_map(test_map)) == false)
		return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
			BRED, NC, test_number));
	free_array(test_map);

	test_number = 6;
	test_map = ft_calloc(4, sizeof(char *));
	test_map[0] = ft_strdup("111");
	test_map[1] = ft_strdup("1E1");
	test_map[2] = ft_strdup("111");
	if (test_bool(true, is_valid_map(test_map)) == false)
		return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
			BRED, NC, test_number));
	free_array(test_map);

	test_number = 7;
	test_map = ft_calloc(4, sizeof(char *));
	test_map[0] = ft_strdup("1");
	test_map[1] = ft_strdup("11E1");
	test_map[2] = ft_strdup("1111");
	if (test_bool(false, is_valid_map(test_map)) == false)
		return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
			BRED, NC, test_number));
	free_array(test_map);

	test_number = 8;
	test_map = ft_calloc(4, sizeof(char *));
	test_map[0] = ft_strdup("1111");
	test_map[1] = ft_strdup("11W1");
	test_map[2] = ft_strdup("1");
	if (test_bool(false, is_valid_map(test_map)) == false)
		return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
			BRED, NC, test_number));
	free_array(test_map);

	test_number = 9;
	test_map = ft_calloc(4, sizeof(char *));
	test_map[0] = ft_strdup("1111");
	test_map[1] = ft_strdup("1W");
	test_map[2] = ft_strdup("1111");
	if (test_bool(false, is_valid_map(test_map)) == false)
		return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
			BRED, NC, test_number));
	free_array(test_map);

	test_number = 10;
	test_map = ft_calloc(4, sizeof(char *));
	test_map[0] = ft_strdup("111");
	test_map[1] = ft_strdup("1R1");
	test_map[2] = ft_strdup("111");
	if (test_bool(false, is_valid_map(test_map)) == false)
		return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
			BRED, NC, test_number));
	free_array(test_map);

	test_number = 11;
	test_map = ft_calloc(4, sizeof(char *));
	test_map[0] = ft_strdup("S");
	test_map[1] = ft_strdup("");
	test_map[2] = ft_strdup("1111");
	if (test_bool(false, is_valid_map(test_map)) == false)
		return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
			BRED, NC, test_number));
	free_array(test_map);

	test_number = 12;
	test_map = ft_calloc(4, sizeof(char *));
	test_map[0] = ft_strdup("1111");
	test_map[1] = ft_strdup("1011");
	test_map[2] = ft_strdup("1111");
	if (test_bool(false, is_valid_map(test_map)) == false)
		return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
			BRED, NC, test_number));
	free_array(test_map);

	test_number = 13;
	test_map = ft_calloc(4, sizeof(char *));
	test_map[0] = ft_strdup("11");
	test_map[1] = ft_strdup("1N");
	test_map[2] = ft_strdup("111111");
	if (test_bool(false, is_valid_map(test_map)) == false)
		return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
			BRED, NC, test_number));
	free_array(test_map);

	test_number = 14;
	test_map = ft_calloc(4, sizeof(char *));
	test_map[0] = ft_strdup("1111");
	test_map[1] = ft_strdup("1NS1");
	test_map[2] = ft_strdup("111111");
	if (test_bool(false, is_valid_map(test_map)) == false)
		return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
			BRED, NC, test_number));
	free_array(test_map);

	test_number = 15;
	test_map = ft_calloc(4, sizeof(char *));
	test_map[0] = ft_strdup("1111");
	test_map[1] = ft_strdup("1WW1");
	test_map[2] = ft_strdup("111111");
	if (test_bool(false, is_valid_map(test_map)) == false)
		return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
			BRED, NC, test_number));
	free_array(test_map);

	test_number = 16;
	test_map = ft_calloc(4, sizeof(char *));
	test_map[0] = ft_strdup("11111");
	test_map[1] = ft_strdup("1W10");
	test_map[2] = ft_strdup("11111");
	if (test_bool(false, is_valid_map(test_map)) == false)
		return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
			BRED, NC, test_number));
	free_array(test_map);

	test_number = 17;
	test_map = ft_calloc(4, sizeof(char *));
	test_map[0] = ft_strdup("");
	test_map[1] = ft_strdup("");
	test_map[2] = ft_strdup("");
	if (test_bool(false, is_valid_map(test_map)) == false)
		return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
			BRED, NC, test_number));
	free_array(test_map);

	test_number = 18;
	test_map = ft_calloc(4, sizeof(char *));
	if (test_bool(false, is_valid_map(test_map)) == false)
		return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
			BRED, NC, test_number));
	free_array(test_map);

	test_number = 18;
	test_map = NULL;
	if (test_bool(false, is_valid_map(test_map)) == false)
		return ((void)printf("%sX%s is_valid_map() failed test:%d\n",
			BRED, NC, test_number));

	printf("%sV%s is_valid_map() tests:%d\n", BGRN, NC, test_number + 1);
}

void run_func_tests(void (*f)(void))
{
	int child_pid;

	child_pid = fork();
	// child
	if (child_pid == 0)
	{
		signal(SIGSEGV, sigsegv_exit);
		f();
		exit(0);
	}
	// parent
	else
		wait(NULL);
}

int main()
{
	run_func_tests(t_is_valid_file);
	run_func_tests(t_is_valid_map);
	return (0);
}
