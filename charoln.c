/*
* This file is subject to the terms and conditions of the GNU General Public
* License. See the file COPYING in the main directory of this archive for
* more details.
*/

#include "charoln.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifdef TESTING
#include "tests/_charoln.h"
#endif //TESTING

void _str_resize(String *dest, size_t target_size) {
        // If string is less than half of target_size
        // we simply set string to target_size
        // Otherwise we increase by a multiple of 1.5
        if (dest->size * 1.5 < target_size) {
                dest->size = target_size;
        } else {
                dest->size *= 1.5;
        }

        char *temp = realloc(dest->str_ptr, dest->size * sizeof(char));
        if (temp == NULL) {
                // Failure
                dest->status_code = ERROR_ALLOCATION;
                fprintf(stderr, "%s", "str_write: realloc failure");
                return;
        } else {
                dest->str_ptr = temp;
                dest->status_code = SUCCESS;
        }
}

String *str_init(void)
{
        String *retval = malloc(sizeof(String));
        retval->str_ptr = malloc(INIT_STR_SIZE * sizeof(char));

        if (
                retval == NULL ||
                retval->str_ptr == NULL
        ) {
                return NULL;
        };

        memset(retval->str_ptr, '\0', INIT_STR_SIZE);
        retval->len = 0;
        retval->size = INIT_STR_SIZE;
        retval->status_code = SUCCESS;

        return retval;
}

void str_destroy(String *source)
{
        free(source->str_ptr);
        free(source);
}

char *str_get(String *source)
{
        return source->str_ptr;
}

size_t str_len(String *source)
{
        return source->len;
}

void _overwrite_char(String *dest, const char *source)
{
        dest->status_code = ERROR_UNSET;
        size_t input_len = strlen(source);

        // Realloc if string length is more than source size
        if (dest->size < input_len + 1) {
                _str_resize(dest, input_len + 1);
                if (dest->status_code == ERROR_ALLOCATION) {
                        return;
                }
        }

        strcpy(dest->str_ptr, source);
        dest->len = input_len;
        dest->status_code = SUCCESS;
}

void _overwrite_string(String *dest, String *source)
{
        dest->status_code = ERROR_UNSET;
        size_t input_len = source->len;

        // Realloc if string length is more than source size
        if (dest->size < input_len + 1) {
                _str_resize(dest, input_len + 1);
                if (dest->status_code == ERROR_ALLOCATION) {
                        return;
                }
        }
        
        strcpy(dest->str_ptr, source->str_ptr);
        dest->len = input_len;
        dest->status_code = SUCCESS;
}

void _append_char(String *dest, const char *source)
{
        dest->status_code = ERROR_UNSET;
        size_t input_len = strlen(source);

        // Realloc total length is more than str_obj size
        if (dest->size < dest->len + input_len + 1) {
                _str_resize(dest, dest->len + input_len + 1);
                if (dest->status_code == ERROR_ALLOCATION) {
                        return;
                }
        }

        strcat(dest->str_ptr, source);
        dest->len += input_len;
        dest->status_code = SUCCESS;
}

void _append_string(String *dest, String *source)
{
        dest->status_code = ERROR_UNSET;
        size_t input_len = source->len;

        // Realloc if total length is more than dest size
        if (dest->size < dest->len + input_len + 1) {
                _str_resize(dest, dest->len + input_len + 1);
                if (dest->status_code == ERROR_ALLOCATION) {
                        return;
                }
        }

        strcat(dest->str_ptr, source->str_ptr);
        dest->len += input_len;
        dest->status_code = SUCCESS;
}

String *str_slice(String *source, int start, int end) {
        if (start < 0) {start += source->len;}
        if (end < 0) {end += source->len;}

        String *slice = malloc(sizeof(String));
        slice->str_ptr = source->str_ptr + start;
        slice->len = end - start;
        slice->size = 0;

        // Error checking
        if (
                start > source->len ||
                end > source->len ||
                start > end
        ) {
                slice->status_code = ERROR_ALLOCATION;
        } else {
                slice->status_code = SUCCESS;
        }
        return slice;
}
