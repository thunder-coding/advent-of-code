import re

notRegex = re.compile("^NOT (?P<a>[0-9]+|[a-z]+) -> (?P<dest>[a-z]+)$")
copyRegex = re.compile("^(?P<a>[0-9]+|[a-z]+) -> (?P<dest>[a-z]+)$")
binaryRegex = re.compile(
    "^(?P<a>[0-9]+|[a-z]+) (?P<gate>AND|OR|LSHIFT|RSHIFT) (?P<b>[0-9]+|[a-z]+) -> (?P<dest>[0-9]+|[a-z]+)$"
)

UINT16_MAX = (2**16) - 1


def signal(s: str) -> int | str:
    if s.isdecimal():
        raw = int(s)
        if raw > UINT16_MAX:
            raise Exception("raw signal cannot be greater than UINT16_MAX")
        return raw
    else:
        return s


def parseInstruction(line: str):
    notMatch = notRegex.match(line)
    if notMatch != None:
        return {
            "gate": "NOT",
            "a": signal(notMatch.group("a")),
            "dest": notMatch.group("dest"),
        }
    copyMatch = copyRegex.match(line)
    if copyMatch != None:
        return {
            "gate": "COPY",
            "a": signal(copyMatch.group("a")),
            "dest": copyMatch.group("dest"),
        }
    binaryMatch = binaryRegex.match(line)
    if binaryMatch != None:
        return {
            "gate": binaryMatch.group("gate"),
            "a": signal(binaryMatch.group("a")),
            "b": signal(binaryMatch.group("b")),
            "dest": binaryMatch.group("dest"),
        }
    raise Exception("unable to parse line: '" + line + "'")
