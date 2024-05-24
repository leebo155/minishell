# minishell
 Create a simple shell.
 
  <img alt="image" src="https://github.com/leebo155/minishell/blob/main/img/minishell1.jpg">

## Introduction

* This project offers an opportunity to learn about processes and file descriptors by creating a simple shell.
* The basic functionality of the program is similar to that of bash.
* There are built-in commands: `cd`, `env`, `echo`, `pwd`, `export`, `unset`, `exit`.
* Pipes `|`, each redirection `>`  `>>`  `<`  `<<` and quotes `'` `"` are implemented.
* You can use environment variables`($ followed by a sequence of characters)` and `$?`.
  
## Process
* Here's a simple diagram depicting the parsing process:   
  ◦ The command line is divided based on whitespace.   
  ◦ Merge the divided words based on the pipe.   
  ◦ Execute all merged chunks.   
  <img alt="image" src="https://github.com/leebo155/minishell/blob/main/img/minishell2.jpg">
  
* Here's the parsing order represented as a structure:   
  ◦ As the string is divided, it is all transformed into chunk structures.   
  ◦ Traverse the chunk list and convert chunks into parser_info structures, with pipes as the delimiter.   
  ◦ Convert the transformed parser_info into cmd structures for execution.   
  <img alt="image" src="https://github.com/leebo155/minishell/blob/main/img/minishell3.jpg">

* Here's a diagram that provides a more detailed representation of the parsing order using structures:
  <img alt="image" src="https://github.com/leebo155/minishell/blob/main/img/minishell4.jpg">

* Here's a flowchart:
  <img alt="image" src="https://github.com/leebo155/minishell/blob/main/img/minishell%20flow.jpg">
  
## Makefile

| Rules | Description |
| ----- | ----------- |
| all | Compile a program minishell. |
| clean | Remove all the temporary generated files. |
| fclean | Remove all the generated files. |
| re | Remove all the generated files and compile a minishell. |

## Usage

* You should run it without any arguments.
  ```shall
  $> ./minishell
  minishell$
  ```

* It won't execute if there are any arguments.
  ```shall
  $> ./minishell leebo155
  I don't need any arguments!
  ```
