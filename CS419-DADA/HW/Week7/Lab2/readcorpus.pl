#!/usr/bin/perl

use strict;
use warnings;
use Getopt::Long;
use File::Basename;
use JSON;

my $file;
my $prog = basename($0);
my $args = GetOptions ("file=s" => \$file); 
my $json = new JSON;
my $jsontext;
my $urldata = {};

help() if (!$file);

# Load file.
{
    local $/ = undef;
    die "Unable to open $file" unless open (FILE, "<$file");
    $jsontext = <FILE>;
}

# Interact with JSON hash
die "Unable to decode JSON" unless $urldata = $json->decode($jsontext);
foreach my $record (@{$urldata}) {

    # Do something with the URL record data...
    print $record->{domain_age_days}, "\n";
  
}

sub help {

    print STDERR "Usage: $prog --file=[filename]\n";
    exit 1;
}
