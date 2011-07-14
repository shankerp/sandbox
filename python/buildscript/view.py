#!/usr/bin/python

try:
    import sys
    import pynotify
except:
    print "Error while loading external depencencies."
    print "Make sure 'pynotify' is installed."
    exit()

def printOptions():
    print 'Following options are available'
    print '1. Build all packages'
    print '2. Build a single package'
    print '3. Build a range of packages'
    print '4. Install system dependencies'
    print '5. Help'

def notify(message, icon):
    title_string = 'Build Output'
    
    if not pynotify.init("Make Monitor"):
        sys.exit(1)

    n = pynotify.Notification(title_string, message, icon)

    if not n.show():
        print "Failed to send notification"
        sys.exit(1)

def getPackageDetails():
    """
        Helper function for updating ini file with new package.

        Gets the new package name and other environment variables
        that should be used when building.
    """
    package = raw_input('Insert package name with path to build --> ')
    print 'Add environment variables to build'
    envvars = []
    try:
        while (True):
            try:
                env = raw_input('Environment variable name --> ')
                value = raw_input('Environment variable value --> ')
            except:
                raise StopIteration()
            envvars.append((env, value))
    except StopIteration:
        pass
    print ""
    return package, envvars

def printListWithBullets(alist):
    """
        Prints the items of a list with numbered bullets.
    """
    i = 1
    for item in alist:
        sys.stdout.write(str(i))
        sys.stdout.write('. ')
        print item
        i += 1

if __name__ == '__main__':
   printOptions() 
   package, envvars = getPackageDetails()
   print package
   printListWithBullets(envvars)
