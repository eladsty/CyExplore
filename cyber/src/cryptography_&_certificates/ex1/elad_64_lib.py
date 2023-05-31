import base64

def B64_Enc(str):
    str_bytes = str.encode('ascii')
    base64_bytes = base64.b64encode(str_bytes)
    return base64_bytes.decode('ascii')

 
def b64_Dec(str64):
    str64_bytes = str64.encode('ascii')
    str_bytes = base64.b64decode(str64_bytes)
    return str_bytes.decode('ascii')
 