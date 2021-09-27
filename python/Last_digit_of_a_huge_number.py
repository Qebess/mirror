def last_digit(lst):
    if len(lst)==0:
        return 1
    lst.reverse()
    print(lst)
    for i in range(len(lst)):
        lst[i] = lst[i]%1000
    print(lst)

    for i in range(len(lst)-1):
        d= lst[i+1]**lst[i]
        lst[i+1]  = d %1000
        if d>=100 and d%100 == 0 :lst[i+1]=100
    print(lst)
    return lst[-1]%10

