/*
* This file is subject to the terms and conditions of the GNU General Public
* License. See the file COPYING in the main directory of this archive for
* more details.
*/

#include "charoln.h"
#include <stdlib.h>
#include <string.h>

String *str_init(void)
{
        String *dest = malloc(sizeof(String));
        dest->error_msg = malloc(50 * sizeof(char));
        dest->str_obj_ptr = malloc(sizeof(str_obj));
        dest->str_obj_ptr->str_ptr = malloc(INIT_STR_SIZE * sizeof(char));

        if (
                dest == NULL ||
                dest->error_msg == NULL ||
                dest->str_obj_ptr == NULL ||
                dest->str_obj_ptr->str_ptr == NULL
        ) {
                return NULL;
        };

        memset(dest->str_obj_ptr->str_ptr, '\0', INIT_STR_SIZE);
        dest->str_obj_ptr->len = 0;
        dest->str_obj_ptr->size = INIT_STR_SIZE;
        dest->error_code = SUCCESS;

        return dest;
}

void str_destroy(String *dest)
{
        free(dest->str_obj_ptr->str_ptr);
        free(dest->str_obj_ptr);
        free(dest->error_msg);
        free(dest);
}

char *str_get(String *dest)
{
        return dest->str_obj_ptr->str_ptr;
}

size_t str_len(String *dest)
{
        return dest->str_obj_ptr->len;
}

void str_write(String *dest, const char *source)
{
        dest->error_code = ERROR_UNSET;
        size_t input_len = strlen(source);

        // Realloc is string length is more than str_obj size
        if (dest->str_obj_ptr->size < input_len + 1) {
                while (dest->str_obj_ptr->size < input_len + 1) {
                        dest->str_obj_ptr->size *= 1.5;
                }

                char *temp = realloc(dest->str_obj_ptr->str_ptr, dest->str_obj_ptr->size * sizeof(char));
                if (temp == NULL) {
                        // Failure
                        strcpy(dest->error_msg, "str_write: realloc failure");
                        dest->error_code = ERROR_ALLOCATION;
                        return;
                } else {
                        dest->str_obj_ptr->str_ptr = temp;
                }
        }

        // Write input into str_obj
        strcpy(dest->str_obj_ptr->str_ptr, source);
        dest->str_obj_ptr->len = input_len;

        dest->error_code = SUCCESS;
}

void str_add(String *dest, const char *source)
{
        dest->error_code = ERROR_UNSET;
        size_t input_len = strlen(source);

        // Realloc total length is more than str_obj size
        if (dest->str_obj_ptr->size < dest->str_obj_ptr->len + input_len + 1) {
                while(dest->str_obj_ptr->size < dest->str_obj_ptr->len + input_len + 1) {
                        dest->str_obj_ptr->size *= 1.5;
                }
                char *temp = realloc(dest->str_obj_ptr->str_ptr, dest->str_obj_ptr->size * sizeof(char));
                if (temp == NULL) {
                        strcpy(dest->error_msg, "str_add: realloc failure");
                        dest->error_code = ERROR_ALLOCATION;
                        return;
                } else {
                        dest->str_obj_ptr->str_ptr = temp;
                }
        }

        strcat(dest->str_obj_ptr->str_ptr, source);
        dest->str_obj_ptr->len += input_len;

        dest->error_code = SUCCESS;
}
