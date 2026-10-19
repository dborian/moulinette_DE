#include "../include/moulinette.h"

int error_handler(int error)
{
    if (error == 1)
    {
        printf("moulinette: error wrong argument\nSaisissez « moulinette --help » pour plus d'informations.\n");
        return (1);
    }
    else if (error == 2)
    {
        printf("malloc error\n");
        return (2);
    }
    else if (error == 3)
    {
        printf("a files is missing go fuck yourself\n");
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

int ft_egal(char *str1, char *str2)
{
    int i;

    i = 0;
    while (str1[i] || str2[i])
    {
        if (str1[i] != str2[i])
            return (1);
        i++;
    }
    return (0);
}

void ft_print_help()
{
    printf("Utilisation : moulinette [OPTION]... [FICHIER]...\nCorriger la piscine 42 pour un usage a la maison.\n\n-c, --correction  demander une correction du day actuelle depuis la racine du dossier, si la moulinette ne trouve pas le probleme est humain\n");
}

char *ft_get_day(int *error)
{
    char *pwd;
    char *day;
    int i;
    int j;

    pwd = getenv("PWD");
    j = ft_strlen(pwd);
    while(pwd[j] != '/')
        j--;
    i = ft_strlen(pwd);
    i = i - j++;
    day = malloc(sizeof(char) * i + 1);
    if (!day)
    {
        *error = 2;
        return (NULL);
    }
    i = 0;
    while (pwd[j])
        day[i++] = pwd[j++];
    day[i] = 0;
    return (day);
}

void    ft_correct_shell00(int *error)
{
    printf("test\n");
    (void)error;
}

int ft_correct(cmd cmd, int *error)
{
    (void)cmd;
    char *actual_day;

    actual_day = ft_get_day(error);
    if (*error != 0)
        return (error_handler(*error));
    if (ft_egal(actual_day, "shell00") == 0)
    {
        ft_correct_shell00(error);
        if (*error != 0)
        {
            return *error;
        }
    }
    free(actual_day);
    return (0);
}

int option_choose(cmd cmd, int *error)
{
    *error = 0;
    if (ft_egal(cmd.cmd[0], "--help") == 0)
        ft_print_help();
    else if (ft_egal(cmd.cmd[0], "-c") == 0 || ft_egal(cmd.cmd[0], "--correction") == 0)
    {
        ft_correct(cmd, error);
        if (*error != 0)
        {
            return (*error);
        }
    }
    else
        printf ("ca existe pas ca comme option\n");
    return (0);
}

int main(int argc, char **argv)
{
    cmd cmd;

    if (argc > 3 || argc == 1)
        return(error_handler(1));
    cmd = init_struct(argv, argc);
    if (cmd.error != 0)
        return (error_handler(cmd.error));
    if (option_choose(cmd, &cmd.error) != 0)
        return (error_handler(cmd.error));
    free(cmd.cmd[0]);
    if (argc == 3)
        free(cmd.cmd[1]);
    free(cmd.cmd);
    return (0);
}