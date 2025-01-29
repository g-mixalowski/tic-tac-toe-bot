#include "game.hpp"
#include <array>
#include "game.hpp"
#include <pybind11/pybind11.h>
#include "game.hpp"

namespace py = pybind11;

PYBIND11_MODULE(tictactoe, m) {
    py::class_<tictactoe::Game> game(m, "Game");
    
    game.def(py::init<int, int, int>())
        .def("next_move", &tictactoe::Game::next_move, "make next move", py::arg("row"), py::arg("column"))
        .def("current_move", &tictactoe::Game::current_move)
        .def("is_over", &tictactoe::Game::is_over)
        .def("has_draw", &tictactoe::Game::has_draw)
        .def("winner", &tictactoe::Game::winner)
        .def("cell", &tictactoe::Game::cell, "show cell content", py::arg("row"), py::arg("column"));

    py::enum_<tictactoe::OptionalPlayer>(game, "OptionalPlayer")
        .value("X", tictactoe::OptionalPlayer::X)
        .value("O", tictactoe::OptionalPlayer::O)
        .value("NOTHING", tictactoe::OptionalPlayer::NOTHING);
        
}

namespace tictactoe {

bool Game::next_move(const int row, const int column) {
    if (is_valid_cell(row, column) &&
        field_[row][column] == OptionalPlayer::NOTHING) {
        field_[row][column] = current_move_;
        ++total_moves_;
        check_winner(row, column);
        std::swap(current_move_, next_move_);
        return true;
    }
    return false;
}

void Game::check_winner(const int checked_row, const int checked_column) {
    static constexpr std::array<std::pair<int, int>, 4> directions{
        std::pair{0, 1}, std::pair{1, 0}, std::pair{1, 1}, std::pair{-1, 1}};
    for (auto [row_dir, col_dir] : directions) {
        int value = 0;
        int row = checked_row - (winstreak_ - 1) * row_dir;
        int col = checked_column - (winstreak_ - 1) * col_dir;
        for (int step = 0; step < winstreak_ * 2 - 1; ++step) {
            if (is_valid_cell(row, col)) {
                value = (field_[row][col] == current_move_ ? value + 1 : 0);
                winner_ = (value == winstreak_ ? current_move_ : winner_);
            }
            row += row_dir;
            col += col_dir;
        }
    }
    has_draw_ =
        (total_moves_ >= rows_ * columns_ && winner_ == OptionalPlayer::NOTHING);
}

}  // namespace tictactoe
