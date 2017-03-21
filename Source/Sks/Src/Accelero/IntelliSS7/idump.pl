#!perl
# Copyright (C) 2000-2000 IntelliNet Technologies, Inc.  All rights reserved.
#

#
# $Id: idump.pl,v 1.1.1.1 2007-10-08 11:11:10 bsccs2 Exp $
#
# $Log: not supported by cvs2svn $
# Revision 1.1.1.1  2007/10/04 13:23:38  bsccs2
# init tree
#
# Revision 1.1.1.1  2007/08/03 06:48:37  cvsadmin
# BscCs2
#
# Revision 1.1.1.1  2007/03/08 15:12:52  cvsadmin
# BSC project
#
# Revision 9.1  2005/03/23 12:51:01  cvsadmin
# Begin PR6.5
#
# Revision 8.2  2005/03/21 13:49:06  cvsadmin
# PR6.4.2 Source Propagated to Current
#
# Revision 7.1  2002/08/26 22:08:32  mmiers
# Begin PR6.2
#
# Revision 6.1  2002/02/28 16:13:16  mmiers
# Begin PR7.
#
# Revision 5.1  2001/08/16 20:45:05  mmiers
# Start PR6.
#
# Revision 4.1  2001/05/01 00:52:59  mmiers
# Begin PR5
#
# Revision 3.1  2000/08/15 23:55:38  mmiers
#
# Begin round 4.
#
# Revision 1.1  2000/04/04 14:59:19  npopov
# PERL script for dumping the DBM-files to text files and vice versa
#
#



$TESTDIR = $ENV{'TESTDIR'};
#$utildir = "$TESTDIR/newest"; # Various auxiliary utilites
$usage = "Usage: $0 <Test directory> (dump/undump/showall/info/newInfo/noOnce) <DBM-file name> <'info'-separator>";
$directory = shift(@ARGV) || die $usage;
$command = shift(@ARGV) || die $usage;
$dbmfile = shift(@ARGV) || die $usage;
$directory = "$TESTDIR/$directory"; # Location of test cases

;#Open list of tests
;# Each entry has the following format:
;#  status(0-3)<TAB>args to asn1<TAB>categories<TAB>comment
dbmopen(test, "$directory/$dbmfile", 0660) ||
		die "Could not open test file, '$dbmfile'\n";


;# Are we running on a terminal?
$tty = (-t STDIN)? 1: 0;

@statnames = (
    "Passes",
    "Once passed",
    "Fails",
    "Once failed",
    "Not known",
    "Once not known"
);

