package main

import "fmt"
import "reflect"
import "flag"
import "hash/crc32"
import "bufio"
import "os"

var options struct {
	maxholes int
	turn     string
	myside   string
}

type step struct {
	turn, offset int32
	hash         uint32
}

type tpath struct {
	steps   []step
	cholies [2]int
}

func (p *tpath) String() string {
	return fmt.Sprintf("(%v,%v) %v", p.cholies[0], p.cholies[1], p.steps)
}

func argparse() {
	flag.IntVar(&options.maxholes, "holes", 7,
		"number of holes on each side")
	flag.StringVar(&options.turn, "turn", "clock",
		"who is starting the turns, clock | antic")

	flag.Parse()
}

func main() {
	var turn byte

	argparse()

	switch options.turn {
	case "clock":
		turn = 0
	case "antic":
		turn = 1
	default:
		panic("turn can be `clock` or `antic`")
	}
	paths := make([]tpath, 0)
	play(
		initialize(options.maxholes),
		make([]step, 0),
		[2]int{},
		turn,
		func(steps []step, cholies [2]int) {
			fmt.Println("... fin", len(steps), cholies)
			paths = append(paths, tpath{steps: steps, cholies: cholies})
			//getchar()
		},
	)
}

func play(holes []int, path []step, cholies [2]int, turn byte, callb func([]step, [2]int)) {
	numholes, played := byte(len(holes)/2), false

	if ok, split := splitcheck(holes); ok {
		callb(path, [2]int{cholies[0] + split[0], cholies[1] + split[1]})
	}
loop:
	for offset := byte(0); offset < numholes; offset++ {
		hash := hashholes(holes, offset)
		if holes[offset] > 0 {
			for _, step := range path {
				if step.hash == hash {
					//fmt.Println("loop detected, skipping", holes, offset)
					continue loop
				}
			}
			nextholes, nextcholies := playeach(holes, offset, turn, cholies)
			played = true
			//fmt.Println("playeach", holes, offset, turn, cholies)
			nextholes = reverse(nextholes)
			play(
				nextholes,
				append(path, step{int32(turn), int32(offset), hashholes(holes, offset)}),
				nextcholies,
				1-turn,
				callb,
			)
		}
	}
	if played == false {
		callb(path, cholies)
	}
	return
}

func playeach(holes []int, offset, turn byte, cholies [2]int) ([]int, [2]int) {
	var count int

	playholes := make([]int, len(holes))

	if ok, split := exitcases(holes); ok {
		return playholes, [2]int{cholies[0] + split[0], cholies[1] + split[1]}
	}

	copy(playholes, holes)

	next := func(x byte) byte {
		return (x + 1) % byte(len(holes))
	}
	for playholes[offset] > 0 {
		count, playholes[offset] = playholes[offset], 0
		offset = next(offset)
		for i := 0; i < count; i++ {
			playholes[offset] += 1
			if playholes[offset] == 4 {
				cholies[turn] += 4
				playholes[offset] = 0
			}
			offset = next(offset)
		}
	}
	offset = next(offset)
	cholies[turn] += playholes[offset]
	playholes[offset] = 0
	return playholes, cholies
}

func hashholes(holes []int, offset byte) uint32 {
	var scratchpad = make([]byte, len(holes))
	for i, h := range holes {
		scratchpad[i] = byte(h)
	}
	return crc32.ChecksumIEEE(scratchpad)
}

func splitcheck(holes []int) (bool, [2]int) {
	n := 0
	for i := 0; i < len(holes); i++ {
		if holes[i] > 1 {
			return false, [2]int{0, 0}
		}
		n += holes[i]
	}
	return true, [2]int{n / 2, n / 2}
}

func exitcases(holes []int) (bool, [2]int) {
	if holes[6] == 1 && reflect.DeepEqual(holes[7:], []int{0, 0, 0, 0, 0, 0, 0}) {
		return true, [2]int{sum(holes[:7]), 0}
	}
	return false, [2]int{0, 0}
}

func sum(holes []int) int {
	n := 0
	for _, v := range holes {
		n += v
	}
	return n
}

func initialize(numholes int) []int {
	holes := make([]int, 2*numholes)
	for i := 0; i < len(holes); i++ {
		holes[i] = 5
	}
	return holes
}

func reverse(holes []int) []int {
	rholes := make([]int, len(holes))
	for i, j := 0, len(holes)-1; j >= 0; i, j = i+1, j-1 {
		rholes[i] = holes[j]
	}
	return rholes
}

func getchar() {
	reader := bufio.NewReader(os.Stdin)
	reader.ReadString('\n')
}
