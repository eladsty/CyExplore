from bank_account import BankAccount

# def test_init():
str_bank_account = BankAccount("Tom")
one_bank_acc = BankAccount(1)

def test_init():
    assert one_bank_acc.id == 1
    assert str_bank_account.id == "Tom"
    assert one_bank_acc.balance == 0
    assert str_bank_account.balance == 0
    assert isinstance(str_bank_account, BankAccount) == True
    assert isinstance(one_bank_acc, BankAccount) == True

def test_deposit():
    assert str_bank_account.deposit(100) == True
    assert one_bank_acc.deposit(100) == True
    assert str_bank_account.balance == 100
    assert one_bank_acc.balance == 100
    
def test_withdrawal():   
    assert str_bank_account.withdraw(100) == True
    assert one_bank_acc.withdraw(100) == True
    assert str_bank_account.balance == 0
    assert one_bank_acc.balance == 0
    assert str_bank_account.withdraw(100) == False
    assert one_bank_acc.withdraw(100) == False     
