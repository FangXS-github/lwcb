#include "lwcb.h"

#include <stdio.h>
#include <string.h>

#define INT_BUFFER_CAPACITY 5
int int_buffer_array[INT_BUFFER_CAPACITY];

int main(void) 
{
    lwcb_t int_buffer;
    
    // 初始化缓冲区：指定元素大小和容量
    lwcb_init(&int_buffer, int_buffer_array, sizeof(int), INT_BUFFER_CAPACITY);
    
    // 写入数据
    for (int i = 0; i < INT_BUFFER_CAPACITY; i++) {
        int ret = lwcb_push(&int_buffer, &i);
        printf("write: %d, count: %u, ret=%d\n", i, lwcb_get_count(&int_buffer), ret);
    }
    
    // 读取数据
    while (!lwcb_is_empty(&int_buffer)) {
        int read_num = 0;
        int ret = lwcb_pop(&int_buffer, &read_num);
        printf("read: %d, count: %u, ret=%d\n", read_num, lwcb_get_count(&int_buffer), ret);
    }
    
    return 0;
}