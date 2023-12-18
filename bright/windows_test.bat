@echo off
rem Run make
make

rem Run bright yispTest.lisp yispResults.txt
bright yispTest.lisp >> yispResults.txt

rem peform unit test on output
rem unfortunately wont represent color if sent to a file for output
py test.py