#########################################################################
# Author: 0054
# Created Time: 2016年06月25日 星期六 23时21分46秒
# File Name: git.sh
# Description: 
#########################################################################
#!/bin/bash

read a 

git add $a

git commit -m" update"

git push origin master
