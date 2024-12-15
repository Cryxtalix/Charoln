/*
* This file is subject to the terms and conditions of the GNU General Public
* License. See the file COPYING in the main directory of this archive for
* more details.
*/

#ifndef CHAROLN
#define CHAROLN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef INIT_STR_SIZE
#define INIT_STR_SIZE 50
#endif //INIT_STR_SIZE

typedef enum {
        SUCCESS,
        ERROR_UNSET,
        ERROR_ALLOCATION
} ErrorCode;

typedef struct {
        char *str_ptr;
        size_t len;
        size_t size;
        ErrorCode error_code;
} String;

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
 * @return size_t
 */
size_t str_len(String *dest);

/*
 * Write text to string
 *
 * @note Writes string, overwriting any existing data.
 * @param String
 * @param String or const char *
 */
#define str_write(dest, source) _Generic((source), \
                                            const char *: _overwrite_char, \
                                                  char *: _overwrite_char, \
                                                String *: _overwrite_string \
                                          )(dest, source)
void _overwrite_char(String *dest, const char *source);
void _overwrite_string(String *dest, String *source);

/*
 * Append to String
 *
 * @param String
 * @param String or const char *
 */
#define str_append(dest, source) _Generic((source), \
                                            const char *: _append_char, \
                                                String *: _append_string \
                                          )(dest, source)
void _append_char(String *dest, const char *source);
void _append_string(String *dest, String *source);

#endif // CHAROLN
