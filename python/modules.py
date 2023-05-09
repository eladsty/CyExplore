
# EX1
miao = 3
def IsDefine(name_to_check):
    if name_to_check in globals():
        print("yes")
    else:
        print("not defined")
IsDefine("miao")
IsDefine("miaouch")

# EX2

def CircleArea(radius):
    return 3.14 * radius * radius

def TriangleArea(height, base):
    return height * base / 2

def RectangleArea(height, width):
    return height * width

 