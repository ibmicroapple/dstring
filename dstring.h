#ifndef DSTRING_H
#define DSTRING_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <wchar.h>
#include <wctype.h>

#define STRING_NULL (String){0}
#define WSTRING_NULL (WString){0}
#define STRING_OK 0
#define STRING_ERR -1

typedef struct
{
	char	*c_str;
	size_t	length,
		blocksize,
		size;
} String;

typedef struct
{
	wchar_t	*w_str;
	size_t	length,
		blocksize,
		size;
} WString;

int string_set(String *p_string, const char * const p_text);
int string_setn(String *p_string, const char * const p_text, const size_t length);
int string_setf(String *p_string, const char * const p_format, ...);
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
int string_levenshtein(String *p_string1, String *p_string2);
void string_clear(String *p_string);
int string_towstring(WString *p_wstring, String *p_string);
int string_getpos(String *p_string);

int wstring_set(WString *p_string, const wchar_t * const p_text);
int wstring_setn(WString *p_string, const wchar_t * const p_text, const size_t length);
int wstring_setf(WString *p_string, const wchar_t * const p_format, ...);
int wstring_setfva(WString *p_string, const wchar_t * const p_format, va_list va_args, const size_t length);
int wstring_setc(WString *p_string, const wchar_t ch);
int wstring_add(WString *p_string, const wchar_t * const p_text);
int wstring_addn(WString *p_string, const wchar_t * const p_text, const size_t length);
int wstring_addf(WString *p_string, const wchar_t * const p_format, ...);
int wstring_addfva(WString *p_string, const wchar_t * const p_format, va_list va_args, const size_t length);
int wstring_addc(WString *p_string, const wchar_t ch);
int wstring_delc(WString *p_string);
int wstring_insert(WString *p_string, const size_t p_pos, const wchar_t * const p_text);
int wstring_insertn(WString *p_string, const size_t p_pos, const wchar_t * const p_text, const size_t length);
int wstring_insertf(WString *p_string, const size_t p_pos, const wchar_t * const p_format, ...);
int wstring_insertfva(WString *p_string, const size_t p_pos, const wchar_t * const p_format, va_list va_args, const size_t length);
int wstring_insertc(WString *p_string, const size_t p_pos, const wchar_t ch);
int wstring_remove(WString *p_string, const size_t p_pos, const size_t length);
int wstring_replace(WString *p_string, const wchar_t * const p_old, const wchar_t * const p_new);
int wstring_replacec(WString *p_string, const wchar_t p_old, const wchar_t p_new);
int wstring_compare(WString *p_string1, WString *p_string2);
int wstring_getline(WString *p_string, FILE *p_stream);
int wstring_readfile(WString *p_string, const char *filename);
int wstring_tolower(WString *p_string);
int wstring_toupper(WString *p_string);
int wstring_levenshtein(WString *p_string1, WString *p_string2);
void wstring_clear(WString *p_string);
int wstring_tostring(String *p_string, WString *p_wstring);
int wstring_frommb(WString *p_string, const char * const p_text);

int cstr_levenshtein(const char * const p_cstr1, const char * const p_cstr2);
int wstr_levenshtein(const wchar_t * const p_wstr1, const wchar_t * const p_wstr2);

#define string_print(p_string) puts(((String*)p_string)->c_str)
#define wstring_print(p_string) wprintf(L"%ls\n", ((WString*)p_string)->w_str)

int string_set(String *p_string, const char * const p_text)
{
	if(p_string->c_str) string_clear(p_string);

	p_string->length = strlen(p_text);
	p_string->size = p_string->length + p_string->blocksize + 1;
	p_string->c_str = malloc(sizeof(char) * p_string->size);

	if(!p_string->c_str) return(STRING_ERR);

	memcpy(p_string->c_str, p_text, p_string->length);
	p_string->c_str[p_string->length] = '\0';

	return(STRING_OK);
}

int string_setn (String *p_string, const char * const p_text, const size_t length)
{
	if(p_string->c_str) string_clear(p_string);
	if(!length) return(STRING_OK);

	p_string->length = length;
	p_string->size = p_string->length + p_string->blocksize + 1;
	p_string->c_str = malloc(sizeof(char) * p_string->size);

	if(!p_string->c_str) return(STRING_ERR);

	memcpy(p_string->c_str, p_text, p_string->length);
	p_string->c_str[p_string->length] = '\0';

	return(STRING_OK);
}

