input = None
try:
    input = open("./2015/06/input.txt", "r")
except:
    print("Error opening input.txt")
    exit(1)


class Lightgrid:
    lights = None

    def __init__(self) -> None:
        self.lights = []
        for _ in range(1000):
            _arr = []
            for _ in range(1000):
                _arr.append(0)
            self.lights.append(_arr)

    def on(self, begx, begy, endx, endy):
        for x in range(begx, endx + 1):
            for y in range(begy, endy + 1):
                self.lights[x][y] += 1

    def off(self, begx, begy, endx, endy):
        for x in range(begx, endx + 1):
            for y in range(begy, endy + 1):
                if self.lights[x][y] != 0:
                    self.lights[x][y] -= 1

    def toggle(self, begx, begy, endx, endy):
        for x in range(begx, endx + 1):
            for y in range(begy, endy + 1):
                self.lights[x][y] += 2

    def brightness(self):
        brightness = 0
        for column in self.lights:
            for light in column:
                brightness += light
        return brightness


nice_brightness = 0
line = None
lightgrid = Lightgrid()
while True:
    line = input.readline()
    if line == "":
        break
    # Trim away the ending newline character
    if line.endswith("\n"):
        line = line[:-1]

    fun = None
    if line.startswith("turn on "):
        line = line[len("turn on ") :]
        fun = lightgrid.on
    elif line.startswith("turn off "):
        line = line[len("turn off ") :]
        fun = lightgrid.off
    elif line.startswith("toggle "):
        line = line[len("toggle ") :]
        fun = lightgrid.off
        fun = lightgrid.toggle
    else:
        print("Error parsing input.txt unable to parse instruction")
        exit(1)

    [beg, end] = line.split(" through ")
    [begx, begy] = beg.split(",")
    [endx, endy] = end.split(",")
    begx = int(begx)
    begy = int(begy)
    endx = int(endx)
    endy = int(endy)
    fun(begx, begy, endx, endy)

print(lightgrid.brightness())
