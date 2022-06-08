#include<stdio.h>
#include <stdlib.h>

void* aligned_malloc(size_t size, size_t alignment)
{
    if(alignment & (alignment - 1)) //检测alignment是否为2的整数次幂
    {
        return NULL;
    }
    else
    {
        void *p = malloc(sizeof(void*) + size + alignment);
        if(p)
        {
			void *pbuf = (void*)((size_t)p + sizeof(void*));
			void *ptr = (void*)(((size_t)pbuf | (alignment - 1)) + 1);

			//void *ptr2 = (void*)(((size_t)pbuf + alignment - 1) & -alignment);

			//把原始的分配内存的地址存储起来，以便free的时候调用把所有的内存都释放掉
			((void**)ptr)[-1] = p;
            return ptr;
        }
        else
        {
           return NULL;
        }
    }
}
 
void aligned_free(void *ptr)
{
    //free 会根据 malloc 分配的内存首地址，找到相关管理结构体，根据size等信息来释放 相关内存
    free(((void**)ptr)[-1]);
}

void main()
{
	void * data = aligned_malloc(100,128);
	printf("hello world!\n");
	getchar();
}
