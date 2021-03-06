# dstring
## Dynamic string library, ANSI C 89, unicode / utf-8 support

Description
-----------
This single-header 'library' provides dynamically growing and shrinking strings for the C programming language.
It supports unicode and does comply to the ANSI C89 standard.

Installation
------------
Just copy dstring.h to your include directory and include it in your project. No external libraries, apart from the C standard library are needed.

Usage
-----
For a quick start you may want to take a look at the simple [example](https://github.com/ibmicroapple/dstring/blob/master/example.c).

Common Mistakes
---------------
- Before working with unicode you may need to set the correct locale. An example is given in the example.
- Before using an object of type String or WString you MUST initialize it with zero.
- Calling a unicode function on a normal string or vice versa

Quickstart
----------
The following code snippet should give you a basic overview over some essential functions.
Working with unicode-strings is equivalent to working with normal strings, but type- and function names differ.
```
/* Create a local string object and initialize it with Null. */
String mystr = STRING_NULL;

/* Set string */
string_set(&mystr, "Hello World!");

/* Add string */
string_add(&mystr, " Goodbye!");

/* Print string */
string_print(&mystr);

/* Print some information about the string */
printf(	"c_str: '%s'\n"
	"length: '%d'\n"
	"blocksize: '%d'\n"
	"size: '%d'\n",
	mystr.c_str, mystr.length, mystr.blocksize, mystr.size);

/* Clear the string */
string_clear(&mystr);
```

**Set**
```
int string_set(String *p_string, const char * const p_text);
int string_setn(String *p_string, const char * const p_text, const size_t length);
int string_setf(String *p_string, const char * const p_format, ...);
int string_setfva(String *p_string, const char * const p_format, va_list va_args, const size_t length);
int string_setc(String *p_string, const char ch);
```

**Add**
```
int string_add(String *p_string, const char * const p_text);
int string_addn(String *p_string, const char * const p_text, const size_t length);
int string_addf(String *p_string, const char * const p_format, ...);
int string_addfva(String *p_string, const char * const p_format, va_list va_args, const size_t length);
int string_addc(String *p_string, const char ch);
```

**Delete**
```
int string_delc(String *p_string);
int string_remove(String *p_string, const size_t p_pos, const size_t length);
```

**Insert**
```
int string_insert(String *p_string, const size_t p_pos, const char * const p_text);
int string_insertn(String *p_string, const size_t p_pos, const char * const p_text, const size_t length);
int string_insertf(String *p_string, const size_t p_pos, const char * const p_format, ...);
int string_insertfva(String *p_string, const size_t p_pos, const char * const p_format, va_list va_args, const size_t length);
int string_insertc(String *p_string, const size_t p_pos, const char ch);
```

**Replace**
```
int string_replace(String *p_string, const char * const p_old, const char * const p_new);
int string_replacec(String *p_string, const char p_old, const char p_new);
```

**Misc**
```
int string_compare(String *p_string1, String *p_string2);
int string_getline(String *p_string, FILE *p_stream);
int string_readfile(String *p_string, const char *filename);
int string_tolower(String *p_string);
int string_toupper(String *p_string);
void string_clear(String *p_string);
```

Contributing
------------
Any contribution is highly appreciated. The best way to contribute is to open a [pull request on GitHub](https://help.github.com/articles/using-pull-requests).

License
-------
[MIT](https://github.com/ibmicroapple/dstring/blob/master/LICENSE)

Copyright
---------
Copyright (C) 2016 ibmicroapple
