package main
import (
    "encoding/json"
    "fmt"
)

var val = `{ "name": "Franklin",
"members": ["Kriton","Ernie","Margot","Sundaresan","Lenora","Robin","Rick","Ranjit","Kathryn","Tracey","Bob","Charley","Andre","Miek"],
"language": "python" }`

func main() {
    // Map of interfaces can receive any value types
    value := map[string]interface{}{}

    fmt.Println(json.Unmarshal([]byte(val), &value))
    fmt.Println(value)
}
