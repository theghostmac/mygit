# mygit - Git Assistance Tool

`mygit` is a command-line tool designed to streamline and simplify common Git operations. It offers a set of commands that encapsulate complex Git workflows, making it easier to manage your Git repositories.

## Features

- **Create New Project:** Initializes a new project with Git.
- **Commit Changes:** Simplifies the process of committing changes with a category and message.
- **Push Changes:** Pushes committed changes to the remote repository.
- **Stage Files:** Interactively stage files with a simple yes/no prompt.
- **Commit and Push Staged Changes:** Combines committing and pushing of staged changes into one easy step.

## Installation

To install `mygit`, follow these steps:

1. Clone the repository: `git clone [repository-url]`
2. Navigate to the cloned directory: `cd mygit`
3. Compile the program: `make build`
4. Add `mygit` to your PATH (optional): `export PATH=$PATH:/path/to/mygit`

Make sure you have `gcc` installed on your system to compile the program.

## Usage

### Creating a New Project

```
mygit new <project_name>
```

Initializes a new project and sets up a Git repository.

### Committing Changes

```
mygit commit
```

Prompts for a commit category and message, then commits the changes.

### Pushing Changes

```
mygit push
```

Pushes the committed changes to the remote repository.

### Staging Files

```
mygit stage
```

Interactively select files to stage for the next commit.

### Committing and Pushing Staged Changes

```
mygit push staged
```

Commits the staged changes with a specified category and message, then pushes to the remote repository.

## Contributing

Contributions to `mygit` are welcome. Please fork the repository and submit pull requests with your improvements.

## License

`mygit` is open-sourced software licensed under [My license](LICENSE).
