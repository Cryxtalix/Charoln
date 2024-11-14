/*
* This file is subject to the terms and conditions of the GNU General Public
* License. See the file COPYING in the main directory of this archive for
* more details.
*/

#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "charoln.h"

char *string_to_fill(size_t len);
int get_random_int(int min, int max);
void test_str_init(void);
void test_str_get(void);
void test_str_len(void);
void test_str_write(void);
void test_str_add(void);

// Create test string to completely fill size in memory
// Free after use
char *string_to_fill(size_t len)
{
        char *str = malloc(len * sizeof(char));
        if (str == NULL) {
                fprintf(stderr, "Test: string_to_fill: Memory reallocation of str_ptr failed\n");
                return NULL;
        }
        memset(str, 'a', len);
        str[len - 1] = '\0';
        return str;
}

int get_random_int(int min, int max)
{
        srand(time(0));
        return (rand() % (max - min + 1)) + min;
}

void test_str_init(void)
{
        String *tstr = str_init();

        // Check that the pointers are not NULL
        assert(tstr != NULL);
        assert(tstr->str_obj_ptr != NULL);
        assert(tstr->str_obj_ptr->str_ptr != NULL);
        printf("%s\n", "str_init test passed");

        str_destroy(tstr);
}

void test_str_get()
{
        String *tstr = str_init();
        const char *value = "Hello how are you? λゅ🚒會意";
        str_write(tstr, value);
        assert(strcmp(str_get(tstr), value) == 0);
        printf("%s\n", "str_get test passed");

        str_destroy(tstr);
}

void test_str_len()
{
        String *tstr = str_init();
        // Fill with strings of random length
        for (int i = 0; i < 5; i++) {
                size_t random = get_random_int(100, 2000);
                char *value = string_to_fill(random);
                str_write(tstr, value);

                // Ensure that str_len returns same result as random
                assert(str_len(tstr) == random - 1);
                free(value);
        }

        printf("%s\n", "str_len test passed");

        str_destroy(tstr);
}

void test_str_write()
{
        String *tstr = str_init();
        // Create 199 char long sting to test realloc mechanism
        char *value = string_to_fill(200);
        str_write(tstr, value);

        // Check size, string content, real length and stored length
        assert(tstr->str_obj_ptr->size >= 200);
        assert(strcmp(tstr->str_obj_ptr->str_ptr, value) == 0); // Content
        assert(strlen(tstr->str_obj_ptr->str_ptr) == strlen(value)); // Real length
        assert(tstr->str_obj_ptr->len == 199); // Stored length
        free(value);
        
        // Write string of exact size(including null terminator) and check if realloc is triggered
        const size_t current_size = tstr->str_obj_ptr->size;
        char *value2 = string_to_fill(current_size);
        str_write(tstr, value2);

        // Ensure size and length is as expected
        assert(tstr->str_obj_ptr->size == current_size); // Size has not changed
        assert(tstr->str_obj_ptr->len + 1 == current_size); // Length is as expected
        free(value2);
        
        printf("%s\n", "str_write test passed");

        str_destroy(tstr);
}

void test_str_add()
{
        String *tstr = str_init();
        // Create a 199 char long string with str_add
        char *value = string_to_fill(200);
        str_add(tstr, value);

        // Check size, string content, real length and stored length
        assert(tstr->str_obj_ptr->size >= 200);
        assert(strcmp(tstr->str_obj_ptr->str_ptr, value) == 0); // Content
        assert(strlen(tstr->str_obj_ptr->str_ptr) == strlen(value)); // Real length
        assert(tstr->str_obj_ptr->len == 199); // Stored length
        free(value);

        // Add string of exact size(including null terminator) and check if realloc is triggered
        const size_t current_size = tstr->str_obj_ptr->size;
        const size_t additional = current_size - tstr->str_obj_ptr->len;
        char *value2 = string_to_fill(additional);
        str_add(tstr, value2);

        // Ensure size and length is as expected
        assert(tstr->str_obj_ptr->size == current_size); // Size has not changed
        assert(tstr->str_obj_ptr->len == current_size - 1); // Length is as expected
        free(value2);

        printf("%s\n", "str_add test passed");

        str_destroy(tstr);
}

int main(void)
{
        // Run tests
        test_str_init();
        test_str_get();
        test_str_len();
        test_str_write();
        test_str_add();

        return 0;
}
