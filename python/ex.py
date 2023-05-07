ch = 'a'
str = "basasababa"
def char_cnt(ch, str):
    x = 0
    for i in len(str):
        if(str[i] == ch):
            x += 1
    print("number of appearances is:", x)

char_cnt(ch, "str")