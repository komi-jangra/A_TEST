#!perl
#
# Copyright (C) 2000-2000 IntelliNet Technologies, Inc.  All rights reserved.
#

#
# $Id: irt.pl,v 1.1.1.1 2007-10-08 11:11:10 bsccs2 Exp $
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
# Revision 1.20  2000/06/14 20:12:19  npopov
# Fixed the problem with libraries for C++ test cases.
#
# Revision 1.19  2000/06/13 15:33:12  npopov
# Fixed compilation problem for C++.
#
# Revision 1.18  2000/05/25 13:23:14  npopov
# Fixed the create command for multiple source files.
#
# Revision 1.17  2000/05/24 16:15:34  npopov
# Fixed the problem with C/C++ compiler options used for building test cases.
#
# Revision 1.16  2000/05/02 16:07:47  npopov
# Unix-related changes.
#
# Revision 1.15  2000/05/01 17:42:46  npopov
# Unix related changes.
#
# Revision 1.14  2000/04/28 17:17:08  npopov
# More unix related changes.
#
# Revision 1.13  2000/04/28 16:16:22  npopov
# Unix related changes.
#
# Revision 1.12  2000/04/14 14:17:39  npopov
# The lock file is now removed in case of build errors
#
# Revision 1.11  2000/04/13 15:21:59  npopov
# Added dots for the FROM field of email messages
#
# Revision 1.10  2000/04/13 13:52:51  npopov
# Added a computer name for identifying email messages
#
# Revision 1.9  2000/04/10 14:31:03  npopov
# Minor correction for the email notification message
#
# Revision 1.8  2000/04/06 17:05:12  npopov
# A database dump to a text file is now done for backup at nightly runs.
#
# Revision 1.7  2000/04/06 16:32:55  npopov
# The MTP3, SCCP, TCAP and ASN.1/C runtume libraries are now test case specific.
#
# Revision 1.6  2000/04/06 15:18:42  npopov
# The vendor library is now test case specific.
#
# Revision 1.5  2000/04/06 13:17:32  npopov
# Added email notification when build fails.
#
# Revision 1.4  2000/04/05 13:58:23  npopov
# Fixed the remove command
#
# Revision 1.3  2000/04/04 16:57:15  npopov
# Fixed mail lists
#
# Revision 1.2  2000/03/31 16:23:48  npopov
# Update & build is now done if -make is specified
#
# Revision 1.1  2000/03/31 15:22:16  npopov
# PERL script to run runtime regression tests
#
#


$WINDOWS = "yes";		# Should be "yes" for Windows & "" for Unix
	;#
	;# Uncomment the next line for Windows.
	;#
#include "D:/cvsroot/intelliss7/maillist.pl"
	;#
	;# Uncomment the next line for Unix.
	;#
;#include "/freespace/cvsroot/IntelliSS7/maillist.pl"

$TMP = "/tmp" unless ($TMP = $ENV{'TMP'});
($testdaemon = "$0") =~ s@.*/@@;	# remove pathname qualifiers
$testdaemon =~ s@\.pl@@;		# remove the .pl
($DAEMON = $testdaemon) =~ tr/a-z/A-Z/;

if ($WINDOWS) {
    $ITS_ROOT  = $ENV{'ITS_ROOT'};
    $ITS_ROOT =~ s/\\/\//;
    $MAILDIR = $ENV{'MAILDIR'};
    $COMPUTERNAME = $ENV{'COMPUTERNAME'};
    $TMP =~ s/\\/\//;
    $TMP =~ tr/A-Z/a-z/;
    $TESTDIR = $ENV{'TESTDIR'};
    $CC = 'cl';
    $LINK =  'link';
    $C_LIB = "$ITS_ROOT/runtime/supportmdd.lib $ITS_ROOT/runtime/coremdd.lib ws2_32.lib msvcrtd.lib kernel32.lib user32.lib advapi32.lib";
    $CPP_LIB = "$ITS_ROOT/runtime/support++mdd.lib $ITS_ROOT/runtime/core++mdd.lib ws2_32.lib msvcrtd.lib kernel32.lib user32.lib advapi32.lib";
    $LINKOPTIONS = "/nologo /pdb:none /release -subsystem:console -debug:full -debugtype:cv";
    $INCLUDE = "-I$ITS_ROOT/common/include -I$ITS_ROOT/common/include/asn-c -I$ITS_ROOT/TCAP/include -I$ITS_ROOT/SCCP/include -I$ITS_ROOT/MTP3/include -I$ITS_ROOT/IS41/include -I$ITS_ROOT/GSMMAP/include -I$ITS_ROOT/GSMMAP/include/itu";
    $C_OPTIONS = "-W3 -MDd -DWIN32 -D_WIN32 -Z7 -Od -GB -Ze $INCLUDE";
    $CPP_OPTIONS = "-TP -GX $C_OPTIONS -I$ITS_ROOT/common/include/asn-cpp";
    $DIFF = "diff -H";
    $obj = "obj";
    $lib = "lib";
    $CODETEST = "";
}
else {
    $ITS_ROOT  = $ENV{'ITS_ROOT'};
    $ITS_ROOT =~ s/\\/\//;
    $COMPUTERNAME = $ENV{'COMPUTERNAME'};
    $TMP =~ s/\\/\//;
    $TMP =~ tr/A-Z/a-z/;
    $TESTDIR = $ENV{'TESTDIR'};
    $CC = $ENV {'CC'} || 'gcc';
    $INCLUDE = "-I$ITS_ROOT/common/include -I$ITS_ROOT/TCAP/include -I$ITS_ROOT/SCCP/include -I$ITS_ROOT/MTP3/include -I$ITS_ROOT/IS41/include -I$ITS_ROOT/GSMMAP/include";
    $C_OPTIONS = "-Dsolaris $INCLUDE";
    $LIB = "-lm -lsocket -lnsl";
    $CPP_OPTIONS = "-g $C_OPTIONS";
    $DIFF = "diff";
    $obj = "o";
    $lib = "a";
    $CODETEST = "";
}

