# dstring
## Dynamic string library, ANSI C 89

Description
-----------
This single-header 'library' provides dynamically growing and shrinking strings for the C programming language.
It has written conforming to the ANSI C89 standard.
Using the dynamic strings provided by dstring simplifies and speeds up working with text in C.

Installation
------------
Just copy dstring.h to your include directory and include it in your project. No external libraries, apart from the C standard library are needed.

Usage
-----

<<<<<<< HEAD
Set
- ``` ```
- string_setn
- string_setf
- string_setfva
- string_setc

Add
---

Del
---

Insert

=======
Set
```
`int string_set(String *p_string, const char * const p_text);`
`int string_setn(String *p_string, const char * const p_text, const size_t length);`
`int string_setf(String *p_string, const char * const p_format, ...);`
int string_setfva(String *p_string, const char * const p_format, va_list va_args, const size_t length);
int string_setc(String *p_string, const char ch);
int string_add(String *p_string, const char * const p_text);
int string_addn(String *p_string, const char * const p_text, const size_t length);
int string_addf(String *p_string, const char * const p_format, ...);
int string_addfva(String *p_string, const char * const p_format, va_list va_args, const size_t length);
int string_addc(String *p_string, const char ch);
int string_delc(String *p_string);
int string_insert(String *p_string, const size_t p_pos, const char * const p_text);
int string_insertn(String *p_string, const size_t p_pos, const char * const p_text, const size_t length);
int string_insertf(String *p_string, const size_t p_pos, const char * const p_format, ...);
int string_insertfva(String *p_string, const size_t p_pos, const char * const p_format, va_list va_args, const size_t length);
int string_insertc(String *p_string, const size_t p_pos, const char ch);
int string_remove(String *p_string, const size_t p_pos, const size_t length);
int string_replace(String *p_string, const char * const p_old, const char * const p_new);
int string_replacec(String *p_string, const char p_old, const char p_new);
int string_compare(String *p_string1, String *p_string2);
int string_getline(String *p_string, FILE *p_stream);
int string_readfile(String *p_string, const char *filename);
int string_tolower(String *p_string);
int string_toupper(String *p_string);
void string_clear(String *p_string);
```
>>>>>>> 5a3bb763d12d18d20b09cf2ba748f16b90f63856
Contributing
------------
Any contribution is highly appreciated. The best way to contribute is to open a [pull request on GitHub](https://help.github.com/articles/using-pull-requests).

License
-------
[MIT](https://github.com/ibmicroapple/dstring/blob/master/LICENSE)

Copyright
---------
Copyright (C) 2016 ibmicroapple
