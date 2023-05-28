from datetime import datetime
import unittest
from functools import reduce


class Machine:

    total_pay = 0
    pricing = 0
    join_time = datetime.now()
    active = False

    def __init__(self, model_type):
        self.pricing = 2 if model_type == 1 else 5

    def start_machine(self):
        if self.active is False:
            self.join_time = datetime.now()
            self.active = True
            return True
        return False

    def stop_machine(self):
        if self.active is True:
            self.total_pay += int((datetime.now() - self.join_time).total_seconds())/60 * self.pricing
            self.active = False
            return True
        return False

    def switch_plan(self, new_model_type):
        if not self.stop_machine():
            return False
        self.pricing = 2 if self.pricing == 5 else 2
        if not self.start_machine():
            return False
        return True

    def get_cost(self):
        if self.active is False:
            return self.total_pay
        return int((datetime.now() - self.join_time).total_seconds())/60 * self.pricing + self.total_pay


class JoinCloud:
    machine_log = []

    def add_machine(self, machine):
        if not isinstance(machine, Machine):
            return False
        self.machine_log.append(machine)
        return True

    def get_total_cost(self):
        total = reduce(lambda total_log, machine: total_log + machine.get_cost(), self.machine_log, 0)
        return total


class TestMachine(unittest.TestCase):

    def setUp(self):
        self.instance1 = Machine(1)
        self.instance2 = Machine(2)
        self.log = JoinCloud()

    def test_init_macine(self):
        self.assertFalse(self.instance1.active, msg='machine activeation')
        self.assertFalse(self.instance2.active, msg='machine activeation')
        self.assertEqual(self.instance1.pricing, 2)
        self.assertEqual(self.instance2.pricing, 5)
    def test_get_total_cost(self):
        self.assertIsNotNone(self.instance1, msg='None returned from get_total_cost')

    def test_add_machine(self):
        self.assertTrue(self.log.add_machine(self.instance1), msg='add machine to log')
        self.assertFalse(self.log.add_machine(self.log), msg='add log to log')

    def test_get_cost(self):
        self.assertIsInstance(self.instance1.get_cost(), int, msg='return is not of type int')

    def test_start_machine(self):
        self.assertTrue(self.instance1.start_machine(), msg='start machine')

    def test_switch_plan(self):
        self.instance1.start_machine()
        self.assertTrue(self.instance1.switch_plan(2), msg='can\'t switch models')

    def test_stop_machine(self):
        self.instance1.start_machine()
        self.assertTrue(self.instance1.stop_machine(), msg='stop machine')

