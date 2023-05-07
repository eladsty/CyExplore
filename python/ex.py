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

def is_leap(year):
    if (year % 400 == 0) or (year % 100 != 0) and (year % 4 == 0):
        return 1
    else:
        return 0
    
x = is_leap(1500)
print(x)   
x = is_leap(1616)
print(x)    
x = is_leap(1000)
print(x)


""" EX5 """

def check_pwd(password):
     cond1=0
     cond2=0
     cond3=0
     cond4=0

     if len(password) < 8:
         return False

     for l in password:
         if l in '[A-Z]':
             cond1 = 1
         if l in '[a-z]':
             cond2 = 1
         if ( ord(l) in range(ord('0'), ord('9')) ):
             cond3 = 1
         if l == '@' or l == '#' or l == '&' or l == '%':
             cond4 = 1

     if cond1+cond2+cond3+cond4 > 3:
         return True
     else:
         return False


print(check_pwd("283fF9a8j%"))
print(check_pwd("dq#Sf"))

""" EX6 """

def dev_sum(num):
    sum = 0
    for i in range(2, num - 1):
        if (0 == (num % i)):
            sum += i
    return sum + 1 + num

 
print(dev_sum(3))


""" EX7 """

def min_curr(money):
    curr_devision = [200, 100, 50, 20, 10, 5, 2, 1]
    i = 0
    while (0 != money):
        res = (money // curr_devision[i])
        if (0 < res * curr_devision[i]):
            print(res, " bills of ", curr_devision[i])
            money -= (res * curr_devision[i])
            i += 1
        else:
            i += 1

min_curr(414)
min_curr(100)
min_curr(0)

""" EX8 """

def prime(num):
    if(1 >= num):
        return False
    res = dev_sum(num)
    if (res == (num + 1)):
        return True
    else:
        return False
    
print(prime(2))
print(prime(3))
print(prime(22))
 
