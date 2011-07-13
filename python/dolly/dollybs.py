# A simple cloner for Mantis
# Copyright (C) 2011 Bharathwaaj Srinivasan (bsrinivasan@mvista.com)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

"""
A simple cloner for Mantis.
"""
from BeautifulSoup import BeautifulSoup
from fetch import Fetch
from urlparse import urlparse, urlsplit

class Dolly:
    def __init__(self):
        pass

    def load(self, loadUrl):
        o = urlparse(loadUrl)
        print o.scheme
        print o.port
        print o
        o = urlsplit(loadUrl)
        print o.geturl()
        reader = Fetch()
        htmlFile = reader.get(loadUrl)
        soup = BeautifulSoup(htmlFile)
        form = soup.find('form')
        print form
        print form['action']
        print form['method']
        #print form['onsubmit']
        if 'action' in form:
            print form['action']
        if 'method' in form:
            print form['method']
        if 'onsubmit' in form:
            print form['onsubmit']

if __name__ == '__main__':
    handle = Dolly()
    handle.load('https://210.154.183.61:4443/mantis/login_page.php')
