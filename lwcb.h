#ifndef LIGHT_WEIGHT_CIRCULAR_BUFFER_H
#define LIGHT_WEIGHT_CIRCULAR_BUFFER_H

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    void*       buffer;        // 缓冲区数组
    uint32_t    element_size;  // 每个元素的大小 单位：字节
    uint32_t    capacity;      // 缓冲区容量（元素数量）
    uint32_t    head;          // 下一个写入位置
    uint32_t    tail;          // 下一个读取位置
    uint32_t    count;         // 当前元素数量
} lwcb_t;

/**
 * @brief 初始化循环缓冲区
 * @param cb 缓冲区控制结构体指针
 * @param buffer 用户提供的缓冲区数组
 * @param element_size 每个元素的大小（字节）
 * @param capacity 缓冲区容量（元素数量）
 * @return 成功返回0，失败返回-1
 */
int lwcb_init(lwcb_t* cb, void* buffer, uint32_t element_size, uint32_t capacity);

/**
 * @brief 向缓冲区写入数据
 * @param cb 缓冲区控制结构体指针
 * @param data 要写入的数据指针
 * @return 成功返回0，失败返回-1（缓冲区满或参数错误）
 */
int lwcb_push(lwcb_t* cb, const void* data);

/**
 * @brief 从缓冲区读取数据
 * @param cb 缓冲区控制结构体指针
 * @param data 接收数据的缓冲区指针
 * @return 成功返回0，失败返回-1（缓冲区空或参数错误）
 */
int lwcb_pop(lwcb_t* cb, void* data);

/**
 * @brief 检查缓冲区是否为空
 * @param cb 缓冲区控制结构体指针
 * @return 空返回true，否则返回false
 */
bool lwcb_is_empty(const lwcb_t* cb);

/**
 * @brief 检查缓冲区是否已满
 * @param cb 缓冲区控制结构体指针
 * @return 满返回true，否则返回false
 */
bool lwcb_is_full(const lwcb_t* cb);

/**
 * @brief 获取当前元素数量
 * @param cb 缓冲区控制结构体指针
 * @return 元素数量
 */
uint32_t lwcb_get_count(const lwcb_t* cb);

#endif /* LIGHT_WEIGHT_CIRCULAR_BUFFER_H */

