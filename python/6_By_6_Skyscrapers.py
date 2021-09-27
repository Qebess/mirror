def print_table(table):
    print("-----1-----","  ------2------","  -----3-----")
    for y in range(6):
        for n in range(3):
            for x in range(6):
                print(table[n][x][y],end=" ")
            print(" | ",end="")
        print()
    print("-----4-----","  ------5------","  -----6-----")
    for y in range(6):
        for n in range(3,6):
            for x in range(6):
                print(table[n][x][y],end=" ")
            print(" | ",end="")
        print()


def make_cut(table,n,x,y):
    for xx in range(6):
        table[n][xx][y] = 0
    for yy in range(6):
        table[n][x][yy] = 0
    for nn in range(6):
        table[nn][x][y] = 0

def print_ans_table(ans_table):
    print("-------------")
    for x in range(6):
        for y in range(6):
            print(ans_table[y][x],end =' ')
        print(" |")
#def set_clues()
def scan_by_1(info,table,ans_table):
    d = 0
    for y in range(4):
        for x in range(6):
            if info[y][x] == 1:
                if y == 0:
                    ans_table[d][0] = 6
                    make_cut(table,5,d,0)
                if y == 1:
                    ans_table[5][d-6] = 6
                    make_cut(table,5,5,d-6)
                if y == 2:
                    ans_table[17-d][5] = 6
                    make_cut(table,5,17-d,5)
                if y == 3:
                    ans_table[0][23 - d] = 6
                    make_cut(table,5,0,23-d)
            d+=1

def opponent_sum(info,table,ans_table):
    for y in range(2):
        for x in range(6):
            if info[y][x] + info[y+2][5-x] == 7:
                if y == 0:
                    ans_table[x][info[y][x]-1] = 6
                    make_cut(table,5,x,info[y][x]-1)
                if y == 1:
                    ans_table[6-info[y][x]][x] = 6
                    make_cut(table,5,6-info[y][x],x)

def scan_by_6(info,table,ans_table):
    d = 0
    for y in range(4):
        for x in range(6):
            if info[y][x] == 6:
                if y == 0:
                    for s in range(1,7):
                        ans_table[x][s-1] = s
                        make_cut(table,s-1,x,s-1)
                if y == 1:
                    for s in range(1,7):
                        ans_table[6-s][x] = s
                        make_cut(table,s-1,6-s,x)
                if y == 2:
                    for s in range(1,7):
                        ans_table[5-x][6-s] = s
                        make_cut(table,s-1,5-x,6-s)
                if y == 3:
                    for s in range(1,7):
                        ans_table[s-1][5-x] = s
                        make_cut(table,s-1,s-1,5-x)
def scan_for_once(table,ans_table):
    for n in range(6):
        for y in range(6):
            for x in range(6):
                if table[n][y][x] == 1:
                    table[n][y][x] = 0
                    d = 0
                    for i in range(6):
                        if table[n][i][x] == 1:
                            d+=1
                    if d == 0:
#                       print(" n = ",str(n),"y:x",str(y),str(x))
                        ans_table[y][x] = n+1
                        make_cut(table,n,y,x)
                        break
                    d = 0
                    for i in range(6):
                        if table[n][y][i] == 1:
                            d+=1
                    if d == 0:
#                       print(" n = ",str(n),"y:x",str(y),str(x))
                        ans_table[y][x] = n+1
                        make_cut(table,n,y,x)
                        break
                    table[n][y][x] = 1
def scan_for_2_6(info,table,ans_table):
    d = 0
    for y in range(4):
        for x in range(6):
            if info[y][x] == 2:
                if y == 0:
                    if ans_table[x][5] == 6:
                        ans_table[x][0] = 5
                        make_cut(table,4,x,0)
                elif y == 1:
                    if ans_table[0][x] == 6:
                        ans_table[5][x] = 5
                        make_cut(table,4,5,x)
                elif y == 2:
                    if ans_table[-x-1][0] == 6:
                        ans_table[-x-1][5] = 5
                        make_cut(table,4,-x-1,5)
                elif y == 3:
                    if ans_table[5][-x-1] == 6:
                        ans_table[0][-x-1] = 5
                        make_cut(table,4,0,-x-1)
        d+=1

