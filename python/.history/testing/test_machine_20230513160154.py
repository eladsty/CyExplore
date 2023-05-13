
from machine_class import Machine
from time import sleep

a = Machine()
b = Machine()
c = Machine()
d = Machine()

def test_MachineInit():
    assert isinstance(a, Machine) == True
    assert isinstance(b, Machine) == True
    assert isinstance(c, Machine) == True
    assert isinstance(d, Machine) == True    
    assert a.time_started == 0
    assert a.cost_per_minute == 0
    assert d.cost_per_minute == 0

def test_test_MachineStart():
    two_bucks = Machine()
    five_bucks = Machine()
    two_bucks.start_machine(1)
    five_bucks.start_machine(2)
    assert two_bucks.cost_per_minute == 2
    assert five_bucks.cost_per_minute == 5
    
def test_MachineCostTest():
    a.start_machine(1)
    b.start_machine(1)
    c.start_machine(1)
    d.start_machine(2)
    
    sleep(60)

    e = Machine()
    e.start_machine(2)

    sleep(60)

    b.stop_machine()

    sleep(60)

    machine_rig = [a,b,c,d,e]
    
    total_price = 0
    for machine in machine_rig:
        total_price += machine.check_total_cost()
    assert total_price >= 43
    assert total_price <= 43.1
 

 