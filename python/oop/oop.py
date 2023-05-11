import math

class Point:
    
    def __init__(self,x = 0.0, y = 0.0):
        if not isinstance(x and y , int or float):
            print("type error")
        else:
            self.x = x
            self.y = y
    def distance_from_origin(self):
        return math.sqrt(self.x**2 + self.y**2) 
    

p = Point(3, 4)
 
print(p.distance_from_origin())


# ex2 --------------------------------------------------
class Node:
   def __init__(self, data=None):
        self.data = data
        self.next = None

# maybe if statement is redundant
class SList:
    def __init__(self):
        self.head_node = None

    def push(self, data):
        if self.head_node is None:
            self.head_node = Node(data)
        else:
            new_node = Node(data)
            new_node.next = self.head_node
            self.head_node = new_node
    def pop(self):
        self.head_node = self.head_node.next

    def head(self):
        if self.head_node.data:
            return self.head_node.data

    def len(self):
        counter = 0
        curr = self.head_node
        while curr:
            counter += 1
            curr = curr.next
        return counter

    def Is_Empty(self):
        return self.head_node is None


new_list = SList()
assert(True == new_list.Is_Empty())
assert(0 == new_list.len())

for i in range(1,8,2):
    new_list.push(i)
assert(False == new_list.Is_Empty())
assert(7 == new_list.head())
assert(4 == new_list.len())

for i in range(1,5):
    new_list.pop()

assert(0 == new_list.len())
assert(True == new_list.Is_Empty())


# ex3 --------------------------------------------------

import datetime
import time


 
class Machine:
    def __init__(self):
        self.time_started = 0
        self.cost_per_minute = 0
        self.is_active = 0
        self.total_time = 0

    def start_machine(self, machine_type):       
        self.is_active = 1
        if machine_type == 1:
            self.cost_per_minute = 2
        elif machine_type == 2:
            self.cost_per_minute = 5
        self.time_started = datetime.datetime.now()

    def check_time_active(self):
        self.total_time += self.is_active * ( datetime.datetime.now() - self.time_started ).total_seconds() / 60
        return self.total_time 
    
    def check_total_cost(self):
        self.check_time_active()
        return self.cost_per_minute * self.total_time
    
    def stop_machine(self):
        self.check_time_active()
        self.is_active = 0

 
def test_driver():
    a = Machine()
    b = Machine()
    c = Machine()
    d = Machine()
    e = Machine()

    a.start_machine(1)
    b.start_machine(1)
    c.start_machine(1)
    d.start_machine(2)

    time.sleep(60)

    e.start_machine(2)

    time.sleep(60)

    b.stop_machine()

    time.sleep(60)

    machine_rig = [a,b,c,d,e]

    def machines_total_cost(machine_rig):
        total_price = 0
        for machine in machine_rig:
            total_price += machine.check_total_cost()
        return total_price


    print(machines_total_cost(machine_rig))

test_driver()