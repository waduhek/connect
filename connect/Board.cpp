#include <connect/Board.hpp>
#include <iostream>

Board::Board(unsigned int const rows, unsigned int const columns) {
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

Board::State Board::get_board_state() const { return this->board_state; }

Board::Colour Board::get_current_player() const { return this->current_player; }

void Board::pretty_print_board_state() const {
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

void Board::switch_player() {
    if (this->current_player == Board::Colour::Yellow) {
        this->current_player = Board::Colour::Red;
    } else {
        this->current_player = Board::Colour::Yellow;
    }
}

Board::Colour Board::check_winner(unsigned int const row,
                                  unsigned int const column) const {
    // Check in the horizontal direction.
    if (this->board_state[row][column + 1] == this->current_player ||
        this->board_state[row][column - 1]) {
        unsigned int current_player_coin_count = 1;

        // Traverse to the left most coin from the current coin.
        unsigned int current_column = column - 1;
        while (this->board_state[row][current_column] == this->current_player) {
            --current_column;
            ++current_player_coin_count;
        }

        // Traverse right from the current coin.
        current_column = column + 1;
        while (this->board_state[row][current_column] == this->current_player) {
            ++current_column;
            ++current_player_coin_count;
        }

        if (current_player_coin_count >= 4) {
            return this->current_player;
        }
    }

    // Check in the vertical direction.
    if (this->board_state[row + 1][column] == this->current_player ||
        this->board_state[row - 1][column] == this->current_player) {
        unsigned int current_player_coin_count = 1;

        // Traverse to the the top most coin from the current coin.
        unsigned int current_row = row - 1;
        while (this->board_state[current_row][column] == this->current_player) {
            --current_row;
            ++current_player_coin_count;
        }

        // Traverse to the bottom most coin from the current coin.
        current_row = row + 1;
        while (this->board_state[current_row][column] == this->current_player) {
            ++current_row;
            ++current_player_coin_count;
        }

        if (current_player_coin_count >= 4) {
            return this->current_player;
        }
    }

    // Check in the descending diagonal.
    if (this->board_state[row - 1][column - 1] == this->current_player ||
        this->board_state[row + 1][column + 1] == this->current_player) {
        unsigned int current_player_coin_count = 1;

        // Traverse to the top of the diagonal.
        unsigned int current_row = row - 1;
        unsigned int current_column = column - 1;
        while (this->board_state[current_row][current_column] ==
               this->current_player) {
            --current_row;
            --current_column;
            ++current_player_coin_count;
        }

        // Traverse to the bottom of the diagonal.
        current_row = row + 1;
        current_column = column + 1;
        while (this->board_state[current_row][current_column] ==
               this->current_player) {
            ++current_row;
            ++current_column;
            ++current_player_coin_count;
        }

        if (current_player_coin_count >= 4) {
            return this->current_player;
        }
    }

    // Check the ascending diagonal.
    if (this->board_state[row - 1][column + 1] == this->current_player ||
        this->board_state[row + 1][column - 1] == this->current_player) {
        unsigned int current_player_coin_count = 1;

        // Traverse to the top of the diagonal.
        unsigned int current_row = row - 1;
        unsigned int current_column = column + 1;
        while (this->board_state[current_row][current_column] ==
               this->current_player) {
            --current_row;
            ++current_column;
            ++current_player_coin_count;
        }

        // Traverse to the bottom of the diagonal.
        current_row = row + 1;
        current_column = column - 1;
        while (this->board_state[current_row][current_column] ==
               this->current_player) {
            ++current_row;
            --current_column;
            ++current_player_coin_count;
        }

        if (current_player_coin_count >= 4) {
            return this->current_player;
        }
    }

    return Board::Colour::Null;
}

Board::Colour Board::place_coin(unsigned int const column) {
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
            this->switch_player();

            if (winner != Board::Colour::Null) {
                return winner;
            }

            break;
        }
    }

    return Board::Colour::Null;
}