int string_setf (String *p_string, const char * const p_format, ...)
{
	va_list args;

	if(p_string->c_str) string_clear(p_string);

	va_start(args, p_format);

		p_string->length = vsnprintf(0, 0, p_format, args);

	va_end(args);

	va_start(args, p_format);

		p_string->size = p_string->length + p_string->blocksize + 1;

		p_string->c_str = malloc(sizeof(char) * p_string->size);

		if(!p_string->c_str)
		{
			va_end(args);
			return(STRING_ERR);
		}

		vsprintf(p_string->c_str, p_format, args);

	va_end(args);

	return(STRING_OK);
}

int string_setfva (String *p_string, const char * const p_format, va_list va_args, const size_t length)
{
	if(p_string->c_str) string_clear(p_string);

	p_string->size = length + p_string->blocksize + 1;

	p_string->c_str = malloc(sizeof(char) * p_string->size);

	if(!p_string->c_str)
	{
		return(STRING_ERR);
	}

	vsprintf(p_string->c_str, p_format, va_args);

	return(STRING_OK);
}

int string_setc (String *p_string, const char ch)
{
	if(p_string->c_str) string_clear(p_string);

	p_string->length = 1;
	p_string->size = p_string->length + p_string->blocksize + 1;
	p_string->c_str = malloc(sizeof(char) * p_string->size);

	if(!p_string->c_str) return(STRING_ERR);

	p_string->c_str[0] = ch;
	p_string->c_str[p_string->length] = '\0';

	return(STRING_OK);
}

int string_add (String *p_string, const char * const p_text)
{
	size_t textlen, new_size;
	char * new_c_str;

	if(!p_string->c_str) return(string_set(p_string, p_text));

	textlen = strlen(p_text);

	if(!textlen) return(STRING_ERR);

	if((p_string->length + textlen + 1) > p_string->size)
	{
		new_size = p_string->length + textlen + p_string->blocksize + 1;
		new_c_str = realloc(p_string->c_str, sizeof(char) * new_size);

		if(!new_c_str) return(STRING_ERR);

		p_string->c_str = new_c_str;
	}

	memcpy(&p_string->c_str[p_string->length], p_text, textlen);

	p_string->length += textlen;
	p_string->size = new_size;

	p_string->c_str[p_string->length] = '\0';

	return(STRING_OK);
}

int string_addn (String *p_string, const char * const p_text, const size_t length)
{
	size_t	new_size;
	char	* new_c_str;

	if(!p_string->c_str) return(string_setn(p_string, p_text, length));

	if((p_string->length + length + 1) > p_string->size)
	{
		new_size = p_string->length + length + p_string->blocksize + 1;
		new_c_str = realloc(p_string->c_str, sizeof(char) * new_size);

		if(!new_c_str) return(STRING_ERR);

		p_string->c_str = new_c_str;
	}

	memcpy(&p_string->c_str[p_string->length], p_text, length);

	p_string->length += length;
	p_string->size = new_size;

	p_string->c_str[p_string->length] = '\0';

	return(STRING_OK);
}

int string_addf (String *p_string, const char * const p_format, ...)
{
	size_t length, new_size;
	char * new_c_str;

	va_list args;

	va_start(args, p_format);

		length = vsnprintf(0, 0, p_format, args);

	va_end(args);

	va_start(args, p_format);

		if((p_string->length + length + 1) > p_string->size)
		{
			new_size = p_string->length + length + p_string->blocksize + 1;
			new_c_str = realloc(p_string->c_str, sizeof(char) * new_size);

			if(!new_c_str)
			{
				va_end(args);
				return(STRING_ERR);
			}

			p_string->c_str = new_c_str;
		}

		vsprintf(&p_string->c_str[p_string->length], p_format, args);

		p_string->length += length;
		p_string->size = new_size;

	va_end(args);

	return(STRING_OK);
}

int string_addfva (String *p_string, const char * const p_format, va_list va_args, const size_t length)
{
	size_t new_size;
	char * new_c_str;

	if((p_string->length + length + 1) > p_string->size)
	{
		new_size = p_string->length + length + p_string->blocksize + 1;
		new_c_str = realloc(p_string->c_str, sizeof(char) * new_size);

		if(!new_c_str)
		{
			return(STRING_ERR);
		}

		p_string->c_str = new_c_str;
	}

	vsprintf(&p_string->c_str[p_string->length], p_format, va_args);

	p_string->length += length;
	p_string->size = new_size;

	return(STRING_OK);
}

