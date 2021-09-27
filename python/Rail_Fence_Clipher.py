def encode_rail_fence_cipher(string, n):
    string = list(string)
    step = (n-1)*2
    ans = string[::step]
    end_ans = string[n-1::step]
    for i in range(1,n-1):
        line_left = string[i::step]
        line_right = string[step-i::step]
        for j in range(len(line_right)):
            ans += line_left[j]
            ans += line_right[j]
        if len(line_left)>len(line_right):
            ans += line_left[-1]
    ans += end_ans

    string = ""
    for i in ans:
        string+=i
    return string



def decode_rail_fence_cipher(string, n):
    string = list(string)

    ans = ["" for i in string]
    ln = len(string)
    step =  (n-1)*2
    print()
    top  = (ln + step-1)// step
    bot = (ln+step//2-1)//step
    for i in range(0,top):
        ans[i*step]=string[i]
    for (j,i) in enumerate(range(len(string)-bot,len(string))):
        ans[n-1 + j*step] = string[i]


    ln -= (top+bot)
    ln_tiers =[]
    for i in range(n-2):
        ln_tiers.append((ln+i)//(n-2))
    if top>bot:
        ln_tiers.reverse()
    tiers = []
    midle = ""
    for i in range(top,len(string)-bot):
        midle +=string[i]

    sum = 0
    for i in ln_tiers:
        tiers.append(midle[sum:sum+i:])
        sum+=i
    y = 0
    if len(ln_tiers)== 0:
        string = ""
        for i in ans:
            string += i
        return string

    for x in range(max(ln_tiers)):
        if y == 0:
            for i in range(n-2):
                y=i
                if x > ln_tiers[i]:
                    continue
                for k in range(len(ans)):
                    if ans[k] =="":
                        ans[k] = tiers[y][x]
                        break
        else:
            for i in range(n-2).__reversed__():
                y=i
                if x > ln_tiers[i]:
                    continue
                for k in range(len(ans)):
                    if ans[k] =="":
                        ans[k] = tiers[y][x]
                        break
    string =""
    for i in ans:
        string+=i
    return string
