map {/^(\d+)\,(\d+)\,/&&++$n&&($b+=$1)&&++$p[$2];} <>; END{print "numPkts:$n numBytes:$b\n\nIP Protocols\n",map{$p[$_]&&"$_: $p[$_]\n"}(0..$#p)}
