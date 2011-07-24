import controller
import argparse

class Main(object):
    def __init__(self):
        self.controller = None

    def narrowDownMenu(self, configfile):
        print configfile
        self.controller = controller.Controller()
        self.controller.prepare(configfile)
        try:
            packages = self.controller.getPackagesToBuild()
        except:
            print 'What man! you made him quit!'
        self.controller.buildPackages(packages)
    
    def parse_args(self, args=None):
        parser = argparse.ArgumentParser(
                description='Build Script for Montavista Digital Media Framework')
        parser.add_argument('--menu', help='Displays a menu of options to choose', action=controller.Menu, nargs=0) 
        parser.add_argument('--deps', help='Installs dependency packages', action=controller.Deps, nargs=0) 
        args = parser.parse_args()
        if args.menu is not None:
            self.narrowDownMenu(args.menu)

def main():
    handle = Main()
    handle.parse_args()

if __name__ == '__main__':
    main()
