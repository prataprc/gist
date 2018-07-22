import akka.actor.{Actor,SupervisorFactory}
import akka.config.Supervision.{SupervisorConfig, OneForOneStrategy, Supervise, Permanent}
import akka.dispatch.{Dispatchers, MessageDispatcher}

import java.io.RandomAccessFile
import java.nio.ByteBuffer
import java.nio.channels.FileChannel

val ACTORS_COUNT = Runtime.getRuntime.availableProcessors
// Duration of the task that should be performed by the actor
val TASK_DURATION = 10000

/*
 * Initialization of the smart work stealing dispatcher that polls messages from
 * the mailbox of a busy actor and finds other actor in the pool that can process
 * the message.
 */
val workStealingDispatcher = Dispatchers.newExecutorBasedEventDrivenWorkStealingDispatcher("pooled-dispatcher")
  .withNewThreadPoolWithLinkedBlockingQueueWithUnboundedCapacity
  .setCorePoolSize(ACTORS_COUNT)
  .buildThreadPool

val filePath = new java.io.File(args(0))
val file = new RandomAccessFile(filePath,"r").getChannel.map(FileChannel.MapMode.READ_ONLY, 0, filePath.length.toInt)

case class ParseJob(start:Int, end:Int)

val result = scala.collection.mutable.LinkedList[(Int,Int)]()

object Parser {
  var countJobs = 0

  def addJob(j:ParseJob) = synchronized {
    countJobs += 1
    allParsers(0) ! j
  }
  def doneWithJob = synchronized {
    countJobs -= 1
    if (countJobs == 0) {
      allParsers foreach (_ ! "Shutdown")
    }
  }
}

class Parser(id:Int, zDispatcher: MessageDispatcher) extends Actor {
  self.id = "parser " + id
  self.dispatcher = zDispatcher

  case class Entry(ip:Int, date:Int, pos:Int)

  val monthValue = Map(
      "Jan" -> 1,
      "Feb" -> 2,
      "Mar" -> 3,
      "Apr" -> 4,
      "May" -> 5,
      "Jun" -> 6,
      "Jul" -> 7,
      "Aug" -> 8,
      "Sep" -> 9,
      "Oct" -> 9,
      "Nov" -> 11,
      "Dec" -> 12)

  def parseDate(buffer:ByteBuffer, posStart:Int) = {
    var pos = posStart
    var sub0 = 0
    while (buffer.get(pos) != slashByte) {
      sub0 *= 10
      sub0 += buffer.get(pos) - zeroByte
      pos += 1
    }
    pos += 1
    var sub1 = ""
    while (buffer.get(pos) != slashByte) {
      sub1 += buffer.get(pos).toChar
      pos += 1
    }
    pos += 1
    var sub2 = 0
    while (buffer.get(pos) != slashByte) {
      sub2 *= 10
      sub2 += buffer.get(pos) - zeroByte
      pos += 1
    }
    sub0 | (monthValue(sub1) << 8) | sub2 << 16
  }

  val zeroByte = '0'.toByte
  val nineByte = '9'.toByte
  val periodByte = '.'.toByte
  val spaceByte = ' '.toByte
  val slashByte = '/'.toByte
  val newLineByte = '\n'.toByte
  val openBracket = '['.toByte

  def parseLine(buffer:ByteBuffer, filePos:Int) = {
    // parse the line
    var pos = filePos
    var ip = 0
    var place = 0
    var parsedIp = false
    while(pos < buffer.capacity && !parsedIp) {
      val byte = buffer.get(pos)
      if (byte >= zeroByte && byte <= nineByte) {
        place *= 10
        place += (byte - zeroByte)
      } else if (byte == periodByte || byte == spaceByte) {
        ip <<= 8
        ip += place
        place = 0
      } else {
        parsedIp = true
      }
      pos += 1
    }
    while(buffer.get(pos) != openBracket) {
      pos += 1
    }
    /*
    println("pos:%d IP: %d.%d.%d.%d" format(filePos,
          ip>>24 & 0xff,
          ip>>16 & 0xff,
          ip>>8 & 0xff,
          ip & 0xff
    ))
    */

    Some(Entry(ip,parseDate(buffer, pos), filePos-2))
  }

