from parseInstruction import parseInstruction


def parse(input):
    parsed = {}
    for line in input.split("\n"):
        instruction = parseInstruction(line)
        if instruction["dest"] in parsed:
            raise Exception(
                "Wire '%s' cannot recieve signal from multiple sources"
                % instruction["dest"]
            )
        parsed[instruction["dest"]] = {
            "gate": instruction["gate"],
            "a": instruction["a"],
            "status": "NOT_CALCULATED",
        }
        if instruction["gate"] in ["AND", "OR", "LSHIFT", "RSHIFT"]:
            parsed[instruction["dest"]]["b"] = instruction["b"]
    return parsed
