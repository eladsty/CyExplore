#  approved by Afonin.M

#ex1

def a_to_z():
    for l in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":     
        with open(l + ".txt","w") as my_file:
            my_file.write("letter: " + l)

a_to_z()

#  approved by Afonin.M

#ex2

def read_n_lines(path, n):
    with open(path, "r") as my_file:
            for i in range(n):
                print(my_file.readlines(n))
 
read_n_lines("/home/elad/elad.shem-tov/python/files/ext2test.txt", 3)

#  approved by Afonin.M

#ex3
print("below is EX3 ------------")

import csv 
#  gender agerange and vaccinated

def input_writer(line_val, user_input, path):
    min_age = int(user_input[1].split('-')[0])
    max_age= int(user_input[1].split('-')[1])
    print(user_input[0]  )

    with open("/home/elad/elad.shem-tov/python/files/filtered_data.txt", "a") as new_file:
        if(line_val[0] == str(user_input[0]) and \
            int(line_val[1]) >= min_age and \
            int(line_val[1]) <= max_age and \
            line_val[6] == str(user_input[2]) ):
            new_file.write(str(line_val) + "\n")
      
def csv_stat(path):
    with open(path, "r") as csv_file:
        csv_reader = csv.reader(csv_file)
        csv_reader.__next__()
        dict_obj = csv.DictReader(csv_file)
        sum = 0
        n_patient = 0
        vac_min = 150
        unvac_min = 150
        vac_max = 0
        unvac_max = 0
        
        input_list = [val for val in input("Enter gender,age-range,vaccinated (Y or N)\n").split(',')]
        
        for line in csv_reader:
            if(int(line[1]) < int(vac_min) and line[6] == 'Y'):
                vac_min = line[1]
            if(int(line[1]) > int(vac_max) and line[6] == 'Y'):
                vac_max = line[1]    
            if(int(line[1]) < int(unvac_min) and line[6] == 'N'):
                unvac_min = line[1]  
            if(int(line[1]) > int(unvac_max) and line[6] == 'N'):
                unvac_max = line[1]  
            n_patient += 1
            sum += int(line[4])
            input_writer(line, input_list, path)

        print("vaxed min-max: " + str(vac_min) +  " " + str(vac_max))
        print("unvaccinated min-max: " + str(unvac_min)+ " "+ str(unvac_max))
        print("average days of hospitalization is: " + str(sum / n_patient) )     

csv_stat("/home/elad/elad.shem-tov/python/files/corona.csv")

