@echo off
rem Run make
make

rem Run bright yispTest.lisp yispResults.txt
bright yispTest.lisp >>  yispResults.txt

rem Run unit test