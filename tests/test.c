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
void test_str_slice(void);

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
        assert(tstr->status_code == SUCCESS);
        printf("%s\n", "str_init test passed");

        str_destroy(tstr);
}

void test_str_resize(void)
{
        String *tstr = str_init();
        int target = get_random_int(51, 150);
        _str_resize(tstr, target);
        assert(tstr->size >= (size_t)target);

        target = get_random_int(200, 400);
        _str_resize(tstr, target);
        assert(tstr->size >= (size_t)target);
        printf("%s\n", "_str_resize test passed");

        str_destroy(tstr);
}

void test_str_write(void)
{
        /*** TESTING CHAR* ARGUMENT ***/
        String *tstr = str_init();
        // Create 199 char long sting to test realloc mechanism
        char *value = string_to_fill(101);
        str_write(tstr, value);

        // Check size, string content, real length and stored length
        assert(tstr->status_code == SUCCESS);
        assert(tstr->size == 100);
        assert(memcmp(tstr->str_ptr, value, 100) == 0); // Content
        assert(tstr->len == 100); // Stored length

        /*** TESTING STRING ARGUMENT ***/
        String *tstr2 = str_init();
        str_write(tstr2, tstr);

        // Check size, string content, real length and stored length
        assert(tstr2->status_code == SUCCESS);
        assert(tstr2->size == 100);
        assert(memcmp(tstr->str_ptr, value, 100) == 0); // Content
        assert(tstr2->len == 100); // Stored length

        free(value);
        printf("%s\n", "str_write test passed");
        str_destroy(tstr);
        str_destroy(tstr2);
}

void test_str_get(void)
{
        const char *value = "Hello how are you? λゅ🚒會意";

        // Write into String
        String *tstr = str_init();
        str_write(tstr, value);

        // Extract from String
        char *tstr2 = str_get(tstr);

        // Compare c strings
        assert(strcmp(tstr2, value) == 0);

        printf("%s\n", "str_get test passed");
        str_destroy(tstr);
        free(tstr2);
}

void test_str_append(void)
{
        /*** TESTING DIFFERENT TYPE ARGUMENTS ***/
        String *tstr = str_init();
        String *tstr2 = str_init();
        str_write(tstr, "Hello");
        str_write(tstr2, "World");

        // APPEND STRING
        str_append(tstr, tstr2);
        assert(tstr->status_code == SUCCESS);
        assert(tstr->len == 10);

        // APPEND CHAR ARR
        str_append(tstr, "Good!");
        assert(tstr->status_code == SUCCESS);
        assert(tstr->len == 15);

        // Ensure String is similar
        const char *cmp = "HelloWorldGood!";
        char *cmp2 = str_get(tstr);
        assert(strcmp(cmp, cmp2) == 0);

        printf("%s\n", "str_append test passed");
        str_destroy(tstr);
        str_destroy(tstr2);
        free(cmp2);
}

void test_str_slice(void)
{
        String *tstr = str_init();
        str_write(tstr, "assignment");

        // Slice sign
        String *slice = str_slice(tstr, 2, 6);
        assert(slice != NULL);
        char *cmp = str_get(slice);
        assert(strcmp(cmp, "sign") == 0);
        assert(slice->status_code == SUCCESS);
        str_destroy(slice);
        free(cmp);

        // Slice negative
        slice = str_slice(tstr, -4, 11);
        assert(slice != NULL);
        cmp = str_get(slice);
        assert(strcmp(cmp, "ment") == 0);
        str_destroy(slice);
        free(cmp);

        // Slice out of range
        slice = str_slice(tstr, -11, 11);
        assert(slice == NULL);
        slice = str_slice(tstr, -10, 12);
        assert(slice == NULL);
        str_destroy(slice);

        printf("%s\n", "str_slice test passed");
        str_destroy(tstr);
}

int main(void)
{
        // Run tests
        test_str_init();
        test_str_resize();
        test_str_write();
        test_str_get();
        test_str_append();
        test_str_slice();

        return 0;
}
