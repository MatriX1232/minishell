# Minishell

![GitHub repo size](https://img.shields.io/github/repo-size/MatriX1232/minishell)
![GitHub contributors](https://img.shields.io/github/contributors/MatriX1232/minishell)
![GitHub stars](https://img.shields.io/github/stars/MatriX1232/minishell?style=social)
![GitHub forks](https://img.shields.io/github/forks/MatriX1232/minishell?style=social)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20MacOS-informational)
![Language](https://img.shields.io/badge/Language-C-blue)
![License](https://img.shields.io/github/license/MatriX1232/minishell)

Minishell is a simple shell implementation project created as part of the 42 school curriculum. This project involves building a minimal, functional shell with a subset of features found in common UNIX shells like `bash` or `zsh`.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Supported Commands](#supported-commands)
- [Built-ins](#built-ins)
- [Credits](#credits)

## Overview

Minishell is designed to mimic the behavior of the Bash shell, allowing users to interact with the command line, execute commands, and manage environment variables. The goal is to develop a deeper understanding of process management, pipes, redirection, and UNIX signals.

## Features
- Interactive prompt where users can type commands.
- Supports simple command execution and command chaining with pipes (`|`).
- Input/output redirection (`>`, `>>`, `<`).
- Signal handling for `Ctrl+C`, `Ctrl+D`, and `Ctrl+\`.
- Environment variable management with `export`, `unset`, etc.
- Built-in commands like `cd`, `pwd`, `echo`, and more.
- Error handling for command not found or invalid syntax.

## Installation

To build and run the minishell, follow these steps:

1. Clone the repository:
  ```bash
  git clone https://github.com/MatriX1232/minishell.git
  ```
2. Navigate to the project directory:
  ```bash
  cd minishell
  ```
3. Build the project:
  ```bash
  make
  ```
4. Run the shell:
  ```bash
  ./minishell
  ```

## Usage
Once the shell is running, you will be presented with a prompt where you can type and execute commands.
You can use both built-in commands and external programs.
```bash
^_^  minishell ▶ pwd
/home/msolinsk/42Warsaw/Core_Curriculum/minishell
^_^  minishell ▶ export MY_VAR=HELL
^_^  minishell ▶ echo "Welcome to programming $MY_VAR."
Welcome to programming HELL.
^_^  minishell ▶ ls
LICENSE  Makefile  include  libft  minishell  src
^_^  minishell ▶ unset
＞︿＜ minishell ▶ Usage: unset <variable>
^_^  minishell ▶
```
Exiting the Shell
You can exit the minishell by typing ```exit``` or using ```Ctrl+D```.

## Credits
This project was developed as an group project in colaboration with [idomagal](https://github.com/igordotdev)
