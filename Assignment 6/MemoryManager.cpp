#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "MemoryManager.h"

#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

struct Node* head;

struct Node* usedHead;

struct Node {
	unsigned short* address;
	unsigned short size;
	struct Node * next;
	struct Node * previous;
};



namespace MemoryManager {

	// IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT
	//
	// This is the only static memory that you may use, no other global variables
	// may be created, if you need to save data make it fit in MM_pool
	//
	// IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT

	const int MM_POOL_SIZE = 65536;
	char MM_pool[MM_POOL_SIZE];

	// I have provided this tool for your use
	void memView(int start, int end)
	{
		const unsigned int SHIFT = 8;
		const unsigned int MASK = 1 << SHIFT - 1;

		unsigned int value;	// used to facilitate bit shifting and masking

		cout << "         Pool                     Unsignd  Unsigned " << endl;
		cout << "Mem Add  indx   bits   chr ASCII#  short      int    " << endl;
		cout << "-------- ---- -------- --- ------ ------- ------------" << endl;

		for (int i = start; i <= end; i++)
		{
			cout << (long*)(MM_pool + i) << ':';	// the actual address in hexadecimal
			cout << '[' << setw(2) << i << ']';		// the index into MM_pool

			value = MM_pool[i];
			cout << " ";
			for (int j = 1; j <= SHIFT; j++)	// the bit sequence for this byte (8 bits)
			{
				cout << ((value & MASK) ? '1' : '0');
				value <<= 1;
			}
			cout << " ";

			cout << '|' << *(char*)(MM_pool + i) << "| (";	// the ASCII character of the 8 bits (1 byte)
			cout << setw(4) << ((int)(*((unsigned char*)(MM_pool + i)))) << ")";// the ASCII number of the character

			cout << " (" << setw(5) << (*(unsigned short*)(MM_pool + i)) << ")";// the unsigned short value of 16 bits (2 bytes)
			cout << " (" << setw(10) << (*(unsigned int*)(MM_pool + i)) << ")";	// the unsigned int value of 32 bits (4 bytes)

			cout << endl;
		}
	}

	// Initialize set up any data needed to manage the memory pool
	void initializeMemoryManager(void) {
	
		
		*(unsigned short*)MM_pool = (unsigned short)6;//tracker of next free address, since first available address is always at 6
		*(unsigned short*)(MM_pool + 1) = 0;
		*(unsigned short*)(MM_pool + 2) = 0;
		*(unsigned short*)MM_pool = (unsigned short)65535; //last index of the 64k memory pool
	}

	// Return a pointer inside the memory pool
	// If no chunk can accommodate aSize call onOutOfMemory() 
	void* allocate(int aSize) {
		static bool flag = true;
		

		//used for entering allocate method for the first time only
		if (flag) {
			
			/*
			unsigned short nextMem = *(unsigned short*)& MM_pool[0];
			*(unsigned short*)& MM_pool[0] += aSize;
			flag = false;
			return (void*)& MM_pool[nextMem];
			*/
			

			*(unsigned short*)& MM_pool[0] = 6;
			unsigned short nam;
			nam = *(unsigned short*)& MM_pool[0];
			*(unsigned short*)& MM_pool[0] = nam + aSize;
			flag = false;

			//constructing the first node of the linked list
			Node* newNode = new (struct Node);
			newNode->next = NULL;
			newNode->previous = NULL;
			head = newNode;
			head->size = aSize;
			head->address = 0;
			return (void*)&MM_pool[nam];
		}

		if(aSize< freeMemory()) {
			*(unsigned short*)(MM_pool + *(unsigned short*)MM_pool) = (unsigned short)aSize;
			*(unsigned short*)(MM_pool) = (unsigned short)(*(unsigned short*)MM_pool + aSize + 6);

			//add the first node to beginning of linked list, since linked list is entirely empty...
			struct Node* newNode = new (struct Node);
			newNode->previous = NULL;
			newNode->next = head;
			head->previous = newNode;
			head = newNode;
			head->size = aSize;
			head->address = (unsigned short*)(MM_pool + *(unsigned short*)MM_pool - aSize - 6);


			//return the address of next available slot for allocation
			return (void*)( MM_pool + *(unsigned short*) MM_pool - aSize);
		}
		else {
			onOutOfMemory();
			return 0;
		}


	}

