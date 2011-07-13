class Mantis:
    count = 1
    def GenerateNextURL(self):
        self.__class__.count += 1
        return "hello" + str(self.__class__.count)

if __name__ == '__main__':
    e = Mantis();
    url = e.GenerateNextURL()
    print "url got is %s" % url
    url = e.GenerateNextURL()
    print "url got is %s" % url
    url = e.GenerateNextURL()
    print "url got is %s" % url
    url = e.GenerateNextURL()
    print "url got is %s" % url
    url = e.GenerateNextURL()
    print "url got is %s" % url
