import random
import numpy as np

class Board:
    def __init__(self, n):
        self.n_queen = n
        self.map = [[0 for j in range(n)] for i in range(n)]
        self.fit = 0
        self.nfit = 0
        self.maxfit = (self.n_queen * (self.n_queen - 1)) / 2

        for i in range(self.n_queen):
            j = random.randint(0, self.n_queen - 1)
            self.map[i][j] = 1

    def fitness(self):
        for i in range(self.n_queen):
            for j in range(self.n_queen):
                if self.map[i][j] == 1:
                    for k in range(1, self.n_queen - i):
                        if self.map[i + k][j] == 1:
                            self.fit += 1
                        if j - k >= 0 and self.map[i + k][j - k] == 1:
                            self.fit += 1
                        if j + k < self.n_queen and self.map[i + k][j + k] == 1:
                            self.fit += 1

    def nfitness(self):
        self.set_nfit(self.maxfit)
        for i in range(self.n_queen):
            for j in range(self.n_queen):
                if self.map[i][j] == 1:
                    for k in range(1, self.n_queen - i):
                        if self.map[i + k][j] == 1:
                            self.nfit -= 1
                        if j - k >= 0 and self.map[i + k][j - k] == 1:
                            self.nfit -= 1
                        if j + k < self.n_queen and self.map[i + k][j + k] == 1:
                            self.nfit -= 1

    def show(self):
        print(np.matrix(self.map))
        print("Fitness: ", self.fit)

    def flip(self, i, j):
        if self.map[i][j] == 0:
            self.map[i][j] = 1
        else:
            self.map[i][j] = 0

    def set_map(self, m):
        self.map = m

    def get_map(self):
        return self.map

    def set_fit(self, f):
        self.fit = f

    def get_fit(self):
        return self.fit

    def set_nfit(self, f):
        self.nfit = f

    def get_nfit(self):
        return self.nfit


if __name__ == '__main__':
    test = Board(5)
    test.fitness()
    test.show()