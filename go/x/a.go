package checkinit

type Logger interface {
    Print(s string)
}

func Myfunc(logger Logger) {
    logger.Print("hello world")
}
