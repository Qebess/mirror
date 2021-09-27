class User:
    def __init__(self):
        self.rank = -8
        self.progress = 0
        self.honor = [i for i in range(-8, 9) if i != 0]

    def inc_progress(self, kata_lvl):
        index_kata = self.honor.index(kata_lvl)
        index_rank = self.honor.index(self.rank)
        if self.rank == 8:
            return None
        if index_kata > index_rank:
            d = index_kata - index_rank
            self.progress += 10 * d * d
        elif index_kata == index_rank:
            self.progress += 3
        elif index_rank > index_kata:
            d = index_rank - index_kata
            if d == 1:
                self.progress += 1

        if self.progress >= 100:
            i = self.progress // 100
            if index_rank + i < len(self.honor):
                self.rank = self.honor[index_rank + i]
                self.progress %= 100
                if self.rank == 8:
                    self.progress = 0
            else:
                self.rank = 8
                self.progress = 0

