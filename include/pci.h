#pragma once

#include <stdint.h>

// giant struct representing a pci device
typedef struct {
	uint16_t vendor;
	uint16_t device;
	uint8_t function;
	uint8_t slot;
	uint8_t bus;
	uint8_t revision;
	uint8_t class;
	uint8_t subclass;
	uint8_t irq_line;
	uint8_t irq_pin;
	uint8_t latency;
	uint8_t grant;
	uint8_t programming;
	uint32_t bar0;
	uint32_t bar1;
	uint32_t bar2;
	uint32_t bar3;
	uint32_t bar4;
	uint32_t bar5;
	uint32_t id;
} pci_t;

enum {
	PCI_CMD_IO       = 0b0000000000000001, // io space enable
	PCI_CMD_MEM      = 0b0000000000000010, // memory space enable
	PCI_CMD_MASTER   = 0b0000000000000100, // bus master enable
	PCI_CMD_CYCLE    = 0b0000000000001000, // special cycle enable
	PCI_CMD_WRITE    = 0b0000000000010000, // memory write enable
	PCI_CMD_SNOOPY   = 0b0000000000100000, // snoopy :3 (vga snoop enable)
	PCI_CMD_PARERROR = 0b0000000001000000, // parity error / disable
	PCI_CMD_SIGERROR = 0b0000000100000000, // signal error / enable
	PCI_CMD_FB2B     = 0b0000001000000000, // fast back to back / enable
	PCI_CMD_IRQ      = 0b0000010000000000, // irq enable / disable
};

void pci_config_set_addr(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset);
uint8_t pci_config_inb(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset);
uint16_t pci_config_inw(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset);
uint32_t pci_config_ind(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset);
uint32_t pci_config_outb(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset, uint8_t d);
uint32_t pci_config_outw(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset, uint16_t d);
uint32_t pci_config_outd(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset, uint32_t d);