int string_addc (String *p_string, const char ch)
{
	size_t new_size;
	char * new_c_str;

	if(!p_string->c_str) return(string_setc(p_string, ch));

	if((p_string->length + 1 + 1) > p_string->size)
	{
		new_size = p_string->length + 1 + p_string->blocksize + 1;
		new_c_str = realloc(p_string->c_str, sizeof(char) * new_size);

		if(!new_c_str) return(STRING_ERR);

		p_string->c_str = new_c_str;
	}

	p_string->c_str[p_string->length] = ch;
	p_string->length++;
	p_string->c_str[p_string->length] = '\0';
	p_string->size = new_size;

	return(STRING_OK);
}

int string_delc (String *p_string)
{
	char * new_cstr;

	if(!p_string->length) return(STRING_ERR);

	p_string->length--;
	p_string->c_str[p_string->length] = '\0';

	if(p_string->length + p_string->blocksize < p_string->size)
	{
		new_cstr = realloc(p_string->c_str, p_string->length);
		if(!new_cstr) return(STRING_OK);

		p_string->c_str = new_cstr;
		p_string->size = p_string->length + 1;
	}

	return(STRING_OK);
}

int string_insert(String *p_string, const size_t p_pos, const char * const p_text)
{
	String new_string = {0, .blocksize = p_string->blocksize};

	string_setn(&new_string, p_string->c_str, p_pos);

	string_add(&new_string, p_text);

	string_add(&new_string, &p_string->c_str[p_pos]);

	string_clear(p_string);

	*p_string = new_string;

	return(STRING_OK);
}

int string_insertn (String *p_string, const size_t p_pos, const char * const p_text, const size_t length)
{
	String new_string = {0, .blocksize = p_string->blocksize};

	string_setn(&new_string, p_string->c_str, p_pos);

	string_addn(&new_string, p_text, length);

	string_add(&new_string, &p_string->c_str[p_pos]);

	string_clear(p_string);

	*p_string = new_string;

	return(STRING_OK);
}

int string_insertf (String * p_string, const size_t p_pos, const char * const p_format, ...)
{
	size_t length;
	char * buffer;
	int status;

	va_list args;

	va_start(args, p_format);

		length = vsnprintf(0, 0, p_format, args);

	va_end(args);

	va_start(args, p_format);

		buffer = malloc(sizeof(char) * length);
		if(!buffer)
		{
			va_end(args);
			return(STRING_ERR);
		}

		vsprintf(buffer, p_format, args);

		status = string_insert(p_string, p_pos, buffer);

		free(buffer);

	va_end(args);

	return(status);
}

int string_insertfva (String * p_string, const size_t p_pos, const char * const p_format, va_list va_args, const size_t length)
{
	char * buffer;
	int status;

	buffer = malloc(sizeof(char) * length);
	if(!buffer) return(STRING_ERR);

	vsprintf(buffer, p_format, va_args);

	status = string_insert(p_string, p_pos, buffer);

	free(buffer);

	return(status);
}

int string_insertc (String * p_string, const size_t p_pos, const char ch)
{
	String new_string = {0, .blocksize = p_string->blocksize};

	if(p_pos > p_string->length) return(STRING_ERR);

	if(p_pos)
	{
		string_setn(&new_string, p_string->c_str, p_pos);
	}

	string_addc(&new_string, ch);

	if(p_pos || p_string->length)
	{
		string_add(&new_string, &p_string->c_str[p_pos]);
	}

	string_clear(p_string);

	*p_string = new_string;

	return(STRING_OK);
}

int string_remove (String * p_string, const size_t p_pos, const size_t length)
{
	String new_string = {0, .blocksize = p_string->blocksize};

	if((p_pos + length) > p_string->length) return(STRING_ERR);

	string_setn(&new_string, p_string->c_str, p_pos);

	string_add(&new_string, &p_string->c_str[p_pos + length]);

	string_clear(p_string);

	*p_string = new_string;

	return(STRING_OK);
}

int string_replace (String * p_string, const char * const p_old, const char * const p_new)
{
	char *strpos, *old_strpos;

	String new_string = {0, .blocksize = p_string->blocksize};

	for(old_strpos = p_string->c_str; (strpos = strstr(old_strpos, p_old)); old_strpos = strpos + strlen(p_old))
	{
		string_addn(&new_string, old_strpos, strpos - old_strpos);
		string_add(&new_string, p_new);
	}

	if((old_strpos - p_string->c_str) < p_string->length)
	{
		string_add(&new_string, old_strpos);
	}

	string_clear(p_string);

	*p_string = new_string;

	return(STRING_OK);
}

