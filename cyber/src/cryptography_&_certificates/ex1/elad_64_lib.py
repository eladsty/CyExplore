import base64

def B64_Enc(str):
    str_bytes = str.encode('ascii')
    base64_bytes = base64.b64encode(str_bytes)
    return base64_bytes.decode('ascii')

 
def b64_Dec(str64):
    str64_bytes = str64.encode('ascii')
    str_bytes = base64.b64decode(str64_bytes)
    return str_bytes.decode('ascii')




import string

# Set up character mappings
CHARS = string.ascii_uppercase + string.ascii_lowercase + string.digits + '+/'
CHAR_MAP = {char: index for index, char in enumerate(CHARS)}
PADDING_CHAR = '='

def base64_encode(data):
    output = ''

    # Prepare data
    if isinstance(data, str):
        data = data.encode()

    padding = 3 - len(data) % 3
    if padding != 3:
        data += b'\x00' * padding

    # Encode each 24-bit chunk
    for i in range(0, len(data), 3):
        chunk = int.from_bytes(data[i:i+3], 'big')
        output += CHARS[chunk >> 18]
        output += CHARS[(chunk >> 12) & 63]
        output += CHARS[(chunk >> 6) & 63]
        output += CHARS[chunk & 63]

    if padding != 3:
        output = output[:-padding] + padding * PADDING_CHAR

    return output

def base64_decode(data):
    output = bytearray()

    # Validate padding
    padding = data.count(PADDING_CHAR)
    if padding > 2 or (len(data) % 4) != 0:
        raise ValueError('Invalid padding')

    # Decode each 24-bit chunk
    for i in range(0, len(data), 4):
        chunk = CHAR_MAP[data[i]] << 18
        chunk += CHAR_MAP[data[i+1]] << 12
        if data[i+2] != PADDING_CHAR:
            chunk += CHAR_MAP[data[i+2]] << 6
        if data[i+3] != PADDING_CHAR:
            chunk += CHAR_MAP[data[i+3]]
        output.extend(chunk.to_bytes(3, 'big'))

    return bytes(output[:-padding]) if padding else bytes(output)


# Test encode & decode functions
tests = [ "abcde" , "0",  "abcdef"] 
for test in tests:
    encoded = base64_encode(test)
    decoded = base64_decode(encoded)
    print("testcase: " + str(test) + "," + "encoded:"+ str(encoded) )
    print("testcase: "+ str(test) +"," + "after encoding and decoding:" + str(decoded) )


 
 