#!/usr/bin/perl
print "Please enter a string:\n";
$mystring = <>;
if($mystring =~ /\bWorld\b/i) { print "Yes\n"; }
##!/usr/bin/perl 
use 5.10.1;
use warnings;
use strict;

my $str = q/hello hello hello/;
my $count1 =()= $str =~ /(?=\bhello hello\b)/g;
say $count1;  # gives 2

my $count2 =()= $str =~ /\bhello\b/g;
say $count2;  # gives 3

