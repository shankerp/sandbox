#!/usr/bin/python

try:
    import subprocess, os, sys, pynotify
except:
    print "Error while loading external depencencies."
    print "Make sure 'os' and 'pynotify' is installed."
    exit()

def notify(message, icon):
    title_string = 'Build Output'
    
    if pynotify.init('Make Monitor'):
        n = pynotify.Notification(title_string, message, icon)
        n.set_urgency(pynotify.URGENCY_CRITICAL)
        n.show()

def runBashScript(script):
    p = subprocess.Popen("%s" % (script), shell=True, executable = "/bin/bash")
    sts = os.waitpid(p.pid, 0)[1]
    if ((sts/256) == 0):
        notify("Yay! Success :)", "emblem-favorite")
    else:
        notify("Booo.. Failure :(", "dialog-warning")

def main():
    print "Arguments passed ", "%s"%sys.argv[1]
    runBashScript(sys.argv[1])

if __name__ == '__main__':
    main()
