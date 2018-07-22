message = 'In scope'

def scope1function() :
    global message
    message += ' In scope1function'
    print message

print __builtin__.all
