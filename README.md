# minishell
Known Bugs with examples:
- `"*"hola`   Wildcard may expand when it should not
- `<< "'$USER'"` Ends with `''$USER'` instead of `'$USER'`
- `<< eof << eof3 | | << eof4` Here-docs before syntax error are not executed

By [crmanzan](https://github.com/Bgoost) and yours truly
