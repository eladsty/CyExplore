import unittest
import string




class BankAccount:
    def __init__(self, id):
        self.id = id
        self.balance = 0

    def withdraw(self, amount):
        if self.balance >= amount:
            self.balance -= amount
            return True
        return False

    def deposit(self, amount):
        self.balance += amount
        return True


class TestBankAccount(unittest.TestCase):
    def setUp(self):
        self.account_1 = BankAccount('123456')

    def test_deposit(self):
        self.assertTrue(self.account_1.deposit(13))

    def test_withdraw(self):
        self.account_1.deposit(50)
        self.assertFalse(self.account_1.withdraw(70), msg='overdraft')
        self.assertTrue(self.account_1.withdraw(35))

    def stress_test(self):
        for x in [100]:
            self.account_1.deposit(30)
        self.assertTrue(self.account_1.withdraw(1000))