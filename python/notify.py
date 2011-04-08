#!/usr/bin/python

try:
    import pynotify, time
except:
    print "Error while loading external depencencies."
    print "Make sure 'pynotify' is installed."
    exit()

def main():
    title_string = 'Notifications'
    message = "Hello! This is a notification"
    icon = "emblem-favorite"
    if pynotify.init('Make Monitor'):
        n = pynotify.Notification(title_string, message, icon)
        n.set_urgency(pynotify.URGENCY_CRITICAL)
        n.show()
    title_string = "Updated Notification"
    message = "Hello! Updated notification"
    icon = "dialog-warning"
    n.update(title_string, message, icon);
    time.sleep(1)
    n.show()
    time.sleep(1)
    n.close()

if __name__ == '__main__':
    main()

