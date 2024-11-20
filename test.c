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
void test_str_overwrite(void);
void test_str_get(void);
void test_str_len(void);
void test_str_append(void);

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
        assert(tstr->error_msg != NULL);
        assert(tstr->str_obj_ptr != NULL);
        assert(tstr->str_obj_ptr->str_ptr != NULL);
        assert(tstr->error_code == SUCCESS);
        printf("%s\n", "str_init test passed");

        str_destroy(tstr);
}

void test_str_overwrite()
{
        String *tstr = str_init();
        // Create 199 char long sting to test realloc mechanism
        char *value = string_to_fill(200);
        str_overwrite(tstr, value);

        // Check size, string content, real length and stored length
        assert(tstr->error_code == SUCCESS);
        assert(tstr->str_obj_ptr->size >= 200);
        assert(strcmp(tstr->str_obj_ptr->str_ptr, value) == 0); // Content
        assert(strlen(tstr->str_obj_ptr->str_ptr) == strlen(value)); // Real length
        assert(tstr->str_obj_ptr->len == 199); // Stored length
        free(value);
        
        // Write string of exact size(including null terminator) and check if realloc is triggered
        const size_t current_size = tstr->str_obj_ptr->size;
        char *value2 = string_to_fill(current_size);
        str_overwrite(tstr, value2);

        // Ensure size and length is as expected
        assert(tstr->error_code == SUCCESS);
        assert(tstr->str_obj_ptr->size == current_size); // Size has not changed
        assert(tstr->str_obj_ptr->len + 1 == current_size); // Length is as expected
        free(value2);

        // Test overwriting with shorter string
        char *value3 = string_to_fill(100);
        str_overwrite(tstr, value3);

        // Ensure length is now as expected
        assert(tstr->error_code == SUCCESS);
        assert(tstr->str_obj_ptr->len == 99);
        
        printf("%s\n", "str_overwrite test passed");

        str_destroy(tstr);
}

void test_str_get()
{
        String *tstr = str_init();
        const char *value = "Hello how are you? λゅ🚒會意";
        str_overwrite(tstr, value);
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
                str_overwrite(tstr, value);

                // Ensure that str_len returns same result as random
                assert(str_len(tstr) == random - 1);
                free(value);
        }

        printf("%s\n", "str_len test passed");

        str_destroy(tstr);
}

void test_str_append()
{
        // APPEND STRING OBJ
        String *tstr = str_init();
        String *tstr2 = str_init();
        str_overwrite(tstr, "Hello");
        str_overwrite(tstr2, "world");

        str_append(tstr, tstr2);
        assert(tstr->error_code == SUCCESS);
        assert(tstr->str_obj_ptr->len == 10);

        // APPEND CHAR ARR
        str_append(tstr, "Good!");
        assert(tstr->error_code == SUCCESS);
        assert(str_len(tstr) == 15);

        printf("%s\n", "str_append test passed");
        str_destroy(tstr);
        str_destroy(tstr2);
}

int main(void)
{
        // Run tests
        test_str_init();
        test_str_overwrite();
        test_str_get();
        test_str_len();
        test_str_append();

        return 0;
}
