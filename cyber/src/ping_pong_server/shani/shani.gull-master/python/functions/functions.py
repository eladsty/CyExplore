import sys
import os
from functools import reduce
import math

"""
/* Status : imple teasted
 * Reviewer :
 * Description : removes from a given list all words containing only
                lowercase letters.
 * Arguments : a list of strings
 * Return : void
 * Time Complexity : O(n)
 * comments :
 */
"""


def ex1(arg):
    return filter(lambda string: string.islower(), arg)



#x = lambda a: filter(function=(i for i in a if i.islower()), iterable=arg)
#print(x(['SHANI', 'shani', 'MICHAEL', 'michael', 'ShAnI']))

"""
/* Status : imple teasted
 * Reviewer :
 * Description : sort an array of numbers(strings)
 * Arguments : a list of numbers(strings)
 * Return : void
 * Time Complexity : O(n)
 * comments :
 */
"""


def ex2(arg):
    arg.sort(reverse=False, key=lambda a: int(a))


"""
/* Status : imple tested
 * Reviewer :
 * Description : sums up all list elements
 * Arguments : list on ints
 * Return : void
 * Time Complexity : O(n)
 * comments :
 */
"""


def ex3(arg):
    positive = [i for i in arg if i > 0]
    negative = [i for i in arg if i < 0]
    print("sum of positive is >> " + str(reduce(lambda a, b: a + b, positive)))
    print("sum of negative is >> " + str(reduce(lambda a, b: a + b, negative)))


    """print(sum(filter(lambda a: a > 0, arg)))
    print(sum(filter(lambda a: a < 0, arg)))"""



"""
/* Status : imple tested
 * Reviewer :
 * Description : returns a list of all even numbers from a given list 
 * Arguments : list of ints
 * Return : list of even elements from given list
 * Time Complexity : O(n)
 * comments :
 */
"""


def ex4(arg):
    return [pow(i, 2) for i in arg if 0 == i % 2]


"""
/* Status : imple tested
 * Reviewer :
 * Description : takes dictionary of products and prices and cut all prices by 
                    10%
 * Arguments : dict
 * Return : void
 * Time Complexity : O(n)
 * comments :
 */
"""


def ex5(arg):
    for k, v in arg.items():
        arg[k] = v / 10


"""
/* Status : imple tested
 * Reviewer :
 * Description : sum the gimatric value of a string in hebrew
 * Arguments : 
 * Return : void
 * Time Complexity : O(n)
 * comments :
 */
"""


def ex6(arg):
    sum_of = 0
    alphabet = {"א": 1, "ב": 2, "ג": 3, "ד": 4, "ה": 5,
                  'ו': 6, "ז": 7, "ח": 8, "ט": 9, "י": 10, "כ": 20, "ל": 30, "מ": 40, "נ": 50,
                  "ס": 60, "ע": 70, "פ": 80, "צ": 90, "ק": 100, "ר": 200, "ש": 300, "ת": 400,
                  "ך": 500, "ם": 600, "ן": 700, "ף": 800, "ץ": 900, ' ': 0}
    for i in arg:
        sum_of += alphabet[i]
    print(sum_of)


"""
/* Status : imple tested
 * Reviewer :
 * Description : validates a credit card
 * Arguments : card number
 * Return : void
 * Time Complexity : O(n)
 * comments :
 */
"""


def ex7(card):
    cvv = [int(card) for card in str(card)]
    sum_dig = 0
    for x in cvv[-2::-2]:
        x *= 2
        sum_dig += x if x < 9 else x - 9
    return not (sum_dig + sum(cvv[-1::-2])) % 10





if __name__ == '__main__':
    names = ['SHANI', 'shani', 'MICHAEL', 'michael', 'ShAnI']
    numbers = ['132', '98', '13', '30']
    nums = [132, 98, 13, -30]
    prices = {'apple': 32, 'banana': 45, 'pineapple': 100}


s = "The quick"
lst = [1, 2, 3]

print(s)
print(lst)



