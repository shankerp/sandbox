#!/usr/bin/python

import unittest
import model

"""
--menu testcases
1-0
0-1
0-3
1-4
-1--5
-2-3
2-3
0,1-3
1,2-3
1,1-3
2-2,3
1-1,3
"""
__author__ = "Bharathwaaj Srinivasan (bharathwaaj.s@gmail.com)"
__version__ = "$Revision: 0.1 $"
__date__ = "$Date: 25/07/2011 07:42 $"
__copyright__ = "Copyright (c) 2011 Bharathwaaj Srinivasan"
__license__ = "LGPL"

"""
                    ("1-0", )
                    ("0-1", )
                    ("0-3", )
                    ("1-4", )
                    ("-1--5", )
                    ("-2-3", )
                    ("0,1-3", )
                    """
class TestMultipleOptions(unittest.TestCase):
    knownValues = ( ("2-3",   [1, 2]),
                    ("1,2-3", [0, 1, 2]),
                    ("1,1-3", [0, 1, 2]),
                    ("2-2,3", [1, 2]),
                    ("1-1,3", [0, 2]))

    def testForKnownValues(self):
        for string, listy in self.knownValues:
            result = model.parseMultipleOptions(string)
            self.assertEqual(listy, result)

if __name__ == "__main__":
    unittest.main()
