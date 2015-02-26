map {($_==-1&&print "numPkts:$n numBytes:$b\n\nIP Protocols\n",map{$p[$_]&&"$_: $p[$_]\n"}(0..$#p))||(/^(\d+)\,(\d+)\,/&&++$n&&($b+=$1)&&++$p[$2])} <>,-1;