def rec_0(n,d,x,table):
    if  n>= 1:
        for i in range(n-1):
            table[d][x][i] = 0
        rec_0(n-1,d-1,x,table)

def rec_1(n,d,y,table):
    if n>=1:
        for i in range(n-1):
            table[d][-i-1][y] = 0
        rec_1(n-1,d-1,y,table)

def rec_2(n,d,x,table):
    if n>=1:
        for i in range(n-1):
            table[d][-x-1][-i-1] = 0
        rec_2(n-1,d-1,x,table)

def rec_3(n,d,y,table):
    if n>=1:
        for i in range(n-1):
            table[d][i][-y-1] = 0
        rec_3(n-1,d-1,y,table)

def scan_info_0123(info,table):
    for y in range(4):
        for x in range(6):
            if info[y][x]>1 and info[y][x]<6:
                d = 5
                n = info[y][x]
                if y == 0:
                    rec_0(n,d,x,table)
                if y == 1:
                    rec_1(n,d,x,table)
                if y == 2:
                    rec_2(n,d,x,table)
                if y == 3:
                    rec_3(n,d,x,table)

#def check_lines(info,table,ans_table)
def rec_brute(line,n1,n2,possible_numbers,ans_line,bad_line):
    if 0 in line:
        i = line.index(0)
        line_cpy = line.copy()
        possible_numbers_cpy = [[i for i in j] for j in possible_numbers]
        if len(possible_numbers_cpy[i]) == 0:
#           print("broken!")
#           print(line_cpy)
#           print(possible_numbers_cpy)
#           print("<><><><><><><><><><><><><><><><><><><><><><><>")
            bad_line.append(line_cpy)
            return
        for s in possible_numbers_cpy[i]:
#           print(possible_numbers_cpy)
#           print("s = ",str(s), "i = ", str(i))
            line_cpy[i] = s
#           print(line_cpy)
            possible_numbers_cpy[i] = []
            for k in range(6):
                if s in possible_numbers_cpy[k]:
                    possible_numbers_cpy[k].remove(s)
            l1 = line_cpy.copy()
            pn = [[i for i in j] for j in possible_numbers_cpy]
#           print("==================",str(i),"================")
            rec_brute(l1,n1,n2,pn,ans_line,bad_line)
            line_cpy = line.copy()
            possible_numbers_cpy = [[i for i in j ] for j in possible_numbers]

    else:
#       print("[+] Start of analizing full line...")
#       print(line)
#       print(n1,n2)
        n11 = 0
        n22 = 0
        max  = 0
        if n1 != 0:
            for d in line:
                if max < d:
                    max = d
                    n11 += 1

        max = 0
        if n2 != 0:
            for d in line.__reversed__():
                if max < d:
                    max = d
                    n22 +=1
#       print(n11,n22)
        if (n1 == n11) & (n2 == n22) & (0 not in line):
            ans_line.append(line)
        else:
            bad_line.append(line)
def brute_lines(info,table,ans_table):
    for y in range(2):
        for x in range(6):
#           print("info[y][x]",str(info[y][x]))
#           print((info[y][x]<2) | (info[y][x] == 6))
            if (info[y][x] == 6):
#               print("skipped info [y][x] ", str(info[y][x]))
                continue
            else:
#               print("go")
                ans_line = []
                bad_line = []

                n1 = info[y][x]
                n2 = info[(y+2)%4][-x-1]
                line = [0,0,0,0,0,0]
                possible_numbers = [[] for i in range(6)]
                if y == 0:
                    for i in range(6):
                        line[i] = ans_table[x][i]
                elif y == 1:
                    for i in range(6):
                        line[i] = ans_table[-i-1][x]
            #----------------------------------
                for i in range(6):
                    if y == 0:
                        for n in range(6):
                            if table[n][x][i] == 1:
                                possible_numbers[i].append(n+1)
                    elif y == 1:
                        for n in range(6):
                            if table[n][-i-1][x] == 1:
                                possible_numbers[i].append(n+1)
