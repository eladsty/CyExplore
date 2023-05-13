 
from machine_class import machine
from time import sleep

def test_driver():
    a = Machine()
    b = Machine()
    c = Machine()
    d = Machine()

    a.start_machine(1)
    b.start_machine(1)
    c.start_machine(1)
    d.start_machine(2)

    time.sleep(60)

    e = Machine()
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