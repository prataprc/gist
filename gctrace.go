package main

import (
	"flag"
	"fmt"
	"io/ioutil"
	"math"
	"regexp"
	"sort"
	"strconv"
	"strings"
)

// go run gctest.go -n 8 -loop 1000000000 -maxsize 100
//      3674,93s user 204,88s system 595% cpu 10:51,41 total
// 2000000

// go run gctest.go -n 8 -loop 1000000000 -maxsize 1000
//      7586,44s user 1621,51s system 578% cpu 26:32,53 total
// 200000

// go run gctest.go -n 8 -loop 1000000000 -maxsize 10000
// 20000

var options struct {
	str  string // string to parse
	file string // file that contains the string
}

type Stat struct {
	mark     uint64
	sweep    uint64
	clean    uint64
	preHeap  uint64
	postHeap uint64
	preObjs  uint64
	postObjs uint64
	allocs   uint64
	frees    uint64
}

// Regular expression that parses
//  gc131(8): 14+133+6 ms, 4296 -> 2217 MB 888433 -> 463452 (22763539-22300087)
//  objects, 1(6) handoff, 92(69055) steal, 281/94/564 yields
var pattern = `^gc[0-9]+\([0-9]+\): ([0-9]*)\+([0-9]*)\+([0-9]*) ms, ([0-9]*) -> ([0-9]*) MB ([0-9]*) -> ([0-9]*) \(([0-9]*)-([0-9]*)\).*`
var re *regexp.Regexp
var err error

func main() {
	flag.StringVar(&options.str, "s", "", "String to parse")
	flag.StringVar(&options.file, "f", "", "File that contain debug trace")
	flag.Parse()
	re, err = regexp.Compile(pattern)
	if err != nil {
		panic(err)
	}
	if options.file != "" {
		text, err := ioutil.ReadFile(options.file)
		if err != nil {
			panic(err)
		}
		stats := make([]Stat, 0)
		for _, line := range strings.Split(string(text), "\n") {
			ss := re.FindStringSubmatch(strings.Trim(line, " "))
			if len(ss) == 10 {
				stats = append(stats, Stat{
					mark:     atoi(ss[1]),
					sweep:    atoi(ss[2]),
					clean:    atoi(ss[3]),
					preHeap:  atoi(ss[4]),
					postHeap: atoi(ss[5]),
					preObjs:  atoi(ss[6]),
					postObjs: atoi(ss[7]),
					allocs:   atoi(ss[8]),
					frees:    atoi(ss[9]),
				})
			}
		}
		consolidate(stats)
	}
}

