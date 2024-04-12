input = None
try:
    input = open("./2015/01/input.txt", "r")
except:
    print("Error opening input.txt")
    exit(1)

floor = 0

for char in input.read():
    if char == "(":
        floor = floor + 1
    elif char == ")":
        floor = floor - 1
    else:
        print("Warning unknown character: '", char, "'", sep="")

print(floor)
