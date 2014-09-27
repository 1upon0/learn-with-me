$N=<>;while($N--){$i=<>-1;F:for(;;){$i++;next if $i!=reverse $i;foreach(2..int($i**0.5+1)){next F if!($i%$_);}print $i."\n";last;}}

127
3.14