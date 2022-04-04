#include <connect/Board.hpp>
#include <iostream>
#include <stdexcept>

Board::Board(unsigned int const rows, unsigned int const columns) noexcept {
    // Set the rows and columns class properties.
    this->rows = rows;
    this->columns = columns;

    for (size_t i = 0; i < this->rows; ++i) {
        std::vector<Board::Colour> current_row;

        for (size_t j = 0; j < this->columns; ++j) {
            current_row.push_back(Board::Colour::Null);
        }

        this->board_state.push_back(current_row);
    }

    // Yellow will always be the first player.
    this->current_player = Board::Colour::Yellow;
}

Board::State Board::get_board_state() const noexcept {
    return this->board_state;
}

Board::Colour Board::get_current_player() const noexcept {
    return this->current_player;
}

void Board::pretty_print_board_state() const noexcept {
    for (auto row_it = this->board_state.begin();
         row_it < this->board_state.end(); ++row_it) {
        for (auto col_it = row_it->begin(); col_it < row_it->end(); ++col_it) {
            switch (*col_it) {
                case (Board::Colour::Yellow):
                    std::cout << " Y ";
                    break;

                case (Board::Colour::Red):
                    std::cout << " R ";
                    break;

                default:
                    std::cout << " . ";
                    break;
            }
        }

        std::cout << "\n";
    }

    std::cout << std::endl;
}

void Board::switch_player() noexcept {
    if (this->current_player == Board::Colour::Yellow) {
        this->current_player = Board::Colour::Red;
    } else {
        this->current_player = Board::Colour::Yellow;
    }
}

bool Board::check_horizontal_direction(
    unsigned int const row, unsigned int const column) const noexcept {
    unsigned int coin_count = 1;

    // Check in the left direction.
    int current_column = column - 1;
    for (; current_column >= 0 &&
           this->board_state[row][current_column] == this->current_player;
         --current_column) {
        ++coin_count;
    }

    // Check in the right direction.
    current_column = column + 1;
    for (; current_column < this->columns &&
           this->board_state[row][current_column] == this->current_player;
         ++current_column) {
        ++coin_count;
    }

    return coin_count >= 4;
}

bool Board::check_vertical_direction(unsigned int const row,
                                     unsigned int const column) const noexcept {
    unsigned int coin_count = 1;

    // Check in the upper portion.
    int current_row = row - 1;
    for (; current_row >= 0 &&
           this->board_state[current_row][column] == this->current_player;
         --current_row) {
        ++coin_count;
    }

    // Check in the botton portion.
    current_row = row + 1;
    for (; current_row < this->rows &&
           this->board_state[current_row][column] == this->current_player;
         ++current_row) {
        ++coin_count;
    }

    return coin_count >= 4;
}

bool Board::check_ascending_diagonal(unsigned int const row,
                                     unsigned int const column) const noexcept {
    unsigned int coin_count = 1;

    // Check up the diagonal.
    int current_row = row - 1;
    int current_column = column + 1;
    for (;
         current_row >= 0 && current_column < this->columns &&
         this->board_state[current_row][current_column] == this->current_player;
         --current_row, ++current_column) {
        ++coin_count;
    }

    // Check down the diagonal.
    current_row = row + 1;
    current_column = column - 1;
    for (;
         current_row < this->rows && current_column >= 0 &&
         this->board_state[current_row][current_column] == this->current_player;
         ++current_row, --current_column) {
        ++coin_count;
    }

    return coin_count >= 4;
}

bool Board::check_descending_diagonal(
    unsigned int const row, unsigned int const column) const noexcept {
    unsigned coin_count = 1;

    // Check up the diagonal.
    int current_row = row - 1;
    int current_column = column - 1;
    for (;
         current_row >= 0 && current_column >= 0 &&
         this->board_state[current_row][current_column] == this->current_player;
         --current_row, --current_column) {
        ++coin_count;
    }

    // Check down the diagonal.
    current_row = row + 1;
    current_column = column + 1;
    for (;
         current_row < this->rows && current_column < this->columns &&
         this->board_state[current_row][current_column] == this->current_player;
         ++current_row, ++current_column) {
        ++coin_count;
    }

    return coin_count >= 4;
}

Board::Colour Board::check_winner(unsigned int const row,
                                  unsigned int const column) const noexcept {
    return (this->check_horizontal_direction(row, column) ||
            this->check_vertical_direction(row, column) ||
            this->check_ascending_diagonal(row, column) ||
            this->check_descending_diagonal(row, column))
               ? this->current_player
               : Board::Colour::Null;
}

Board::Colour Board::place_coin(unsigned int const column) {
    // Check if at least the topmost slot is available.
    if (this->board_state[0][column] != Board::Colour::Null) {
        throw std::out_of_range("No more coins can be placed in this column");
    }

    // Get the coins in the column the player wants to play their next move in.
    std::vector<Board::Colour> current_column;
    for (auto it = this->board_state.begin(); it < this->board_state.end();
         ++it) {
        current_column.push_back((*it)[column]);
    }

    // Find the first position from the bottom where the coin can be placed.
    for (size_t i = current_column.size() - 1; i >= 0; --i) {
        Board::Colour current_position = current_column[i];

        if (current_position == Board::Colour::Null) {
            // Place the coin in the available location.
            this->board_state[i][column] = this->current_player;

            auto winner = this->check_winner(i, column);

            if (winner != Board::Colour::Null) {
                return winner;
            }

            this->switch_player();
            break;
        }
    }

    return Board::Colour::Null;
}
