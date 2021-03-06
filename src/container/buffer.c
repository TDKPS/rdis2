#include "buffer.h"

#include <stdio.h>
#include <string.h>

static const struct _object buffer_object = {
    (void     (*) (void *)) buffer_delete, 
    (void *   (*) (const void *)) buffer_copy,
    NULL,
    NULL
};


struct _buffer * buffer_create (const uint8_t * bytes, size_t size)
{
    struct _buffer * buffer = (struct _buffer *) malloc(sizeof(struct _buffer));

    buffer->object      = &buffer_object;
    buffer->bytes       = (uint8_t *) malloc(size);
    buffer->size        = size;
    buffer->permissions = 0;

    memcpy(buffer->bytes, bytes, size);

    return buffer;
}


struct _buffer * buffer_create_null (size_t size)
{
    struct _buffer * buffer = (struct _buffer *) malloc(sizeof(struct _buffer));

    buffer->object      = &buffer_object;
    buffer->bytes       = (uint8_t *) malloc(size);
    buffer->size        = size;
    buffer->permissions = 0;

    memset(buffer->bytes, 0, buffer->size);

    return buffer;
}


struct _buffer * buffer_load_file (const char * filename)
{
    FILE * fh;
    size_t filesize;

    fh = fopen(filename, "rb");
    if (fh == NULL)
        return NULL;

    fseek(fh, 0, SEEK_END);
    filesize = ftell(fh);
    fseek(fh, 0, SEEK_SET);

    struct _buffer * buffer = buffer_create_null(filesize);

    size_t bytes_read;
    bytes_read = fread(buffer->bytes, 1, filesize, fh);

    if (bytes_read != filesize) {
        object_delete(buffer);
        buffer = NULL;
    }

    fclose(fh);
    return buffer;
}


void buffer_delete (struct _buffer * buffer)
{
    free(buffer->bytes);
    free(buffer);
}


struct _buffer * buffer_copy (const struct _buffer * buffer)
{
    return buffer_create(buffer->bytes, buffer->size);
}


int buffer_safe_byte (const struct _buffer * buffer, size_t offset)
{
    if (offset >= buffer->size)
        return -1;
    else
        return (unsigned int) buffer->bytes[offset];
}