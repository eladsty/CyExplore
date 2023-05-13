# approved: Michael afonin

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
 
