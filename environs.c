#include "shell.h"

/**
 * _myexit - Implements the exit command.
 * @info: Pointer to a structure containing potential arguments.
 * 
 * Return: If a specific exit status is provided, returns that status.
 *         Returns -2 if no argument is provided.
 *         Returns 1 on error (invalid exit status).
 */
int _myexit(info_t *info)
{
    int exit_status;

    if (info->argv[1]) {
        exit_status = _erratoi(info->argv[1]);
        if (exit_status == -1) {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return 1;
        }
        info->err_num = _erratoi(info->argv[1]);
        return exit_status;
    }

    info->err_num = -1;
    return -2;
}

/**
 * _mycd - Implements the cd (change directory) command.
 * @info: Pointer to a structure containing potential arguments.
 * 
 * Return: Always returns 0.
 */
int _mycd(info_t *info)
{
    char *current_dir, *dir, buffer[1024];
    int chdir_ret;

    current_dir = getcwd(buffer, 1024);
    if (!current_dir)
        _puts("TODO: >>getcwd failure emsg here<<\n");

    if (!info->argv[1]) {
        dir = _getenv(info, "HOME=");
        if (!dir)
            chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    } else if (_strcmp(info->argv[1], "-") == 0) {
        if (!_getenv(info, "OLDPWD=")) {
            _puts(current_dir);
            _putchar('\n');
            return 1;
        }
        _puts(_getenv(info, "OLDPWD="));
        _putchar('\n');
        chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
    } else {
        chdir_ret = chdir(info->argv[1]);
    }

    if (chdir_ret == -1) {
        print_error(info, "can't cd to ");
        _eputs(info->argv[1]);
        _eputchar('\n');
    } else {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }

    return 0;
}

/**
 * _myhelp - Implements the help command.
 * @info: Pointer to a structure containing potential arguments.
 * 
 * Return: Always returns 0.
 */
int _myhelp(info_t *info)
{
    char **arg_array;

    arg_array = info->argv;
    _puts("Help function: Displays available commands.\n");
    if (0)
        _puts(*arg_array); /* Temporary unused workaround */
    return 0;
}
