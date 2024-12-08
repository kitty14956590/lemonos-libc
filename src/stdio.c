#include <string.h>
#include <stdlib.h>
#include <sys/syscall.h>

void puts(char * text) {
	syscall(SYSCALL_WRITE, 1, text, strlen(text));
}

void outb(uint16_t port, uint8_t val) {
	asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port) :"memory");
}

void outw(uint16_t port, uint16_t val) {
	asm volatile ("outw %0, %1" : : "a"(val), "Nd"(port) :"memory");
}

void outl(uint16_t port, long val) {
	asm volatile ("outl %0, %1" : : "a"(val), "Nd"(port) :"memory");
}

void outd(uint16_t port, uint32_t val) {
	asm volatile ("outl %0, %1" : : "a"(val), "Nd"(port) :"memory");
}

uint8_t inb(uint16_t port) {
	uint8_t ret;
	asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}

uint16_t inw(uint16_t port) {
	uint16_t ret;
	asm volatile ("inw %1, %0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}

long inl(uint16_t port) {
	long ret;
	asm volatile ("inl %1, %0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}

uint32_t ind(uint16_t port) {
	uint32_t ret;
	asm volatile ("inl %1, %0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}
