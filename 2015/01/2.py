input = None
try:
    input = open("./2015/01/input.txt", "r")
except:
    print("Error opening input.txt")
    exit(1)

floor = 0
basement = -1
count = 0
for char in input.read():
    count = count + 1
    if char == "(":
        floor = floor + 1
    elif char == ")":
        floor = floor - 1
    else:
        print("Warning unknown character: '", char, "'", sep="")
    if floor == basement:
        print(count)
        exit(0)

print("Santa will never reach basement")
