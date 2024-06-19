#include "malloc_cache.h"
#include "test.pb-c.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	MallocCache mcache;
	Foo__Person person = FOO__PERSON__INIT;
	//初始化,添加4个person
	person.n_phone = 4;
	person.phone = (Foo__Person__PhoneNumber**)mcache.malloc(sizeof(Foo__Person__PhoneNumber*) * person.n_phone);
	Foo__Person__PhoneNumber phone = FOO__PERSON__PHONE_NUMBER__INIT;
	for(int i = 0; i < person.n_phone; i++)
	{
		Foo__Person__PhoneNumber* p = (Foo__Person__PhoneNumber*)mcache.malloc(sizeof(Foo__Person__PhoneNumber));
		*p = phone;
		//把i转换成字符串
		p->number = (char*)mcache.malloc(10);
		sprintf(p->number, "%d", i);
		person.phone[i] = p;
	}
	person.n_phone = 2;
	//开始打包
	size_t size = foo__person__get_packed_size(&person);
	unsigned char* packed = (unsigned char*)mcache.malloc(size);
	size_t size2 = foo__person__pack(&person, packed);
	assert(size == size2);
	//解包
	Foo__Person* person2 = foo__person__unpack(NULL, size, packed);
	assert(person2 != NULL);
	assert(person2->n_phone == person.n_phone);
	for(int i = 0; i < person2->n_phone; i++)
	{
		assert(strcmp(person2->phone[i]->number, person.phone[i]->number) == 0);
	}

	//释放person2
	foo__person__free_unpacked(person2, NULL);

	return 0;
}