$HELP = "$ITS_ROOT/$testdaemon.help.txt";
push(@INC, '$PERLDIR');
$directory = "$TESTDIR/runtimetest";
;#$typetest = "$TESTDIR/typetest"; #Directory of asn1 test cases
@outsufs = ("out");
$curdir = `pwd`;
chop $curdir;

if ($WINDOWS) {
    `rm -f $directory/$testdaemon.lock 2>&1`;
    if (-e "$directory/$testdaemon.lock") {
	die "$DAEMON is running.  Try again later.\n";
    }
}
else {
    @program_list = ($testdaemon, cpprmake);
    foreach $program (@program_list) {
	&checkProcess($program);
    }
    $pid = $$;
    $username = $ENV{'HOME'} || "cron";
    $hostname = &get_hname;
    $lockfilename = "$directory/$testdaemon.lock";
    open(LOCKFILE, ">$lockfilename") || die "Error creating lock file $directory/$testdaemon.lock.";
    print(LOCKFILE $pid, ' ', $username, ' ', $hostname);
    close(LOCKFILE); 
}

$outputdir = "OUTPUT";
$extraargs = "";		# extra arguments

@alternateOutputDirs = (
    "OUTPUT",
    "OUTPUT1"
);
@alternateExtraArgs = (
    ""
);
@alternateOutputDirs = (
    "OUTPUT",
    "OUTPUT1"
);
@sourcesuf = (
    "c",
    "cpp"
);

$usage = "Usage: $testdaemon command [flags]\nType \"$testdaemon help\" for help.\n";

$build = "-n";
if ($ARGV[0] eq "-make") {
    shift(@ARGV);
    $build = "Update all";
}

$command = shift(@ARGV) || die $usage;
if ($command eq "help") {
    ($pager = $ENV{"PAGER"}) || ($pager = "more");
    system "$pager $HELP";
    exit 0;
}

;#Open list of tests
;# Each entry has the following format:
;#  status(0-3)<TAB>args to asn1<TAB>categories<TAB>comment
dbmopen(tests, "$directory/Tests", 0660) ||
		die "Could not open tests file, 'Tests'.\n";

;# Are we running on a terminal?
$tty = (-t STDIN)? 1: 0;

umask(027);
if ($WINDOWS) {
    open(LOCKFILE, ">$directory/$testdaemon.lock");
}


