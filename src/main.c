#include "../include/moulinette.h"

int error_handler(int error)
{
    if (error == 1)
    {
        printf("moulinette: erreur pas de dossier indiquer\nSaisissez « moulinette --help » pour plus d'informations.\n");
        return (1);
    }
    else if (error == 2)
    {
        printf("malloc error\n");
        return (2);
    }
    return (0);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char *ft_calloc(char *base)
{
    char    *str;
    int     i;

    i = -1;
    str = malloc(sizeof(char) * ft_strlen(base) + 1);
    if (!str)
        return (NULL);
    while (base[++i])
        str[i] = base[i];
    str[i] = 0;
    return (str);
}

char **init_option(char **argv, int argc, int *error)
{
    int i;
    int j;
    char **option;

    i = 1;
    j = 0;
    option = malloc(sizeof(char *) * argc - 1);
    if (!option)
    {
        *error = 2;
        return(NULL);
    }
    while (i < argc)
    {
        if (argv[i][0] == '-')
        {
            option[j] = ft_calloc(argv[i]);
            if (!option[j])
            {
                *error = 2;
                while (j >= 0)
                    free (option[j--]);
                return (NULL);
            }
            j++;
        }
        i++;
    }
    return (option);
}

cmd init_struct(char **argv, int argc)
{
    cmd cmd;

    cmd.error = 0;
    cmd.cmd = init_option(argv, argc, &cmd.error);
    if (!cmd.cmd)
        return(cmd);
    return(cmd);
}

int main(int argc, char **argv)
{
    cmd cmd;
    
    if (argc == 1)
        return(error_handler(1));
    cmd = init_struct(argv, argc);
    if (cmd.error != 0)
        return (error_handler(cmd.error));
    // option_choose(argv);
    return (0);
}