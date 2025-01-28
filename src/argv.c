#include <stddef.h>
#include <stdio.h>
#include <string.h>

int args_contains(char * argv[], char * needle) {
	int i = 0;
	for (char * arg = argv[0]; arg != NULL; arg = argv[i++]) {
		if (strcmp(arg, needle) == 0) {
			return 1;
		}
	}
	return 0;
}

int args_contains_long(char * argv[], char * shortname, char * longname) {
	return args_contains(argv, shortname) || args_contains(argv, longname);
}
