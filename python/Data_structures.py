""" Approved by Amir """

# EX1

def string_extractor(list_ts):
    return [elem for elem in list_ts if type(elem) == str]
 
list_test = [4,"hello", False, "world"]

string_extractor(list_test)

print(string_extractor(list_test))

""" Approved by Amir """
# EX2

def str_to_dic(str):
    return {c: str.count(c) for c in str}   
dictionary = str_to_dic("basasababa")

print(dictionary)


""" APPROVED BY AMIR """
# EX3

def same_elem(list1, list2):
    return list(set(list1) & set(list2))

list1 = [1,3,4,5]
list2 = [2,3,5,7]
listy  = same_elem(list1, list2) 
print(listy)

""" APPROVED BY AMIR """
#EX4

def unique_val(dictionary):
    dic_list = []
    for key in dictionary:
        dic_list.append(dictionary[key])
    return list(set(dic_list))

dictio4 = {"brand": "Ford", "model": "Mustang", "year": 1964, "year": 1965, "yea2": 1964, "year": 1964}
print(unique_val(dictio4))

""" Approved by amir """
#EX5
def lef_rot(list4 ,rotate_n):
    return (list4[rotate_n:] + list4[:rotate_n])

print(lef_rot([1,2,3,4,5,6], 2))

""" approved by amir """
#EX6
def print_sec(list5):
    while len(list5):
        for num in list5[::2]:
            print(num)
        del list5[::2]
print(print_sec([1,2,3,4,5,6,7,8,9]))
 
""" Approved by Amir """

#EX7

def dict_to_tup(dict7):
    list_frmdic = []
    for key, value in dict7.items():
        list_frmdic.append((key, value))
    return list_frmdic
    
dict_even =  { 'apples': 10, 'oranges': 12, 'strawberries': 31 }
print( dict_to_tup(dict_even) )

""" Approved by Amir """

#EX8

my_dict = {'a':10, 'b':5 , 'c': 33, 'd': 51, 'e': 70}

key_max = max(my_dict.keys(), key=(lambda k: my_dict[k]))
key_min = min(my_dict.keys(), key=(lambda k: my_dict[k]))

print('Maximum Value: ',my_dict[key_max])
print('Minimum Value: ',my_dict[key_min])

