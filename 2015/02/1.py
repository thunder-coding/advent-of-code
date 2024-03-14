input = None
try:
    input = open("./2015/02/input.txt", "r")
except:
    print("Error opening input.txt")
    exit(1)

area = 0
for line in input.read().split("\n"):
    if line == "":
        continue
    sides = line.split("x")
    for i in range(len(sides)):
        sides[i] = int(sides[i])
    sides.sort()
    area += 3 * sides[0] * sides[1] + 2 * sides[2] * (sides[0] + sides[1])

print(area)
