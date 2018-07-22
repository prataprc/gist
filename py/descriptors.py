#! /usr/bin/env python

class EmailAddress(object):
    def _set_email(self, email):
        print "set", email
        self._email = email
    def _get_email(self):
        print "get", self._email
        return self._email
    email = property(_get_email, _set_email)

e = EmailAddress()
e.email = [ 'hello@world' ]
e.email.append( 'ok@world' )

e.email
