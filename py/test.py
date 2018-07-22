#! /usr/bin/env python

import unittest

class Test( unittest.TestCase ) :
    def setUp( self ) :
        print "Setting up ..."

    def tearDown( self ) :
        print "Tearing Down ... "

    def testcase1( self ) :
        print "testcase1"

    def testcase2( self ) :
        print "testcase2"


def suite():
    suite = unittest.TestSuite()
    suite.addTest(Test('testcase1'))
    suite.addTest(Test('testcase2'))
    return suite


if __name__ == '__main__' :
    unittest.main(defaultTest='suite')
