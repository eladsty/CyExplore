#include <assert.h>    /* assert */
#include <stdlib.h>    /* malloc, free */
#include <string.h>    /* memcpy */
#include <sys/types.h> /* size_t, ssite_t */
#include <stddef.h>    /* offsetof */

#include "cbuff_read_write_index.h"

#define MIN(a,b) ((a) < (b)) ? (a) : (b)

/* In this DS we assume Read and Write sizes are guarded by
   external sempahores using producer / consumer pattern.
   Therefore it uses separate read and write offsets, and maintains no 
   size member.*/
struct c_buff
{
    size_t capacity; /* Initialized and never changes - can be read from multiple thread asynchronously */
    size_t write_offset;  /* Starting position for write operations.          */
    size_t read_offset;  /* Starting position for read operations.          */
    char buffer[1];
};

void CBuffPrintDebug(const c_buff_t *c_buff);


c_buff_t *CBuffCreate(size_t capacity)
{
    c_buff_t *c_buff = NULL;
    size_t unused_mem = sizeof(c_buff_t) - offsetof(struct c_buff, buffer);
    size_t buffer_size = 0;
    
    assert(capacity);
    
    /* Using the padding memory for the buffer size to allocate - flexible array */
    if (capacity > unused_mem)
    {
        buffer_size = capacity - unused_mem;
    }
    
    
    c_buff = (c_buff_t *) malloc(sizeof(c_buff_t) + buffer_size);
    
    if (c_buff)
    {
        c_buff->capacity = capacity;
        c_buff->write_offset = 0;
        c_buff->read_offset = 0;
    }
    
    return c_buff;
}


void CBuffDestroy(c_buff_t *c_buff)
{
    assert(c_buff);
    
    free(c_buff);
    c_buff = NULL;
}


ssize_t CBuffRead(c_buff_t *c_buff, void *dest, size_t bytes_num)
{
    size_t bytes_to_read = 0;
    size_t bytes_to_copy = 0;
    
    assert(c_buff);
    assert(dest);
    
    bytes_to_read = bytes_num;
    
    /* Copy from the right side of buffer. */
    bytes_to_copy = MIN(bytes_to_read, c_buff->capacity - c_buff->read_offset);
    memcpy(dest, &c_buff->buffer[c_buff->read_offset], bytes_to_copy);
    dest = (char *) dest + bytes_to_copy;
    
    /* Copy from the left side of buffer. */
    if (bytes_to_read > bytes_to_copy )
    {
        bytes_to_copy = bytes_to_read - bytes_to_copy;
        memcpy(dest, &c_buff->buffer[0], bytes_to_copy);
    }
    
    /* Update read offset: */
    c_buff->read_offset = (c_buff->read_offset + bytes_to_read) % 
                           c_buff->capacity;
    
    return bytes_to_read;  
}


ssize_t CBuffWrite(c_buff_t *c_buff, const void *src, size_t bytes_num)
{
    size_t bytes_to_write = 0;
    size_t bytes_to_copy = 0;
    
    assert(c_buff);
    assert(src);
    
    bytes_to_write = bytes_num;
    
    /* Copy into the right side of buffer. */
    bytes_to_copy = MIN(bytes_to_write, c_buff->capacity - c_buff->write_offset);
    memcpy(&c_buff->buffer[c_buff->write_offset], src, bytes_to_copy);
    src = (char *) src + bytes_to_copy;
    
    /* Copy into the left side of buffer. */
    if (bytes_to_write > bytes_to_copy )
    {
        bytes_to_copy = bytes_to_write - bytes_to_copy;
        memcpy(&c_buff->buffer[0], src, bytes_to_copy);
    }
    
    /* Update write offset: */
    c_buff->write_offset = (c_buff->write_offset + bytes_to_write) % 
                           c_buff->capacity;    

    return bytes_to_write;
}


int CBuffIsEmpty(const c_buff_t *c_buff)
{
    assert(c_buff);	
    
    /* Also here, we are counting on external semaphores usage upon
       Read / Write calls. If used correctly, The following IsEmpty() is 
       now valid (non thread-safe of course):*/
    return (c_buff->read_offset == c_buff->write_offset);
}


size_t CBuffFreeSpace(const c_buff_t *c_buff)
{
    assert(c_buff);
    
    /* Also here, we are counting on external semaphores usage upon
       Read / Write calls. If used correctly, The following FreeSpace() is 
       now valid (non thread-safe of course):*/    
    return (c_buff->write_offset > c_buff->read_offset) ? 
                (c_buff->write_offset > c_buff->read_offset) : 
                (c_buff->write_offset - 0) + (c_buff->capacity - c_buff->read_offset);
}


 size_t CBuffCapacity(const c_buff_t *c_buff)
{
    return c_buff->capacity;
}

