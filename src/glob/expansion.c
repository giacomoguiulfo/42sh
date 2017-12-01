/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinfemi <aakin-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:23:00 by akinfemi          #+#    #+#             */
/*   Updated: 2017/11/30 16:23:02 by akinfemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include <stdlib.h>
#include <stdio.h>

char            *get_home()
{
    return (ft_strdup(ft_getenv(sh_singleton()->env, "HOME")));
    // return (ft_strdup("/Users/akinfemi"));
}

char            *expand_home(char **pre)
{
    char        *home;
    char        *str;
    char        *temp;

    if (!pre || !*pre)
        return 0;
    str = *pre;
    if (str[0] != '~')
        return 0;
    home = get_home();
    temp = home;
    *pre = ft_strjoin(home, str + 1);
    free(temp);
    free(str);
    return (*pre);
}

char            *get_var_name(char *path)
{
    int         end;

    end = 1;
    if (path[end] == ';' || path[end] == ' ' || path[end] == '/' || path[end] == '\0')
        return (ft_strdup("$"));
    while (path[end])
    {
        if (path[end] == ';' || path[end] == ' ' || path[end] == '/' || path[end] == '\0' || path[end] == '$')
            break;
        end++;
    }
    return (ft_strsub(path, 1, end - 1));
}

char            *replace(char *str, char *new, char *old, char delim)
{
    int         end;
    int         len;
    char        *first_part;
    char        *res;

    end = 0;
    len = ft_strlen(str) + ft_strlen(new);
    while (str[end])
    {
        if (str[end] == '\0' || str[end] == delim)
            break;
        end++;
    }
    first_part = ft_strsub(str, 0, end);
    res = ft_strjoin(first_part, new);
    free(first_part);
    free(new);
    new = ft_strsub(str, end + ft_strlen(old) + 1, len);
    first_part = res;
    res = ft_strjoin(first_part, new);
    free(first_part);
    free(new);
    return (res);
}

char            *expand_dollar(char *path)
{
    char        *str;
    char        *dollar;
    char        *var;
    char        *replacement;

    if (!path)
        return (0);
    dollar = ft_strchr(path, '$');
    if (!dollar)
        return (path);
    while ((dollar = ft_strchr(path, '$')))
    {
        var = get_var_name(dollar);
        replacement = ft_strdup(ft_getenv(sh_singleton()->env, ft_toupper(var)));
        // replacement = ft_strdup("/Users/akinfemi");
        path = replace(path, replacement, var, '$');
    }
    return (path);
}