#!/usr/bin/python

import model
import view
import sys

"""
        try:
            self.sections.remove['GLOBALS']
        except:
            print 'WARNING! No \'GLOBALS\' section found in config file'
"""

def main(configfile):
    handle = model.ConfigFileHandler()
    handle.parseConfigFile(configfile)
    sections = handle.getSections()
    view.printListWithBullets(sections)
    items = handle.getItemsForSection(sections[0])
    print items
    rv = model.executeCommand("echo $MODII_TARGET_ARCH", items)
    if rv == 1:
        view.notify("Yay! Success :)", "emblem-favorite")
    else:
        view.notify("Booo.. Failure :(", "dialog-warning")

if __name__ == '__main__':
    main('example.cfg')
