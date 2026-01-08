/**
 * @brief Convert an unsigned integer to a string in the specified radix.
 *
 * Converts `value` into a NUL-terminated string written to `out`. Supports
 * radices 2 through 36, using lowercase letters for digits >= 10.
 *
 * @param value The integer to convert.
 * @param radix The numeric base to use (2..36).
 * @param out Buffer to write the NUL-terminated result into.
 * @param out_size Size of `out` in bytes.
 * @return 0 on success, -1 if radix is out of range, -2 if buffer is too small.
 *
 * @note This function does not prefix the result (no "0x" for hex).
 *
 * Example:
 * @code
 * char buf[65];
 * if (ul_to_radix(255, 16, buf, sizeof buf) == 0) {
 *     printf("%s\n", buf); // prints "ff"
 * }
 * @endcode
 */
int ul_to_radix(unsigned long value, int radix, char *out, size_t out_size);
