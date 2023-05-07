import sys

""" EX1 """

def char_cnt(ch, str):
    x = 0
    for i in str:
        if i == ch:
            x += 1
    return x

ch = "a"
str = "basasababa"
k = char_cnt(ch, str)
print(k)
""" print(sys.getrefcount(k))
 """


""" EX2 """
def flip_num(num):
    rev_num = 0
    flag = 1
    if num < 0:
        num *= -1
        flag = -1
    while num != 0:
        digit = num % 10
        rev_num = rev_num * 10 + digit
        num //= 10
    return rev_num * flag

flipped = flip_num(-1234)
print(flipped)


""" EX3 """

def cel_fer(deg):
    fer = deg * 1.8 + 32
    return fer

fer = cel_fer(180)
print(fer)


""" EX4 """

def Is_Leap(year):
    if (year % 400 == 0) or (year % 100 != 0) and (year % 4 == 0):
        return 1
    else:
        return 0
    
x = Is_Leap(1500)
print(x)   
x = Is_Leap(1616)
print(x)    
x = Is_Leap(1000)
print(x)


""" EX5 """

def IsComplexed(pwd):
    nums = set('0123456789$,')
    spec = set('@#%&$, ')
    upper = set('ABCDEFGHIJKLMNOPQRSTUVWXYZ$,')
    lower = set('abcdefghijklmnopqrstuvwxyz$,')

    if (len(pwd > 7) and (any(c in nums) for c in pwd) and any(c in spec) for c in pwd) and any((c in lower) for c in pwd) and any((c in upper) for c in pwd):
    print('Found').


else:
    print('Not Found')


    if(len(pwd) < 8):
        return 0
    if ('0') or ('1') or ('2') or ('3') or ('4') or ('5') in pwd:

