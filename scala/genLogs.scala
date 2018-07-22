// Usage:
// <program-name>  <seed>  <count>

val seed = args(0).toLong
val countLines = args(1).toLong

import java.util.{Random, Date}

val rnd = new Random(seed)

var linesPerPage = 2000 + rnd.nextInt(2000)
var currLine = 0

val milliPerDay = 24l*3600*1000
val dateStart = new Date((new Date).getTime - 1000*milliPerDay)    // 1000 days back
var currDate = dateStart

def createIps(n:Int) = {
  var ips = List[Int]()
  (1 to n) foreach {i=>
    ips ::= rnd.nextInt
  }
  ips
}

var currIps = createIps(linesPerPage)

def formatIp(ip:Int) = {
  "%d.%d.%d.%d" format (
      (ip>>24) & 0xff,
      (ip>>16) & 0xff,
      (ip>>8) & 0xff,
      (ip) & 0xff)
}

object someString {
  val strings = List(
      """"GET /robots.txt HTTP/1.0" 404 169 "-" "CatchBot/3.0; +http://www.catchbot.com" "-" """,
      """"GET /experiments/jigsaw/j.js HTTP/1.1" 200 5387 "http://lavadip.com/experiments/jigsaw/" "Mozilla/5.0 (Windows NT 6.1; WOW64) Chrome/13.0.782.55" "-" """
  )

  val count = strings.length
  def get = {
    strings(rnd.nextInt(count))
  }
}

val dateFormatter = new java.text.SimpleDateFormat("[dd/MMM/yyyy:HH:mm:ss Z] ")

(1l to countLines) foreach {i =>
  if (currLine > linesPerPage) {
    linesPerPage = 2000 + rnd.nextInt(2000)     // new value
    currDate = new Date(currDate.getTime + milliPerDay)
    currIps = createIps(linesPerPage/4 + rnd.nextInt(linesPerPage))
    currLine = 0
  }

  val ip = currIps(rnd.nextInt(currIps.length))
  println(formatIp(ip) + " - - " + dateFormatter.format(currDate) + someString.get)

  currLine += 1
}
