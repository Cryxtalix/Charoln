/*
* This file is subject to the terms and conditions of the GNU General Public
* License. See the file COPYING in the main directory of this archive for
* more details.
*/

#include "charoln.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static void _str_resize(String *dest, size_t target_size) {
        // If string is less than half of target_size
        // we simply set string to target_size
        // Otherwise we increase by a multiple of 1.5
        if (dest->size * 2 < target_size) {
                dest->size = target_size;
        } else {
                dest->size *= 1.5;
        }

        char *temp = realloc(dest->str_ptr, dest->size * sizeof(char));
        if (temp == NULL) {
                // Failure
                strcpy(dest->error_msg, "str_write: realloc failure");
                dest->error_code = ERROR_ALLOCATION;
                return;
        } else {
                dest->str_ptr = temp;
        }
}

String *str_init(void)
{
        String *dest = malloc(sizeof(String));
        dest->error_msg = malloc(50 * sizeof(char));
        dest->str_ptr = malloc(INIT_STR_SIZE * sizeof(char));

        if (
                dest == NULL ||
                dest->error_msg == NULL ||
                dest->str_ptr == NULL
        ) {
                return NULL;
        };

        memset(dest->str_ptr, '\0', INIT_STR_SIZE);
        dest->len = 0;
        dest->size = INIT_STR_SIZE;
        dest->error_code = SUCCESS;

        return dest;
}

void str_destroy(String *dest)
{
        free(dest->str_ptr);
        free(dest->error_msg);
        free(dest);
}

char *str_get(String *dest)
{
        return dest->str_ptr;
}

size_t str_len(String *dest)
{
        return dest->len;
}

void str_overwrite(String *dest, const char *source)
{
        dest->error_code = ERROR_UNSET;
        size_t input_len = strlen(source);

        // Realloc is string length is more than str_obj size
        if (dest->size < input_len + 1) {
                _str_resize(dest, input_len + 1);
        }

        // Write input into str_obj
        strcpy(dest->str_ptr, source);
        dest->len = input_len;

        dest->error_code = SUCCESS;
}

void _append_char(String *dest, const char *source)
{
        dest->error_code = ERROR_UNSET;
        size_t input_len = strlen(source);

        // Realloc total length is more than str_obj size
        if (dest->size < dest->len + input_len + 1) {
                _str_resize(dest, dest->len + input_len + 1);
        }

        strcat(dest->str_ptr, source);
        dest->len += input_len;

        dest->error_code = SUCCESS;
}

void _append_string(String *dest, String *source)
{
        dest->error_code = ERROR_UNSET;
        size_t input_len = source->len;

        // Realloc if total length is more than dest size
        if (dest->size < dest->len + input_len + 1) {
                _str_resize(dest, dest->len + input_len + 1);
        }

        strcat(dest->str_ptr, source->str_ptr);
        dest->len += input_len;

        dest->error_code = SUCCESS;
}
