def snail(snail_map):
    if len(snail_map[0]) == 0:
        return []
    ans = []
    for i in range(len(snail_map)):
        ans.append(snail_map[0][i])
    turn = 1
    line = len(snail_map)
    x = line-1
    y = 0
    while  line != 1:
        line -= 1
        if turn == 1:
            for i in range(1,line+1):
                ans.append(snail_map[y+i][x])
            y = y + line
            for i in range(1,line+1):
                ans.append(snail_map[y][x-i])
            x = x- line
            turn = 0
        else:
            for i in range(1,line+1):
                ans.append(snail_map[y-i][x])
            y = y -line
            for i  in range(1,line+1):
                ans.append(snail_map[y][x+i])
            x = x +line
            turn =1
    return ans