import functools 
# for reduce

#ex1

def remove_from_list(list_ex1, key):
    print(list(filter(lambda x: x != key, list_ex1)))

ex1_list = ["the", "fox", "jumped", "over", "the", "fence"]
remove_from_list(ex1_list, "fox")

# ------------------------------------------------------------------------------------
#ex2
def sort_str(num_str_li):
    num_str_li.sort(key=lambda x:x)
    print(num_str_li)

num_str_li = ["6","3","1","7","2","-2",]
sort_str(num_str_li)

# -------------------------------------------------------------------------------------
#ex3

def list_sum(neg_ints, pos_ints):
    pos_sum = sum(map(lambda x: int(x), pos_ints))
    neg_sum = sum(map(lambda x: int(x), neg_ints))
    print([pos_sum, neg_sum])

print( list_sum([-4,-2,-2,-1,-2,-3], [4,2,2,1,2,3]) )

# -------------------------------------------------------------------------------------
#ex4
def list_sum(int_li):
    new_int_list = [x * x for x in int_li if (x % 2 == 0) in int_li]
    print(new_int_list)

list_sum([1,2,3,4,5])

# -------------------------------------------------------------------------------------
#ex5

def sale_func(prod_table):
    prod_table.update( (key, val * 0.9)for key, val in prod_table.items() )
    print(prod_table)

sale_func({"bread": 6, "milk":  7, "bamba": 8, "bisli": 9})


# -------------------------------------------------------------------------------------
#ex6
def gematria_cal(user_input):
    gematria_dic = {"א":1, "ב":2, "ג":3, "ד":4, "ה":5, "ו":6, "ז":7, "ח":8, "ט":9, "י":10,"ך":20,"כ":20, "ל":30,"ם":40, "מ":40, 
    "נ":50,"ן":50, "ס":60, "ע":70, "ף":80, "פ":80, "צ":90, "ק":100, "ר":200, "ש":300, "ת":400, " ":0}
    gem_sum = 0
    for x in user_input: 
        gem_sum += gematria_dic[x]
    print(gem_sum)
    
gematria_cal("אינפיניטי לאבס")

# -------------------------------------------------------------------------------------
#ex7
card_func = lambda i : i-9 if i > 9 else i
def is_card_valid(card_num):
    int_list =  [int(i) for i in card_num]
    int_list[-2::-2]  = [ int(i) for i in card_num[-2::-2] ]
    int_list = map(card_func, int_list)
    sum = functools.reduce(lambda a , b : a + b, int_list)
    return sum % 10 == 0

    
print(is_card_valid("4513256858760869") ) 
 