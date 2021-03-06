#include <vector>

class Board final {
   public:
    /**
     * Constructs a new board instance.
     *
     * @param rows The number of rows in the board. Default 5.
     * @param columns The number of columns in the board. Default 6.
     */
    Board(unsigned int const rows = 5, unsigned int const columns = 6) noexcept;

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
    State get_board_state() const noexcept;

    Colour get_current_player() const noexcept;

    /**
     * Prints the board state to STDOUT.
     */
    void pretty_print_board_state() const noexcept;

    /**
     * Places a coin in the board.
     *
     * @param column The column in which the coin is to be placed. Note: Value
     * must be zero indexed.
     *
     * @returns The colour that has won. `Board::Colour::Null` if no one has
     * won.
     *
     * @throws `std::out_of_range` error if provided column value cannot hold
     * any more coins.
     */
    Colour place_coin(unsigned int const column);

   private:
    unsigned int rows;

    unsigned int columns;

    State board_state;

    Colour current_player;

    /**
     * Changes the current player.
     */
    void switch_player() noexcept;

    /**
     * Checks for a winner in the horizontal direction.
     *
     * @param row The row in which the coin was placed.
     * @param column The column in which the coin was placed.
     *
     * @returns `true` if the current player has won.
     */
    bool check_horizontal_direction(unsigned int const row,
                                    unsigned int const column) const noexcept;

    /**
     * Checks for a winner in the vertical direction.
     *
     * @param row The row in which the coin was placed.
     * @param column The column in which the coin was placed.
     *
     * @returns `true` if the current player has won.
     */
    bool check_vertical_direction(unsigned int const row,
                                  unsigned int const column) const noexcept;

    /**
     * Checks for a winner in the ascending diagonal.
     *
     * @param row The row in which the coin was placed.
     * @param column The column in which the coin was placed.
     *
     * @returns `true` if the current player has won.
     */
    bool check_ascending_diagonal(unsigned int const row,
                                  unsigned int const colum) const noexcept;

    /**
     * Checks for a winner in the descending diagonal.
     *
     * @param row The row in which the coin was placed.
     * @param column The column in which the coin was placed.
     *
     * @returns `true` if the current player has won.
     */
    bool check_descending_diagonal(unsigned int const row,
                                   unsigned int const colum) const noexcept;

    /**
     * Checks if the current player has won the game.
     *
     * @param row The row in which the coin was placed.
     * @param column The column in which the coin was placed.
     *
     * @return The current winner. If `Board::Colour::Null`, then no one has won
     * yet.
     *
     * @note Do not change the current player till the function returns.
     */
    Colour check_winner(unsigned int const row,
                        unsigned int const column) const noexcept;
};
