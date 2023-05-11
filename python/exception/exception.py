
def check_pwd(password):
     cond1=0
     cond2=0
     cond3=0
     cond4=0
     exceptions= ""
     
     try:
        if len(password) < 8:
            raise Exception("password length should be 8 or longer") 
     except Exception as len_err:
         error = True
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
    
         if cond1 + cond2 + cond3 + cond4 == 4: 
            return True
     else:
         if cond1 == 0:
             exceptions += "password must contain capital letters"
         if cond2 == 0:
             exceptions += "password must contain lower case letters"
         if cond3 == 0:
             exceptions += "password must contain numbers "
         if cond4 == 0:
             exceptions += "password must contain a least one @ # & or %"
        
 

print(check_pwd("283fF9a8j%"))
print(check_pwd("dq#Sf"))

