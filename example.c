/* This serves as a simple example on how to use the
 * dynamic strings provided by dstring.h
 */

#include "dstring.h"
#include <locale.h>

/* Prints a string to the console by calling puts
 * on the actual cstring contained within a string object.
 */

void example_wstring()
{
	setlocale(LC_CTYPE, "en_US.UTF-8");

	WString myLocalString = WSTRING_NULL;


	wstring_set(&myLocalString, L"Hello World²");
	wstring_print(&myLocalString);


	wstring_add(&myLocalString, L" Goodbye cruel world!");
	wstring_print(&myLocalString);


	wstring_addc(&myLocalString, L'X');
	wstring_print(&myLocalString);

	wstring_clear(&myLocalString);
}

void lev()
{
	WString str1 = WSTRING_NULL;
	WString str2 = WSTRING_NULL;

	wstring_set(&str1, L"Helö");
	wstring_set(&str2, L"Hello");

	printf("%d\n", wstring_levenshtein(&str1, &str2));

	wstring_clear(&str1);
	wstring_clear(&str2);
}

void example_string()
{
	/* When creating a new object of type String we do always need
	 * to initialize it with zero.
	 * You do need to do this for both heap- and stack-allocated strings!
	 */
	String myLocalString = STRING_NULL;

	/* Let's add a simple Hello World message to our dynamic string and
	 * print it to the console.
	 */

	string_set(&myLocalString, "Hello World!");

	string_print(&myLocalString);

	/* We can now continue working on the string by dynamically adding
	 * more text to it.
	 */

	string_add(&myLocalString, " Goodbye cruel world!");

	string_print(&myLocalString);

	/* We may even use printf-like formatting when adding text to a
	 * string.
	 */

	string_addf(&myLocalString, " Dynamic %s are awesome!", "strings");

	string_print(&myLocalString);

	/* Maybe we do not like some phrases contained within a string.
	 * That's not a problem, since we can simply replace them.
	 * NOTE: The following function will only replace the first instance
	 * of a word, if found. To replace e.g. all phrases of a string
	 * you need to call it multiple times (until STRING_ERR is returned).
	 */

	string_replace(&myLocalString, "world", "errors");

	string_print(&myLocalString);

	/* If we forgot to add something, we can simply insert snippets of
	 * text afterwards by using the insert function.
	 */

	size_t position = strstr(myLocalString.c_str, "errors") - myLocalString.c_str;

	string_insert(&myLocalString, position, "runtime ");

	string_print(&myLocalString);

	/* When we are done working with a string, we need to clear it.
	 * This frees up the memory occupied by the string.
	 * We can clear a string at any time, even if we didn't use it.
	 */

	string_clear(&myLocalString);
}

int main()
{
	/* showcase standard string functions */
	example_string();

	/* showcase wide-string functions */
	example_wstring();

	return(0);
}