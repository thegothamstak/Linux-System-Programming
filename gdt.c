/*
	Implementation of segment descriptor and GDT.

	Author : Shripad
	Date : 9th May 2018
*/

#include<stdio.h>

#define LENGTH 5

//	Structure for single segment
struct segment_field{
	/*32 bit low word */
	unsigned int base_address_00_15/*16*/;		//Base Address
	unsigned int segment_limit_00_15/*16*/;		//Segment Limit
	/*32 bit high word */
	unsigned int base_address_16_23/*8*/;		//Base
	unsigned int base_address_24_31/*8*/;		//Base
	unsigned int segment_limit/*4*/;			//Segment Limit
	unsigned int segment_dpl/*2*/;				//Descriptor Privilege Level 
	unsigned int segment_present/*1*/;			//Segment Present
	unsigned int segment_descriptor_type/*1*/;	//Segment Descriptor Type (0 = System, 1 = Code or Data)
	unsigned int segment_granularity/*1*/;		//Granularit
	unsigned int segment_db/*1*/;				//Default Operation Size (0 = 16 bit segment, 1 = 32 bit segment)
	unsigned int segment_avl/*1*/;				//Available System Software
	unsigned int segment_l/*1*/;				//64 bit coe segment
	unsigned int segment_type/*4*/;				//Segment Type
}gdt[LENGTH];	//Array of struct segment_field (GDT Implementation)

//  Function for adding description of segment to GDT  
void addToSegment(struct segment_field gdt[]){     
	for(int i = 0; i < LENGTH; ++i){
		gdt[i].base_address_00_15 = (i == 0) ? 0 : gdt[i - 1].segment_limit_00_15 + gdt[i - 1].base_address_00_15;
		gdt[i].segment_limit_00_15 = (i == 0) ? 2 : i + 2;
		gdt[i].base_address_16_23 = 0;
		gdt[i].base_address_24_31 = 0;
		gdt[i].segment_limit = 0;
		gdt[i].segment_dpl = (i < 3) ? 1 : 0;
		gdt[i].segment_present = (i < 3) ? 1 : 0;
		gdt[i].segment_descriptor_type = (i < 3) ? 1 : 0;
		gdt[i].segment_granularity = (i < 3) ? 1 : 0;
		gdt[i].segment_db = (i < 3) ? 1 : 0;
		gdt[i].segment_avl = (i < 3) ? 1 : 0;
		gdt[i].segment_l = (i < 3) ? 1 : 0;
		gdt[i].segment_type = (i < 3) ? 1 : 0;;
	}
}

//	Function to print segment description from GDT
void printSegment(struct segment_field gdt[]){
	for(int i = 0; i < LENGTH; ++i){
		printf("Base Address : %d%d%d\n",gdt[i].base_address_16_23,gdt[i].base_address_24_31,gdt[i].base_address_00_15); 
		printf("Segment Limit : %d%d\n",gdt[i].segment_limit,gdt[i].segment_limit_00_15); 
		//printf("Base 16 - 23 : %d\n",gdt[i].base_address_16_23);
		//printf("Base 24 - 31 : %d\n",gdt[i].base_address_24_31); 
		//printf("Segment Limit : %d\n",gdt[i].segment_limit);
		printf("Segment dpl : %d\n",gdt[i].segment_dpl);
		printf("Segment Present : %d\n",gdt[i].segment_present); 
		printf("Segment Descriptor Type : %d\n",gdt[i].segment_descriptor_type); 
		printf("Segment Granularity : %d\n",gdt[i].segment_granularity); 
		printf("Segment db : %d\n",gdt[i].segment_db); 
		printf("Segment Available : %d\n",gdt[i].segment_avl); 
		printf("Segment l : %d\n",gdt[i].segment_l); 
		printf("Segment Type : %d\n",gdt[i].segment_type);
		printf("\n\n"); 
	}	
}

//	Main function
int main(){
	
	//Passing the gdt array of structure segment_field to the functions
	addToSegment(gdt);
	printSegment(gdt);

	return 0;
}