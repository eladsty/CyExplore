 

#ex1

def a_to_z():
    for l in "A-Z":     
        with open(l + ".txt","w") as my_file:
            my_file.write("letter: " + l)

a_to_z()

#ex2

def read_n_lines(path, n):
    with open(path, "r") as my_file:
            for i in range(n):
                print(my_file.readlines(n))
 
read_n_lines("/home/elad/elad.shem-tov/python/files/ext2test.txt", 3)

#ex3

import csv 
print("below is EX3 ------------")
def csv_stat(path):
    vac = [] 
    non_vac = [] 
    with open(path, "r") as csv_file:
        csv_reader = csv.reader(csv_file)
        for line in csv_reader:
            print(line)

csv_stat("/home/elad/elad.shem-tov/python/files/corona.csv")

# patient for patient in csv_reader if (patient[5] == 'N') in csv_reader