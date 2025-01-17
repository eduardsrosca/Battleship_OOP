#ifndef CLEARSCREEN_H
#define CLEARSCREEN_H

#include <cstdlib>

/**
 * @brief Clears the console screen.
 *
 * This function uses system-specific commands to clear the console screen.
 * It calls the `system` function with the appropriate command for the operating system:
 * - On Windows, it uses "cls".
 * - On Unix-like systems, it uses "clear".
 *
 * @note Use of `system` may have security implications. Avoid using it in environments where
 *       user input can control the argument passed to `system`.
 */
void clearScreen();

#endif // CLEARSCREEN_H
