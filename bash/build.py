#!/usr/bin/env python
import subprocess
import optparse
import re

homeDirUsage = """
du -sh $HOME | cut -f1
"""

ipaddress = """
/sbin/ifconfig -a | awk '/(cast)/ {print $2}' | cut -d':' -f2 | head -1
"""

"""
messages = "tail /var/log/messages"
space = "df -h"
listdir = "ls -l"

cmds = [messages, space, listdir]

def runCommands(commands = cmds):
    count = 0
    for cmd in cmds:
        count += 1
        print "Running Command Number %s" % count
        subprocess.call(cmd, shell=True)

runCommands()
"""
