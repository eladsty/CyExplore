APPROVED: MICHAEL AFONIN

def check_pwd(password):
     error = False
     try:
        if len(password) < 8:
            raise Exception("password must be at least 8 characters") 
     except Exception as len_err:
          print("Type of exception:",e)
          error = True
     try:
        if not any(l.isupper() for l in password):
            raise Exception(" Password must contain at least one capital letter")
     except Exception as l:
          print("Type of exception:",e)
          error = True
     try:
        if not any(l.isdigit() for l in password):
            raise Exception(" Password must contain at least one digit")
     except Exception as l:
             print("Type of exception:",e)             
             error = True
     try:
        if not any(l.islower() for l in password):
            raise Exception(" Password must contain at least one lower case letter")
     except Exception as l:
             print("Type of exception:",e)             
             error = True 
     try:
        special_chars = "@#&%"
        if not any(l in special_chars for l in password):
            raise Exception(" Password must contain at least one of these symbols: @#&%")
     except Exception as l:
             print("Type of exception:",e)             
             error = True

     if not error:
          print(" valid password")


check_pwd("234234234234")

def TestDriver():
    passwords = ["283fF9a8j%", "dq#2Sf", "12312312"]

    for pw in passwords:
        check_pwd(pw)
 
