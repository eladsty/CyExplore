import math
import time
from datetime import datetime
from functools import reduce


"""
/* Status : imple tested
 * Reviewer : 
 * Description : class init an object to a point on a cartesian coordinate 
                system, and calculate it's distance from the point of origin.
 * Arguments : only numbers, else an error will appear
 * Return : 
 * comments :
 */
"""


class Point:

    def __new__(cls, *args):
        if not all(isinstance(x, (int, float)) for x in args):
            raise TypeError('invalid argument - must be a number')
        return super().__new__(cls)

    def __init__(self, x=0.0, y=0.0):
        self.x = x
        self.y = y

    def distance_from_origin(self):
        return math.dist((0, 0), (self.x, self.y))


"""
/* Status : imple tested
 * Reviewer : 
 * Description : linked list create, push, pop, head, len, is_empty
 * Arguments :
 * Return : 
 * comments :
 */
"""


class LinkedList:
    def __init__(self):
        self.head = None
        self.len = 0
        return


class Node:
    def __init__(self, data=None):
        self.data = data
        self.next = None

    def __repr__(self):
        return self.data


def create():
    slist = LinkedList()
    slist.head = Node()
    return slist


def push(slist, data):
    x = slist.head
    print(x.__repr__())
    while x.next is not None:
        x = x.next
        print(x.__repr__())
    if x.data is None:
        x.data = data
    else:
        x.next = Node(data)
    slist.len += 1
    return


def is_empty(slist):
    if slist.len == 0:
        return True
    return False


def pop(slist):
    if is_empty(slist):
        raise TypeError('List is empty')
    if slist.head.next is type(Node):
        slist.head = slist.head.next

    else:
        slist.head.data = None
    slist.len -= 1
    return


def head(slist):
    if is_empty(slist):
        raise TypeError('List is empty')
    print(slist.head.data.__repr__())
    return slist.head.data.__repr__()


def list_len(slist):
    return slist.len


"""
/* Status : imple tested
 * Reviewer : 
 * Description : linked list create, push, pop, head, len, is_empty
 * Arguments :
 * Return : 
 * comments :
 */
"""


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
        return

    def stop_machine(self):
        if self.active is True:
            self.total_pay += int((datetime.now() - self.join_time).total_seconds())/60 * self.pricing
            self.active = False

    def switch_plan(self, new_model_type):
        self.stop_machine()
        self.pricing = 2 if self.pricing == 5 else 2
        self.start_machine()

    def get_cost(self):
        if self.active is False:
            return self.total_pay
        return int((datetime.now() - self.join_time).total_seconds())/60 * self.pricing + self.total_pay


class JoinCloud:
    machine_log = []

    def add_machine(self, machine):
        self.machine_log.append(machine)

    def get_total_cost(self):
        total = reduce(lambda total_log, machine: total_log + machine.get_cost(), self.machine_log, 0)
        return total


if __name__ == '__main__':
    cloud = JoinCloud()
    # phase 1
    a = Machine(1)
    a.start_machine()
    cloud.add_machine(a)

    b = Machine(1)
    b.start_machine()
    cloud.add_machine(b)

    c = Machine(1)
    c.start_machine()
    cloud.add_machine(c)

    d = Machine(2)
    d.start_machine()
    cloud.add_machine(d)

    time.sleep(60)
    # phase 2
    e = Machine(2)
    e.start_machine()
    cloud.add_machine(e)

    time.sleep(60)
    # phase 3
    b.stop_machine()

    time.sleep(60)

    print(cloud.get_total_cost())





