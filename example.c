#include "dstring.h"

#define string_print(p_string) puts(((String*)p_string)->c_str)

int main()
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

	string_replace(&myLocalString, "world", "humans");

	string_print(&myLocalString);

	/* When we are done working with a string, we need to clear it.
	 * This frees up the memory occupied by the string.
	 * We can clear a string at any time, even if we didn't use it.
	 */

	string_clear(&myLocalString);

	return(0);
}