import hashlib

input = None
try:
    input = open("./2015/04/input.txt", "r")
except:
    print("Error opening input.txt")
    exit(1)

secret = input.read()

i = 1
while True:
    h = hashlib.md5()
    h.update((secret + str(i)).encode())
    if h.hexdigest().startswith("00000"):
        print(i)
        exit(0)
    i += 1
