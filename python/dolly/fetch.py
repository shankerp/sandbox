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
Handles network interactions
"""
import urllib

class Fetch:
    def get(self, url):
        sock = urllib.urlopen(url)
        resource = sock.read()
        sock.close()
        return resource

    def post(self, url, data):
        postData = urllib.urlencode(data)
        sock = urllib.urlopen(url, postData)
        resource = sock.read()
        sock.close()
        return resource

if __name__ == '__main__':
    handle = Fetch() 
    htmlFile = handle.get('https://210.154.183.61:4443/mantis/login_page.php')
    print htmlFile
