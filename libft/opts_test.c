#include "includes/libft.h"
#include <stdbool.h>

#define LS_FLAG_A (1 << 0)
#define LS_FLAG_B (1 << 1)
#define LS_FLAG_W (1 << 2)
#define LS_FLAG_H (1 << 3)
#define HAS_FLAG_A(a) (a & LS_FLAG_A)
#define HAS_FLAG_B(a) (a & LS_FLAG_B)
#define HAS_FLAG_W(a) (a & LS_FLAG_W)
#define HAS_FLAG_H(a) (a & LS_FLAG_H)

int get_cols(char *def_val, char *opt_arg, void *data)
{
	ft_printf("1.def_val: %s\n", def_val);
	ft_printf("2.opt_arg: %s\n", opt_arg);
	if (!opt_arg)
		return (1);
	(void)data;
	return (0);
}

int get_rows(char *def_val, char *opt_arg, void *data)
{
	ft_printf("1.def_val: %s\n", def_val);
	ft_printf("2.opt_arg: %s\n", opt_arg);
	(void)data;
	return (0);
}

t_optsdata opts =
{
	"ls", /* Command name */
	"list directory contents", /* Command description */
	"MIT License", /* Epilog */
	NULL, /* ARGV */
	true, /* Help */
	true, /* Usage */
	true, /* Required opts */
	{
		{'a', "all", "include hidden files", NULL, NULL, LS_FLAG_A, 0, NULL, false, false},
		{'b', "ball", "include ball files", NULL, NULL, LS_FLAG_B, 0, NULL, false, false},
		{'w', "width", "output width", "100", "COLS", LS_FLAG_W, 0, &get_cols, true, false},
		{'h', "height", "output height", "200", "ROWS", LS_FLAG_H, 0, &get_rows, true, false},
		{0, NULL, NULL, NULL, NULL, 0, 0, NULL, false, false}
	}
};

int main()
{
	t_optparser data;
	char *args[] = {
		"ls",
		// "-baw=",
		"--height",
		"190",
		// "--all",
		// "--ball",
		// "--help",
		0
	};
	ft_bzero(&data, sizeof(t_optparser));
	// g_argv = args;
	int ret = ft_opts((char **)args, &opts, &data, true);
	ft_printf("Returns ret: %d\n", ret);
	ft_printf("%b\n", data.flags);
	if (HAS_FLAG_A(data.flags))
		ft_printf("It has flag 'a'\n");
	if (HAS_FLAG_B(data.flags))
		ft_printf("It has flag 'b'\n");
	if (HAS_FLAG_W(data.flags))
		ft_printf("It has flag 'w'\n");
	if (HAS_FLAG_H(data.flags))
		ft_printf("It has flag 'h'\n");
	// ft_printf("%s\n", *(data.argv));
	// ft_opts_parse(&opts, &data);
	// ft_printf("%s\n", *(data.argv));
	return (0);
}
