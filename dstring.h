#ifndef DSTRING_H
#define DSTRING_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#define STRING_NULL (String){0}
#define STRING_OK 0
#define STRING_ERR -1

typedef struct
{
	char	*c_str;
	size_t	length,
		blocksize,
		size;
} String;

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
void string_clear(String *p_string);

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

#endif /* DSTRING_H */