#include <connect/Board.hpp>
#include <iostream>
#include <stdexcept>

#define MAX_ROWS 10
#define MAX_COLUMNS 10

int get_player_input(Board &board) {
    int column;
    std::cout << (board.get_current_player() == Board::Colour::Red ? "Red "
                                                                   : "Yellow ")
              << "player - Enter column to play: ";
    std::cin >> column;
    std::cout << "\n\n";

    return column;
}

int main(int argc, char **argv) {
    if (argc == 2 || argc >= 4) {
        std::cout << "Usage: connect_cli [<rows>] [<columns>]\n"
                     "    Starts a game of Connect-4 with the given number of "
                     "rows columns. If no rows or columns are provided, uses a "
                     "5x6 board."
                  << std::endl;

        return 126;
    }

    Board board;
    int rows = 5;
    int columns = 6;

    if (argc == 3) {
        rows = atoi(argv[1]);
        columns = atoi(argv[2]);

        if (rows <= 0 || columns <= 0 || rows > MAX_ROWS ||
            rows > MAX_COLUMNS) {
            std::cerr << "Invalid number of rows or columns.\nEnter a value "
                         "between 1 and "
                      << MAX_ROWS << " for rows and between 1 and "
                      << MAX_COLUMNS << " for columns." << std::endl;
            return 126;
        }

        std::cout << "Starting a game with a " << rows << "x" << columns
                  << " board.\n\n";

        board = Board(rows, columns);
    }

    unsigned int move_counter = rows * columns;

    std::cout << "Current board:\n\n";
    board.pretty_print_board_state();

    Board::Colour winner = Board::Colour::Null;
    while (winner == Board::Colour::Null && move_counter > 0) {
        int const entered_column = get_player_input(board);

        if (entered_column <= 0 || entered_column > columns) {
            std::cerr << "Invalid column value entered. Please try again.\n";
        } else {
            try {
                winner = board.place_coin(entered_column - 1);
            } catch (std::out_of_range const &e) {
                std::cerr << e.what() << "\n";
                continue;
            }

            --move_counter;
            board.pretty_print_board_state();
        }
    }

    if (move_counter == 0 && winner == Board::Colour::Null) {
        std::cout << "Draw!";
    } else {
        std::cout << (winner == Board::Colour::Red ? "Red " : "Yellow ")
                  << "wins!" << std::endl;
    }

    return 0;
}
