#ifndef GAME_HPP_
#define GAME_HPP_

#include <vector>
#include "game.hpp"

namespace tictactoe {

enum class OptionalPlayer { X, O, NOTHING };

class Game {
public:
    Game() {
    }

    Game(int rows, int columns, int winstreak)
        : rows_(rows), columns_(columns), winstreak_(winstreak) {
        field_ = std::vector<std::vector<OptionalPlayer>>(
            rows_,
            std::vector<OptionalPlayer>(columns_, OptionalPlayer::NOTHING)
        );
    }

    [[nodiscard]] bool next_move(int row, int column);

    [[nodiscard]] OptionalPlayer current_move() const {
        return current_move_;
    }

    [[nodiscard]] bool is_over() const {
        return has_draw_ || winner_ != OptionalPlayer::NOTHING;
    }

    [[nodiscard]] bool has_draw() const {
        return has_draw_;
    }

    [[nodiscard]] OptionalPlayer winner() const {
        return winner_;
    }

    [[nodiscard]] OptionalPlayer cell(const int row, const int column) const {
        return field_[row][column];
    }

private:
    void check_winner(int row, int column);

    [[nodiscard]] bool is_valid_cell(const int row, const int column) {
        return 0 <= row && row < rows_ && 0 <= column && column < columns_;
    }

    std::vector<std::vector<OptionalPlayer>> field_ =
        std::vector<std::vector<OptionalPlayer>>(
            rows_,
            std::vector<OptionalPlayer>(columns_, OptionalPlayer::NOTHING)
        );
    OptionalPlayer current_move_ = OptionalPlayer::O;
    OptionalPlayer next_move_ = OptionalPlayer::X;
    OptionalPlayer winner_ = OptionalPlayer::NOTHING;
    bool has_draw_ = false;
    int total_moves_ = 0;
    int rows_ = 10;
    int columns_ = 10;
    int winstreak_ = 5;
};

}  // namespace tictactoe

#endif  // GAME_HPP
