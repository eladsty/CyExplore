"""
/* Status : Approved
 * Reviewer : Nevo
 * Description :  put element in list as long as its not a type string
 * Arguments : list
 * Return : list without strings
 * Time Complexity : O(n)
 * comments :
 */
"""


def ex1_remove_non_str(list_):
    for i in list_:
        if type(i) != str:
            list_.remove(i)
    return


""" 
/* Status : Approved
 * Reviewer : Nevo
 * Description : create a dictionary where key is a letter from string and value
 * is the number of occurrences
 * Arguments : string
 * Return : dictionary
 * Time Complexity : O(n)
 * comments : pretty self explanatory
 */
"""


def ex2_dict_from_str(string):
    return {i: string.count(i) for i in string}


""" 
/* Status : Approved
 * Reviewer : Nevo 
 * Description : find intersecting elements of two lists
 * Arguments : two lists
 * Return : a list of all intersecting elements
 * Time Complexity : O(n)
 * comments : list intersection 
 */
"""


def ex3_both_lists(list_1, list_2):
    return list_1 and list_2


""" 
/* Status : Approved
 * Reviewer : Nevo
 * Description : find unique values in a dictionary
 * Arguments : dictionary
 * Return : list of unique values
 * Time Complexity : O(n)
 * comments : set command does not allow for duplicated values
 */
"""


def ex4_dict_value_to_list(dictionary):
    return list(set(i for i in dictionary.values()))


""" 
/* Status : Approved
 * Reviewer : Nevo 
 * Description : rotates list to the left
 * Arguments : list
 * Return : list rotated to the left
 * Time Complexity : O(n)
 * comments : start list from 1 index and append the 0 index at the end
 */
"""


def ex5_list_rotation(given_list):
    return given_list[1:] + given_list[:1]


""" 
/* Status : Approved
 * Reviewer : Nevo 
 * Description : prints and removes every second element in a list until empty
 * Arguments : list
 * Return : void
 * Time Complexity : O(n)
 * comments : slicing
 */
"""


def ex6_list_remove_second_element(list_):
    while len(list_):
        print(list_[::2])
        del list_[::2]
    return


""" 
/* SStatus : Approved
 * Reviewer : Nevo 
 * Description :
 * Arguments : 
 * Return : 
 * Time Complexity : O(n)
 * comments : 
 */
"""


def ex7_dict_to_tuple(dictionary):
    return dictionary.items()


""" 
/* Status : Approved
 * Reviewer : Nevo
 * Description :
 * Arguments : 
 * Return : 
 * Time Complexity : O(n)
 * comments : 
 */
"""


def ex8_min_max_dict_values(dic):
    print(min(dic, key=dic.get), (max(dic, key=dic.get)))
    return


if __name__ == '__main__':
    list1 = ['apple', 17, 32, 46.5, 'banana', 13]
    ex1_remove_non_str(list1)
    print(ex2_dict_from_str("shani_shalom"))

    ex3_both_lists(['shani', 'shalom', 13, 52.3], ['shalom', 13])
    ex4_dict_value_to_list({'shani': 1, 2: 2, 3: 5, 'shaked': 4})
    ex5_list_rotation(['apple', 'orange', 'Elad', 'banana', 'shalom'])
    ex6_list_remove_second_element([1, 2, 3, 4, 5, 6, 7, 8])
    ex7_dict_to_tuple({'shani': 1, 2: 2, 3: 5, 'shaked': 4})
    ex8_min_max_dict_values({'shani': 1, 2: 2, 3: 5, 'shaked': 4})



