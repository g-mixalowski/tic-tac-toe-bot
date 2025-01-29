#include <pybind11/pybind11.h>
#include "game.hpp"

namespace py = pybind11;

PYBIND11_MODULE(game, m) {
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