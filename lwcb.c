#include "lwcb.h"

int lwcb_init(lwcb_t* cb, void* buffer, uint32_t element_size, uint32_t capacity)
{
    if ((cb == NULL) || (buffer == NULL) || (element_size == 0) || (capacity == 0)) {
        return -1;
    }

    memset(cb, 0, sizeof(lwcb_t));
    cb->buffer = buffer;
    cb->element_size = element_size;
    cb->capacity = capacity;
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;

    return 0;
}

int lwcb_push(lwcb_t* cb, const void* data)
{
    if ((cb == NULL) || (data == NULL) || (cb->buffer == NULL)) {
        return -1;
    }

    if (lwcb_is_full(cb)) {
        return -1;
    }

    uint8_t* buffer_ptr = (uint8_t*)cb->buffer;
    void* write_ptr = &buffer_ptr[cb->head * cb->element_size];
    
    memcpy(write_ptr, data, cb->element_size);
    
    cb->head = (cb->head + 1) % cb->capacity;
    cb->count++;

    return 0;
}

int lwcb_pop(lwcb_t* cb, void* data)
{
    if ((cb == NULL) || (data == NULL) || (cb->buffer == NULL)) {
        return -1;
    }

    if (lwcb_is_empty(cb)) {
        return -1;
    }

    uint8_t* buffer_ptr = (uint8_t*)cb->buffer;
    const void* read_ptr = &buffer_ptr[cb->tail * cb->element_size];
    
    memcpy(data, read_ptr, cb->element_size);
    
    cb->tail = (cb->tail + 1) % cb->capacity;
    cb->count--;

    return 0;
}

bool lwcb_is_empty(const lwcb_t* cb)
{
    if (cb == NULL) {
        return true;
    }
    return (cb->count == 0);
}

bool lwcb_is_full(const lwcb_t* cb)
{
    if (cb == NULL) {
        return false;
    }
    return (cb->count == cb->capacity);
}

uint32_t lwcb_get_count(const lwcb_t* cb)
{
    if (cb == NULL) {
        return 0;
    }
    return cb->count;
}

    