import math

class Point:
    
    def __init__(self,x = 0.0, y = 0.0):
        if not isinstance(x and y , int or float):
            print("type error")
        else:
            self.x = x
            self.y = y
    def distance_from_origin(self):
        return math.sqrt( math.pow(self.x, 2) + math.pow(self.y, 2) )
    
    

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


