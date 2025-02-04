#include <unistd.h>
#include <runtime.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>

int cpu_get_temp() {
	if (!__is_lemonos) {
		return 0;
	}
	return syscall(SYSCALL_GETTHERM);
}

void * brk(uintptr_t _break) {
	return (void *) (uint32_t) syscall(45, _break); // CHANGE ME
}

void * malloc(uint32_t size) {
	if (!__is_lemonos) {
		void * p = brk(0);
		void * newbrk = brk(((uintptr_t) p) + size);
		if (newbrk == (void *) -1) {
			return NULL;
		}
		return p;
	}
	return (void *) (uint32_t) syscall(SYSCALL_MALLOC, size);
}

void exit(int code) {
	syscall(SYSCALL_EXIT, code);
}

void free(void * p) {
	if (p == NULL) {
		return;
	}
	syscall(SYSCALL_FREE, p);
}

int syscall(const int number, ...) {
	va_list listp;
	va_list * argv;
	va_start(listp, number);
	argv = &listp;
	uint32_t ret = 0;
	uint32_t ebx = (uint32_t) va_arg(*argv, uint32_t);
	uint32_t ecx = (uint32_t) va_arg(*argv, uint32_t);
	uint32_t edx = (uint32_t) va_arg(*argv, uint32_t);
	uint32_t esi = (uint32_t) va_arg(*argv, uint32_t);
	uint32_t edi = (uint32_t) va_arg(*argv, uint32_t);
	uint32_t ebp = (uint32_t) va_arg(*argv, uint32_t);
	asm volatile ("int $0x80" : "=a" (ret) : "a" (number), "b" (ebx), "c" (ecx), "d" (edx), "S" (esi), "D" (edi));
	return ret;
}
