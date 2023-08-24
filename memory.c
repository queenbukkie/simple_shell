#include "shell.h"

/**
 * bfree - Frees a pointer and sets the address to NULL.
 * @ptr: Address of the pointer to be freed.
 *
 * This function frees the memory allocated for the given pointer and sets
 * the pointer's value to NULL to prevent accidental access to the memory.
 *
 * Return: 1 if the pointer was freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
