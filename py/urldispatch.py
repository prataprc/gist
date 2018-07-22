import re

URLSEP = '/'
re_name = re.compile( r"([^{]*)(\{[^{}]+\})?(.+)?" )

def _make_regex( pattern ):
    segs = pattern.split( URLSEP )
    regex = r'^'
    for seg in segs :
        if not seg : continue
        regex += '/'
        prefix, name, suffix = re_name.match( seg ).groups()
        if name :
            name = name[1:-1]
        try :
            name, patt = name.split(':')
        except :
            patt = None
        regex += prefix if prefix else ''
        if name and patt :
            regex += '(?P<%s>%s)' % (name, patt)
        elif patt :
            regex += '(%s)' % patt
        elif name and suffix :
            regex += '(?P<%s>.+(?=%s))' % (name, suffix)
        elif name and name[0] == '*' :
            regex += '(?P<%s>.+)' % name[1:]
        elif name :
            regex += '(?P<%s>[^/]+)' % name
        regex += suffix if suffix else ''
    regex += '$'
    return regex

cases = [
    '/hello/world',
    '/{hello}/{world}',
    '/he{ll}o/{wo:.o}rld',
    '/hel{lo}/wo{rl}d/{*remains}',
]

cases = [ (x, re.compile(_make_regex(x)) ) for x in cases ]
for x, regex in cases :
    regexc = _make_regex(x)
    m = regex.match( '/hello/world/how/are' )
    print( x, regexc, m and m.groupdict() )
