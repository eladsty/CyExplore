import os.path
import sys
import csv
import math


# Reading context manager
class ReadLines(object):
    def __init__(self, file_name):
        self.file_name = file_name

    def __enter__(self):
        self.file = open(self.file_name, 'r')
        return self.file

    def __exit__(self, *args):
        self.file.close()


# Writing context manager
class WriteFiles(object):
    def __init__(self, file_name):
        self.file_name = file_name

    def __enter__(self):
        self.file = open(self.file_name, 'w', newline="")
        return self.file

    def __exit__(self, *args):
        self.file.close()
"""
/* Status : approved
 * Reviewer : Hen
 * Description : creates files with names A.txt-Z.txt containing their name A-Z
 * Arguments : none
 * Return : void
 * comments :
 */
"""

# context manager



def ex1():
    names = list('ABCDEFGHIJKLMNOPQRSTUVWXYZ')
    for x in names:
        with WriteFiles(f"{x}.txt") as letter_file:
            letter_file.write(x)


"""
/* Status : approved
 * Reviewer : Hen
 * Description : reads lines from a file
 * Arguments : filename
 * Return : 
 * comments :
 */
"""





def ex2(file_name, n):
    with ReadLines(file_name) as file:
        print(file.readlines()[:n])


"""
/* Status : approved
 * Reviewer : Hen
 * Description : min and max ages for vaccinated or not, average hospital stay
                    and filter the csv file to a new file with conditions.
 * Arguments : file_name - the csv source file, filter_categories - list of 
                categories to filter out of, filter_condition - list of 
                conditions to be writen as 'cond' and the index of their 
                respective category, and conditional function as value.
 * Return : void
 * comments : 
 */
"""


def min_max_age(file_name):
    vacc = []
    non_vacc = []
    with ReadLines(file_name) as covid:
        content = csv.reader(covid)
        next(content, None)
        for x in content:
            if x[6] == 'Y':
                vacc.append(int(x[1]))
            else:
                non_vacc.append(int(x[1]))
        print("the youngest vaccinated patient is of age " + str(min(vacc)))
        print("the oldest vaccinated patient is of age " + str(max(vacc)) + "\n")
        print("the youngest non-vaccinated patient is of age " + str(min(non_vacc)))
        print("the oldest non-vaccinated patient is of age " + str(max(non_vacc)))
    return


def hospitalization(file_name):
    length = []
    with ReadLines(file_name) as covid:
        content = csv.reader(covid)
        next(content, None)
        for x in content:
            length.append(int(x[4]))
    print("the average length of hospitalization is " + str(sum(length)/ len(length)))
    return


def check_dict(dic, *keys, **value_conditions):
    for key in range(len(keys)):
        if not value_conditions[f'cond{key}'](dic[keys[key]]):
            return False
    return True


def filtered(file_name, *filter_categories, **filter_condition):
    with ReadLines(file_name) as src, WriteFiles(f'filtered_{filter_categories}.csv') as dest:
        reader = csv.DictReader(src)
        writer = csv.DictWriter(dest, fieldnames=reader.fieldnames)
        targets = [name for name in reader if check_dict(name, *filter_categories, **filter_condition)]
        writer.writeheader()
        for row in targets:
            writer.writerow(row)


filtered('corona.csv', 'Age', 'gender', cond0=lambda a: int(a) > 30, cond1=lambda a: a == 'F')
