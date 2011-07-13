#!/usr/bin/python

import ConfigParser
import subprocess
import os

class ConfigError(Exception):
    pass

def executeCommand(script, envvars):
    buildenv = os.environ
    for name, value in envvars:
        buildenv[name] = value
    p = subprocess.Popen("%s" % (script), shell=True, executable = "/bin/bash", env=buildenv)
    sts = os.waitpid(p.pid, 0)[1]
    if ((sts/256) == 0):
        notify("Yay! Success :)", "emblem-favorite")
    else:
        notify("Booo.. Failure :(", "dialog-warning")

class ConfigFileHandler():
    """Ini File Handler
        Parses the ini file and stores the information
     obtained from the same.
    """
    def __init__(self):
        self.filename = ""
        self.sections = []
        self.cfg = ConfigParser.RawConfigParser()

    def parseConfigFile(self, filename):
        config = []
        try:
            self.cfg.read(filename)
        except ConfigParser.Error, exc:
            raise ConfigError("Error reading config file %r : %s" %
                    (filename, str(exc)))
        self.sections = self.cfg.sections()
        try:
            self.sections.remove['GLOBALS']
        except:
            print 'WARNING! No \'GLOBALS\' section found in config file'
        print self.cfg.sections()
        for i in cfg.sections():
            print "Section name %s" % i
            for name, value in cfg.items(i):
                print "name is %s Value is %s" % (name, value)

    def updateConfigFile(self, pkgName, envvars):
        pass

if __name__ == '__main__':
    handle = ConfigFileHandler()
    handle.parseConfigFile('example.cfg')
    #readConfigFile()
    #writeConfigFile()
