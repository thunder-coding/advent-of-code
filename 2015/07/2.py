from parse import parse
from calculate import calculate

input = None
try:
    input = open("./2015/07/input.txt", "r")
except:
    print("Error opening input.txt")
    exit(1)
parsed = parse(input.read())
a = calculate(parsed, "a")

for key in parsed:
    parsed[key]["status"] = "NOT_CALCULATED"

parsed["b"]["status"] = "CALCULATED"
parsed["b"]["calculated"] = a

print(calculate(parsed, "a"))
