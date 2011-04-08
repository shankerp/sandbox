import sys, os, socket

# Stores the IP Address
ip_address = sys.argv[1]

try:
    socket.gethostbyaddr(socket.gethostbyname(ip_address))
    # If previous line doesn't throw exception, IP address is being used by someone
    print "No"
except socket.herror:
    # socket.gethostbyaddr() throws error, so IP is not being used at present
    # You can write os.system() and give it ifconfig and route commands as parameter.
    print "Yes"
