# Assignment – Optional Challenge Exercises  
###Hayatullah_23035
## Output 
### 1. Uptime Program
xv6 kernel is booting

hart 2 starting  
hart 1 starting  
init: starting sh  
$ uptime  
Uptime (ticks): 412  

---

### 2. Find with Regex
xv6 kernel is booting  

hart 2 starting  
hart 1 starting  
init: starting sh  
$ echo > b  
$ mkdir a  
$ echo > a/b  
$ mkdir a/aa  
$ echo > a/aa/b  
$ find . b  
./zombie  
./b  
./a/b  
./a/aa/b  
$ findexec . b -exec echo found  
found ./b  
found ./a/b  
found ./a/aa/b  
$ find . ".*b"  
$ find . "a.*"  
$  

---

### 3. Shell Modifications
xv6 kernel is booting  

hart 2 starting  
hart 1 starting  
init: starting sh  

$ sleep 10 &  
$ wait  
$  

xv6 kernel is booting  
hart 1 starting  
hart 2 starting  

init: starting sh  

$ echo "echo hello" > script  
$ sh < script  
hello  
$  

xv6 kernel is booting  

hart 2 starting  
hart 1 starting  
init: starting sh  
$ mysh  
$ echo hello  
hello  
$ !!  
echo hello  
hello  
$ ec<TAB>  
exec
