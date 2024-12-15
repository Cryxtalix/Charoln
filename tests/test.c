/*
* This file is subject to the terms and conditions of the GNU General Public
* License. See the file COPYING in the main directory of this archive for
* more details.
*/

#include "_charoln.h"
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char *string_to_fill(size_t len);
int get_random_int(int min, int max);
void test_str_init(void);
void test_str_resize(void);
void test_str_write(void);
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
        assert(tstr->str_ptr != NULL);
        assert(tstr->error_code == SUCCESS);
        printf("%s\n", "str_init test passed");

        str_destroy(tstr);
}

void test_str_resize(void)
{
        String *tstr = str_init();
        int t_size = get_random_int(51, 150);
        _str_resize(tstr, t_size);
        assert(tstr->size >= (size_t)t_size);

        t_size = get_random_int(200, 400);
        _str_resize(tstr, t_size);
        assert(tstr->size >= (size_t)t_size);
        printf("%s\n", "_str_resize test passed");

        str_destroy(tstr);
}

void test_str_write(void)
{
        /*** TESTING DIFFERENT CHAR* ARGUMENT ***/
        String *tstr = str_init();
        // Create 199 char long sting to test realloc mechanism
        char *value = string_to_fill(200);
        str_write(tstr, value);

        // Check size, string content, real length and stored length
        assert(tstr->error_code == SUCCESS);
        assert(tstr->size >= 200);
        assert(strcmp(tstr->str_ptr, value) == 0); // Content
        assert(strlen(tstr->str_ptr) == strlen(value)); // Real length
        assert(tstr->len == 199); // Stored length

        /*** TESTING DIFFERENT STRING ARGUMENT ***/
        String *tstr2 = str_init();
        str_write(tstr2, tstr);

        // Check size, string content, real length and stored length
        assert(tstr2->error_code == SUCCESS);
        assert(tstr2->size >= 200);
        assert(strcmp(tstr2->str_ptr, value) == 0); // Content
        assert(strlen(tstr2->str_ptr) == strlen(value)); // Real length
        assert(tstr2->len == 199); // Stored length

        free(value);
        printf("%s\n", "str_write test passed");
        str_destroy(tstr);
        str_destroy(tstr2);
}

void test_str_get(void)
{
        String *tstr = str_init();
        const char *value = "Hello how are you? λゅ🚒會意";
        str_write(tstr, value);
        assert(strcmp(str_get(tstr), value) == 0);
        printf("%s\n", "str_get test passed");

        str_destroy(tstr);
}

void test_str_len(void)
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

void test_str_append(void)
{
        /*** TESTING DIFFERENT TYPE ARGUMENTS ***/
        // APPEND STRING OBJ
        String *tstr = str_init();
        String *tstr2 = str_init();
        str_write(tstr, "Hello");
        str_write(tstr2, "world");

        str_append(tstr, tstr2);
        assert(tstr->error_code == SUCCESS);
        assert(tstr->len == 10);

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
        test_str_resize();
        test_str_write();
        test_str_get();
        test_str_len();
        test_str_append();

        return 0;
}