int string_replacec(String *p_string, const char p_old, const char p_new)
{
	size_t i;

	for(i = 0; i < p_string->length; i++)
	{
		if(p_string->c_str[i] == p_old)
		{
			p_string->c_str[i] = p_new;
		}
	}

	return(STRING_OK);
}

int string_compare (String * p_string1, String * p_string2)
{
	if(p_string1->length != p_string2->length) return(0);

	return(!(strncmp(p_string1->c_str, p_string2->c_str, p_string1->length)));
}

int string_getline (String * p_string, FILE * p_stream)
{
	int ch;

	if(p_string->c_str) string_clear(p_string);

	for(ch = fgetc(p_stream); ch != '\n' && ch != EOF; ch = fgetc(p_stream))
	{
		string_addc(p_string, ch);
	}

	return(STRING_OK);
}

static long filesize(FILE *file)
{
	long offset, len;

	offset = ftell(file);
	fseek(file, 0, SEEK_END);
	len = ftell(file);
	fseek(file, offset, SEEK_SET);

	return(len);
}

int string_readfile (String *p_string, const char *p_filename)
{
	FILE *file;
	long size;

	if(p_string->c_str) string_clear(p_string);

	file = fopen(p_filename, "rt");
	if(!file) return(STRING_ERR);

	size = filesize(file);

	p_string->c_str = malloc(sizeof(char) * size + 1);
	if(!p_string->c_str)
	{
		fclose(file);
		return(STRING_ERR);
	}

	p_string->size = size + 1;
	p_string->length = size;

	fread(p_string->c_str, size, 1, file);

	p_string->c_str[p_string->length] = '\0';

	fclose(file);

	return(STRING_OK);
}

void string_clear (String * p_string)
{
	if(p_string->c_str)
	{
		memset(p_string->c_str, 0, p_string->length);
		free(p_string->c_str);
		p_string->c_str = 0;
	}

	p_string->length = p_string->size = 0;
}

int string_tolower(String *p_string)
{
	char *cptr;

	if(!p_string->c_str) return(STRING_ERR);

	for(cptr = p_string->c_str; *cptr; cptr++)
	{
		*cptr = tolower(*cptr);
	}

	return(STRING_OK);
}

int string_toupper(String *p_string)
{
	char *cptr;

	if(!p_string->c_str) return(STRING_ERR);

	for(cptr = p_string->c_str; *cptr; cptr++)
	{
		*cptr = toupper(*cptr);
	}

	return(STRING_OK);
}

static int min(int a, int b, int c)
{
	int m;

	m = a;

	if(b < m) m = b;
	if(c < m) m = c;

	return(m);
}

int string_levenshtein(String *p_string1, String *p_string2)
{
	int n, m;

	// Step 1

	n = p_string1->length;
	m = p_string2->length;

	if(n == 0) return(m);
	if(m == 0) return(n);

	int d[n+1][m+1];

	// Step 2

	int i, j;

	for(i = 0; i <= n; i++)
	{
		d[i][0] = i;
	}

	for(j = 0; j <= m; j++)
	{
		d[0][j] = j;
	}

	// Step 3

	char s1_i, s2_j;
	int cost;

	for(i = 1; i <= n; i++)
	{
		s1_i = p_string1->c_str[i - 1];

		// Step 4

		for(j = 1; j <= m; j++)
		{
			s2_j = p_string2->c_str[j - 1];

			// Step 5

			if(s1_i == s2_j)
			{
				cost = 0;
			}
			else cost = 1;

			// Step 6

			d[i][j] = min(d[i-1][j]+1, d[i][j-1]+1, d[i-1][j-1]+cost);
		}
	}

	return(d[n][m]);
}

int string_towstring(WString *p_wstring, String *p_string)
{
	if(p_wstring->w_str) wstring_clear(p_wstring);

	p_wstring->length = p_string->length;
	p_wstring->size = p_wstring->length + p_wstring->blocksize + 1;
	p_wstring->w_str = malloc(sizeof(wchar_t) * p_wstring->size);
	if(!p_wstring->w_str) return(STRING_ERR);

	mbstowcs(p_wstring->w_str, p_string->c_str, p_wstring->length);

	p_wstring->w_str[p_wstring->length] = L'\0';

	return(STRING_OK);
}

int string_getpos(String *p_string, const char * const p_text)
{
	if(!p_string->c_str) return(STRING_ERR);

	/* On success a positive value is returned, indicating the position of p_text.
	 * On an error a negative value is returned.
	 */
	return(strstr(p_string->c_str, p_text) - p_string->c_str);
}

