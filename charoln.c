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
        if (dest == NULL) { // Check allocation
                fprintf(stderr, "str_init: Memory allocation of String failed\n");
                exit(1);
        }

        // Allocate memory for str_obj
        dest->str_obj_ptr = malloc(sizeof(struct str_obj));
        if (dest->str_obj_ptr == NULL) { // Check if allocation
                fprintf(stderr, "str_init: Memory allocation of str_obj_ptr failed\n");
                exit(1);
        }

        // Allocate memory for string
        dest->str_obj_ptr->str_ptr = malloc(INIT_STR_SIZE * sizeof(char));
        if (dest->str_obj_ptr->str_ptr == NULL) { // Check if allocation
                fprintf(stderr, "str_init: Memory allocation of str_ptr failed\n");
                exit(1);
        }
        memset(dest->str_obj_ptr->str_ptr, '\0', INIT_STR_SIZE);
        dest->str_obj_ptr->len = 0;
        dest->str_obj_ptr->size = INIT_STR_SIZE;

        return dest;
}

void str_destroy(String *dest)
{
        free(dest->str_obj_ptr->str_ptr);
        free(dest->str_obj_ptr);
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
        size_t input_len = strlen(source);

        // Realloc is string length is more than str_obj size
        if (dest->str_obj_ptr->size < input_len + 1) {
                while (dest->str_obj_ptr->size < input_len + 1) {
                        dest->str_obj_ptr->size *= 1.5;
                }

                char *temp = realloc(dest->str_obj_ptr->str_ptr, dest->str_obj_ptr->size * sizeof(char));
                if (temp == NULL) { // Check allocation
                        fprintf(stderr, "str_write: Memory reallocation of str_ptr failed\n");
                        free(dest->str_obj_ptr->str_ptr);
                        exit(1);
                } else {
                        dest->str_obj_ptr->str_ptr = temp;
                }
        }

        // Write input into str_obj
        strcpy(dest->str_obj_ptr->str_ptr, source);
        dest->str_obj_ptr->len = input_len;
}

void str_add(String *dest, const char *source)
{
        size_t input_len = strlen(source);

        // Realloc total length is more than str_obj size
        if (dest->str_obj_ptr->size < dest->str_obj_ptr->len + input_len + 1) {
                while(dest->str_obj_ptr->size < dest->str_obj_ptr->len + input_len + 1) {
                        dest->str_obj_ptr->size *= 1.5;
                }
                char *temp = realloc(dest->str_obj_ptr->str_ptr, dest->str_obj_ptr->size * sizeof(char));
                if (temp == NULL) {
                        fprintf(stderr, "str_add: Memory reallocation of str_ptr failed\n");
                        free(dest->str_obj_ptr->str_ptr);
                        exit(1);
                } else {
                        dest->str_obj_ptr->str_ptr = temp;
                }
        }

        strcat(dest->str_obj_ptr->str_ptr, source);
        dest->str_obj_ptr->len += input_len;
}
