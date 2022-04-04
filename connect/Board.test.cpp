#include <gtest/gtest.h>

#include <connect/Board.hpp>
#include <stdexcept>
#include <vector>

TEST(BoardTest, CreateBoard) {
    Board board;
    Board::State expected_state = {
        {Board::Colour::Null, Board::Colour::Null, Board::Colour::Null,
         Board::Colour::Null, Board::Colour::Null, Board::Colour::Null},

        {Board::Colour::Null, Board::Colour::Null, Board::Colour::Null,
         Board::Colour::Null, Board::Colour::Null, Board::Colour::Null},

        {Board::Colour::Null, Board::Colour::Null, Board::Colour::Null,
         Board::Colour::Null, Board::Colour::Null, Board::Colour::Null},

        {Board::Colour::Null, Board::Colour::Null, Board::Colour::Null,
         Board::Colour::Null, Board::Colour::Null, Board::Colour::Null},

        {Board::Colour::Null, Board::Colour::Null, Board::Colour::Null,
         Board::Colour::Null, Board::Colour::Null, Board::Colour::Null},
    };

    ASSERT_EQ(board.get_board_state(), expected_state);
    ASSERT_EQ(board.get_current_player(), Board::Colour::Yellow);
}

TEST(BoardTest, PlayMove) {
    Board board;

    // Place a coin in the last column
    Board::Colour winner = board.place_coin(5);
    Board::State expected_state = {
        {Board::Colour::Null, Board::Colour::Null, Board::Colour::Null,
         Board::Colour::Null, Board::Colour::Null, Board::Colour::Null},

        {Board::Colour::Null, Board::Colour::Null, Board::Colour::Null,
         Board::Colour::Null, Board::Colour::Null, Board::Colour::Null},

        {Board::Colour::Null, Board::Colour::Null, Board::Colour::Null,
         Board::Colour::Null, Board::Colour::Null, Board::Colour::Null},

        {Board::Colour::Null, Board::Colour::Null, Board::Colour::Null,
         Board::Colour::Null, Board::Colour::Null, Board::Colour::Null},

        {Board::Colour::Null, Board::Colour::Null, Board::Colour::Null,
         Board::Colour::Null, Board::Colour::Null, Board::Colour::Yellow},
    };

    ASSERT_EQ(board.get_board_state(), expected_state);
    ASSERT_EQ(board.get_current_player(), Board::Colour::Red);
    ASSERT_EQ(winner, Board::Colour::Null);
}

TEST(BoardTest, Play2Moves) {
    Board board;

    board.place_coin(0);
    Board::Colour winnner = board.place_coin(0);
    Board::State expected_state = {
        {Board::Colour::Null, Board::Colour::Null, Board::Colour::Null,
         Board::Colour::Null, Board::Colour::Null, Board::Colour::Null},

        {Board::Colour::Null, Board::Colour::Null, Board::Colour::Null,
         Board::Colour::Null, Board::Colour::Null, Board::Colour::Null},

        {Board::Colour::Null, Board::Colour::Null, Board::Colour::Null,
         Board::Colour::Null, Board::Colour::Null, Board::Colour::Null},

        {Board::Colour::Red, Board::Colour::Null, Board::Colour::Null,
         Board::Colour::Null, Board::Colour::Null, Board::Colour::Null},

        {Board::Colour::Yellow, Board::Colour::Null, Board::Colour::Null,
         Board::Colour::Null, Board::Colour::Null, Board::Colour::Null},
    };

    ASSERT_EQ(board.get_board_state(), expected_state);
    ASSERT_EQ(winnner, Board::Colour::Null);
    ASSERT_EQ(board.get_current_player(), Board::Colour::Yellow);
}

TEST(BoardTest, CheckOverflow) {
    Board board;

    board.place_coin(0);
    board.place_coin(0);
    board.place_coin(0);
    board.place_coin(0);
    board.place_coin(0);

    ASSERT_THROW(board.place_coin(0), std::out_of_range);
}

TEST(BoardTest, CheckHorizontalWin) {
    Board board;

    Board::Colour winner = board.place_coin(0);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(0);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(1);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(1);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(2);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(2);
    ASSERT_EQ(winner, Board::Colour::Null);

    winner = board.place_coin(3);
    ASSERT_EQ(winner, Board::Colour::Yellow);
}

TEST(BoardTest, CheckVerticalWin) {
    Board board;

    Board::Colour winner = board.place_coin(0);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(1);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(0);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(1);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(0);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(1);
    ASSERT_EQ(winner, Board::Colour::Null);

    winner = board.place_coin(0);
    ASSERT_EQ(winner, Board::Colour::Yellow);
}

TEST(BoardTest, CheckAscendingDiagonalWin) {
    Board board;

    Board::Colour winner = board.place_coin(0);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(1);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(1);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(2);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(3);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(2);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(2);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(3);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(4);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(3);
    ASSERT_EQ(winner, Board::Colour::Null);

    winner = board.place_coin(3);
    ASSERT_EQ(winner, Board::Colour::Yellow);
}

TEST(BoardTest, CheckDescendingDiagonalWin) {
    Board board;

    Board::Colour winner = board.place_coin(5);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(4);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(4);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(3);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(2);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(3);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(3);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(2);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(1);
    ASSERT_EQ(winner, Board::Colour::Null);
    winner = board.place_coin(2);
    ASSERT_EQ(winner, Board::Colour::Null);

    winner = board.place_coin(2);
    ASSERT_EQ(winner, Board::Colour::Yellow);
}
