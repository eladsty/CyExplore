import os
import stat
import sys
import areas


"""
/* Status : Approved
 * Reviewer : Hen
 * Description : 
 * Arguments : 
 * Return : 
 * comments :
 */
"""


def ex1(var):
    return var in globals()


"""
/* Status : Approved
 * Reviewer : Hen
 * Description : 
 * Arguments : 
 * Return : 
 * comments :
 */
"""


def ex2():
    height = 9
    base = 12
    radius = 4
    print(areas.circle(radius))
    print(areas.triangle(height, base))
    print(areas.rectangle(height, base))


"""
/* Status : Approved
 * Reviewer : Hen
 * Description : 
 * Arguments : 
 * Return : 
 * comments :
 */
"""


def ex3():
    print("Os: " + sys.platform)
    print("User: " + os.getlogin())
    print("Working dir: " + os.getcwd())


"""
/* Status : Approved
 * Reviewer : Hen
 * Description : 
 * Arguments : 
 * Return : 
 * comments :
 */
"""


def ex4():

    sys.argv[1:].reverse()
    print(sys.argv[1:])


"""
/* Status : Approved
 * Reviewer : Hen
 * Description : 
 * Arguments : 
 * Return : 
 * comments :
 */
"""


def ex5(file_name):
    perm = os.stat(file_name)
    print("file location: " + os.path.dirname(file_name))
    print(os.access(file_name, os.X_OK))
    if os.access(file_name, os.X_OK):
        return 0
    os.chmod(file_name, perm.st_mode | stat.S_IXUSR | stat.S_IXGRP)
    return 0


if __name__ == '__main__':
    ex2()
