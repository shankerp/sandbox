#!/usr/bin/perl
print "Please enter your private name:\n";
$name = <>;
chomp($name);
if (lc($name) ne "rachel" && lc($name) ne "bharath")
{
    print "Your name is Rachel!\n";
}
else
{
    print "Your name is not Rachel!\n";
}
