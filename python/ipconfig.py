#!/usr/bin/python
try:
    import subprocess, os, sys, pynotify, socket
except:
    print "Error while loading external depencencies."
    print "Make sure 'os', 'pynotify', 'socket', 'sys', 'subprocess' are installed."
    exit()

def notify(message, icon):
    title_string = 'Auto eth0'
    
    if pynotify.init('ifconfig'):
        n = pynotify.Notification(title_string, message, icon)
        n.set_urgency(pynotify.URGENCY_CRITICAL)
        n.show()

def runBashScript(script):
    p = subprocess.Popen("%s" % (script), shell=True, executable = "/bin/bash")
    sts = os.waitpid(p.pid, 0)[1]
    if ((sts/256) == 0):
        notify("Yay! Success :)", "notification-network-ethernet-connected")
    else:
        notify("Booo.. Failure :(", "notification-network-ethernet-disconnected")

def reassignIpAddress():
    try:
        socket.gethostbyaddr(socket.gethostbyname(ip_address))
        notify("Booo.. Failure :(", "notification-network-ethernet-disconnected")
    except socket.herror:
        notify("Connection established! IP Assigned to  :)", "notification-network-ethernet-connected")

def main():
    print "Arguments passed ", "%s"%sys.argv[1]
    runBashScript(sys.argv[1])

if __name__ == '__main__':
    main()

command = os.WEXITSTATUS(os.system('ping -c 1 192.168.112.227'))
if command == 0:
    print "This IP is used by another person in your network."
else:
    print "Success"
