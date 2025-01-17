#ifndef GRID_H
#define GRID_H

#include <vector>

/**
 * @class Grid
 * @brief A generic 2D grid class template for managing data in a grid-like structure.
 * @tparam T The type of elements stored in the grid.
 */
template <typename T>
class Grid {
private:
    /**
     * @brief 2D vector storing the grid data.
     */
    std::vector<std::vector<T>> data;

    /**
     * @brief The number of rows in the grid.
     */
    int rows;

    /**
     * @brief The number of columns in the grid.
     */
    int cols;

public:
    /**
     * @brief Constructs a Grid with specified dimensions and a default value.
     * @param rows The number of rows in the grid.
     * @param cols The number of columns in the grid.
     * @param defaultValue The default value to initialize all cells in the grid.
     */
    Grid(int rows, int cols, T defaultValue)
        : rows(rows), cols(cols), data(rows, std::vector<T>(cols, defaultValue)) {}

    /**
     * @brief Retrieves the value at a specified cell in the grid.
     * @param row The row index of the cell.
     * @param col The column index of the cell.
     * @return The value stored at the specified cell.
     */
    T get(int row, int col) const {
        return data[row][col];
    }

    /**
     * @brief Sets the value of a specified cell in the grid.
     * @param row The row index of the cell.
     * @param col The column index of the cell.
     * @param value The value to set at the specified cell.
     */
    void set(int row, int col, T value) {
        data[row][col] = value;
    }

    /**
     * @brief Gets the number of rows in the grid.
     * @return The number of rows in the grid.
     */
    int getRows() const {
        return rows;
    }

    /**
     * @brief Gets the number of columns in the grid.
     * @return The number of columns in the grid.
     */
    int getCols() const {
        return cols;
    }
};

#endif // GRID_H
