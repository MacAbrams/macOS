#include <paging.h>
#include <stdio.h>

struct page_directory_entry* page_dir = (struct page_directory_entry*)0x9000;
struct page_table_entry* page_table_table = (struct page_table_entry*)0xA000;


/*flags:
	 * PS
	 * NONE
	 * Accessed
	 * PCD
	 * PWT
	 * US
	 * RW
	 * Present
	*/
	/*
	 * AVL
	 * 3 zero
	 * 4 avl high
	 * 1 avl bit
	 */
struct page_directory_entry new_page_directory_entry(uint32_t address,uint8_t AVL, uint8_t flags){
	
	struct page_directory_entry a;
	a.address = (address >> 8) & 0xffffff;
	a.AVL = (AVL >> 1) & 0xf;
	a.PS = (flags>>7) & 0x1;
	a.AVL_bit= AVL & 0x1;
	a.Accessed= (flags>>5) & 0x1;
	a.PCD= (flags>>4) & 0x1;
	a.PWT= (flags>>3) & 0x1;
	a.US= (flags>>2) & 0x1;
	a.RW= (flags>>1) & 0x1;
	a.Present= flags & 0x1;
	return a;
}

struct page_table_entry new_page_table_entry(uint32_t address,uint8_t AVL, uint8_t flags){
	
	struct page_table_entry a;
	a.address = (address >> 8) & 0xffffff;
	a.AVL = AVL & 0x7;
	a.Global = (flags>>7) & 0x1;
	a.Dirty = 0;
	a.Accessed= (flags>>5) & 0x1;
	a.PCD= (flags>>4) & 0x1;
	a.PWT= (flags>>3) & 0x1;
	a.US= (flags>>2) & 0x1;
	a.RW= (flags>>1) & 0x1;
	a.Present= flags & 0x1;
	return a;
}
void initPaging(){
	//0x83 PS=1 RW=1 Present=1
	page_dir[0] = new_page_directory_entry(0,0,0x83);
	page_dir[1] = new_page_directory_entry((uint32_t)page_table_table,0,0x03);
	printf("%llx\n",sizeof(struct new_page_directory_entry));
	for(int i = 2; i<1024; ++i){
	//	page_dir[i]=new_page_directory_entry(0,0,0);	
	}
}
