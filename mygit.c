#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int create_new_project(char *project_name)
{
    if (mkdir(project_name, 0777) != 0)
    {
        perror("Error creating project directory");
        return 1;
    }

    if (chdir(project_name) != 0)
    {
        perror("Error changing into project directory");
        return 1;
    }

    if (system("git init") != 0)
    {
        printf("Error initializing Git.\n");
        return 1;
    }

    printf("New project '%s' created and Git initialized successfully!\n", project_name);
    return 0;
}

int commit_changes()
{
    if (system("git add .") != 0)
    {
        printf("Error adding files to Git.\n");
        return 1;
    }

    char category[50], message[200];

    printf("Enter commit category: ");
    fgets(category, sizeof(category), stdin);
    category[strcspn(category, "\n")] = '\0'; // Remove trailing newline

    printf("Enter commit message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove trailing newline

    char command[500];
    sprintf(command, "git commit -am \"[%s] %s\"", category, message);

    if (system(command) != 0)
    {
        printf("Error executing Git commit command.\n");
        return 1;
    }

    printf("Commit successful!\n");
    return 0;
}

int push_changes()
{
    if (system("git push") != 0)
    {
        printf("Error pushing to Git repository.\n");
        return 1;
    }

    printf("Push successful!\n");
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 3 && strcmp(argv[1], "new") == 0)
    {
        return create_new_project(argv[2]);
    }
    else if (argc == 2 && strcmp(argv[1], "commit") == 0)
    {
        return commit_changes();
    }
    else if (argc == 2 && strcmp(argv[1], "push") == 0)
    {
        return push_changes();
    }
    else
    {
        printf("Invalid command.\n");
        return 1;
    }
}
