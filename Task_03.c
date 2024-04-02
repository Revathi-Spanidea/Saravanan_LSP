#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Retrieve the value of a specific environment variable
    char *path_value = getenv("PATH"); //Declares a pointer to a character, which will store the value of the PATH environment variable.
                                       // Calls the getenv function to retrieve the value of the PATH environment variable.
    if (path_value != NULL) 
    {
        printf("Value of PATH environment variable: %s\n", path_value);
    } else 
    {
        printf("PATH environment variable not found\n");
    }

    // Set a new environment variable
    char *new_var_name = "MY_VAR";  //Declares two variables to store the name and value of the new environment variable.
    char *new_var_value = "Hello, World!";
    if (setenv(new_var_name, new_var_value, 1) == 0) //Calls the setenv function to set a new environment variable named MY_VAR with the value "Hello, World!".
    {                                                //The third argument (1) indicates whether to overwrite the variable if it already exists (1 for true).
        printf("Successfully set %s=%s\n", new_var_name, new_var_value);
    } 
    else
    {
        printf("Failed to set environment variable");
        return EXIT_FAILURE;
    }

    // Retrieve the value of the newly set environment variable
    char *my_var_value = getenv(new_var_name);
    if (my_var_value != NULL)
    {
        printf("Value of %s environment variable: %s\n", new_var_name, my_var_value);
    } 
    else 
    {
        printf("%s environment variable not found\n", new_var_name);
    }

    return EXIT_SUCCESS;
}

