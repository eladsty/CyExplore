with open("demofile.txt", "r") as f:
    while True:
        chunk = f.read(3999)
        if not chunk:
            break
        print(chunk)
