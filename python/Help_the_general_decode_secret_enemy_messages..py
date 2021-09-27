from string import punctuation
def decode(s):
    #" ,.?"
    punct = punctuation
    list_punct = [i for i in punct if i not in (" ",".",",","?")]
    decoded_s = ""
    code_base = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,? "
    count = 1
    for letter in s:
        value  = {}
        if letter not in list_punct:
            for k in code_base:
                    pos= ((code_base.index(k)+1)*int(pow(2,count))-1) %67
                    value[code_base[pos]] = k
            decoded_s+=value[letter]
        else:
            decoded_s+=letter
        count +=1
    return decoded_s;