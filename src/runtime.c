#include <runtime.h>
#include <locale.h>
#include <stdlib.h>
#include <cpufeats.h>

int __is_lemonos = 1;

// now we must initialise the runtime
void __runtime_entry() {
	__is_lemonos = syscall(222) >= 0; // on any other OS 222 is undefined syscall and will return -1, on LemonOS this is getlocale() (i think?)
	__locale_init();
	__cpufeats_init();
	main();
}
