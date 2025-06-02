# Minishell – 42 Team-Project
**About:**<br />
This project is a small Unix shell written in C.<br />
It works like a basic version of bash, allowing the user to run commands, use pipes, redirects, and environment variables.<br />
The goal is to understand processes, file descriptors, signals, and how a shell works behind the scenes.
<br/><br/>

**Features:**<br />
Built-in commands:<br />
        cd, echo, env, exit, export, pwd, unset<br />

Support for:
        Pipes (|)<br />
        Redirects (>, >>, <)<br />
        Here-documents (<<)<br />
        Environment variables ($VAR)<br />
        Quotes ('single', "double")<br />

Signal handling (e.g. Ctrl+C, Ctrl+\)<br />
<br/><br/>
**Compile:**

        make

**Run:**

        ./minishell

Then enter commands like:

        ls -l | grep .c > files.txt

**What We Learned:**<br />
    Parsing user input and handling special characters<br />
    Creating and managing child processes with fork() and execve()<br />
    Managing file descriptors for input/output redirection<br />
    Handling signals like SIGINT and SIGQUIT<br />
    Implementing a basic shell environment
