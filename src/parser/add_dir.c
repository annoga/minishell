#include "../../inc/minishell.h"

// // Helper function to get the length of the array
static int	get_array_length(void **array)
{
	int	len;

	len = 0;
	if (!array)
		return (0);
	while (array[len])
		len++;
	return (len);
}

// Helper function to allocate memory for the new array
static void	**allocate_new_array(void **array, int *len)
{
	void	**new_array;

	*len = get_array_length(array);
	new_array = malloc(sizeof(void *) * (*len + 2));
	if (!new_array)
	{
		free_split((char **)array);
		return (NULL);
	}
	return (new_array);
}

// Helper function to copy elements from old array to new array
static void	copy_elements(void **new_array, void **old_array, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		new_array[i] = old_array[i];
		i++;
	}
}

// Main function to add a directory to the array
void	*add_dir(void *array, void *dir)
{
	void	**new_array;
	void	**old_array;
	int		len;

	if (!dir)
		return (array);
	old_array = (void **)array;
	new_array = allocate_new_array(old_array, &len);
	if (!new_array)
		return (NULL);
	copy_elements(new_array, old_array, len);
	new_array[len] = dir;
	new_array[len + 1] = NULL;
	free(old_array);
	return (new_array);
}