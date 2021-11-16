#include "environment.h"

bool is_subset(char c, char *subset)
{
	while (*subset)
	{
		if (c == *subset)
			return (true);
		subset++;
	}
	return (false);
}

bool valid_identifier(char *name)
{
	const char c = name[0];
	// https://user-web.icecube.wisc.edu/~dglo/c_class/charfunc.html#:~:text=In%20ASCII%2C%20whitespace%20characters%20are,formfeed%20(%20'%5Cf'%20).
	const char *whitespace = " \t\r\n\v\f";
	// https://www.oreilly.com/library/view/learning-the-bash/1565923472/ch01s09.html
	const char *spcial = "~`#$&*()\\|[]{};,<>/?!";

	if (!(c >= 'a' && c <= 'z') || !(c >= 'A' && c <= 'Z') || c != '_')
		return (false);
	name++;
	while (name)
	{
		if (!(c >= 'a' && c <= 'z') || !(c >= 'A' && c <= 'Z') || c != '_' || (c >= '0' && c <= '9'))
			return (false);
	}
	return (true);
}
