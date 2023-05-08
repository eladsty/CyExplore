# EX1

def string_extractor(list):
    for elem in list:
        if isinstance(elem, str) == False:
            list.remove(elem)
 
list = [4,"hello", False, "world"]

string_extractor(list)

print(list)


# EX2

def str_to_dic(str):
    return {c: str.count(c) for c in str}   
dictionary = str_to_dic("basasababa")

print(dictionary)

# EX3

def same_elem(list1, list2):
    return (set(list1) & set(list2))

list1 = [1,3,4,5]
list2 = [2,3,5,7]
listy  = same_elem(list1, list2) 
print(listy)


#EX4

def unique_val(dictionary):
    dic_list = []
    for key in dictionary:
        dic_list.append(dictionary[key])
    return set(dic_list)

dictio4 = {"brand": "Ford", "model": "Mustang", "year": 1964, "year": 1965, "yea2": 1964, "year": 1964}
print(unique_val(dictio4))


#EX5
def lef_rot(list4 ,rotate_n):
    return (list4[rotate_n:] + list4[:rotate_n])

print(lef_rot([1,2,3,4,5,6], 2))

#EX6
def print_sec(list5):
    while len(list5):
        for num in list5[::2]:
            print(num)
        del list5[::2]
print(print_sec([1,2,3,4,5,6,7,8,9]))
 

#EX7

def dict_to_tup(dict7):
    list_frmdic = []
    for key, value in dict7.items():
        list_frmdic.append((key, value))
    return list_frmdic
    
dict_even =  { 'apples': 10, 'oranges': 12, 'strawberries': 31 }
print( dict_to_tup(dict_even) )


 #EX7

