#!/usr/bin/python

import ConfigParser
import subprocess
import os
import re
from types import StringType
from ordereddict import OrderedDict
from string import Template

class ConfigError(Exception):
    pass

def uniqify(listy):
    seen = set()
    seen_add = seen.add
    return [ x for x in listy if x not in seen and not seen_add(x)]

def parseMultipleOptions(string):
    values = string.split(',')
    result = []
    for i in values:
        i = i.strip(' ')
        j = i.split('-')
        if len(j) is 1:
            result.append(int(i) - 1)
        elif len(j) is 2:
            result.extend(range(int(j[0]) - 1, int(j[1])))
        else:
            raise IOError('refusenik user')
    return uniqify(result)

def readInput(prompt, accepted, multiple=False, retries=5):
    while True:
        ok = raw_input(prompt)
        try:
            int(ok)
            if int(ok) - 1 in accepted:
                return [int(ok) - 1]
        except:
            if multiple:
                try:
                    result = parseMultipleOptions(ok)
                    for i in result:
                        if i not in accepted:
                           raise ValueError('Invalid value') 
                    return result
                except:
                    print 'raised error'
                    pass
        retries = retries - 1
        if retries < 0:
            raise IOError('refusenik user')
        print 'Only follwing values are accepted: '
        for i in accepted: print i + 1

def executeCommand(envvars):
    buildenv = os.environ
    env = OrderedDict()
    for name, value in envvars:
        if name == 'COMMAND':
            commands = value.split(';')
        else:
            env[name] = value
    handleDollarValues(env)
    for key, value in env.items():
        buildenv[key] = value
    for cmd in commands:
        print 'executing cmd %s' % cmd
        p = subprocess.Popen("%s" % (cmd), shell=True, executable = "/bin/bash", env=buildenv)
        sts = os.waitpid(p.pid, 0)[1]
        if ((sts/256) != 0):
            return 0
    return 1

def filesWithExtension(directory, extension):
    pattern = '.*' + extension
    return [f for f in os.listdir(directory) if re.search(pattern, f)]

def handleDollarValues(dictionary):
    if type(dictionary) is not OrderedDict:
        raise TypeError('OrderedDict is expected')
    for key in dictionary.keys():
        s = Template(dictionary[key])
        value = s.substitute(dictionary)
        dictionary[key] = value

class ConfigDict(OrderedDict):
    def handleBackTicks(self, value):
        pattern = re.compile('`(.*)`')
        try:
            out = pattern.search(value).groups()
            proc = subprocess.Popen(out[0], stdout=subprocess.PIPE, shell=True)
            (out, err) = proc.communicate()
            pattern = re.compile('(.*)\n')
            try:
                out = pattern.search(out).groups()[0]
            except:
                pass
        except AttributeError:
            out = value
        return out

    def __setitem__(self, key, val):
        if type(val) is StringType:
            val = self.handleBackTicks(val)
        OrderedDict.__setitem__(self, key, val)

class ConfigFileHandler(object):
    """Ini File Handler
        Parses the ini file and stores the information
     obtained from the same.
    """
    def __init__(self):
        self.filename = ""
        self.cfg = None

    def locateConfigFiles(self):
        pass

    def parseConfigFile(self, filename):
        self.cfg = ConfigParser.ConfigParser(dict_type=ConfigDict)
        self.cfg.optionxform = str
        config = []
        try:
            self.cfg.read(filename)
        except ConfigParser.Error, exc:
            raise ConfigError("Error reading config file %r : %s" %
                    (filename, str(exc)))

    def sections(self):
        return self.cfg.sections()

    def get(self, section, option, raw=False):
        return self.cfg.get(section, option, raw)

    def set(self, section, option, value):
        return self.cfg.set(section, option, value)

    def items(self, section):
        return self.cfg.items(section)

    def updateConfigFile(self, pkgName, envvars):
        pass

if __name__ == '__main__':
    handle = ConfigFileHandler()
    handle.parseConfigFile('example.cfg')
