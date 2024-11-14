/*
* This file is subject to the terms and conditions of the GNU General Public
* License. See the file COPYING in the main directory of this archive for
* more details.
*/

#ifndef CHARLN
#define CHARLN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef INIT_STR_SIZE
#define INIT_STR_SIZE 50
#endif //INIT_STR_SIZE

typedef struct {
        struct str_obj *str_obj_ptr;
}String;

struct str_obj {
        char *str_ptr;
        size_t len;
        size_t size;
};

/*
 * Generates a new string and returns a pointer to it.
 */
String *str_init(void);

/*
 * Free memory of string when no longer in use.
 *
 * @param String
 */
void str_destroy(String *dest);

/*
 * Extracts standard C string.
 *
 * @param String
 */
char *str_get(String *dest);

/*
 * Returns the length of string
 *
 * @param String
 * @return Length uint64_t
 */
size_t str_len(String *dest);

/*
 * Write text to string
 *
 * @note Overwrites any existing data.
 * @param String, const C strings
 */
void str_write(String *dest, const char *source);

/*
 * Append standard C string to String
 *
 * @param String, const c strings
 */
void str_add(String *dest, const char *source);

#endif // CHARLN
