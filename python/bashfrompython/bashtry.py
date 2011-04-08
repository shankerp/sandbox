#!/usr/bin/env python
import subprocess

#Create variables out of shell commands
MESSAGES = "tail /var/log/messages"
SPACE = "df -h"
BUILD = "make"

#Places variables into a list/array
#cmds = [MESSAGES, SPACE]
cmds = [BUILD]

#Create a function, that takes a list parameter
#Function uses default keyword parameter of cmds
def runCommands(commands=cmds):
    #Iterates over list, running statements for each item in the list
    count=0
    for cmd in cmds:
        count+=1
        print "Running Command Number %s" % count
        subprocess.call(cmd, shell=True)

#Function is called
runCommands()