func consolidate(stats []Stat) {
	marks := list(stats, func(s Stat) uint64 { return s.mark })
	sweeps := list(stats, func(s Stat) uint64 { return s.sweep })
	cleans := list(stats, func(s Stat) uint64 { return s.clean })
	cumm := list(stats, func(s Stat) uint64 { return s.mark + s.sweep + s.clean })
	mems := list(stats, func(s Stat) uint64 { return s.preHeap - s.postHeap })
	objs := list(stats, func(s Stat) uint64 { return s.preObjs - s.postObjs })

	// mark/sweep/clean
	markMean := mean(marks)
	sweepMean := mean(sweeps)
	cleanMean := mean(cleans)
	cummMean := mean(cumm)

	markMedian := median(marks)
	sweepMedian := median(sweeps)
	cleanMedian := median(cleans)
	cummMedian := median(cumm)

	markSd := sd(marks)
	sweepSd := sd(sweeps)
	cleanSd := sd(cleans)
	cummSd := sd(cumm)

	fmt.Printf("Total no. of GC        : %v\n", len(stats))
	fmt.Printf("Total gc time          : %v ms\n", sum(cumm))
	fmt.Printf("Total garbage colltd   : %v MB\n", sum(mems))
	fmt.Printf("Max/min mark-time      : %5v / %5v (ms)\n", max(marks), min(marks))
	fmt.Printf("Max/min sweep-time     : %5v / %5v (ms)\n", max(sweeps), min(sweeps))
	fmt.Printf("Max/min cleanup-time   : %5v / %5v (ms)\n", max(cleans), min(cleans))
	fmt.Printf("Max/min gc-time        : %5v / %5v (ms)\n", max(cumm), min(cumm))
	fmt.Printf("Max/min garbage colltd : %5v / %5v (ms)\n", max(mems), min(mems))
	fmt.Println("")
	fmt.Printf("                 mark       sweep      clean      cummulative\n")
	fmt.Printf("average        : %-10v %-10v %-10v %-10v\n", markMean, sweepMean, cleanMean, cummMean)
	fmt.Printf("median         : %-10v %-10v %-10v %-10v\n", markMedian, sweepMedian, cleanMedian, cummMedian)
	fmt.Printf("std-deviation  : %1.8f %-1.8f %-1.8f %-1.8f\n", markSd, sweepSd, cleanSd, cummSd)

	// memory and objects
	memsMean := mean(mems)
	objsMean := mean(objs)

	memsMedian := median(mems)
	objsMedian := median(objs)

	memsSd := sd(mems)
	objsSd := sd(objs)

	fmt.Println("")
	fmt.Printf("                 garbage-collected(MB)    obj-collected\n")
	fmt.Printf("average        : %-10v                %-10v\n", memsMean, objsMean)
	fmt.Printf("median         : %-10v                %-10v\n", memsMedian, objsMedian)
	fmt.Printf("std-deviation  : %1.9v                %1.9v\n", memsSd, objsSd)

	// histogram of mark/sweep/clean
	bins := maxBins(64, max(marks), max(sweeps), max(cleans), max(cumm))
	hsMarks := histogram(marks, bins)
	hsSweeps := histogram(sweeps, bins)
	hsCleans := histogram(cleans, bins)
	hsCumms := histogram(cumm, bins)
	fmt.Printf("\nHistogram for    marks      sweeps     cleans      full-gc\n")
	for i, bin := range bins {
		fmt.Printf("    < %5v ms : %-10v %-10v %-10v %-10v\n",
			bin, hsMarks[i], hsSweeps[i], hsCleans[i], hsCumms[i])
	}
	fmt.Println("")

	// histogram of garbage collected
	bsMems := maxBins(64, max(mems))
	hsMems := histogram(mems, bsMems)
	fmt.Printf("\nHistogram for garbage collected\n")
	for i, count := range hsMems {
		fmt.Printf("    < %5v MB : %-10v\n", bsMems[i], count)
	}
}

func atoi(s string) uint64 {
	x, err := strconv.ParseUint(s, 10, 64)
	if err != nil {
		panic(err)
	}
	return uint64(x)
}

func list(stats []Stat, fn func(Stat) uint64) []uint64 {
	ls := make([]uint64, 0, len(stats))
	for _, stat := range stats {
		ls = append(ls, fn(stat))
	}
	return ls
}

func max(list []uint64) uint64 {
	m := list[0]
	for _, val := range list {
		if val > m {
			m = val
		}
	}
	return m
}

func min(list []uint64) uint64 {
	m := list[0]
	for _, val := range list {
		if val < m {
			m = val
		}
	}
	return m
}

func sum(list []uint64) uint64 {
	sum := uint64(0)
	for _, val := range list {
		sum += val
	}
	return sum
}

func mean(list []uint64) uint64 {
	return sum(list) / uint64(len(list))
}

func median(list []uint64) uint64 {
	vals := make([]int, len(list))
	for _, val := range list {
		vals = append(vals, int(val))
	}
	sort.Ints(vals)
	return uint64(vals[len(vals)/2])
}

func sd(list []uint64) float64 {
	avg := mean(list)
	sum := uint64(0)
	for _, val := range list {
		d := int64(avg) - int64(val)
		sum += uint64(d * d)
	}
	return math.Sqrt(float64(sum) / float64(len(list)))
}

func histogram(list []uint64, bins []uint64) []uint64 {
	hist := make([]uint64, len(bins))
	for _, val := range list {
		for i, t := range bins {
			if val > t {
				continue
			}
			hist[i]++
			break
		}
	}
	return hist
}

func maxBins(start uint64, maxs ...uint64) []uint64 {
	maxbins := make([]uint64, 0)
	for _, max := range maxs {
		bins := []uint64{0}
		bin := start
		for ; bin < max; bin *= 2 {
			bins = append(bins, bin)
		}
		bins = append(bins, bin)
		if len(bins) > len(maxbins) {
			maxbins = bins
		}
	}
	return maxbins
}