if ($command eq "dump") {
    while (($k,$v) = each(test)) {
	if ($v =~ /../) {
	    $status = $&;
	    $other = $';
	    if (($h = chop($status)) ne "	") {
		print STDERR '?"$h" ';
	    }
	    else {
		print "$k	$status	$other\n";
	    }
	}
	else {
	    print STDERR "!$k: $v\n";
	}
    }
}
elsif ($command eq "undump") {
    while (<>) {
	chop;
	($k, $status, $other) = split(/	/, $_,3);
	if ($status =~ m/^[012345]$/ && $other =~ /	.*	/) {
	    $test { $k } = "$status	$other";
	}
	else {
	    print STDERR "!$k: $v\n";
	}
    }
}
elsif ($command =~ /^inf[aimnort]*$/) {
    local ($breik);
    $breik = '	' unless $breik = shift(@ARGV);
    open (Sorted, '|sort');
    while (($k, $v) = each(test)) {
	if (split(/	/, $v, 4) < 4) {
	    print STDERR "!$k: $v\n";
	}
	else {
	    ($status, $argv, $class, $comment) = @_;
	    if ($status =~ /^[012345]$/) {
		$status =~ y/012345/ggbbnn/;
		print Sorted "$k$breik$status$breik$argv$breik$class$breik$comment\n";
	    }
	    else {
		print STDERR "?'$status'	$k	$class	$argv	$comment\n";
	    }
	}
    }
    close Sorted;
}
elsif ($command =~ /^newInf[aimnort]*$/) {
    sub seeOld {
	local ($k, $v, $stryk, $m, $u) = @_;
	($m = $test { $k }) =~ m/(.)(.*)/;
	$u = $2;
	$v =~ s/.//;
	print "#?$k	$&$v\n" if $v ne $u;
	if ($stryk) {
	    print "#<$k	$m\n";
	    $k =~ /./;
	    print "rm -r $directory/Output/$&/$k\n";
	    delete $test { $k };
	}
	else {
	    print "#=<$k	$m\n";
	}
	$m;
    }
    sub change {
	local ($old, $new) = @_;
	local ($oldH, $oldArgv, $oldClass, $oldCment) = split('	', $old, 4);
	local ($newH, $newArgv, $newClass, $newCment) = split('	', $new, 4);
	$newH = $oldH if ($newH | 1) != ($oldH | 1);
	if ($oldClass ne $newClass) {
	    local (@old, @from, $m) = sort split(':', $oldClass);
	    local (@new, @unto) = sort split(':', $newClass);
	    last unless $m = shift @new;
	    for (@old) {
		while ($m lt $_) {
		    push (@unto, $m);
		    $m = pack('C', 255) unless $m = shift @new;
		}
		if ($m gt $_) {
		    push (@from, $_);
		}
		else {
		    $m = pack('C', 255) unless $m = shift @new;
		    $new = $_;
		}
	    }
	    push (@unto, $m) if $m ne pack('C', 255);
	    push (@unto, @new);
	    last unless @from || @unto;
	    @old = split(/ /, $oldArgv);
	    undef @new;
	    while ($_ = shift(@old)) {
		if (/^-/) {
		    shift (@old) if /^-(ex|pr|su)/;
		}
		else {
		    s'$'.$typ' if m/^[^.]*$/;
		    push(@new, $_);
		}
	    }
	    print 'for f in ', join(' ', @new), "\ndo";
	    while (@from && @unto) {
		$old = shift @from;
		$new = shift @unto;
		print "	mv $directory/$old/\$", "f $directory/$new/\$", "f\n";
	    }
	    #Neither the "from" class nor the "unto" class is emptie:
	    #if the followind loop happens, "$new" indeed was set,
	    for (@unto) {
		print "	ln $directory/$new/\$", "f $directory/$_/\$", "f\n";
	    }
	    for (@from) {
		print "	rm $directory/$_/\$", "f\n";
	    }
	    print "done\n";
	}
	"$newH	$newArgv	$newClass	$newCment";
    }
    sub seeNew {
	local ($k, $v, $u) = @_;
	print "#?$k	$u\n" if $u = $test { $kNew };
	$test { $k } = $v;
	print "#>$k	$v\n";
	$k =~ /./;
	print "mkdir -m 0775 -p $directory/Output/$&/$k\n";
    }
    local ($kNew, $new, $kOld, $old, $k, $n, $breik);
    $breik = '	' unless $breik = shift(@ARGV);
    while (<>) {
	chop;
	$n = s/^	//;
	if (split($breik, $_, 5) < 5) {
	    print "#!$_\n";
	}
	else {
	    $k = shift(_);
	    ($status = shift(_)) =~ y/gbn/024/;
	    unshift(_, $status);
	    if ($n) {
		&seeNew($kNew, $new) if ($kNew);
		$kNew = $k;
		$new = join('	', @_);
	    }
	    else {
		&seeOld($kOld, $old, 1) if $kOld;
		$kOld = $k;
		$old = join('	', @_);
	    }
	    if ($kOld && $kOld eq $kNew) {
		$old = &seeOld($kOld, $old);
		print "#=>$kNew	$new\n";
		do change($old, $new);
		$test { $kNew } = $new;
		undef $kOld;
		undef $kNew;
	    }
	}
    }
    &seeOld($kOld, $old, 1) if $kOld;
    &seeNew($kNew, $new) if ($kNew);
}
elsif ($command eq 'showall') {
    while (($k,$v) = each(test)) {
	if ($v =~ /../) {
	    $status = $&;
	    $other = $';
	    print '?"$h" ' if (($h = chop($status)) ne "	");
	    print "$k: $statnames[$status] ($status)	$other\n";
	}
	else {
	    print "!$k: $v\n";
	}
    }
}
elsif ($command eq "noOnce") {
    for $k (keys(test)) {
	$v = $test { $k };
	if ($v =~ s/^1/0/ || $v =~ s/^3/2/ || $v =~ s/^5/4/) {
	    $status = $&;
	    $other = $';
	    $test { $k } = $v;
	    print "$k: $statnames[$status] ($status)$other\n";
	}
    }
}
else {
    die $usage;
}

dbmclose(test);

