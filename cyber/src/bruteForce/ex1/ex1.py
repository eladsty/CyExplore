
import hashlib
import string
from itertools import product
import datetime 
# charset: l = lowercase, n = numbers

def HashFunc(pass_str, chosen_hash):
    if chosen_hash == 1:
        result = hashlib.sha1(pass_str.encode() )
        return result.hexdigest()
    
    elif chosen_hash == 2:
        result = hashlib.sha256( pass_str.encode() )
        return result.hexdigest()
  

def SHACracker(chosen_hash, pass_len, charset, hash_to_crack):
    alphabet = string.ascii_lowercase
    numbers = string.digits
    final_charset = []

    if 'l' in charset:
        final_charset = list(alphabet)
    if 'd' in charset:
        final_charset = final_charset + list(numbers)
 
    if chosen_hash != 1 and chosen_hash != 2:
        print("wrong hashing algorithm, choose 1 for sha1 or 2 for sha256")
    
    pass_set = product(final_charset, repeat = pass_len) 
    time_start = datetime.datetime.now()

    for pass_str in pass_set:
        str_rep = ''.join([str(x) for x in pass_str])     
        print(str_rep)
        if HashFunc(str_rep ,chosen_hash) == hash_to_crack:
            total_time = datetime.datetime.now() - time_start
            print("The password is : " + str_rep)
            print("The process took" + str(total_time))
            break
        else:
            print(str_rep)
            
if __name__ == "__main__":
    #SHACracker(1, 4, "l", HashFunc("zulu", 1) )
    # SHACracker(2, 4, "l", HashFunc("zulu", 2) )
   
    # SHACracker(1, 5, "l", HashFunc("great", 1) )
    # SHACracker(2, 5, "l", HashFunc("great", 2) )

    # SHACracker(1, 6, "d", HashFunc("123456", 1) )
    # SHACracker(2, 6, "d", HashFunc("123456", 2) )

    # SHACracker(1, 7, "d", HashFunc("1234567", 1) )
    # SHACracker(2, 7, "d", HashFunc("1234567", 2) )

    # SHACracker(1, 8, "d", HashFunc("12345678", 1) )
    # SHACracker(2, 8, "d", HashFunc("12345678", 2) )

    # SHACracker(1, 5, "l", HashFunc("aabbcc", 1) )
    # SHACracker(2, 5, "l", HashFunc("aabbcc", 2) )
     SHACracker(1, 6, "ld", HashFunc("a3ai64", 1) )
     SHACracker(2, 6, "ld", HashFunc("a3ai64", 2) )