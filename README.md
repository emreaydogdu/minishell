# Minishell

#TODO
- ft_split with spaces as delimeter: splits outside a string
- for each splittet node you need to check if its a pipe etc. otherwise its a word and "push" as a token
- 

#Steps
- read input from Terminal (done)
- parse given commands 
- lexer -> parser -> expander -> executor 

#Sources
- https://harm-smits.github.io/42docs/projects/minishell
- https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218
- https://ruslanspivak.com/lsbasi-part7/
- https://42-cursus.gitbook.io/guide/rank-03/minishell/functions
- https://minishell.simple.ink

#Issues\
```echo $?``` return last exitcode 0 or 1\
i should expand $? to its value.

Done ```pwd oi``` -> pwd: too many arguments \
```export hello``` Segfault\ compare with BASH
Done ```export HELLO=123``` Segfault\
```export A-``` -> export: not valid in this context: A- // we are pushing A-= but we should 	not. See BASH what it does.
```export HELLO=123 A``` Segfault\ 
```export HELLO="123 A-"``` Wrong ft_splitting -> ftsplit should check "" even inside strings  like hello"string "yeah\
```export hello world``` Wrong ft_splitting -> ftsplit should check "" even inside strings  like hello"string "yeah\
```export HELLO-=123``` Handle special characters like BASH\
```env``` we have an extra line to remove.

```in Expander``` Fix this: //free(key_env); // Chakib : ATTENTION with SEGFAULT



compare with bash and fix

`builtin issues`
40. too many args


