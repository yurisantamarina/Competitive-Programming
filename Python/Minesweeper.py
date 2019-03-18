import random

MINE = -2
EMPTY = -1
OCCUPIED = 1
OUT = -3
TAX = 10
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]

class Minesweeper:
    def set_mines(self):
        number_of_mines = (self.n ** 2 * TAX) // 100
        self.mines = {}
        for i in range(number_of_mines):
            while True:
                x = random.randint(0, self.n - 1)
                y = random.randint(0, self.n - 1)
                print(x, y)
                if self.board[x][y] == EMPTY:
                    break
            self.board[x][y] = MINE

    def __init__(self, n):
        self.n = n;
        self.board = [0] * n
        for i in range(n):
            self.board[i] = [EMPTY] * n

        self.set_mines()

   
    def change(self, c):
        if c >= 0:
            return str(c)
        return '.'
    
    def __str__(self):
        ans = " " + "".join([str(i) for i in range(self.n)]) + "\n"
        for i in range(self.n):
            ans += (str(i))
            ans += "".join(list(map(self.change, self.board[i])))
            ans += (str(i) + "\n")
        ans += " " + "".join([str(i) for i in range(self.n)]) + "\n"
        return ans

    def inside_board(self, x, y):
        return x >= 0 and x < self.n and y >= 0 and y < self.n
    
    def fill(self, x, y):
        cnt = 0
        for i in range(len(dx)):
            if self.inside_board(x + dx[i], y + dy[i]) and self.board[x + dx[i]][y + dy[i]] == MINE:
                cnt += 1
        return cnt

    def attack(self, x, y):
        if not self.inside_board(x, y):
            return [OUT, "Posição fora do tabuleiro"]
        if self.board[x][y] == MINE:
            return [MINE, "MORREU!!"]
        if self.board[x][y] == EMPTY:
            self.board[x][y] = self.fill(x, y)
            return [EMPTY, "Posição atacada com sucesso!!"]
        return [OCCUPIED, "Voce já atacou essa posição"]
        

n = int(input("Tamanho da matriz (N x N): "))
mine = Minesweeper(n)

print(mine)
while True:
    lin = [int(i) for i in input("Digite uma posicao (X, Y): ").split()]
    [flag, message] = mine.attack(lin[0], lin[1])
    print(message)
    if flag == MINE:
        break
    print(mine)
