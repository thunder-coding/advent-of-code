from parse import parse
from calculate import calculate

input = None
try:
    input = open("./2015/07/input.txt", "r")
except:
    print("Error opening input.txt")
    exit(1)
parsed = parse(input.read())
print(calculate(parsed, "a"))
