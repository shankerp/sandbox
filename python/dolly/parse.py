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
Handles parsing of HTML data
"""
from sgmllib import SGMLParser

class LoginFormParser(SGMLParser):
    def reset(self):
        SGMLParser.reset(self)
        self.url = ''
        self.method = ''
        self.onsubmit = ''

    def start_form(self, attrs):
        for k, v in attrs:
            if k == 'action':
                self.url = v
            if k == 'method':
                self.method = v
            if k == 'onsubmit':
                self.onsubmit = v
