#ifndef MEM_H
#define MEM_H

struct physical_memory_table_entry{
	uint64_t base;
	uint64_t length;
	uint32_t region;
	uint32_t ACPI;
}__attribute__((packed));

struct physical_memory_table_ptr{
	uint32_t count;
	struct physical_memory_table_entry pmt_entry[];
}__attribute__((packed));

#endif
