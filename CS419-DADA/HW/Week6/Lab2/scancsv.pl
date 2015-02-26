#!/usr/bin/perl
#
# Perl framework that reads packet data from CSV file for Lab2
#
#

use strict;
use Text::CSV_XS;
use IO::File;

# for debugging: dump(data_structure)
use Data::Dump qw(dump);


my $fn = shift @ARGV;
my $fh = *STDIN;
if ( defined $fn ) {
    $fh = IO::File->new($fn) || die "$fn: $!";
}

my $csv = Text::CSV_XS->new({ blank_is_undef => 1 });
my $cols = $csv->getline($fh);
$csv->column_names(@$cols); # not really needed
do {
    # verify that the columns match what we expect
    my @csvfields = qw[len proto ipsrc ipdst tcpflags tcpsport tcpdport udpsport udpdport icmpcode icmptype];
    for ( my $i = 0; $i <= $#csvfields; $i++ ) {
	if ( $csvfields[$i] ne $cols->[$i] ) {
	    die "Field $i: $csvfields[$i] != $cols->[$i]\n";
	}
    }
};

# Variables we are going to fill with stats
my $numPackets;
my $numBytes;
my @IPProtos = map {0} (0..255);
# <add more here>
#################

# variables that get stuffed with successive packet values, and one global for debugging
my ($len,$proto,$ipsrc,$ipdst,$tcpflags,$tcpsport,$tcpdport,$udpsport,$udpdport,$icmpcode,$icmptype);
%main::pktvars = (length=>\$len,proto=>\$proto,ipsrc=>\$ipsrc,ipdst=>\$ipdst,tcpflags=>\$tcpflags,tcpsport=>\$tcpsport,tcpdport=>\$tcpdport,udpsport=>\$udpsport,udpdport=>\$udpdport,icmpcode=>\$icmpcode,icmptype=>\$icmptype);
# ... using this CSV module feature
$csv->bind_columns(\$len,\$proto,\$ipsrc,\$ipdst,\$tcpflags,\$tcpsport,\$tcpdport,\$udpsport,\$udpdport,\$icmpcode,\$icmptype);

# Local variables used in loop.
my ($pkt,$pktnum);

my $i=0;
while ( $pkt = $csv->getline($fh) ) {
    next unless $len > 0;
    $tcpflags = hex($tcpflags); # fix this up
    ++$pktnum;

    # debugging
    #DumpCurrentPkt();
    #print $pktnum,': ',CurrentPktToString(),"\n";
    #printf "%5u: %5u\n", $pktnum, $len;

    # Compute statistics
    ++$numPackets;
    $numBytes += $len;
    ++$IPProtos[$proto] if $proto >= 0 && $proto < 256;
    # <add more here>
    #################
    last if --$i == 0;
}

# Check for early exit from getline and print diagnostic.
print STDERR "$pktnum: ",$csv->error_diag,"\n"
    unless eof $fh;

# Print statistics to STDOUT.
print "Num packets: $numPackets, Num bytes: $numBytes\nIP Protocols:\n";
for ( my $i = 0; $i < 256; $i++ ) {
    if ( $IPProtos[$i] > 0 ) {
	printf "%3u: %10u\n", $i, $IPProtos[$i];
    }
}

exit(0);

# Debugging function
sub DumpCurrentPkt {
    dump(\%main::pktvars);
}

# Debugging function
sub CurrentPktToString {
    my $mp = \%main::pktvars;
    return undef unless ${$mp->{length}} > 0;
    my $proto = ${$mp->{proto}};
    my $r = "Length:${$mp->{length}} Proto:$proto ";
    if ( $proto == 1 ) {
	$r .= "(ICMP) ${$mp->{ipsrc}} => ${$mp->{ipdst}} type:${$mp->{icmptype}} code:${$mp->{icmpcode}}";
    } elsif ( $proto == 6 ) {
	$r .= "(TCP) ${$mp->{ipsrc}}:${$mp->{tcpsport}} => ${$mp->{ipdst}}:${$mp->{tcpdport}} flags:$tcpflags";
    } elsif ( $proto == 17 ) {
	$r .= "(UDP) ${$mp->{ipsrc}}:${$mp->{udpsport}} => ${$mp->{ipdst}}:${$mp->{udpdport}}";
    } else {
	$r .= "${$mp->{ipsrc}} => ${$mp->{ipdst}}";
    }
    return $r;
}
