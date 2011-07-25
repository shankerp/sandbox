#!/usr/bin/python

import argparse
import model
import view
import sys
import os

class Menu(argparse.Action):
    def __call__(self, parser, namespace, values, option_string=None):
        listy = model.filesWithExtension(os.getcwd(), 'cfg');
        #TODO Error checking with option to provide the cfg file directory
        view.printListWithBullets(listy)
        try:
            select = model.readInput('Enter which platform: ', range(0, len(listy)))
        except:
            view.printQuit()
            return
        setattr(namespace, self.dest, listy[select[0]])

class Deps(argparse.Action):
    def __call__(self, parser, namespace, values, option_string=None):
        print 'TODO'

class Controller(object):
    def __init__(self):
        self.handle = None
        self.__sections = None
        self.globalcfg = None
        self.globalcmd = None

    def prepare(self, configfile):
        self.handle = model.ConfigFileHandler()
        self.handle.parseConfigFile(configfile)
        self.__sections = self.handle.sections()
        try:
            self.globalcfg = self.handle.items('GLOBALS')
            self.globalcmd = self.handle.get('GLOBALS', 'COMMAND', True)
            self.__sections.remove('GLOBALS')
        except:
            print 'WARNING! No \'GLOBALS\' section found in config file'

    def getSections(self):
        return self.__sections

    def getPackagesToBuild(self):
        view.printListWithBullets(self.__sections)
        try:
            option = model.readInput('Enter the packages to build', range(0, len(self.__sections)), multiple=True)
        except:
            view.printQuit()
            raise ValueError('I Quit!')
        return option

    def buildPackages(self, packages):
        for count in packages:
            section = self.__sections[count]
            try:
                self.handle.get(section, 'COMMAND')
            except:
                self.handle.set(section, 'COMMAND', self.globalcmd)
            envvars = self.globalcfg[:]
            items = self.handle.items(section)
            envvars.extend(items)
            rv = model.executeCommand(envvars)
            if not rv:
                view.notify("Booo.. Failure :(", "dialog-warning")
        else:
            view.notify("Yay! Success :)", "emblem-favorite")

    def run(self):
        view.printListWithBullets(self.__sections)
        for section in self.__sections:
            try:
                self.handle.get(section, 'COMMAND')
            except:
                self.handle.set(section, 'COMMAND', self.globalcmd)
            envvars = self.globalcfg[:]
            items = self.handle.items(section)
            envvars.extend(items)
            rv = model.executeCommand(envvars)

if __name__ == '__main__':
    controller = Controller()
    controller.prepare('example.cfg')
    controller.run()