/* WString functions */

int wstring_set(WString *p_string, const wchar_t * const p_text)
{
	if(p_string->w_str) wstring_clear(p_string);

	p_string->length = wcslen(p_text);
	p_string->size = p_string->length + p_string->blocksize + 1;
	p_string->w_str = malloc(sizeof(wchar_t) * p_string->size);

	if(!p_string->w_str) return(STRING_ERR);

	memcpy(p_string->w_str, p_text, p_string->length * sizeof(wchar_t));
	p_string->w_str[p_string->length] = '\0';

	return(STRING_OK);
}

int wstring_setn (WString *p_string, const wchar_t * const p_text, const size_t length)
{
	if(p_string->w_str) wstring_clear(p_string);
	if(!length) return(STRING_OK);

	p_string->length = length;
	p_string->size = p_string->length + p_string->blocksize + 1;
	p_string->w_str = malloc(sizeof(wchar_t) * p_string->size);

	if(!p_string->w_str) return(STRING_ERR);

	memcpy(p_string->w_str, p_text, p_string->length * sizeof(wchar_t));
	p_string->w_str[p_string->length] = '\0';

	return(STRING_OK);
}

int wstring_setf (WString *p_string, const wchar_t * const p_format, ...)
{
	va_list args;

	if(p_string->w_str) wstring_clear(p_string);

	va_start(args, p_format);

		//FIXME: vsnprintf is not applicable to wchar_t*
//		p_string->length = 128; // vsnprintf(0, 0, p_format, args);

	va_end(args);

	va_start(args, p_format);

		p_string->size = p_string->length + p_string->blocksize + 1;

		p_string->w_str = malloc(sizeof(wchar_t) * p_string->size);

		if(!p_string->w_str)
		{
			va_end(args);
			return(STRING_ERR);
		}

		vswprintf(p_string->w_str, p_string->length, p_format, args);

	va_end(args);

	return(STRING_OK);
}

int wstring_setfva (WString *p_string, const wchar_t * const p_format, va_list va_args, const size_t length)
{
	if(p_string->w_str) wstring_clear(p_string);

	p_string->size = length + p_string->blocksize + 1;

	p_string->w_str = malloc(sizeof(wchar_t) * p_string->size);

	if(!p_string->w_str)
	{
		return(STRING_ERR);
	}

	vswprintf(p_string->w_str, length, p_format, va_args);

	return(STRING_OK);
}

int wstring_setc (WString *p_string, const wchar_t ch)
{
	if(p_string->w_str) wstring_clear(p_string);

	p_string->length = 1;
	p_string->size = p_string->length + p_string->blocksize + 1;
	p_string->w_str = malloc(sizeof(wchar_t) * p_string->size);

	if(!p_string->w_str) return(STRING_ERR);

	p_string->w_str[0] = ch;
	p_string->w_str[p_string->length] = '\0';

	return(STRING_OK);
}

int wstring_add (WString *p_string, const wchar_t * const p_text)
{
	size_t textlen, new_size;
	wchar_t * new_w_str;

	if(!p_string->w_str) return(wstring_set(p_string, p_text));

	textlen = wcslen(p_text);

	if(!textlen) return(STRING_ERR);

	if((p_string->length + textlen + 1) > p_string->size)
	{
		new_size = p_string->length + textlen + p_string->blocksize + 1;
		new_w_str = realloc(p_string->w_str, sizeof(wchar_t) * new_size);

		if(!new_w_str) return(STRING_ERR);

		p_string->w_str = new_w_str;
	}

	memcpy(&p_string->w_str[p_string->length], p_text, textlen * sizeof(wchar_t));

	p_string->length += textlen;
	p_string->size = new_size;

	p_string->w_str[p_string->length] = '\0';

	return(STRING_OK);
}

int wstring_addn (WString *p_string, const wchar_t * const p_text, const size_t length)
{
	size_t	new_size;
	wchar_t	* new_w_str;

	if(!p_string->w_str) return(wstring_setn(p_string, p_text, length));

	if((p_string->length + length + 1) > p_string->size)
	{
		new_size = p_string->length + length + p_string->blocksize + 1;
		new_w_str = realloc(p_string->w_str, sizeof(wchar_t) * new_size);

		if(!new_w_str) return(STRING_ERR);

		p_string->w_str = new_w_str;
	}

	memcpy(&p_string->w_str[p_string->length], p_text, length * sizeof(wchar_t));

	p_string->length += length;
	p_string->size = new_size;

	p_string->w_str[p_string->length] = '\0';

	return(STRING_OK);
}