	// Free up a chunk previously allocated memory
	void deallocate(void* aPointer){
		static bool flag = true;
		//if there isn't any memory left, then nothing can be deallocated
		if (freeMemory() == 0) {
			cout << "There is nothing to deallocate here..." << endl;
			onOutOfMemory();
		}
		else {
			
			unsigned short stoppingLimit = (char*)aPointer - (char*)MM_pool - 6;
			unsigned short dalimit = (unsigned short) size(aPointer); //find the size of the variable to know how much memory must be deallocated
			//dealloation process occurs here
			for (unsigned short i = 0; i < dalimit + 6; i++) {
				MM_pool[(stoppingLimit) + i] = NULL; //making every slot in the MM_pool equal to null
			}

			//deal with linked lists now with removing the node at a specified location
			//including at teh beginning of the linked list, the end and anywhere not in the beginning or the end
			//DO LATER PLEASE THANK YOU SO MUCH
			struct Node* startingPoint = head;

			//remove the node with that address from the inUse list
			while (startingPoint != NULL) {
				if (startingPoint->address == (unsigned short*)(MM_pool + stoppingLimit)) {
					cout << "SWEET " << startingPoint->address << "  " << (unsigned short*)(MM_pool + stoppingLimit) <<endl;
					startingPoint->previous->next = startingPoint->next;
					startingPoint->next->previous = startingPoint->previous;
					break;
				}
				startingPoint = startingPoint->next;
			}
			//adds a node to the used list for the very first time only,
			if (flag) {
				flag = false;
				struct Node* newUsedNode = new (struct Node);
				newUsedNode->next = NULL;
				newUsedNode->previous = NULL;
				usedHead = newUsedNode;
				usedHead->size = dalimit;
				usedHead->address = (unsigned short*)(MM_pool + stoppingLimit);

			}
			//add that removed node to the Used list, assuming this list isn't empty
			else {
				struct Node* newNode = new (struct Node);
				newNode->previous = NULL;
				newNode->next = usedHead;
				usedHead->previous = newNode;
				usedHead = newNode;
				usedHead->size = dalimit;
				usedHead->address = (unsigned short*)(MM_pool + stoppingLimit);

				//usedHead->address = (unsigned short*)(MM_pool + *(unsigned short*)MM_pool - 1);

			}
		}
	}

	// Scans the memory pool and return the total free space remaining in bytes
	int freeMemory(void) {
		return MM_POOL_SIZE - inUseMemory();
	}


	// Scan the memory pool and return the total deallocated memory in bytes
	int usedMemory(void) {
		int usedMemTracker = 0;
		
		struct Node* startingForUsed = usedHead;

		while (startingForUsed != NULL) {
			usedMemTracker += (startingForUsed->size);

			usedMemTracker += 6; //also accumulate 6 bytes since every allocated moment requires 6 bytes, 2 bytes for size amt, 2 bytes for next counter, 2 bytes for previous counter
			startingForUsed = startingForUsed->next;
		}
		return usedMemTracker;
	}


	// Scan the memory pool and return the total in use memory
	int inUseMemory(void) {
		unsigned short useMemTracker = 0; //tracks the total in use memory in the pool

		struct Node* startingPoint = head;

		while (startingPoint != NULL) {
			useMemTracker += (startingPoint->size);
			
			useMemTracker += 6; //also accumulate 6 bytes since every allocated moment requires 6 bytes, 2 bytes for size amt, 2 bytes for next counter, 2 bytes for previous counter
			startingPoint = startingPoint->next;
		}
	
		return useMemTracker;
	}



	// Return the size (in bytes) associated with this memory address
	int size(void * aPointer){
		//retrieves the type of pointer/variable

		unsigned short stoppingLimit = (char*)aPointer - (char*)MM_pool - 6;
		int byteAmount = *(char*)(MM_pool + stoppingLimit); //retain the ASCII form which contains the amount of bytes the variable has accumulated excluding the 6 additional bytes
		
		//if the byte amount received is larger than the size of a student, then this indicates the void pointer was previously a char pointer
		if (byteAmount > 64) {
			byteAmount = 1;
		}
		return byteAmount;		
	}

	// This is called when no more memory is available to allocate
	void onOutOfMemory(void){
		std::cerr << "/nMemory pool out of memory" << std::endl;
		cin.get();
		exit(1);
	}

}

