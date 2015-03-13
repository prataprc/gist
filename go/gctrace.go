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
	stopw    uint64 // stop the world GC
	sweep    uint64 // sweeping
	mark     uint64 // marking
	waitwork uint64 // wait-for-worker threads to finish
	meanHeap uint64 // size of mean live heap after the previous GC
	currHeap uint64 // full heap size (including garbage) before the current GC.
	objs     uint64 // total number of objects in heap (including garbage)
	allocs   uint64 // total number of memory allocation
	frees    uint64 // total number of free operations.
}

// Regular expression that parses
// go1.2:
//      gc131(8): 14+133+6 ms, 4296 -> 2217 MB
//      888433 -> 463452 (22763539-22300087) objects,
//      1(6) handoff, 92(69055) steal, 281/94/564 yields
// go1.3:
//      gc225(8): 16+12+141497+18 us, 420 -> 840 MB,
//      10506401 (1890684303-1880177902) objects,
//      76587/69278/0 sweeps, 12470(779109) handoff, 39(360) steal, 54880/10658/64 yields
var pattern = `^gc[0-9]+\([0-9]+\): ([0-9]*)\+([0-9]*)\+([0-9]*)\+([0-9]*) us, ([0-9]*) -> ([0-9]*) MB, ([0-9]*) \(([0-9]*)-([0-9]*)\).*`
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
					stopw:    atoi(ss[1]),
					sweep:    atoi(ss[2]),
					mark:     atoi(ss[3]),
					waitwork: atoi(ss[4]),
					meanHeap: atoi(ss[5]),
					currHeap: atoi(ss[6]),
					objs:     atoi(ss[7]),
					allocs:   atoi(ss[8]),
					frees:    atoi(ss[9]),
				})
			}
		}
		if len(stats) > 0 {
			consolidate(stats)
		}
	}
}

func consolidate(stats []Stat) {
	stopws := list(stats, func(s Stat) uint64 { return s.stopw })
	sweeps := list(stats, func(s Stat) uint64 { return s.sweep })
	marks := list(stats, func(s Stat) uint64 { return s.mark })
	waitwrks := list(stats, func(s Stat) uint64 { return s.waitwork })
	cumm := list(stats, func(s Stat) uint64 { return s.stopw + s.sweep + s.mark + s.waitwork })
	mems := list(stats, func(s Stat) uint64 { return s.currHeap - s.meanHeap })

	// mark/sweep/clean
	stopwMean, stopwMedian, stopwSd := mean(stopws), median(stopws), sd(stopws)
	sweepMean, sweepMedian, sweepSd := mean(sweeps), median(sweeps), sd(sweeps)
	markMean, markMedian, markSd := mean(marks), median(marks), sd(marks)
	waitwMean, waitwMedian, waitwSd := mean(waitwrks), median(waitwrks), sd(waitwrks)
	cummMean, cummMedian, cummSd := mean(cumm), median(cumm), sd(cumm)

	fmt.Printf("Total no. of GC        : %v\n", len(stats))
	fmt.Printf("Total gc time          : %v us\n", sum(cumm))
	fmt.Printf("Total garbage colltd   : %v MB\n", sum(mems))
	fmt.Printf("Max/min stop-word-time : %5v / %5v (us)\n", max(stopws), min(stopws))
	fmt.Printf("Max/min sweep-time     : %5v / %5v (us)\n", max(sweeps), min(sweeps))
	fmt.Printf("Max/min mark-time      : %5v / %5v (us)\n", max(marks), min(marks))
	fmt.Printf("Max/min wait-on-worker : %5v / %5v (us)\n", max(waitwrks), min(waitwrks))
	fmt.Printf("Max/min gc-time        : %5v / %5v (us)\n", max(cumm), min(cumm))
	fmt.Printf("Max/min garbage colltd : %5v / %5v (us)\n", max(mems), min(mems))
	fmt.Println("")
	fmt.Printf("                 stopw      sweep      mark       waitwrk    cummulative\n")
	fmt.Printf("average        : %-10v %-10v %-10v %-10v %-10v\n", stopwMean, sweepMean, markMean, waitwMean, cummMean)
	fmt.Printf("median         : %-10v %-10v %-10v %-10v %-10v\n", stopwMedian, sweepMedian, markMedian, waitwMedian, cummMedian)
	fmt.Printf("std-deviation  : %-1.8f %-1.8f %-1.8f %-1.8f %-1.8f\n", stopwSd, sweepSd, markSd, waitwSd, cummSd)

	// memory and objects
	memMean, memMedian, memSd := mean(mems), median(mems), sd(mems)

	fmt.Println("")
	fmt.Printf("                 garbage-collected(MB)\n")
	fmt.Printf("average        : %-10v \n", memMean)
	fmt.Printf("median         : %-10v \n", memMedian)
	fmt.Printf("std-deviation  : %1.9v \n", memSd)

	// histogram of mark/sweep/clean
	bins := maxBins(64, max(stopws), max(sweeps), max(marks), max(waitwrks), max(cumm))
	hsStopw := histogram(stopws, bins)
	hsSweeps := histogram(sweeps, bins)
	hsMarks := histogram(marks, bins)
	hsWaitw := histogram(waitwrks, bins)
	hsCumms := histogram(cumm, bins)
	fmt.Printf("\nHistogram for    stopw      sweeps     marks      waitwrks    full-gc\n")
	for i, bin := range bins {
		fmt.Printf("    < %5v us : %-10v %-10v %-10v %-10v %-10v\n",
			bin, hsStopw[i], hsSweeps[i], hsMarks[i], hsWaitw[i], hsCumms[i])
	}
	fmt.Println("")

	// histogram of garbage collected
	bins = maxBins(64, max(mems))
	hsMems := histogram(mems, bins)
	fmt.Printf("\nHistogram for garbage collected\n")
	for i, count := range hsMems {
		fmt.Printf("    < %5v MB : %-10v\n", bins[i], count)
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