int wstring_addf (WString *p_string, const wchar_t * const p_format, ...)
{
	size_t length, new_size;
	wchar_t * new_w_str;

	va_list args;

	va_start(args, p_format);

		//FIXME: vsnprintf is not applicable to wchar_t*
//		length = vsnprintf(0, 0, p_format, args);

	va_end(args);

	va_start(args, p_format);

		if((p_string->length + length + 1) > p_string->size)
		{
			new_size = p_string->length + length + p_string->blocksize + 1;
			new_w_str = realloc(p_string->w_str, sizeof(wchar_t) * new_size);

			if(!new_w_str)
			{
				va_end(args);
				return(STRING_ERR);
			}

			p_string->w_str = new_w_str;
		}

		vswprintf(&p_string->w_str[p_string->length], length, p_format, args);

		p_string->length += length;
		p_string->size = new_size;

	va_end(args);

	return(STRING_OK);
}

int wstring_addfva (WString *p_string, const wchar_t * const p_format, va_list va_args, const size_t length)
{
	size_t new_size;
	wchar_t * new_w_str;

	if((p_string->length + length + 1) > p_string->size)
	{
		new_size = p_string->length + length + p_string->blocksize + 1;
		new_w_str = realloc(p_string->w_str, sizeof(wchar_t) * new_size);

		if(!new_w_str)
		{
			return(STRING_ERR);
		}

		p_string->w_str = new_w_str;
	}

	vswprintf(&p_string->w_str[p_string->length], length, p_format, va_args);

	p_string->length += length;
	p_string->size = new_size;

	return(STRING_OK);
}

int wstring_addc (WString *p_string, const wchar_t ch)
{
	size_t new_size;
	wchar_t * new_w_str;

	if(!p_string->w_str) return(wstring_setc(p_string, ch));

	if((p_string->length + 1 + 1) > p_string->size)
	{
		new_size = p_string->length + 1 + p_string->blocksize + 1;
		new_w_str = realloc(p_string->w_str, sizeof(wchar_t) * new_size);

		if(!new_w_str) return(STRING_ERR);

		p_string->w_str = new_w_str;
	}

	p_string->w_str[p_string->length] = ch;
	p_string->length++;
	p_string->w_str[p_string->length] = '\0';
	p_string->size = new_size;

	return(STRING_OK);
}

int wstring_delc (WString *p_string)
{
	wchar_t * new_wstr;

	if(!p_string->length) return(STRING_ERR);

	p_string->length--;
	p_string->w_str[p_string->length] = '\0';

	if(p_string->length + p_string->blocksize < p_string->size)
	{
		new_wstr = realloc(p_string->w_str, p_string->length);
		if(!new_wstr) return(STRING_OK);

		p_string->w_str = new_wstr;
		p_string->size = p_string->length + 1;
	}

	return(STRING_OK);
}

int wstring_insert(WString *p_string, const size_t p_pos, const wchar_t * const p_text)
{
	WString new_string = {0, .blocksize = p_string->blocksize};

	wstring_setn(&new_string, p_string->w_str, p_pos);

	wstring_add(&new_string, p_text);

	wstring_add(&new_string, &p_string->w_str[p_pos]);

	wstring_clear(p_string);

	*p_string = new_string;

	return(STRING_OK);
}

int wstring_insertn (WString *p_string, const size_t p_pos, const wchar_t * const p_text, const size_t length)
{
	WString new_string = {0, .blocksize = p_string->blocksize};

	wstring_setn(&new_string, p_string->w_str, p_pos);

	wstring_addn(&new_string, p_text, length);

	wstring_add(&new_string, &p_string->w_str[p_pos]);

	wstring_clear(p_string);

	*p_string = new_string;

	return(STRING_OK);
}

int wstring_insertf (WString * p_string, const size_t p_pos, const wchar_t * const p_format, ...)
{
	size_t length;
	wchar_t * buffer;
	int status;

	va_list args;

	va_start(args, p_format);

		//FIXME: vsnprintf is not applicable to wchar_t*
//		length = vsnprintf(0, 0, p_format, args);

	va_end(args);

	va_start(args, p_format);

		buffer = malloc(sizeof(wchar_t) * length);
		if(!buffer)
		{
			va_end(args);
			return(STRING_ERR);
		}

		vswprintf(buffer, length, p_format, args);

		status = wstring_insert(p_string, p_pos, buffer);

		free(buffer);

	va_end(args);

	return(status);
}

