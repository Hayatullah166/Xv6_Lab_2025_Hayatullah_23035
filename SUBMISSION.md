# Problem Set #1 — xv6 util lab (Hayatullah 23035)

## outputs (inside xv6 shell)

$ echo > b
$ mkdir a
$ echo > a/b
$ mkdir a/aa
$ echo > a/aa/b
$ finfexec . b -exec echo found
exec finfexec failed
$ findexec . b -exec echo found
found ./b
found ./a/b
found ./a/aa/b
$ sleep 5

$ sixfive sixfive.txt
5
100
18
6

$ memdump
Example 1:
61810
2025
Example 2:
a string
Example 3:
another
Example 4:
B
1996488704
1684828783

Example 5:
hello

$ find . b
./b
./a/b
./a/aa/b

$ findexec . b -exec echo echo found
echo found ./b
echo found ./a/b
echo found ./a/aa/b
