def not_solved(puzzle):
    for i in puzzle:
        for j in i :
            if j == 0:
                return True
    return False

def color_square(i,j,number,table):
    if 0<=i<=2 and 0<=j<=2:
        for y in range(3):
            for x in  range(3):
                table[number-1][y][x] = 0
    #==============================================
    elif 0<=i<=2 and 3<=j<=5:
        for y in range(3):
            for x in range(3,6):
                table[number-1][y][x] = 0
    elif 0<=i<=2 and 6<=j<=8:
        for y in range(3):
            for x in range(6,9):
                table[number-1][y][x] =0
    #==============================================
    if 3 <= i <= 5 and 0 <= j <= 2:
        for y in range(3,6):
            for x in range(3):
                table[number - 1][y][x] = 0
    elif 3 <= i <= 5 and 3 <= j <= 5:
        for y in range(3,6):
            for x in range(3, 6):
                table[number - 1][y][x] = 0
    elif 3 <= i <= 5 and 6 <= j <= 8:
        for y in range(3,6):
            for x in range(6, 9):
                table[number - 1][y][x] = 0
    #==============================================
    if 6 <= i <= 8 and 0 <= j <= 2:
        for y in range(6,9):
            for x in range(3):
                table[number - 1][y][x] = 0
    elif 6 <= i <= 8 and 3 <= j <= 5:
        for y in range(6,9):
            for x in range(3, 6):
                table[number - 1][y][x] = 0
    elif 6 <= i <= 8 and 6 <= j <= 8:
        for y in range(6,9):
            for x in range(6, 9):
                table[number - 1][y][x] = 0




def sudoku(puzzle):
    table = [[[1 for i in range(9)] for i in range(9)] for  i in range(9)]
    for i in range(9):
        for j in range(9):
            if puzzle[i][j] != 0:
                for k in range(9):
                    table[k][i][j] = 0
                    table[puzzle[i][j] - 1][i][k] = 0
                    table[puzzle[i][j] - 1][k][j] = 0
                    color_square(i,j,puzzle[i][j],table)
    while not_solved(puzzle):
        for i in range(9):
            for y in range(9):
                if table[i][y].count(1) == 1:
                    x = table[i][y].index(1)
                    puzzle[y][x] = i+1
                    for k in range(9):
                        table[k][y][x] = 0
                        table[i][y][k] = 0
                        table[i][k][x] = 0
                        color_square(y, x, i+1, table)
            for x in range(9):
                count = 0
                for b in range(9):
                    if table[i][b][x] == 1:
                        count+=1
                        y = b
                if count ==1:
                    puzzle[y][x] = i+1
                    for k in range(9):
                        table[k][y][x] = 0
                        table[i][y][k] = 0
                        table[i][k][x] = 0
                        color_square(y, x, i+1, table)
            #==========================================1
            count = 0
            for a in range(3):
                for b in range(3):
                    if table[i][a][b] == 1:
                        count +=1
                        y = a
                        x = b
            if count == 1:
                puzzle[y][x] = i + 1
                for k in range(9):
                    table[k][y][x] = 0
                    table[i][y][k] = 0
                    table[i][k][x] = 0
                    color_square(y, x, i + 1, table)
            # ==========================================2
            count = 0
            for a in range(3):
                for b in range(3,6):
                    if table[i][a][b] == 1:
                        count += 1
                        y = a
                        x = b
            if count == 1:
                puzzle[y][x] = i + 1
                for k in range(9):
                    table[k][y][x] = 0
                    table[i][y][k] = 0
                    table[i][k][x] = 0
                    color_square(y, x, i + 1, table)
            # ==========================================3
            count = 0
            for a in range(3):
                for b in range(6,9):
                    if table[i][a][b] == 1:
                        count += 1
                        y = a
                        x = b
            if count == 1:
                puzzle[y][x] = i + 1
                for k in range(9):
                    table[k][y][x] = 0
                    table[i][y][k] = 0
                    table[i][k][x] = 0
                    color_square(y, x, i + 1, table)
            # ==========================================4
            count = 0
            for a in range(3,6):
                for b in range(3):
                    if table[i][a][b] == 1:
                        count += 1
                        y = a
                        x = b
            if count == 1:
                puzzle[y][x] = i + 1
                for k in range(9):
                    table[k][y][x] = 0
                    table[i][y][k] = 0
                    table[i][k][x] = 0
                    color_square(y, x, i + 1, table)
            # ==========================================5
            count = 0
            for a in range(3,6):
                for b in range(3,6):
                    if table[i][a][b] == 1:
                        count += 1
                        y = a
                        x = b
            if count == 1:
                puzzle[y][x] = i + 1
                for k in range(9):
                    table[k][y][x] = 0
                    table[i][y][k] = 0
                    table[i][k][x] = 0
                    color_square(y, x, i + 1, table)
            # ==========================================6
            count = 0
            for a in range(3,6):
                for b in range(6,9):
                    if table[i][a][b] == 1:
                        count += 1
                        y = a
                        x = b
            if count == 1:
                puzzle[y][x] = i + 1
                for k in range(9):
                    table[k][y][x] = 0
                    table[i][y][k] = 0
                    table[i][k][x] = 0
                    color_square(y, x, i + 1, table)
            # ==========================================7
            count = 0
            for a in range(6,9):
                for b in range(3):
                    if table[i][a][b] == 1:
                        count += 1
                        y = a
                        x = b
            if count == 1:
                puzzle[y][x] = i + 1
                for k in range(9):
                    table[k][y][x] = 0
                    table[i][y][k] = 0
                    table[i][k][x] = 0
                    color_square(y, x, i + 1, table)
            # ==========================================8
            count = 0
            for a in range(6,9):
                for b in range(3,6):
                    if table[i][a][b] == 1:
                        count += 1
                        y = a
                        x = b
            if count == 1:
                puzzle[y][x] = i + 1
                for k in range(9):
                    table[k][y][x] = 0
                    table[i][y][k] = 0
                    table[i][k][x] = 0
                    color_square(y, x, i + 1, table)
            # ==========================================9
            count = 0
            for a in range(6,9):
                for b in range(6,9):
                    if table[i][a][b] == 1:
                        count += 1
                        y = a
                        x = b
            if count == 1:
                puzzle[y][x] = i + 1
                for k in range(9):
                    table[k][y][x] = 0
                    table[i][y][k] = 0
                    table[i][k][x] = 0
                    color_square(y, x, i + 1, table)


    return puzzle