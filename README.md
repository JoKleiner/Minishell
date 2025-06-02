# Minishell – 42 Team-Project
**About:**<br />
This project is a small Unix shell written in C.<br />
It works like a basic version of bash, allowing the user to run commands, use pipes, redirects, and environment variables.<br />
The goal is to understand processes, file descriptors, signals, and how a shell works behind the scenes.
<br/><br/>

**Team:**<br />
This was a team project done together with Horrjiy.<br />

**My part:**
- Parsing using a linked list<br />
- Handling of pipes (|)<br />
- Redirects (>, <, >>)<br />
- Here-documents (<<)<br />
- Expanding the Environment variables<br />

**Horrjiy’s part:**
- All built-in commands<br />
- Command execution<br />

**Both worked on:**
- Signal handling (Ctrl+D Ctrl+C, Ctrl+\\) <br />
<br />

**Features:**
Built-in commands:<br />
- cd, echo, env, exit, export, pwd, unset<br />

**Support for:**
- Pipes (|)<br />
- Redirects (>, >>, <)<br />
- Here-documents (<<)<br />
- Environment variables ($VAR)<br />
- Quotes ('single', "double")<br />

**Signal handling:**
- Ctrl+C<br />
- Ctrl+\ <br />
- Ctrl+D<br />

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
