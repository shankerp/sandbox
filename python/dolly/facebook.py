import cookielib
import os
import urllib
import urllib2

# set these to whatever your fb account is
fb_username = "cel_bsrinivasan"
fb_password = "welcome"

cookie_filename = "facebook.cookies"

class WebGamePlayer(object):

    def __init__(self, login, password):
        """ Start up... """
        self.login = login
        self.password = password

        self.cj = cookielib.MozillaCookieJar(cookie_filename)
        if os.access(cookie_filename, os.F_OK):
            self.cj.load()
        self.opener = urllib2.build_opener(
            urllib2.HTTPRedirectHandler(),
            urllib2.HTTPHandler(debuglevel=0),
            urllib2.HTTPSHandler(debuglevel=0),
            urllib2.HTTPCookieProcessor(self.cj)
        )
        self.opener.addheaders = [
            ('User-agent', ('Mozilla/4.0 (compatible; MSIE 6.0; '
                           'Windows NT 5.2; .NET CLR 1.1.4322)'))
        ]

        # need this twice - once to set cookies, once to log in...
        print self.loginToFacebook()
        print self.loginToFacebook()

        self.cj.save()

    def loginToFacebook(self):
        """
        Handle login. This should populate our cookie jar.
        """
        login_data = urllib.urlencode({
            'email' : self.login,
            'pass' : self.password,
        })
        #response = self.opener.open("https://login.facebook.com/login.php", login_data)
        response = self.opener.open("https://210.154.183.61:4443/mantis/login.php", login_data)
        return ''.join(response.readlines())

test = WebGamePlayer(fb_username, fb_password)
