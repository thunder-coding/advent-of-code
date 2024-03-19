import re

input = None
try:
    input = open("./2015/05/input.txt", "r")
except:
    print("Error opening input.txt")
    exit(1)

nice_count = 0
line = None
while True:
    line = input.readline()
    if line == "":
        break
    # Trim away the ending newline character
    if line.endswith("\n"):
        line = line[:-1]
    # Seriously speaking, who the fuck finds Python readible I don't know
    # I can't decide what's worse, the fact that I have to use 'and', 'not' and 'or' or the fact that there is no increment operator
    #
    # Also hate the language for fucking trying to reinvent standards, "([.])" des not work but "(.)" does. Makes no sense just like the language itself
    if (
        (re.search(r"([aeiouAEIOU]).*?([aeiouAEIOU]).*?([aeiouAEIOU])", line) != None)
        and (re.search(r"(.)\1", line) != None)
        and (re.search(r"ab|cd|pq|xy", line) == None)
    ):
        nice_count += 1

print(nice_count)
