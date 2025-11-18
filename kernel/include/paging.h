#ifndef PAGING_H
#define PAGING_H 1
#include <stdint.h>

struct page_directory_entry{
	// 31-12 address
	// 11-8 AVL
	// 7 PS(0)
	// 6 AVL
	// 5 A
	// 4 PCD
	// 3 PWT
	// 2 U/S
	// 1 R/W
	// 0 P
	uint32_t address : 24;
	uint32_t AVL:4;
	uint32_t PS:1; //equals 0
	uint32_t AVL_bit:1;
	uint32_t Accessed:1;
	uint32_t PCD:1;
	uint32_t PWT:1;
	uint32_t US:1;
	uint32_t RW:1;
	uint32_t Present:1; // equals 1
}__attribute((packed));

struct page_directory_entry_4MB{
	// 31-22 address 31-22
	// 21 reserved (0)
	// 20-13 bits 39-32 address
	// 12 PAT
	// 11-9 AVL
	// 8 G
	// 7 PS(1)
	// 6 D
	// 5 A
	// 4 PCD
	// 3 PWT
	// 2 U/S
	// 1 R/W
	// 0 P
	uint32_t address_low : 10;
	uint32_t reserved:1; //0
	uint32_t address_high:8;
	uint32_t PAT:1;
	uint32_t AVL:3;
	uint32_t Global:1;
	uint32_t PS:1; //equals 1
	uint32_t Dirty:1;
	uint32_t Accessed:1;
	uint32_t PCD:1;
	uint32_t PWT:1;
	uint32_t US:1;
	uint32_t RW:1;
	uint32_t Present:1; // equals 1
}__attribute((packed));

struct page_table_entry{
	// 31-12 address
	// 11-9 AVL
	// 8 Global
	// 7 PAT
	// 6 Dirty
	// 5 Accessed
	// 4 PCD
	// 3 PWT
	// 2 U/S
	// 1 R/W
	// 0 Present
	uint32_t address : 24;
	uint32_t AVL:3;
	uint32_t Global:1;
	uint32_t PAT:1;
	uint32_t Dirty:1;
	uint32_t Accessed:1;
	uint32_t PCD:1;
	uint32_t PWT:1;
	uint32_t US:1;
	uint32_t RW:1;
	uint32_t Present:1; // equals 1
}__attribute((packed));

struct page_table_entry new_page_table_entry(uint32_t address,uint8_t AVL, uint8_t flags);
void initPaging();

#endif
