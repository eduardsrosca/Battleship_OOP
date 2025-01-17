#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Checks if a value is within a specified range [min, max].
 *
 * @tparam T The type of the value and the range bounds.
 * @param value The value to check.
 * @param min The minimum bound of the range (inclusive).
 * @param max The maximum bound of the range (inclusive).
 * @return True if the value is within the range, false otherwise.
 */
template <typename T>
bool isWithinBounds(const T& value, const T& min, const T& max) {
    return value >= min && value <= max;
}

#endif // UTILS_H
