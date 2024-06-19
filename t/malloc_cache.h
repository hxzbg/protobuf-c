#ifndef _MALLOC_LIST_H
#define _MALLOC_LIST_H

#include <cstdlib> // Add this line to include the <cstdlib> header

//辅助类，用于自动释放内存
class MallocCache
{
public:
	MallocCache()
	{
		head = 0;
	}

	~MallocCache()
	{
		MallocNode* node = head;
		while (node)
		{
			MallocNode* next = node->next;
			::free(node->data);
			delete node;
			node = next;
		}
	}

	void* malloc(size_t size)
	{
		MallocNode* node = new MallocNode;
		node->data = ::malloc(size);
		node->next = head;
		head = node;
		return node->data;
	}

protected:
	struct MallocNode
	{
		MallocNode* next;
		void* data;
	};
	struct MallocNode* head;
};

#endif