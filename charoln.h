/*
* This file is subject to the terms and conditions of the GNU General Public
* License. See the file COPYING in the main directory of this archive for
* more details.
*/

#ifndef CHAROLN
#define CHAROLN

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifndef INIT_STR_SIZE
#define INIT_STR_SIZE 50
#endif //INIT_STR_SIZE

typedef enum {
        SUCCESS,
        ERROR_UNSET,
        ERROR_ALLOCATION
} StatusCode;

typedef struct {
        char *str_ptr;
        size_t len; // Zero if newly initialized
        size_t size; // Zero if substring
        StatusCode status_code;
} String;

/*
 * Generates a new String and returns a pointer to it.
 */
String *str_init(void);

/*
 * Free memory of String
 *
 * @param String
 */
void str_destroy(String *dest);

/*
 * Returns heap allocated standard C string.
 * Free after use
 *
 * @param String
 */
char *str_get(String *dest);

/*
 * Write text to String
 *
 * @note Writes String, overwriting any existing data.
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

/*
 * Slices a String
 * Returns a new String, NULL ptr if error
 *
 * @param String
 * @param int start
 * @param int end
 * @returns String with size of 0
 */
String *str_slice(String *source, int start, int end);

#endif // CHAROLN
