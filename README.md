# 🐚 Minishell - As beautiful as a shell can be

A minimal yet powerful shell implementation, developed as part of the **42 School Common Core**. This project is a deep dive into systems programming, process management, and command-line parsing.

---

## 🚀 Overview
The goal of this project was to create a simple shell, mimicking the behavior of **Bash**. It handles command execution, redirections, pipes, and signals, all while ensuring a leak-free environment.

### 🛠 Tech Stack
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![Makefile](https://img.shields.io/badge/Makefile-000000?style=for-the-badge&logo=gnu-make&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)

---

## ✨ Key Features
* **Command Execution:** Full support for executables found in the PATH or via absolute/relative paths.
* **Built-ins:** Custom implementation of:
  * `echo` (with `-n` option)
  * `cd` (relative/absolute paths)
  * `pwd`, `export`, `unset`, `env`, `exit`
* **Redirections:** Support for `<`, `>`, `<<` (heredoc), and `>>`.
* **Pipes:** Multi-piping support (`|`) to chain commands efficiently.
* **Signal Handling:** Proper management of `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` in both interactive and child-process modes.
* **Environment Variables:** Dynamic management of environment variables using a linked list.

---

## 🧠 What I Learned
Developing Minishell was a milestone in my path at **42 Firenze**. It allowed me to master:
* **Process Orchestration:** Using `fork()`, `waitpid()`, and `execve()` to manage child processes.
* **File Descriptor Manipulation:** Redirection logic using `dup2()` and `pipe()`.
* **Parsing Logic:** Building a robust lexer and parser to handle tokens, quotes, and expansions.
* **Memory Management:** Ensuring no memory leaks even in complex edge cases (verified with Valgrind).

---

## 🛠 Installation & Usage

### Prerequisites
You need the `readline` library installed on your system.
* **Fedora/Bazzite:** `sudo dnf install readline-devel`
* **Debian/Ubuntu:** `sudo apt-get install libreadline-dev`

### Compilation
Clone the repository and run:
```bash
make
```
---
## 👥 The Team
This project was developed in collaboration with:
* **Giulia Viganò** - [@giuliavigano](https://github.com/giuliavigano/giuliavigano)
* **Manuel Chiaramello** - [@chiaramellomanuel](https://github.com/chiaramellomanuel)

Working in a pair allowed us to tackle the complexity of the shell by dividing the logic into **Parsing/Lexing** and **Execution/Built-ins**, ensuring a modular and well-tested codebase.
