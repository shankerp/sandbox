#!/usr/bin/python

import ConfigParser
import subprocess
import os
import re

class ConfigError(Exception):
    pass

def executeCommand(script, envvars):
    buildenv = os.environ
    for name, value in envvars:
        buildenv[name] = value
    p = subprocess.Popen("%s" % (script), shell=True, executable = "/bin/bash", env=buildenv)
    sts = os.waitpid(p.pid, 0)[1]
    if ((sts/256) == 0):
        return 1
    else:
        return -1

class ConfigDict(dict):
    def __init__(self):

    def handleBackTicks(value):
        pattern = re.compile('`(.*)`')
        try:
            out = pattern.search(value).groups()
            proc = subprocess.Popen(out[0], stdout=subprocess.PIPE, shell=True)
            (out, err) = proc.communicate()
            print "program output:", repr(out)
        except AttributeError:
            out = value
        return out

class ConfigFileHandler(object):
    """Ini File Handler
        Parses the ini file and stores the information
     obtained from the same.
    """
    def __init__(self):
        self.filename = ""
        self.cfg = ConfigParser.RawConfigParser()
        self.cfg.optionxform = str

    def parseConfigFile(self, filename):
        config = []
        try:
            self.cfg.read(filename)
        except ConfigParser.Error, exc:
            raise ConfigError("Error reading config file %r : %s" %
                    (filename, str(exc)))
        print self.cfg.sections()
        for i in self.cfg.sections():
            print "Section name %s" % i
            for name, value in self.cfg.items(i):
                print "name is %s Value is %s" % (name, value)

    def getSections(self):
        return self.cfg.sections()

    def getItemsForSection(self, section):
        return self.cfg.items(section)

    def updateConfigFile(self, pkgName, envvars):
        pass

if __name__ == '__main__':
    handle = ConfigFileHandler()
    handle.parseConfigFile('example.cfg')
    #readConfigFile()
    #writeConfigFile()
