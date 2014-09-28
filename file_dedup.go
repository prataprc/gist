package main

import "fmt"
import "os"
import "log"
import "path/filepath"

func main() {
    filenames := []string{}
    filepath.Walk(".", func(path string, info os.FileInfo, err error) error {
        if err != nil {
            log.Fatal(err)
        }
        _, filename := filepath.Split(path)
        filenames = append(filenames, filename)
        return nil
    })
    for i, xname :=  range filenames {
        for _, yname := range filenames[i+1:] {
            // check whether the lengths are
            //x, y := len(xname), len(yname)
            //if float64((max(x,y) - min(x,y))) / float64(max(x,y)) > 0.33 {
            //    continue
            //}
            common := lcs(xname, yname)
            x, y, z := len(xname), len(yname), len(common)
            if (float64(z) / max(x,y)) < 0.66 {
                continue
            }
            fmt.Println(xname)
            fmt.Println("    ", yname)
            fmt.Println("    ", common)
        }
    }
}

func max(a, b int) float64 {
    if a > b {
        return float64(a)
    }
    return float64(b)
}

func min(a, b int) float64 {
    if a < b {
        return float64(a)
    }
    return float64(b)
}

//func lcs(a, b string) string {
//    aLen, bLen := len(a), len(b)
//    if aLen == 0 || bLen == 0 {
//        return ""
//    } else if a[aLen-1] == b[bLen-1] {
//        return lcs(a[:aLen-1], b[:bLen-1]) + string(a[aLen-1])
//    }
//    x := lcs(a, b[:bLen-1])
//    y := lcs(a[:aLen-1], b)
//    if len(x) > len(y) {
//        return x
//    }
//    return y
//}

func lcs(a, b string) string {
    arunes := []rune(a)
    brunes := []rune(b)
    aLen := len(arunes)
    bLen := len(brunes)
    lengths := make([][]int, aLen+1)
    for i := 0; i <= aLen; i++ {
        lengths[i] = make([]int, bLen+1)
    }
    // row 0 and column 0 are initialized to 0 already
    for i := 0; i < aLen; i++ {
        for j := 0; j < bLen; j++ {
            if arunes[i] == brunes[j] {
                lengths[i+1][j+1] = lengths[i][j] + 1
            } else if lengths[i+1][j] > lengths[i][j+1] {
                lengths[i+1][j+1] = lengths[i+1][j]
            } else {
                lengths[i+1][j+1] = lengths[i][j+1]
            }
        }
    }

    // read the substring out from the matrix
    s := make([]rune, 0, lengths[aLen][bLen])
    for x, y := aLen, bLen; x != 0 && y != 0; {
        if lengths[x][y] == lengths[x-1][y] {
            x--
        } else if lengths[x][y] == lengths[x][y-1] {
            y--
        } else {
        s = append(s, arunes[x-1])
        x--
        y--
        }
    }
    // reverse
    // string
    for i, j := 0, len(s)-1; i < j; i, j = i+1, j-1 {
        s[i], s[j] = s[j], s[i]
    }
    return string(s)
}
