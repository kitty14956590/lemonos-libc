#include <runtime.h>
#include <locale.h>
#include <stdlib.h>
#include <cpufeats.h>

int __is_lemonos = 1;

// now we must initialise the runtime
void __runtime_entry() {
	__is_lemonos = syscall(222) != -1;
	__locale_init();
	__cpufeats_init();
	main();
}
