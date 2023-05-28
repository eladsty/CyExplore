from collections import Counter  # counter
import re  # search

""" 
/* Status : Approved
 * Reviewer : Nevo
 * Description : this function takes a string and a character and returns the 
 * number of appearances of such character in such string.
 * Arguments : string, char.
 * Return : number of times char is in string.
 * Time Complexity : O(1)
 * comments : I tried 3 different methods
 */
"""


def count_char1(string, char):
    counter = 0
    for i in string:
        if i == char:
            counter = counter + 1
    print("counted the letter" + " '" + str(char) + "' " + str(counter) + " " + "times")
    return counter


def count_char2(string, char):
    counter = string.count(char)
    print("counted the letter" + " '" + str(char) + "' " + str(counter) + " " + "times")
    return counter


def count_char3(string, char):
    counter = Counter(string)
    print("counted the letter" + " '" + str(char) + "' " + str(counter[char]) + " " + "times")
    return counter


""" 
/* Status : Approved
 * Reviewer : Nevo
 * Description : receive an int input from user and flips its digits
 * Arguments : void
 * Return : flipped int
 * Time Complexity : O(n)
 * Space Complexity :
 */
"""


def mirror_num():
    num = int(input("Enter a number>>"))
    new_num = 0
    while num:
        remainder = num % 10
        new_num = new_num*10 + remainder
        num //= 10
    return new_num


""" 
/* Status : Approved
 * Reviewer : Nevo
 * Description :  receive an string input from user and flips its digits
 * Arguments : void
 * Return : works on all types of inputs
 * Time Complexity : O(n)
 * Space Complexity :
 */
"""


def mirror_string():
    num = str(input("Enter a number>>"))
    new_num = str(num)[::-1]
    if type(num) == float:
        new_num = float(num)
    elif type(num) == int:
        new_num = int(num)
    return new_num


""" 
/* Status : Approved
 * Reviewer : Nevo
 * Description :  converts celsius_to_fahrenheit
 * Arguments : void
 * Return : temp in F
 * Time Complexity : O(1)
 * Space Complexity :
 */
"""


def celsius_to_fahrenheit():
    temp = float(input("How hot is it right now outside the USA?>>"))
    temp = temp*(9/5) + 32
    return temp


""" 
/* Status : Approved
 * Reviewer : Nevo
 * Description :  check if a year was a leap year
 * Arguments : void
 * Return : true or false
 * Time Complexity : O(1)
 * Space Complexity :
 */
"""


def is_leap_year():
    year = int(input("Enter a year>>"))
    return 0 == year % 4 and (0 == year % 400 or 0 != year % 100)


""" 
/* Status : Approved
 * Reviewer : Nevo
 * Description : check if a password is valid
 * Arguments : void
 * Return : true or false
 * Time Complexity : O(1)
 * Space Complexity :
 */
"""


def pass_complexity1():
    password = str(input("your password>>"))
    temp = 0
    if password.isupper and password.isupper and password.isdigit and 8 <= len(password) and ('@' in password or '#' in password or '%' in password or '&' in password):
        return 0
    return 1


def pass_complexity2():
    password = str(input("your password>>"))
    strength = re.compile('[a-zA-Z0-9@#%&]')
    if strength.search(password) and len(password) >= 8:
        return 0
    return 1


""" 
/* Status : Approved
 * Reviewer : Nevo
 * Description :  calculate sum of divisors
 * Arguments : integer
 * Return : sum of its divisors
 * Time Complexity : O(n)
 * Space Complexity :
 */
"""


def sum_of_divisors(number):
    sum_of = 0
    for i in range(1, (number + 1)):
        if 0 == number % i:
            sum_of += i
    return sum_of


""" 
/* Status : Approved
 * Reviewer : Nevo
 * Description :  finds minimum amount of currency elements to make an amount 
                    of money
 * Arguments : amount of money
 * Return : amount of currency elements to make an amount of money
 * Time Complexity : O(n)
 * Space Complexity :
 */
"""


def min_monetized(money):
    notes = [200, 100, 50, 20, 10, 5, 1]
    ret = 0
    for i in notes:
        if money >= i:
            ret += money // i
            money %= i
    return ret


""" 
/* Status : Approved
 * Reviewer : Nevo
 * Description : if a number is prime
 * Arguments : a number
 * Return : if its prime, true. else false
 * Time Complexity : O(n) 
 * Space Complexity :
 */
"""


def is_prime(num):
    if sum_of_divisors(num) == num + 1:
        return 0
    return 1





if __name__ == '__main__':
    count_char1('history has its eyes on you', 's')
    count_char2('what\'s the hurry', 's')
    count_char3('utensils', 'w')
    print(is_prime(-3))
    print(min_monetized(64))
    print(sum_of_divisors(103))

    print(pass_complexity1())
    print(pass_complexity2())
    print(is_leap_year())
    print(is_leap_year())
    print(mirror_num())
    print(celsius_to_fahrenheit())


