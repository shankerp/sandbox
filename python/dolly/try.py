import urllib2

theurl = 'https://210.154.183.61:4443/mantis/login_page.php'
req = urllib2.Request(theurl)
try:
    handle = urllib2.urlopen(req)
    print handle
except IOError, e:
    if hasattr(e, 'code'):
        if e.code != 401:
            print 'We got another error'
            print e.code
        else:
            print e.headers
