import unittest
from bank_account import BankAccount
# approved: Michael afonin


class BankAccTest(unittest.TestCase):
    def setUp(self):
        self.person = ["Tom", 1]
        self.str_bank_account = BankAccount(person[0])
        self.one_bank_acc = BankAccount(person[1])
 
    def test_init_valid(self):
        self.assertIsInstance(self.str_bank_account, BankAccount)
        self.assertIsInstance(self.one_bank_acc, BankAccount)
        self.assertIsNot(self.str_bank_account.id, self.one_bank_acc)
        self.assertEqual(self.str_bank_account.id, "Tom")
        self.assertEqual(self.one_bank_acc.id, 1)

    def test_deposit(self):
        self.assertTrue(self.str_bank_account.deposit(100))
        self.assertTrue(self.one_bank_acc.deposit(100))

    def test_withrawal(self):
        self.assertTrue(self.str_bank_account.withdraw(100))
        self.assertTrue(self.one_bank_acc.withdraw(100))
        self.assertEqual(0, self.str_bank_account.balance)
        self.assertEqual(0, self.one_bank_acc.balance)
        self.assertFalse(self.str_bank_account.withdraw(100))
        self.assertFalse(self.one_bank_acc.withdraw(100))
         

if __name__ == '__main__':
    BankAccTest.test_init()
    BankAccTest.test_init_valid()
    unittest.main()
