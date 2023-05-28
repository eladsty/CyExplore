

def pass_complexity():
    password = str(input("your password>>"))
    temp = 0
    if not (password.isupper and password.isupper and password.isdigit and (
            '@' in password or '#' in password or '%' in password or '&'
            in password)):
        raise TypeError('Weak password brah')
    if 8 >= len(password) :
        raise TypeError('too short brah')
    return True




print(pass_complexity())