int wstring_insertfva (WString * p_string, const size_t p_pos, const wchar_t * const p_format, va_list va_args, const size_t length)
{
	wchar_t * buffer;
	int status;

	buffer = malloc(sizeof(wchar_t) * length);
	if(!buffer) return(STRING_ERR);

	vswprintf(buffer, length, p_format, va_args);

	status = wstring_insert(p_string, p_pos, buffer);

	free(buffer);

	return(status);
}

int wstring_insertc (WString * p_string, const size_t p_pos, const wchar_t ch)
{
	WString new_string = {0, .blocksize = p_string->blocksize};

	if(p_pos > p_string->length) return(STRING_ERR);

	if(p_pos)
	{
		wstring_setn(&new_string, p_string->w_str, p_pos);
	}

	wstring_addc(&new_string, ch);

	if(p_pos || p_string->length)
	{
		wstring_add(&new_string, &p_string->w_str[p_pos]);
	}

	wstring_clear(p_string);

	*p_string = new_string;

	return(STRING_OK);
}

int wstring_remove (WString * p_string, const size_t p_pos, const size_t length)
{
	WString new_string = {0, .blocksize = p_string->blocksize};

	if((p_pos + length) > p_string->length) return(STRING_ERR);

	wstring_setn(&new_string, p_string->w_str, p_pos);

	wstring_add(&new_string, &p_string->w_str[p_pos + length]);

	wstring_clear(p_string);

	*p_string = new_string;

	return(STRING_OK);
}

int wstring_replace (WString * p_string, const wchar_t * const p_old, const wchar_t * const p_new)
{
	wchar_t *strpos, *old_strpos;

	WString new_string = {0, .blocksize = p_string->blocksize};

	for(old_strpos = p_string->w_str; (strpos = wcsstr(old_strpos, p_old)); old_strpos = strpos + wcslen(p_old))
	{
		wstring_addn(&new_string, old_strpos, strpos - old_strpos);
		wstring_add(&new_string, p_new);
	}

	if((old_strpos - p_string->w_str) < p_string->length)
	{
		wstring_add(&new_string, old_strpos);
	}

	wstring_clear(p_string);

	*p_string = new_string;

	return(STRING_OK);
}

int wstring_replacec(WString *p_string, const wchar_t p_old, const wchar_t p_new)
{
	size_t i;

	for(i = 0; i < p_string->length; i++)
	{
		if(p_string->w_str[i] == p_old)
		{
			p_string->w_str[i] = p_new;
		}
	}

	return(STRING_OK);
}

int wstring_compare (WString * p_string1, WString * p_string2)
{
	if(p_string1->length != p_string2->length) return(0);

	return(!(wcsncmp(p_string1->w_str, p_string2->w_str, p_string1->length)));
}

int wstring_getline (WString * p_string, FILE * p_stream)
{
	wint_t ch;

	if(p_string->w_str) wstring_clear(p_string);

	for(ch = fgetwc(p_stream); ch != '\n' && ch != WEOF; ch = fgetwc(p_stream))
	{
		wstring_addc(p_string, ch);
	}

	return(STRING_OK);
}

/*
int wstring_readfile (WString *p_string, const char *p_filename)
{
	FILE *file;
	long size;

	if(p_string->w_str) wstring_clear(p_string);

	file = fopen(p_filename, "rt");
	if(!file) return(STRING_ERR);

	size = filesize(file);

	p_string->w_str = malloc(sizeof(wchar_t) * size + 1);
	if(!p_string->w_str)
	{
		fclose(file);
		return(STRING_ERR);
	}

	p_string->size = size + 1;
	p_string->length = size;

	fread(p_string->w_str, size, 1, file);

	p_string->c_str[p_string->length] = '\0';

	fclose(file);

	return(STRING_OK);
}*/

void wstring_clear (WString * p_string)
{
	if(p_string->w_str)
	{
		memset(p_string->w_str, 0, p_string->length);
		free(p_string->w_str);
		p_string->w_str = 0;
	}

	p_string->length = p_string->size = 0;
}

int wstring_tolower(WString *p_string)
{
	wchar_t *cptr;

	if(!p_string->w_str) return(STRING_ERR);

	for(cptr = p_string->w_str; *cptr; cptr++)
	{
		*cptr = towlower(*cptr);
	}

	return(STRING_OK);
}

