#include <vector>

class Board final {
   public:
    /**
     * Constructs a new board instance.
     *
     * @param rows The number of rows in the board. Default 5.
     * @param columns The number of columns in the board. Default 6.
     */
    Board(unsigned int const = 5, unsigned int const = 6);

    enum Colour {
        Yellow,
        Red,
        Null,
    };

    using State = std::vector<std::vector<Colour>>;

    /**
     * Gets the current board state.
     *
     * @returns The current state of the board.
     */
    State get_board_state();

    /**
     * Prints the board state to STDOUT.
     */
    void pretty_print_board_state();

    /**
     * Places a coin in the board.
     *
     * @param column The column in which the coin is to be placed.
     *
     * @returns The colour that has won. `Board::Colour::Null` if no one has
     * won.
     */
    Colour place_coin(unsigned int const);

   private:
    unsigned int rows;

    unsigned int columns;

    State board_state;

    Colour current_player;

    /**
     * Changes the current player.
     */
    void switch_player();

    /**
     * Checks if the current player has won the game.
     *
     * @param row The row in which the coin was placed.
     * @param column The column in which the coin was placed.
     *
     * @return The current winner. If `Board::Colour::Null`, then no one has won
     * yet.
     */
    Colour check_winner(unsigned int const, unsigned int const);
};