  def readNextLine(buffer:ByteBuffer, posStart:Int) = {
    if (posStart != buffer.capacity) {
      val result = parseLine(buffer, posStart).get
      // skip to end of line
      var pos = posStart + 20
      var currByte = spaceByte
      while (currByte != newLineByte) {
        currByte = buffer.get(pos)
        pos+=1
      }
      Some(Entry(result.ip, result.date, pos))
    } else {
      None
    }
  }

  def readPrevLine(file:ByteBuffer, pos:Int) = {
    var currPos = pos
    if (currPos >= 0) {
      var currByte = spaceByte
      while (currPos > 0 && currByte != newLineByte) {
        currByte = file.get(currPos)
        currPos -= 1
      }
      parseLine(file, if (currPos > 0) currPos+2 else 0)

    } else {
      None
    }
  }

  def receive = {
    case job:ParseJob => {
        // self.reply("Actor " + self.id + " replied to " + message)
        // println(self.id + " rcvd job: " + job)

        val visitors = scala.collection.mutable.Set.empty[Int]

        val mid = (job.start + job.end) / 2 

        // seek to begin of line
        var curr = mid
        var currByte = file.get(curr)
        while(curr > job.start && currByte != newLineByte) {
          currByte = file.get(curr)
          curr -= 1
        }
        var checkpoint = if (curr > 0) curr+2 else 0
        // curr -= 1

        // get first entry from current position
        var firstEntry = readPrevLine(file, curr)
        var lastSameEntry = firstEntry
        var currEntry = firstEntry
        val beginEpoch = 
        if (firstEntry.isDefined) {


          // keep reading backwards until different date
          while (currEntry.isDefined && currEntry.get.date == firstEntry.get.date) {
            lastSameEntry = currEntry

            // Update counters
            visitors += currEntry.get.ip

            // Get prev entry
            currEntry = readPrevLine(file, currEntry.get.pos)
          }
          lastSameEntry.get.pos
        } else {
          firstEntry = readNextLine(file, curr)
          checkpoint = firstEntry.map(_.pos).getOrElse(checkpoint)
          checkpoint
        }



        // Start searching forwards
        // println("Searching forward from " + checkpoint)
        curr = checkpoint
        // get first entry from current position
        currEntry = firstEntry
        lastSameEntry = firstEntry

        // keep reading forwards until different date
        while (currEntry.isDefined && currEntry.get.date == firstEntry.get.date) {
          lastSameEntry = currEntry

          // Update counters
          visitors += currEntry.get.ip

          // Get prev entry
          currEntry = readNextLine(file, curr)
          curr = currEntry.map(_.pos).getOrElse(curr)
        }

        val endEpoch = lastSameEntry.get.pos

        println("Unique " + visitors.size)
        result.synchronized {
          result :+ (firstEntry.get.date, visitors.size)
        }

        if (beginEpoch > job.start && (beginEpoch) < job.end) {
          Parser addJob ParseJob(job.start, beginEpoch)
        }
        if (endEpoch < job.end && (endEpoch) > job.start) {
          Parser addJob ParseJob(endEpoch, job.end)
        }
        Parser doneWithJob
      }
    case "Shutdown" => exit
    case _ =>
  }

} 

val supervisor = SupervisorFactory(
  SupervisorConfig(
    OneForOneStrategy(List(classOf[Exception]), 1000, TASK_DURATION),
    {
     ((1 to ACTORS_COUNT) map (i => Supervise(Actor.actorOf(new Parser(i, workStealingDispatcher)).start, Permanent)
     )).toList
    }
    )).newInstance

// Starts supervisor and all supervised actors
supervisor.start

val allParsers = Actor.registry.actorsFor[Parser]
Parser addJob ParseJob(0, file.capacity)

