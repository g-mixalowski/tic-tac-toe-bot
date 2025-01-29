import tictactoe

g = tictactoe.Game(10, 10, 5)
print(g.is_over())
print(g.winner())
g.next_move(0, 0)
print(g.cell(0, 0))