if ($command eq "create") {
    local ($km, @found, $found);

    $name = shift(@ARGV) || die $usage;
    if ($name eq "-g") {
	$status = "0";
	$name = shift(@ARGV) || die $usage;
    }
    elsif ($name eq "-b") {
	$status = "2";
	$name = shift(@ARGV) || die $usage;
    }
    elsif ($name eq '-n' || $name eq "-u") {
	$status = "4";
	$name = shift(@ARGV) || die $usage;
    }
    else {
	$status = "4";
    }
    $name =~ s/\.$sourcesuf[0]//;
    $name =~ s/\.$sourcesuf[1]//;
    &make(0);
    (@categories = split(/:/, shift(@ARGV))) || die $usage;
    @args = @ARGV;
    &verifyName($name,"Name of testcase");
    if ($tests { $name }) {
       push (found, $name);
    }
#    elsif ($name =~ /......./) {
#	$km = $&;
#	@found = grep(/^$km/i, keys tests);
#    }
    else {
	@found = grep(/^$name$/i, keys tests);
    }
    if ($found = shift found) {
	if ($tty) {
	    print STDERR "Overwrite existing test case '$found'?  ";
	    if (!&get_y_or_n) {
		die "Aborted.\n";
	    }
	}
;	# Delete old files
;#	($firstChar = $found) =~ s/(.).*/$1/;
	system "rm -fr $directory/$outputdir/$found" if -e "$directory/$outputdir/$found";
	$cat = (split(/\t/, $tests { $found }))[2];
	foreach $curcat (split(/:/, $cat)) {
	    unlink "$directory/$curcat/$found.@sourcesuf[0]";
	    unlink "$directory/$curcat/$found.@sourcesuf[1]";
	}
    }
    foreach $curcat (@categories) { # Are we creating new categories?
	if (!-e "$directory/$curcat" || !-d "$directory/$curcat") {
	    if ($tty) {
		print STDERR "Create new category '$curcat'?  ";
		if (!&get_y_or_n) {
		    die "Aborted.\n";
		}
	    }
	    mkdir("$directory/$curcat", 0770);
	    chmod 0770, "$directory/$curcat";
	}
    }

;#    @stat = stat(_);
;#    chmod $stat[2] & ~0222, $filename;

    push(@args, $name);
    foreach $curcat (@categories) {
	$found = "";
	foreach $arg (@args) {
	    ($cpp, $filename) = &checkFile($arg);
	    if (-e $filename) {
		`rm -f $directory/$curcat/$filename 2>&1`;
		`cp $filename $directory/$curcat/$filename`;
		$found = "yes";
	    }
	}
	if ($found eq "") {
	    die "No .@sourcesuf[0] or .@sourcesuf[1] files found.\n";
	}
    }

    print STDERR "Comment?  " if $tty;
    $comment = <STDIN>;
    chop $comment;
    $args = join(" ", @args);
    ($status, $message) = &run(1, $name, $status, $args, @categories);
    print "$name: $message\n" if $message;
    $tests{$name} = "$status\t$args\t" . join(":", @categories) . "\t$comment";

    if (!-e "$outputdir/$name") {
	mkdir ("$outputdir/$name", 0770);
	chmod 0770, "$outputdir/$name";
    }
    &cmd("mv -f", "$name.", "$outputdir/$name/", @outsufs, "dif");
}
elsif ($command eq "remove") {
;    # Delete some test cases; use with care
;    # Uses standard args (see parseargs) + -F --> dont confirm
    @names = &parseargs;
    if (defined($flag = shift(@ARGV))) {
	if ($flag eq "-F") {
	    $forced = 1;
	}
	else {
	    die $usage;
	}
	die $usage if $#ARGV >= 0;
    }
    if (!$tty) {
	$forced = 1;
    }
    foreach $name (@names) {
	print STDERR "Delete test case '$name'?  " if !$forced;
	if ($forced || &get_y_or_n) {
	    $cat = (split (/\t/, $tests{$name}))[2];
	    system "rm -fr $directory/$outputdir/$name" if -e "$directory/$outputdir/$name";
	    foreach $curcat (split(/:/, $cat)) {
		unlink "$directory/$curcat/$name.@sourcesuf[0]";
		unlink "$directory/$curcat/$name.@sourcesuf[1]";
		`rmdir $directory/$curcat 2>&1`;
	    }
	    delete $tests{$name};
	}
    }
}
elsif ($command eq "info" || $command =~ m/^ho[uw]$/) {
;    # Get info on some test cases
;    # Uses standard args and
;    #  -ddataspec Specify output format
;    # The output format is in the same form as SCCS prs
;    # The keys are:
;    #   :N:   Name of test case
;    #   :A:   Actual args to test case
;    #   :Ag:  Actual arguments to test case, less the name
;    #   :Ca:  Categories the test case belongs to
;    #   :C:   Comments on the test case
;    #   :Sn:  Status, numeric format (0-3)
;    #   :S: or :St:  Status, text format
;    #   :Sl:  Status, one-letter form
;    # The default format is  ":N:\t:S:\t:C:"
    

    @statletter = ('g', 'g', 'b', 'b', 'n', 'n');
    @statnames = ("Passes", "Once passed", "Fails", "Once failed", "Not known",
		  "Was unknown");
    @names = &parseargs;
    if (defined($dataspec = shift @ARGV)) {
	die $usage if $dataspec !~ s/^-d//;
	die $usage if $#ARGV >= 0;
    } else {
	$dataspec = ":N:\t:S:\t:C:";
    }
    $dataspec =~ s/\\t/\t/g; $dataspec =~ s/\\n/\n/g;
    foreach $name (@names) {
	if (!defined($tests{$name})) { 
	    print STDERR "$name does not exist\n";
	    next;
	}
	($status, $args, $categories, $comment) = 
	    split(/\t/, $tests{$name});
	$categories = join(", ", split(/:/, $categories));
	$_ = $dataspec;
	s/:N:/$name/g; s/:Ca:/$categories/g; s/:C:/$comment/g;
	s/:A:/$args/g; $args =~ s/(^| )$name$//; s/:Ag:/$args/g; s/:Sn:/$status/g;
	s/:Sl:/$statletter[$status]/g; s/:St?:/$statnames[$status]/g;
	print $_ . "\n";
    }
}
elsif ($command eq "update") {
;    # Updates output, status, and/or category of some test cases
;    # Standard args plus
;    #   -uo  Update output
;    #   -ug  Change to "good" status (the test case now works)
;    #   -ub  Change to "bad" status (the test case was thought to work, incorrectly)
;    #   -uccat1:..:catn  Add the listed categories
;    #   -uC  Change the test comment
;    #   -udccat1:..:catn  Delete the listed categories
;    #   -ua   Change the arguments (remainder of command line)
;    #   -u[nu] change to unknown status
;    #   -o#	use the #th alternate Output directory and asn1 arguments

    $newstatus = -1; $output = 0; $ctc = 0; @argv = ();
    
    while (defined($flag = shift @ARGV)) {
	if ($flag =~ s/^-o//) {
	    die "-o index must not be greater than $#alternateOutputDirs\n" if $flag > $#alternateOutputDirs;
	    die "-o index must be 0 or greater.\n" if $flag < 0;
	    $outputdir = $alternateOutputDirs[$flag];
	    $extraargs = $alternateExtraArgs[$flag];
	    $outputdir = $alternateOutputDirs[$flag];
	}
	elsif ($flag !~ s/^-u//) {
	    push (@argv, $flag);
	}
	else {
	    while ($flag) {
		if ($flag =~ s/^o//) {$output = 1;}
		elsif ($flag =~ s/^g//) { $newstatus = 0; }
		elsif ($flag =~ s/^b//) { $newstatus = 2; }
		elsif ($flag =~ s/^[nu]//) { $newstatus = 4; }
		elsif ($flag =~ s/^C//) { $ctc = 1; }
		elsif ($flag =~ s/^c//) {
		    if (length($flag) > 0) {
			@newcategories = split(/:/, $flag);
		    }
		    else {
			@newcategories = split(/:/, shift @ARGV);
		    }
		    foreach $curcat (@newcategories) {
			if (!-e $curcat || !-d $curcat) {
			    if ($tty) {
				print STDERR "Create new category '$curcat'? ";
				if (!&get_y_or_n) {
				    die "Aborted.\n";
				}
			    }
			    mkdir ("$directory/$curcat", 0770);
			    chmod 0770, "$directory/$curcat";
			}
		    }
		    $flag = "";
		}
		elsif ($flag =~ s/^dc//) {
		    if ($flag) {
			@oldcategories = split(/:/, $flag);
		    }
		    else {
			@oldcategories = split(/:/, shift @ARGV);
		    }
		    $flag = "";
		}
		elsif ($flag =~ s/^a//) {
		    @newargs = @ARGV;
		    @ARGV = ();
		    if ($#newargs < 0) {
			die $usage;
		    }
		    $output = 1;
		}
		else {
		    die $usage;
		}
	    }
	}
    }

    @ARGV = @argv;
    @names = &parseargs;
    die $usage if $#ARGV >= 0;

    &make(0);

    chdir $directory;
    
    foreach $name (@names) {
	($status, $args, $categories, $comment) = split(/\t/, $tests{$name});
	if ($newstatus >= 0) {
	    $status = $newstatus + ($status & 1);
	}
	if ($#newargs >= 0) {
	    $args = join(" ", @newargs);
	}
	if ($output) {
	    $status &= 6;
	    ($status, $message) = &run(1, $name, $status, $args, split(/:/, $categories));
	    print "$name: $message\n" if $message;

;		# Remove the output files if they exist
	    `rm -f $outputdir/$name/$name.out` if -e "$outputdir/$name";
	    `rm -f $outputdir/$name/$name.dif` if -e "$outputdir/$name";
	    `rm -f $outputdir/$name/.* 2>&1`;

;		# Create the output directory if it does not already exist
	    if (!-e "$outputdir/$name") {
		mkdir ("$outputdir/$name", 0770);
		chmod 0770, "$outputdir/$name";
	    }

;		# Copy the newly created output files to the output directory
	    &cmd("mv -f", "$name.", "$outputdir/$name/", @outsufs, "dif");
	    `mv -f .* $outputdir/$name/ 2>&1`;
	}
	if ($ctc) {
	    print STDERR "Changing comment for test case '$name'\n";
	    print STDERR "Old comment: $comment\n";
	    print STDERR "New comment: ";
	    $newcomment = <STDIN>;
	    chop $newcomment;
	    if ($newcomment) {$comment = $newcomment; }
	}
	foreach $newcat (@newcategories) {
	    if ($categories !~ /(.|:)$newcat($|:)/) {
		$categories .= ":$newcat";
		if (-e (split(/:/, $categories))[0] . "/$name.@sourcesuf[0]") {
		    system "cp " . (split(/:/, $categories))[0] . "/$name.@sourcesuf[0] $newcat/$name.@sourcesuf[0]";
		}
		else {
		    system "cp " . (split(/:/, $categories))[0] . "/$name.@sourcesuf[1] $newcat/$name.@sourcesuf[1]";
		}
	    }
	}
	foreach $oldcat (@oldcategories) {
	    $categories =~ s/(^|:)$oldcat//;
	    `rm -f $oldcat/$name.@sourcesuf[0] 2>&1`;
	    `rm -f $oldcat/$name.@sourcesuf[1] 2>&1`;
	    `rmdir $oldcat 2>&1`;
	}
	$categories =~ s/^:*//;
	$tests{$name} = "$status\t$args\t$categories\t$comment";
    }
}
elsif ($command eq "test") {
;    # Test whether output of some test cases has changed
;    # Standard args plus
;    #  -m	send mail and update status in file
;    #  -aasn1 use the listed asn1 instead of one in newest; incompatible
;    #	with -m
;    #  -d	copy the diff output for changed files into this directory
;    #  -o#	use the #th alternate Output directory and asn1 arguments

    local ($broken);
    
    @names = &parseargs;
    $mail = 0;
    while (defined($flag = shift @ARGV)) {
	if ($flag eq "-m") {
	    $mail = 1;
	}
	elsif ($flag eq "-d") { 
	    $copydiff = 1;
	    $olddir = `pwd`;
	    chop $olddir;
	}
	elsif ($flag eq "-k") {
	    $keep_executable = 1;
	    $olddir = `pwd`;
	    chop $olddir;
	} 
	elsif ($flag =~ s/^-a//) {
	    $asn1 = $flag;
	    $asn1spec = 1;
	}
	elsif ($flag =~ s/^-o//) {
	    die "-o index must not be greater than $#alternateOutputDirs\n" if $flag > $#alternateOutputDirs;
	    die "-o index must be 0 or greater.\n" if $flag < 0;
	    $outputdir = $alternateOutputDirs[$flag];
	    $extraargs = $alternateExtraArgs[$flag];
	    $outputdir = $alternateOutputDirs[$flag];
	}
	else {
	    die $usage;
	}
    }
    $asn1spec && $mail && die "Can't send mail and specify asn1.\n";
    
    &make($mail);

    chdir $directory;

    $SIG { 'INT' } = 'neFarrer';
    $SIG { 'TERM' } = 'neFarrer';

    unlink "DIFF_OUT$$"; # We should never need to do this
    while (($name = shift @names) && !$broken) {
	($status, $args, $cats) = split(/\t/, $tests{$name});
	($m, $message) = &run(0, $name, $status, $args, split(/:/, $cats));

	system ">DIFF_OUT$$";
	&diff("DIFF_OUT$$", "$name.", "$outputdir/$name/", @outsufs);

	chmod 0440, "DIFF_OUT$$";
	unlink "$olddir/$name.dif" if ($copydiff);

	if (system("cmp -s DIFF_OUT$$ $outputdir/$name/$name.dif")) {
	    push(@failednames, $message? "$name ($message)": $name);
	    warn $! if ($copydiff && system("cp DIFF_OUT$$ $olddir/$name.dif"));
	    if ($mail) {
		if ((!-e "DIFF_OUT$$") || (-z "DIFF_OUT$$")) {
		    $status &= ~1;
		}
		else {
		    $status |= 1;
		}
		$tests{$name} = $status . substr($tests{$name}, 1, length($tests{$name}) - 1);
		unlink "$outputdir/$name/$name.dif";
		system("mv -f DIFF_OUT$$ $outputdir/$name/$name.dif");
		`mv -f .* $outputdir/$name/ 2>&1`;
	    }
	}
	unlink "DIFF_OUT$$";
	&cmd("rm -f", "$name.", "", @outsufs, "dif");
	`rm -f .* 2>&1`;
    }
    &showTimes($broken? "Broken at '$broken'": 'Time');
    if ($#failednames >= 0) {
	if (!$mail) {
	    print join(" changed\n", sort(@failednames)) . " changed.\n";
	}
	else {
	    &sendmail("The state of the test cases has changed!",
		"The test cases changed are:\n\n" . join("\n", sort(@failednames)), @irtmaillist);
	}
    }
    elsif ($mail) {
	&sendmail("The state of the test cases has not changed.", "No changes.", @irtmaillist);
    }
    if ($mail && $MAILDIR) {
	`mv $TMP/mail$$.raw $MAILDIR`;
    }

    sub neFarrer
    {
	local($signal, $other) = @_;
	$broken = $name;
    }
    sub trapp
    {
	local($signal, $other) = @_;
	&showTimes("Signal $signal at '$name',");
    }
    sub showTimes
    {
	printf join(', ', @_) . " $testdaemon: %.6gu, %.6gs; children: %.6gu, %.6gs\n", times;
    }
}
elsif ($command eq "extract" || $command =~ m/^gett?$/ || $command =~ m/^retrieve?$/o) {
;    # Extracts some test cases
;    # Uses standard args
    @names = &parseargs;
    die $usage if $#ARGV >= 0;
    foreach $name (@names) {
	($status, $args) = split(/\t/, $tests{$name});
	@files = &filesrefed(split(" ", $args));
	while ($file = shift(@files)) {
	    if ($cat = (split(/\t/, $tests{$file}))[2]) {
		($cat) = split(/:/, $cat);
		system "cp $directory/$cat/$file.@sourcesuf[0] $file.@sourcesuf[0]";
		system "cp $directory/$cat/$file.@sourcesuf[1] $file.@sourcesuf[1]";
	    }
	}
	&cmd("cp", "$directory/$outputdir/$name/", "$name.", @outsufs, "dif");
    }
}
elsif ($command eq "rename") {
    local($km, @found, $filename, $cpp, @filelist);
    ($oldname = shift @ARGV) || die $usage;
    ($newname = shift @ARGV) || die $usage;
    chdir $directory;
    if (!defined($info = $tests{$oldname})) {
	die "Test case '$oldname' does not exist.\n";
    }
    if ($tests{$newname}) {
	push (found, $newname);
    }
#    elsif ($newname =~ /......./) {
#	$km = $&;
#        @found = grep(/^$km/i && $_ ne $oldname, keys tests);
#    }
    else {
	@found = grep(/^$newname$/i && $_ ne $oldname, keys tests);
    }
    die "Test case '" . join("', '", @found) . "' already there\n" if (@found);
  
    die "$outputdir name not changed (mv $?)\n" if
	-e "$outputdir/$oldname" &&
	system "mv -f $outputdir/$oldname $outputdir/$newname";
    `mv -f $outputdir/$newname/$oldname.out $outputdir/$newname/$newname.out 2>&1`;
    `mv -f $outputdir/$newname/$oldname.dif $outputdir/$newname/$newname.dif 2>&1`;

    ($status, $args, $categories, $comment) = split(/\t/, $info);
    $args =~ s/$oldname/$newname/;
    @categories = split(/:/, $categories);
    foreach $curcat (@categories) {
	($cpp, $filename) = &checkFile("$curcat/$oldname");
	if ($cpp == -1) {
	    next;
	}
	rename("$filename", "$curcat/$newname.@sourcesuf[$cpp]");
    }
    $tests{$newname} = join("\t", $status, $args, $categories, $comment); 
    delete $tests{$oldname};
}
elsif ($command eq "run") {
    ($name = shift @ARGV) || (die $usage);
    if ($name =~ s/^-a//) {
	$asn1 = $name || ($asn1 = shift @ARGV) || (die $usage);
	($name = shift @ARGV) || (die $usage);
    }
    else {
	&make(0);
    }
    @args = @ARGV;
    push(@args, $name) if -e "$name.$sourcesuf";
    if ($message = &run_test(1, $asn1, $name, @args)) {
	print $message . "\n";
    }
}
elsif ($command eq "clean") {
    foreach $name (@ARGV) {
	&cmd("rm -f", "$name.", "", @outsufs, "dif");
    }
}
elsif ($command eq "batch") {
    @names = &parseargs;
    die $usage if $#ARGV >= 0;
    &list_com(@names);
}
else {
    @names = &parseargs;
    die $usage if $#ARGV >= 0;
    foreach $name (@names) {
	$categories = (split(/\t/, $tests{$name}))[2];
	$category = (split(/:/, $categories))[0];
	push (@newnames, "$directory/$category/$name.$sourcesuf");
    }
    system "$command @newnames";
}
dbmclose(tests);


;# Parse command line options to find the subset of files referred to
;# Formats:
;#   name:...:name    Any one of the names specified (may be only one)
;#   -ccat:...:cat    Any one of the categories specified (may be only one)
;#   -g		     Files that once worked
;#   -b		     Files known to fail
;#   -u		     Files with unknown status
;#   -w		     Files that produce same output as checked in
;#   -f		     Files that produce different output
;#   -s(0|1|2|3|4|5)* All files with the specified status (0=works,1=worked,2=fails,3=failed,4=unknown,5=was unknown)
;#   -pprefix       All files that begin with prefix
;# If several of these are specified, the intersection is returned.  If none are
;# specified, the whole thing is returned.  Unrecognized arguments are left in
;# @ARGV.  
;# Asks for confirmation if entire suite specified and stdin is a terminal
sub parseargs {
    local (@files, @newfiles, @argv, $curarg, $curfile, $foundspec);
    local ($modified) = 0;
    
;    # Search for a name specifier
    foreach $curarg (@ARGV) {
	if ($curarg !~ /^-/) {
	    push (@files, split(/:/, $curarg));
	    $modified = $foundspec = 1;
	}
    }
    if ($foundspec) {
	@files = &verifyfiles(@files);
    }
    else {
	@files = keys %tests; # No name specifier found
    }
    foreach $curarg (@ARGV) {
	if (!$modified) { $modified = -1; }
	elsif ($modified == -1) { $modified = 1; }
	if ($curarg eq "-g") {
	    @files = grep(substr($tests{$_},0,1) & 6 == 0, @files);
	} elsif ($curarg eq "-b") {
	    @files = grep(substr($tests{$_},0,1) & 6 == 2, @files);
	} elsif ($curarg eq "-u") {
	    @files = grep(substr($tests{$_},0,1) & 6 == 4, @files);
	} elsif ($curarg eq "-w") {
	    @files = grep(!(substr($tests{$_},0,1) & 1), @files);
	} elsif ($curarg eq "-f") {
	    @files = grep(substr($tests{$_},0,1) & 1, @files);
	} elsif ($curarg =~ s/^-s//) {
	    @files = grep(($status = substr($tests{$_},0,1),
			   $curarg =~ /$status/), @files);
	} elsif ($curarg =~ s/^-p//) {
	    @files = grep(/^$curarg/, @files);
	} elsif ($curarg =~ s/^-c//) {
	    @cattest = split(/:/, $curarg);
	    while ($curfile = shift(@files)) {
		($s, $a, $cats) = split(/\t/, $tests{$curfile});
		foreach $curcat (@cattest) {
		    if ($cats =~ /$curcat/) {
			push (@newfiles, $curfile);
			last;
		    }
		}
	    }
	    @files = @newfiles;
	} elsif ($curarg =~ /^-/) {
	    push(@argv, $curarg);
	    $modified = 0 if $modified == -1;
	}
    }
    if (!$modified && $tty) {
	print STDERR "Run on whole test set? ";
	if (!&get_y_or_n) { die "Aborted.\n"; }
    }
    @ARGV = @argv;
    @files;
}


;# Parses options to asn1 to find all files referred to
;#  Assumes no -c, -h, -l, or -m; all output files should be produced by our
;#  automatic runs
sub filesrefed {
    local (@temp) = @_;
    local (@files, $cur);
    
    while ($cur = shift(@temp)) {
	push(@files, $cur) if $cur !~ /^-/;
    }
    @files;
}


;# Sends message (the first arg) to the users listed in remainder of args
sub sendmail
{

    local($message) = shift(@_); # get the first argument
    local($body) = shift(@_);
    local($firstUser) = shift(@_);
    local(@users) = @_; # Sets users to the remaining args
    
    $date = `date`;
    chop $date;
    $userlist = join(", ", @users);
    if ($WINDOWS) {
	open(MAILFILE, ">>$TMP/mail$$.raw");
	print MAILFILE <<EOF;
From <$DAEMON.on.$COMPUTERNAME>
To <$firstUser>
Cc <$userlist>
Subject <$message>

$body

$DAEMON Daemon
"Quality Products From Quality Beings"
IntelliNet Technologies, Inc.
EOF
    }
    else {
	open(MAILFILE, "|/usr/lib/sendmail -t");
	print MAILFILE <<EOF;
From: $DAEMON
To: $firstUser
Cc: $userlist
Subject: $message

$body

$DAEMON Daemon
"Quality Products From Quality Beings"
IntelliNet Technologies, Inc.
EOF
    }
    close(MAILFILE);
}


;#Gets an answer to a yes or no question
sub get_y_or_n {
    local ($val) = -1;
    do {
	$ans = <STDIN>;
	if ($ans =~ /^y|Y/) {
	    $val = 1;
	} elsif ($ans =~ /^n|N/) {
	    $val = 0;
	} else {
	    print STDERR "Please answer 'y' or 'n'.\n";
	}
    } while $val < 0;
    $val;
}


;# Links in appropriate files and runs a test case
;# Takes name, status, args, and categories of test to run
;# returns updated status of test case
sub run {
    local ($compile, $name, $status, $args, $cat) = @_;
    local ($file, $curcat, @files);
    

    foreach $file (@files = &filesrefed(split(/ /, $args))) { #for each file in args
	if ($file eq $name) {
	    $curcat = $cat;
	}
#	elsif (!defined($tests{$file})) {
#	    next;
#	}
	else {
	    $curcat = split(/:/, (split(/\t/, $tests{$file}))[2]);
	    if (!$curcat) {
		$curcat = $cat;
	    }
	}
	$symlink_exists = (eval 'symlink("","");', $@ eq '');
	if ($symlink_exists) {
	    `cp -f $directory/$curcat/$file.@sourcesuf[0] $directory 2>&1`;
	    `cp -f $directory/$curcat/$file.@sourcesuf[1] $directory 2>&1`;
	}
	else {
	    `cp -f $directory/$curcat/$file.@sourcesuf[0] $directory 2>&1`;
	    `cp -f $directory/$curcat/$file.@sourcesuf[1] $directory 2>&1`;
	}
    }
    chdir $directory;

    if ($message = &run_test($compile, $name, split(/ /, $args))) {
	$status |= 1;
	@failures = () if $compile;
    }
    system "touch $name.dif";
    &cmd("chmod 0440", "$name.", "", @outsufs, "dif");
    foreach $file (@files) { #for each file in arguments
;#	if ($file ne $name && !defined($tests{$file})) {
;#	    next;
;#	 }
	`rm -f $directory/$file.@sourcesuf[0]`;
	`rm -f $directory/$file.@sourcesuf[1]`;
    }
    ($status, $message);
}


sub make
{

    local($mail) = @_;
    local($exitcode);

    if ($mail) {
		;#
		;# Dump the database to a text file for backup...
		;#
	`idump runtimetest dump Tests >$directory/$testdaemon.dump.txt`;
    }
	;#
	;# Do a build...
	;#
    if ($WINDOWS) {
        system "cd $ITS_ROOT; bw32 $build" unless $build eq '-n';
        $exitcode = $?;
	if ($exitcode >>= 8 && $mail && $MAILDIR) {
	    &sendmail("Build errors prevented $DAEMON from running.", "Build errors.  Please see $TESTDIR/runtimetest/$DAEMON.out on $COMPUTERNAME for more info.", @irtmaillist);
	    `mv $TMP/mail$$.raw $MAILDIR`;
	    close(LOCKFILE);
	    `rm -f $directory/$testdaemon.lock 2>&1`;
	    exit(1);
	}
    }
    else {
        system "cd $ITS_ROOT; bunix $build" unless $build eq '-n';
        $exitcode = $?;
	if ($exitcode >>= 8 && $mail) {
	    &sendmail("Build errors prevented $DAEMON from running.", "Build errors.  Please see $TESTDIR/runtimetest/$DAEMON.out on $COMPUTERNAME for more info.", @irtmaillist);
	    `rm -f $directory/$testdaemon.lock 2>&1`;
	    exit(1);
	}
    }
}


sub verifyfiles
{
;    # make sure given files exist
    local($curfile, @returnfiles);

    foreach $curfile (@_) {
	if (!defined($tests{$curfile})) {
	    print STDERR "Test case '$curfile' does not exist.\n";
	}
	else {
	    push (@returnfiles, $curfile);
	}
    }
    @returnfiles;
}


;# Write the difference file into the first argument ($diffile).
sub diff
{

    local($diffile, $orig, $final, @suffixes) = @_;
    local($suffix, $status, $cmp, $elfyl, @filelist, $name);


;#    $nline = "";
    foreach $suffix (@suffixes) {
	if (-e "$orig$suffix") {
	    $elfyl = $final . "$orig$suffix";
	    if (-e $elfyl) {
		system "cmp -s $orig$suffix $elfyl";
		$cmp = $?;
	    }
	    else {
		system "touch $elfyl";
		$cmp = 2;
	    }
	    system "(echo File: $orig$suffix
			$DIFF $orig$suffix $elfyl) >> $diffile" if $cmp;
	    $status |= $?;
	}
    }
;#    @filelist = <.*>;
;#    foreach $name (@filelist) {
;#	$elfyl = $final . $name;
;#	system "cmp -s $name $elfyl";
;#	$cmp = $?;
;#	if ($cmp) {
;#	    `echo "" >>$diffile 2>&1` if $nline;
;#	    `echo "DOING \\"diff\\" on $name...\n" >>$diffile 2>&1`;
;#	    $nline = "yes";
;#	    system "$DIFF $name $elfyl >>$diffile 2>&1";
;#	}
;#	$status |= $?;
;#    }
    $status;
}


;# Do a given command (first arg) on second & third arg with each suffix in 
;# list that follows
sub cmd
{

    local($prog, $orig, $final, @suffixes) = @_;
    local ($suffix, $status);


    if (length($final) > 0) {
	foreach $suffix (@suffixes) {
	    system "$prog $orig$suffix $final" if -e "$orig$suffix";
	    $status |= $?;
	}
    }
    else {
	foreach $suffix (@suffixes) {
	    system "$prog $orig$suffix" if -e "$orig$suffix";
	    $status |= $?;
	}
    }
    $status;
}


;# Validate name for suitability across all platforms
sub verifyName
{

    local($name, $which) = @_;


;# Check that name includes only digits and letters
    if ( $name !~ /^[0-9a-z]*$/ ) {
	die "$which may include only lowercase letters and digits.\n";
    }
;	# In a case of lengthy name, inform user that it will be truncated
;#    if ($tty) {
;#	# This is more funny than if (length($name) > 7) {}
;#	if ( $name !~ /^.{1,7}$/ ) {
;#	    printf STDERR "$which is too long (>7 chars). OK to truncate?   ";
;#	    if (!&get_y_or_n) {
;#		die "Aborted.\n";
;#	    }
;#	}
;#    }
}	



;#Tester for the decoder/encoder test cases
;#	@(#)deruntst.pl	6.2	97/05/28
sub run_test
{

    local($compile, $name, @args) = @_;
    local($codetester) = "$CODETEST"; # $SRC/memtool.$obj";
    local($cord, #cord = 0: no crash, cord = 1: core dumpd
		$exitcod, $pid, $suf, $firstChar);
    local(@objects, @failures, @compilerExtraOptions, @linkerExtraLibraries, $LIB);


    foreach $arg (@args) {
	($firstChar = $arg) =~ s/(.).*/$1/;
	if ($firstChar eq "-") {
	    push(@compilerExtraOptions, "$arg");
	}
    }
    foreach $arg (@args) {
	($cpp, $filename) = &checkFile($arg);
	if ($cpp == 1) {
	    $LIB = $CPP_LIB;
	    system "$CC -c $CPP_OPTIONS " . join(" ", @compilerExtraOptions) . " $filename >> $name.out 2>&1";
	}
	elsif (!$cpp) {
	    $LIB = $C_LIB;
	    system "$CC -c $C_OPTIONS " . join(" ", @compilerExtraOptions) . " $filename >> $name.out 2>&1";
	}
	else {
	    if (-e "$ITS_ROOT/runtime/$arg.$lib") {
		push(@linkerExtraLibraries, "$ITS_ROOT/runtime/$arg.$lib");
	    }
	    if (-e "$ITS_ROOT/runtime/$arg.$obj") {
		push(@linkerExtraLibraries, "$ITS_ROOT/runtime/$arg.$obj");
	    }
	    next;
	}
	$exitcod = $?;
	if ($exitcod >>= 8) { # If the compile failed 
	    push(@failures, (cpp == 1)? "$arg.cpp (code = $exitcod)": "$arg.c (code = $exitcod)");
	}
	push(@objects, "$arg.$obj");
    }

    if (@failures) {
	unlink @objects;
	return join(", ", @failures) . " not compiled.";
    }

    if ($WINDOWS) {
	system "$LINK $LINKOPTIONS -out:$name.exe " . join(" ", @objects) . " " . join(" ", @linkerExtraLibraries) . " $codetester $LIB >>$name.out 2>&1";
    }
    else {
	system "$CC $C_OPTIONS -o $name.exe " . join(" ", @objects) . " $codetester $LIB >>$name.out 2>&1";
    }
    $exitcod = $?;
    unlink @objects;
    if ($exitcod >>= 8) { # If the link failed
	unlink "$name.exe";
	return "Not linked: $exitcod.";
    }

    unlink "$name.out";
    system "$name.exe >> $name.out 2>&1";
    $exitcod = $?;
;	# Signal from "sh" -OR- signal from "a.out" -OR- core dump
    if ($exitcod & 0377 || ($exitcod >>= 8) & 0200 || -e "core") {
	rename("core", "$name.core") if (!$WINDOWS);
	unlink "$olddir/$name.exe";
	system "mv -f $name.exe $olddir/$name.exe";
	$exitcod = sprintf("Core dumped: %d.", $exitcod);
    }
    elsif ($keep_executable) {
	unlink "$olddir/$name.exe";
	system "mv -f $name.exe $olddir/$name.exe";
	$exitcod = "Failed: $exitcod." if ($exitcod);
    }
    else {
	unlink "$name.exe";
	$exitcod = "Failed: $exitcod." if ($exitcod);
    }
    $exitcod;
}


sub checkProcess
{

    local($lockname) = @_;

    $lockfilename = "$directory/$lockname.lock";
    if (open(LOCKFILE, "$lockfilename")) {
	($pid, $username, $hostname) = split(' ', <LOCKFILE>);
	$cur_host = &get_hname;
	if ($hostname."\n" eq $cur_host) {
		;# Find PID of the specified program.
	    open(PS_RESULT, "ps -e|grep $pid|");
	    split(' ', <PS_RESULT>);
	    close(PS_RESULT);
	    if ($pid eq @_[0]) {
		$is_locked = true;
		die "Can't run $DAEMON right now since $lockname is currently being run by $username.\n";
	    }
	    else {
		close(LOCKFILE);
		`rm -f $lockfilename 2>&1`;
		$is_locked = false;
	    }
	}
	else {
	    die "Can't run $DAEMON right now since $lockname is currently being run on $hostname by $username.\n";
	}
    }
    else {
	$is_locked = false;
    }
    $is_locked;
}


sub get_hname
{

    open(HNAME, "hostname|");
    $get_hname = <HNAME>;
    close(HNAME); 
    $get_hname;
}


sub checkFile
{

    local($name) = @_;
    local($cpp, $filename);


    if (-e "$name.@sourcesuf[0]") {
	$filename = "$name.@sourcesuf[0]";
	$cpp = 0;
    }
    elsif (-e "$name.@sourcesuf[1]") {
	$filename = "$name.@sourcesuf[1]";
	$cpp = 1;
    }
    else {
	$filename = "";
	$cpp = -1;
    }
    ($cpp, $filename);
}

chdir $curdir;
if ($WINDOWS) {
    close(LOCKFILE);
}
`rm -f $directory/$testdaemon.lock 2>&1`;

