def calculate(parsed, wireId):
    if not wireId in parsed:
        raise Exception("Wire '%s' not found in circuit" % wireId)
    wire = parsed[wireId]

    if wire["status"] == "CALCULATED":
        return wire["calculated"]
    elif wire["status"] == "CALCULATING":
        raise Exception(
            "Recursion detected when calculating value for wire '%s'" % wireId
        )
    wire["status"] = "CALCULATING"
    a = wire["a"]
    if type(a) == str:
        a = calculate(parsed, a)
    b = None
    if "b" in wire:
        b = wire["b"]
        if type(b) == str:
            b = calculate(parsed, b)

    if wire["gate"] == "COPY":
        wire["calculated"] = a
    elif wire["gate"] == "NOT":
        wire["calculated"] = ~a & 0xFFFF
    elif wire["gate"] == "AND":
        wire["calculated"] = a & b
    elif wire["gate"] == "OR":
        wire["calculated"] = a | b
    elif wire["gate"] == "LSHIFT":
        wire["calculated"] = (a << b) & 0xFFFF
    elif wire["gate"] == "RSHIFT":
        wire["calculated"] = a >> b
    else:
        raise Exception("Unknown gate found '%s'" % wire["gate"])

    wire["status"] = "CALCULATED"
    return wire["calculated"]
