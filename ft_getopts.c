/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:07:57 by giacomo           #+#    #+#             */
/*   Updated: 2017/11/24 19:34:36 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

typedef long long t_flag;

typedef struct  s_ftopts
{
    char        c;
    char        *str;
    t_flag      flags_on;
    t_flag      flags_off;
    int         (*getopt)();
    int         arg_required:1;
}               t_ftopts;

typedef struct  s_ftopts_data
{
    t_flag      flags;
    char        **argv;
}               t_ftopts_data;

static char *getopt_arg(char ***av, char *arg)
{
    char *ret;

    if (!arg || !*arg || !*(arg + 1))
    {
        (*av)++;
        return (**av);
    }
    ret = arg + 1;
    return (ret);
}

static t_ftopts *getmap_short(t_ftopts opts_map[], char c)
{
    int i;

    i = 0;
    while (opts_map[i].c)
    {
        if (opts_map[i].c == c)
            return (&opts_map[i]);
        i++;
    }
    return (NULL);
}

static t_ftopts *getmap_long(t_ftopts opts_map[], char *name)
{
    int i;

    i = 0;
    while (opts_map[i].c)
    {
        if (opts_map[i].str && !strcmp(opts_map[i].str, name))
            return (&opts_map[i]);
        i++;
    }
    return (NULL);
}

int ftopts_short(char ***av, t_ftopts opts_map[], void *data)
{
    t_ftopts    *opt;
    char        *opt_ch;
    char        *arg;
    int         i;

    opt_ch = **av + 1;
    i = 0;
    while (opt_ch[i] && !(arg = NULL))
    {
        opt = getmap_short(opts_map, opt_ch[i]);
        if (!opt)
            return (1);
        ((t_ftopts_data *)data)->flags |= opt->flags_on;
        ((t_ftopts_data *)data)->flags &= ~opt->flags_off;
        if (opt->getopt)
        {
            if (opt->arg_required && !(arg = getopt_arg(av, arg + i)))
                return (1);
            arg = arg ? arg : **av;
            if (opt->getopt(arg, data))
                return (1);
            if (opt->arg_required)
                break ;
        }
        i++;
    }
    (*av)++;
    return (0);
}

int ftopts_long(char ***av, t_ftopts opts_map[], void *data)
{
    t_ftopts    *opt;
    char        *opt_name;
    char        *arg;

    opt_name = **av + 2;
    opt = getmap_long(opts_map, opt_name);
    if (!opt)
        return (1);
    ((t_ftopts_data*)data)->flags |= opt->flags_on;
    ((t_ftopts_data*)data)->flags &= ~opt->flags_off;
    if (opt->getopt)
    {
        if (opt->arg_required && !(arg = getopt_arg(av, NULL)))
            return (1);
        if (opt->getopt(arg, data))
            return (1);
    }
    (*av)++;
    return (0);
}

int ft_getopts(char **av, t_ftopts opts_map[], void *data)
{
    if (!av)
        return (1);
    av++;
    while (av && *av)
    {
        if (!strcmp(*av, "-") || (!strcmp(*av, "--") && av++))
            break ;
        if ((*av)[0] == '-' && (*av)[1] == '-')
        {
            if (ftopts_long(&av, opts_map, data))
                return (1);
        }
        else if ((*av)[0] == '-')
        {
            if (ftopts_short(&av, opts_map, data))
                return (1);
        }
        else
            break ;
    }
    ((t_ftopts_data *)data)->argv = av;
    return (0);
}
