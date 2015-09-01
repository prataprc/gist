package main

import "runtime"
import "fmt"
import "strconv"
import "strings"

func main() {
	var ms runtime.MemStats
	runtime.ReadMemStats(&ms)
	for i := 0; i < 10000; i++ {
		memstatsRepr(&ms)
	}
}

var fmsg = ` [Info] memstats {
"Alloc":%v, "TotalAlloc":%v, "Sys":%v, "Lookups":%v, "Mallocs":%v,
"Frees":%v, "HeapAlloc":%v, "HeapSys":%v, "HeapIdle":%v, "HeapInuse":%v,
"HeapReleased":%v, "HeapObjects":%v, "StackInuse":%v, "StackSys":%v,
"MSpanInuse":%v, "MSpanSys":%v, "MCacheInuse":%v, "MCacheSys":%v,
"BuckHashSys":%v, "GCSys":%v, "OtherSys":%v, "NextGC":%v, "LastGC":%v,
"PauseTotalNs":%v, "PauseNs":%v, "PauseEnd":%v, "NumGC":%v, "EnableGC":%v,
"DebugGC":%v, "BySize":%v
}`

func memstatsRepr(ms *runtime.MemStats) {
	var s [256]string

	for i, item := range ms.PauseNs {
		s[i] = strconv.Itoa(int(item))
	}
	PauseNs := "[" + strings.Join(s[:], ", ") + "]"
	for i, item := range ms.PauseEnd {
		s[i] = strconv.Itoa(int(item))
	}
	PauseEnd := "[" + strings.Join(s[:], ", ") + "]"
	for i, item := range ms.BySize {
		s[i] = fmt.Sprintf(
			`{"Size":%v, "Mallocs": %v, "Frees": %v}`,
			item.Size, item.Mallocs, item.Frees)
	}
	BySize := "[" + strings.Join(s[:len(ms.BySize)], ", ") + "]"

	fmsg = strings.Replace(fmsg, "\n", "", -1)
	fmt.Printf(
		fmsg,
		ms.Alloc, ms.TotalAlloc, ms.Sys, ms.Lookups, ms.Mallocs,
		ms.Frees, ms.HeapAlloc, ms.HeapSys, ms.HeapIdle, ms.HeapInuse,
		ms.HeapReleased, ms.HeapObjects, ms.StackInuse, ms.StackSys,
		ms.MSpanInuse, ms.MSpanInuse, ms.MCacheInuse, ms.MCacheSys,
		ms.BuckHashSys, ms.GCSys, ms.OtherSys, ms.NextGC, ms.LastGC,
		ms.PauseTotalNs, PauseNs, PauseEnd, ms.NumGC, brepr(ms.EnableGC),
		brepr(ms.DebugGC), BySize)
	fmt.Println()
}

func brepr(v bool) string {
	if v {
		return "True"
	}
	return "False"
}