#               print(n1,n2)
                pn_cpy = [[i for i in j] for j in possible_numbers]
                rec_brute(line,n1,n2,pn_cpy,ans_line,bad_line)
#               print("x = ",str(x))
#               print(possible_numbers)
#               for i in ans_line:
#                   print(">>>>>",end = " ")
#                   print(i)
#               for i in bad_line:
#                   print("-----",end = " ")
#                   print(i)
                if len(ans_line) == 1:
#                   print("are u dumb???")
                    if y == 0:
                        for i in range(6):
                            ans_table[x][i] = ans_line[0][i]
                            make_cut(table,ans_line[0][i]-1,x,i)
                        continue

                    if y == 1:
                        for i in range(6):
                            ans_table[-i-1][x] = ans_line[0][i]
                            make_cut(table,ans_line[0][i]-1,-i-1,x)
                        continue
                for i in range(6):
                    if len(ans_line)>1:
                        num  = ans_line[0][i]
                        flag = 1
                        for j in ans_line:
                            if num != j[i]:
                                flag =0
                                break
                        if flag == 1:
                            if y == 0:
                                ans_table[x][i] = num
                                make_cut(table,num-1,x,i)
                            if y == 1:
                                ans_table[-i-1][x] = num
                                make_cut(table,num-1,-i-1,x)

                for i in range(6):
                    if len(possible_numbers[i]) == 0:
                        continue
                    for k in possible_numbers[i]:
                        have = 0
                        for j in range(len(ans_line)):
                            if k == ans_line[j][i]:
                                have = 1
                                break
                        if have == 0:
                            if y == 0:
                                table[k-1][x][i] = 0
                            if y == 1:
                                table[k-1][-i-1][x] = 0
def solve_puzzle(clues):
    table = [[[1 for i in range(6)] for i in range(6)] for i in range(6)]
    ans_table = [[0 for i in range(6)] for i in range(6)]
    clues = [i for i in clues]
#   print(ans_table)
#   clues = [3,2,2,3,2,1,
#            1,2,3,3,2,2,
#            5,1,2,2,4,3,
#            3,2,1,2,2,4]
#   clues = [0,0,0,0,0,0
#           ,0,0,0,0,0,0,
#            0,0,0,0,0,0,
#            0,2,3,4,5,0]
#   clues = [4,2,1,3,2,2,
#            3,4,3,1,4,2,
#            2,1,3,4,3,2,
#            2,1,2,3,2,2]
#==================
    info = [[0 for i in range(6)] for i in range(4)]
    d = 0
    for x in range(4):
        for y in range(6):
#           print("x =",str(x))
#           print("y =",str(y))
            info[x][y] = clues[d]
            d+=1
#==================
#   for i in range(4):
#       for j in range(6):
#           print(str(info[i][j]),end=" ")
#       print()

    scan_by_1(info,table,ans_table)
    opponent_sum(info,table,ans_table)
    scan_by_6(info,table,ans_table)
    scan_for_2_6(info,table,ans_table)
    scan_info_0123(info,table)
    scan_for_once(table,ans_table)

    print_ans_table(ans_table)
    print_table(table)
    d = 1
    while d:
        d = 0
        brute_lines(info,table,ans_table)
        scan_for_once(table,ans_table)
        for i in ans_table:
            if 0 in i:
                d = 1
        print_ans_table(ans_table)
        print_table(table)

#   print_ans_table(ans_table)
    ans_tt =[[0 for i in range(6)] for j in range(6)]
    for i in range(6):
        for j in range(6):
            ans_tt[i][j] = ans_table[j][i]
    ans = tuple(tuple(i) for i in ans_tt)
#   print(ans)
    return ans


