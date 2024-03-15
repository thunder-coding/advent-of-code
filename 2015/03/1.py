input = None
try:
    input = open("./2015/03/input.txt", "r")
except:
    print("Error opening input.txt")
    exit(1)


class Coordinate:
    x = 0
    y = 0

    def __init__(self) -> None:
        self.x = 0
        self.y = 0

    def __str__(self) -> str:
        return "({},{})".format(self.x, self.y)


santaPos = Coordinate()
housesWithGifts = set()
housesWithGifts.add(str(santaPos))
for char in input.read():
    if char == "^":
        santaPos.y += 1
    elif char == "v":
        santaPos.y -= 1
    elif char == "<":
        santaPos.x -= 1
    elif char == ">":
        santaPos.x += 1
    else:
        print("Error, unknown character '", char, "'", sep="")
        exit(1)
    housesWithGifts.add(str(santaPos))

print(
    "Number of houses that recieve atleast one gift from santa is {}".format(
        len(housesWithGifts)
    )
)
