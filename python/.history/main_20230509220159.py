import modules
import os
import platform
import sys
import stat

# approved by adir
print(modules.CircleArea(5))
print(modules.TriangleArea(3,4))
print(modules.RectangleArea(4,3))
# approved by adir

# EX3
print(os.uname()[0])
print(os.getlogin())
print(os.getcwd())

# approved by adir

# EX4

def rev_input():
    print("few")
    print((sys.argv)[1:0:-1] )
rev_input()

# approved by adir

# EX5

def findfile(filename):
    for (root, dirs, files) in os.walk('/', topdown=True):
        if filename in files:
            return os.path.join(root, filename)
    return None

def perm_change():
    path = findfile(sys.argv[1])
    if path == None:
        sys.exit("file not found")

    if os.access(path, os.X_OK) == False:
        current_permissions = stat.S_IMODE(os.lstat(path).st_mode)
        os.chmod(path, current_permissions |  stat.S_IXGRP | stat.S_IXUSR)

 