myName = 'prataprc'
thing1 = 'eyes'
thing2 = 'ears'
thing3 = 'nose'
           
console.log( "I am %s and I have:", myName, thing1, thing2, thing3);
console.log( "integet %d, float %f, url %o", 10, 10.2, google.com )


// Writes a message to the console with the visual "info" icon and color coding
// and a hyperlink to the line where it was called.
console.info(object[, object, ...])
// Writes a message to the console, including a hyperlink to the line where it
// was called.
console.debug(object[, object, ...])
// Writes a message to the console with the visual "warning" icon and color
// coding and a hyperlink to the line where it was called.
console.warn(object[, object, ...])
// Writes a message to the console with the visual "error" icon and color
// coding and a hyperlink to the line where it was called.
console.error(object[, object, ...])

// Tests that an expression is true. If not, it will write a message to the
// console and throw an exception.
console.assert(expression[, object, ...])


// Prints an interactive listing of all properties of the object. This looks
// identical to the view that you would see in the DOM tab.
console.dir(object)
// Prints the XML source tree of an HTML or XML element. This looks identical
// to the view that you would see in the HTML tab. You can click on any node to
// inspect it in the HTML tab.
console.dirxml(node)

// Prints an interactive stack trace of JavaScript execution at the point where
// it is called.
// The stack trace details the functions on the stack, as well as the values
// that were passed as arguments to each function. You can click each function
// to take you to its source in the Script tab, and click each argument value to
// inspect it in the DOM or HTML tabs.
console.trace()

// Writes a message to the console and opens a nested block to indent all future
// messages sent to the console. Call console.groupEnd() to close the block.
console.group(object[, object, ...])
// Closes the most recently opened block created by a call to console.group.
console.groupEnd()

// Creates a new timer under the given name. Call console.timeEnd(name) with
// the same name to stop the timer and print the time elapsed..
console.timeEnd(name)
// Stops a timer created by a call to console.time(name) and writes the time
// elapsed.
console.time(name)
// Turns on the JavaScript profiler. The optional argument title would contain
// the text to be printed in the header of the profile report.
console.profile([title])
// Turns off the JavaScript profiler and prints its report.
console.profileEnd()

// Writes the number of times that the line of code where count was called was
// executed. The optional argument title will print a message in addition to
// the number of the count.
console.count([title])