int wstring_toupper(WString *p_string)
{
	wchar_t *cptr;

	if(!p_string->w_str) return(STRING_ERR);

	for(cptr = p_string->w_str; *cptr; cptr++)
	{
		*cptr = towupper(*cptr);
	}

	return(STRING_OK);
}

int wstring_levenshtein(WString *p_string1, WString *p_string2)
{
	int n, m;

	// Step 1

	n = p_string1->length;
	m = p_string2->length;

	if(n == 0) return(m);
	if(m == 0) return(n);

	int d[n+1][m+1];

	// Step 2

	int i, j;

	for(i = 0; i <= n; i++)
	{
		d[i][0] = i;
	}

	for(j = 0; j <= m; j++)
	{
		d[0][j] = j;
	}

	// Step 3

	wchar_t s1_i, s2_j;
	int cost;

	for(i = 1; i <= n; i++)
	{
		s1_i = p_string1->w_str[i - 1];

		// Step 4

		for(j = 1; j <= m; j++)
		{
			s2_j = p_string2->w_str[j - 1];

			// Step 5

			if(s1_i == s2_j)
			{
				cost = 0;
			}
			else cost = 1;

			// Step 6

			d[i][j] = min(d[i-1][j]+1, d[i][j-1]+1, d[i-1][j-1]+cost);
		}
	}

	return(d[n][m]);
}

int wstring_tostring(String *p_string, WString *p_wstring)
{
	if(p_string->c_str) string_clear(p_string);

	p_string->length = p_wstring->length;
	p_string->size = p_string->length + p_string->blocksize + 1;
	p_string->c_str = malloc(sizeof(char) * p_string->size);
	if(!p_string->c_str) return(STRING_ERR);

	wcstombs(p_string->c_str, p_wstring->w_str, p_string->length);

	p_string->c_str[p_string->length] = '\0';

	return(STRING_OK);
}

int wstring_frommb(WString *p_string, const char * const p_text)
{
	if(p_string->w_str) wstring_clear(p_string);

	p_string->length = strlen(p_text);
	p_string->size = p_string->length + p_string->blocksize + 1;
	p_string->w_str = malloc(sizeof(wchar_t) * p_string->size);
	if(!p_string->w_str) return(STRING_ERR);

	mbstowcs(p_string->w_str, p_text, p_string->length);

	p_string->w_str[p_string->length] = L'\0';

	return(STRING_OK);
}

int cstr_levenshtein(const char * const p_cstr1, const char * const p_cstr2)
{
	int n, m;

	// Step 1

	n = strlen(p_cstr1);
	m = strlen(p_cstr2);

	if(n == 0) return(m);
	if(m == 0) return(n);

	int d[n+1][m+1];

	// Step 2

	int i, j;

	for(i = 0; i <= n; i++)
	{
		d[i][0] = i;
	}

	for(j = 0; j <= m; j++)
	{
		d[0][j] = j;
	}

	// Step 3

	char s1_i, s2_j;
	int cost;

	for(i = 1; i <= n; i++)
	{
		s1_i = p_cstr1[i - 1];

		// Step 4

		for(j = 1; j <= m; j++)
		{
			s2_j = p_cstr2[j - 1];

			// Step 5

			if(s1_i == s2_j)
			{
				cost = 0;
			}
			else cost = 1;

			// Step 6

			d[i][j] = min(d[i-1][j]+1, d[i][j-1]+1, d[i-1][j-1]+cost);
		}
	}

	return(d[n][m]);
}

int wstr_levenshtein(const wchar_t * const p_wstr1, const wchar_t * const p_wstr2)
{
	int n, m;

	// Step 1

	n = wcslen(p_wstr1);
	m = wcslen(p_wstr2);

	if(n == 0) return(m);
	if(m == 0) return(n);

	int d[n+1][m+1];

	// Step 2

	int i, j;

	for(i = 0; i <= n; i++)
	{
		d[i][0] = i;
	}

	for(j = 0; j <= m; j++)
	{
		d[0][j] = j;
	}

	// Step 3

	char s1_i, s2_j;
	int cost;

	for(i = 1; i <= n; i++)
	{
		s1_i = p_wstr1[i - 1];

		// Step 4

		for(j = 1; j <= m; j++)
		{
			s2_j = p_wstr2[j - 1];

			// Step 5

			if(s1_i == s2_j)
			{
				cost = 0;
			}
			else cost = 1;

			// Step 6

			d[i][j] = min(d[i-1][j]+1, d[i][j-1]+1, d[i-1][j-1]+cost);
		}
	}

	return(d[n][m]);
}

#endif /* DSTRING_H */