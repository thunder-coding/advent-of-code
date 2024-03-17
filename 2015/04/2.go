package main

import (
	"crypto/md5"
	"fmt"
	"math"
	"os"
	"strconv"
)

func main() {
	input, err := os.Open("./2015/04/input.txt")
	if err != nil {
		fmt.Fprintln(os.Stderr, "Unable to open input file")
		os.Exit(1)
	}
	inputInfo, _ := input.Stat()
	b := make([]byte, inputInfo.Size())

	input.Read(b)

	secret := string(b)
	for answer := uint64(1); answer != math.MaxUint64; answer++ {
		h := md5.Sum([]byte(secret + strconv.FormatUint(answer, 10)))
		if h[0] == 0 && h[1] == 0 && h[2] == 0 {
			println(answer)
			os.Exit(0)
		}
	}
}
