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

int stage_files()
{
    FILE *fp;
    char path[1035];
    char command[500];

    // Execute a process listing unstaged files
    // Adjusted awk command to include both modified and new files
    fp = popen("git status -s | awk '$1 !~ /^A$/ && $1 != \"\" {print $2}'", "r");
    if (fp == NULL)
    {
        printf("Failed to run command\n");
        return 1;
    }

    // Read the output a line at a time
    while (fgets(path, sizeof(path), fp) != NULL)
    {
        path[strcspn(path, "\n")] = '\0'; // Remove trailing newline
        printf("%s (y/n): ", path);

        char response;
        scanf(" %c", &response); // Read user response

        if (response == 'y' || response == 'Y')
        {
            sprintf(command, "git add %s", path);
            if (system(command) != 0)
            {
                printf("Error staging file %s.\n", path);
            }
            else
            {
                printf("%s staged successfully.\n", path);
            }
        }
    }

    // Close the pipe
    pclose(fp);
    printf("Staging complete.\n");
    return 0;
}

int commit_and_push_staged()
{
    char category[50], message[200];

    printf("Enter commit category: ");
    fgets(category, sizeof(category), stdin);
    category[strcspn(category, "\n")] = '\0'; // Remove trailing newline

    printf("Enter commit message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove trailing newline

    char commit_command[500];
    sprintf(commit_command, "git commit -m \"[%s] %s\"", category, message);

    if (system(commit_command) != 0)
    {
        printf("Error executing Git commit command.\n");
        return 1;
    }

    printf("Commit successful!\n");

    if (system("git push") != 0)
    {
        printf("Error pushing to Git repository.\n");
        return 1;
    }

    printf("Push successful!\n");
    return 0;
}

void print_help()
{
    printf("Available mygit commands:\n");
    printf("  new <project_name> - Create a new project directory and initialize Git\n");
    printf("  commit             - Commit changes with a category and message\n");
    printf("  push               - Push changes to remote repository\n");
    printf("  stage              - Stage selected files interactively\n");
    printf("  help               - Display this help message\n");
    printf("  push staged        - Commit and push staged files\n");
}

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "help") == 0)
    {
        print_help();
        return 0;
    }
    else if (argc == 3 && strcmp(argv[1], "new") == 0)
    {
        return create_new_project(argv[2]);
    }
    else if (argc == 2 && strcmp(argv[1], "commit") == 0)
    {
        return commit_changes();
    }
    else if (argc == 3 && strcmp(argv[1], "push") == 0 && strcmp(argv[2], "staged") == 0)
    {
        return commit_and_push_staged();
    }
    else if (argc == 2 && strcmp(argv[1], "push") == 0)
    {
        return push_changes();
    }
    else if (argc == 2 && strcmp(argv[1], "stage") == 0)
    {
        return stage_files();
    }
    else
    {
        printf("Invalid command.\n");
        return 1;
    }
}
