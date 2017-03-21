#!perl
#
# Copyright (C) 1999-2000 IntelliNet Technologies, Inc.  All rights reserved.
#

;#
;# Warning!  There should exist 2 copies of this script, iac.pl and iac++.pl.
;# The first one is used for testing the ASN.1/C compiler while the second
;# one for testing the ASN.1/C++ compiler.  So only one copy should be edited
;# at a time and then copied to either iac.pl or iac++.pl.
;#

;#
;# $Id: iac.pl,v 1.1.1.1 2007-10-08 11:11:10 bsccs2 Exp $
;#
;# $Log: not supported by cvs2svn $
;# Revision 1.1.1.1  2007/10/04 13:23:38  bsccs2
;# init tree
;#
;# Revision 1.1.1.1  2007/08/03 06:48:37  cvsadmin
;# BscCs2
;#
;# Revision 1.1.1.1  2007/03/08 15:12:51  cvsadmin
;# BSC project
;#
;# Revision 9.1  2005/03/23 12:51:01  cvsadmin
;# Begin PR6.5
;#
;# Revision 8.2  2005/03/21 13:49:06  cvsadmin
;# PR6.4.2 Source Propagated to Current
;#
;# Revision 7.1  2002/08/26 22:08:32  mmiers
;# Begin PR6.2
;#
;# Revision 6.1  2002/02/28 16:13:16  mmiers
;# Begin PR7.
;#
;# Revision 5.1  2001/08/16 20:45:05  mmiers
;# Start PR6.
;#
;# Revision 4.1  2001/05/01 00:52:59  mmiers
;# Begin PR5
;#
;# Revision 3.1  2000/08/15 23:55:37  mmiers
;#
;# Begin round 4.
;#
;# Revision 1.4  2000/04/04 16:57:26  npopov
;# Fixed mail lists
;#
;# Revision 1.3  2000/03/31 16:25:05  npopov
;# Update is now done if -make is specified
;#
;# Revision 1.2  2000/03/28 16:30:49  npopov
;# Added Id & Log macros for CVS
;#
;#


$WINDOWS = "yes";			# Should be "yes" for Windows & "" for Unix
#include "D:/cvsroot/intelliss7/maillist.pl"	# Uncomment for Windows
;#include "/u6/ossi/src/maillist.pl"	# Uncomment for Unix

$TMP = "/tmp" unless ($TMP = $ENV{'TMP'});
($testdaemon = "$0") =~ s@.*/@@;	# remove pathname qualifiers
$testdaemon =~ s@\.pl@@;		# remove the .pl
($DAEMON = $testdaemon) =~ tr/a-z/A-Z/;

if ($WINDOWS) {
    $ITS_ROOT  = $ENV{'ITS_ROOT'};
    $ITS_ROOT =~ s/\\/\//;
    $PERL = $ENV{'PERLDIR'};
    $MAILDIR = $ENV{'MAILDIR'};
    $UTIL = $ENV{'UTIL'};
    $TMP =~ s/\\/\//;
    $TMP =~ tr/A-Z/a-z/;
    $TESTDIR = $ENV{'TESTDIR'};
    if ($DAEMON eq "IAC") {
	$ASN1 = "$ITS_ROOT/tools/bin/asnc.exe" unless ($ASN1 = $ENV{'ASNC'});
    }
    else {
	$ASN1 = "$ITS_ROOT/tools/bin/asncc.exe" unless ($ASN1 = $ENV{'ASNCC'});
    }
    $CC = $ENV {'CC'} || 'cl';
    $INCLUDE = "-I$ITS_ROOT -I$ITS_ROOT/common/include -I.";
    $C_OPTIONS = "-W3 -MDd -DWIN32 -D_WIN32 -Z7 -Od -GB -Ze $INCLUDE";
    $CPP_OPTIONS = "-TP -GX $C_OPTIONS -I$ITS_ROOT/common/include/asn-cpp";
    $DIFF = "diff -H";
}
else {
    $TESTDIR = "/u6/ossi" unless ($TESTDIR = $ENV{'TESTDIR'});
    $ASN1 = "$TESTDIR/src/c++/compiler/asn1cpp" unless ($ASN1 = $ENV{'ASN1CPP'});
    $CC = $ENV {'CC'} || 'g++';
    $INCLUDE = "-I$TESTDIR/src -I$TESTDIR/src/api -I$TESTDIR/src/c++/runtime";
    $WARNING = $ENV{'CFLAGS'}  || ($CC eq 'g++'? '-Wall': ' ');
    $C_OPTIONS = "-DOSSI -DUNIX -g -static $INCLUDE $WARNING";
    $CPP_OPTIONS = "$C_OPTIONS";
    $DIFF = "diff";
    $utildir = "$TESTDIR/src"; # Various auxiliary utilites
}

$HELP = "$ITS_ROOT/$testdaemon.help.txt";
push(@INC, '$PERLDIR');
$WORKDIR = "$TESTDIR/compilertest";
$CURDIR = `pwd`;
chop $CURDIR;

`rm -f $WORKDIR/$testdaemon.lock 2>&1`;
if (-e "$WORKDIR/$testdaemon.lock") {
    die "$DAEMON is running.  Try again later.\n";
}

$sourcesuf = "asn";
$outputdir = "OUTPUT";
$extraargs = "";		# extra arguments to the ASN.1 compiler

;#
;# The index 0 entry is the same a the defaults above.
;# The index 1 entry is for ctest with some additional ASN.1 compiler options
;#
@alternateOutputDirs = (
    "OUTPUT",
    "OUTPUT1"
);

@alternateExtraArgs = (
    ""
);

$usage = "Usage: $testdaemon command [flags]\nType \"$testdaemon help\" for help.\n";

$build = "-n";
if ($ARGV[0] eq "-make") {
    shift(@ARGV);
    $build = $DAEMON eq "IAC"? "Update ASN1CCompiler": "Update ASN1C++Compiler";
}

$command = shift(@ARGV) || die $usage;
if ($command eq "help") {
    ($pager = $ENV{"PAGER"}) || ($pager = "more");
    system "$pager $HELP";
    exit(0);
}

;#
;# Open list of tests. Each entry has the following format:
;#
;# status(0-3)<TAB>args to asn1<TAB>categories<TAB>comment
;#
$dbmfile = $DAEMON eq "IAC"? "$WORKDIR/ctests": "$WORKDIR/cpptests";
dbmopen(tests, $dbmfile, 0660) || die "Could not open tests file, 'ctests'.\n";

;#
;# Are we running on a terminal?
;#
$tty = (-t STDIN)? 1: 0;
umask (027);

open(LOCK, ">$WORKDIR/$testdaemon.lock");

if ($command eq "create" || $command eq "update" || $command eq "test" || $command eq "run") {
    if (!-e $ASN1) {
	die "$ASN1 not found.";
    }
}

if ($command eq "create") {
	;#
	;# Create a new test case.
	;# Format: ctest create [-g|-b|-u] test_name cat_names [args...]
	;#
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
    $name =~ s/\.$sourcesuf//;
    &make;
    (@categories = split(/:/, shift(@ARGV))) || die $usage;
    @args = @ARGV;
    &verifyName($name, "Name of testcase");	
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
		;#
		;# Delete old files...
		;#
;#($firstChar = $found) =~ s/(.).*/$1/;
	if ($DAEMON eq "IAC") {
	    `rm -fr $WORKDIR/$outputdir/$found/c/ 2>&1`;
	}
	else {
	    `rm -fr $WORKDIR/$outputdir/$found/c++/ 2>&1`;
	}
	`rmdir  $WORKDIR/$outputdir/$found 2>&1`;
;#	`rm -fr $WORKDIR/$outputdir/$firstChar/$found` if -e "$WORKDIR/$outputdir/$firstChar/$found";
	$cat = (split(/\t/, $tests { $found }))[2];
	foreach $curcat (split(/:/, $cat)) {
	    unlink "$WORKDIR/$curcat/$found.$sourcesuf";
	}
    }
    foreach $curcat (@categories) { # Are we creating new categories?
	if (!-e "$WORKDIR/$curcat" || !-d "$WORKDIR/$curcat") {
	    if ($tty) {
		print STDERR "Create new category '$curcat'?  ";
		if (!&get_y_or_n) {
		    die "Aborted.\n";
		}
	    }
	    mkdir "$WORKDIR/$curcat", 0770;
	    chmod 0770, "$WORKDIR/$curcat";
	}
    }
    if (!-e "$name.$sourcesuf") {
	print STDERR "Creating virtual test case.\n";
    }
    else {
	@stat = stat(_);
	chmod $stat[2] & ~0222, "$name.$sourcesuf";
	push(@args, $name);
	foreach $curcat (@categories) {
	    if (-e "$WORKDIR/$curcat/$name.$sourcesuf") {
		print STDERR "Overwrite existing $WORKDIR/$curcat/$name.$sourcesuf?  ";
		if (!&get_y_or_n) {
		    die "Aborted.\n";
		}
	    }
	    unlink "$WORKDIR/$curcat/$name.$sourcesuf"
		if (-e "$WORKDIR/$curcat/$name.$sourcesuf");
	    `cp $name.$sourcesuf $WORKDIR/$curcat/$name.$sourcesuf`;
	}
    }
    print STDERR "Comment?  " if $tty;
    $comment = <STDIN>;
    chop $comment;
    $args = join(" ", @args);
    unlink "$TMP/$name.$$.err";
    if ($DAEMON eq "IAC") {
	$lang = "c";
    }
    else {
	$lang = "c++";
    }
    mkdir "$WORKDIR/$lang", 0770;
    chmod 0770, "$WORKDIR/$lang";
    chdir "$WORKDIR/$lang";
    ($status, $message) = &run(1, $name, $status, $args, @categories);
    `rm -f asncc_useful.$sourcesuf 2>&1`;
    `rm -f univ.ph 2>&1`;
    chdir "$WORKDIR";
    print "$name: $message\n" if $message;
    $tests{$name} = "$status\t$args\t" . join(":", @categories) . "\t$comment";
    if (!-e "$outputdir/$name") {
	mkdir "$outputdir/$name", 0770;
	chmod 0770, "$outputdir/$name";
    }
    `mv -fr $lang $outputdir/$name 2>&1`;
    if (chdir "$outputdir/$name/$lang") {
	@dirlist = <*>;
	foreach $dir (@dirlist) {
	    chmod 0770, "$dir";
	}
    }
}
elsif ($command eq "remove") {
	;#
	;# Delete some test cases; use with care.
	;# Uses standard args (see parseargs) + -F --> dont confirm.
	;#
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
	if ($DAEMON eq "IAC") {
	    print STDERR "Delete C files for test case '$name'?  " if !$forced;
	}
	else {
	    print STDERR "Delete C++ files for test case '$name'?  " if !$forced;
	}
	if ($forced || &get_y_or_n) {
	    $cat = (split (/\t/, $tests{$name}))[2];
	    if ($DAEMON eq "IAC") {
		`rm -fr $WORKDIR/$outputdir/$name/c 2>&1`;
	    }
	    else {
		`rm -fr $WORKDIR/$outputdir/$name/c++ 2>&1`;
	    }
	    `rmdir  $WORKDIR/$outputdir/$name 2>&1`;
	    foreach $curcat (split(/:/, $cat)) {
		unlink "$WORKDIR/$curcat/$name.$sourcesuf";
	    }
	    delete $tests{$name};
	}
    }
}
elsif ($command eq "info" || $command =~ m/^ho[uw]$/) {
	;#
	;# Get info on some test cases
	;# Uses standard args and
	;#  -ddataspec Specify output format
	;# The output format is in the same form as SCCS prs
	;# The keys are:
	;#   :N:   Name of test case
	;#   :A:   Actual args to test case
	;#   :Ag:  Actual arguments to test case, less the name
	;#   :Ca:  Categories the test case belongs to
	;#   :C:   Comments on the test case
	;#   :Sn:  Status, numeric format (0-3)
	;#   :S: or :St:  Status, text format
	;#   :Sl:  Status, one-letter form
	;# The default format is  ":N:\t:S:\t:C:"
	;#
    @statletter = ('g', 'g', 'b', 'b', 'n', 'n');
    @statnames = (
	"Passes",
	"Once passed",
	"Fails",
	"Once failed",
	"Not known",
	"Was unknown"
    );
    @names = &parseargs;
    if (defined($dataspec = shift @ARGV)) {
	die $usage if $dataspec !~ s/^-d//;
	die $usage if $#ARGV >= 0;
    }
    else {
	$dataspec = ":N:\t:S:\t:C:";
    }
    $dataspec =~ s/\\t/\t/g;
    $dataspec =~ s/\\n/\n/g;
    foreach $name (@names) {
	if (!defined($tests{$name})) { 
	    print STDERR "$name does not exist.\n";
	    next;
	}
	($status, $args, $categories, $comment) = 
	    split(/\t/, $tests{$name});
	$categories = join(", ", split(/:/, $categories));
	$_ = $dataspec;
	s/:N:/$name/g;
	s/:Ca:/$categories/g;
	s/:C:/$comment/g;
	s/:A:/$args/g;
	$args =~ s/(^| )$name$//;
	s/:Ag:/$args/g;
	s/:Sn:/$status/g;
	s/:Sl:/$statletter[$status]/g;
	s/:St?:/$statnames[$status]/g;
	print $_ . "\n";
    }
}
elsif ($command eq "update") {
	;#
	;# Updates output, status, and/or category of some test cases
	;# Standard args plus
	;#   -uo  Update output
	;#   -ug  Change to "good" status (the test case now works)
	;#   -ub  Change to "bad" status (the test case was thought to work, incorrectly)
	;#   -uccat1:..:catn  Add the listed categories
	;#   -uC  Change the test comment
	;#   -udccat1:..:catn  Delete the listed categories
	;#   -ua   Change the arguments (remainder of command line)
	;#   -u[nu] change to unknown status
	;#   -o#	use the #th alternate Output directory and asn1 arguments
	;#
    if(!$WINDOWS) {
	@program_list=($testdaemon, cppmake);
	foreach $program (@program_list) {
	    &is_locked($program);
	}
	$pid=$$;
	$username=$ENV{'USER'} || "crond";
	$hostname=&get_hname;
	$lockfilename=$utildir.'/'.$testdaemon.'run.lock';
	open(LOCKFILE, ">$lockfilename") || die "Error creating lock file $lockfilename.";
	print(LOCKFILE $pid, ' ', $username, ' ', $hostname);
	close(LOCKFILE); 
    }

    $newstatus = -1;
    $output = 0;
    $ctc = 0;
    @argv = ();
    
    while (defined($flag = shift @ARGV)) {
	if ($flag =~ s/^-o//) {
	    die "-o index must not be greater than $#alternateOutputDirs\n" if $flag > $#alternateOutputDirs;
	    die "-o index must be 0 or greater.\n" if $flag < 0;
	    $outputdir = $alternateOutputDirs[$flag];
	    $extraargs = $alternateExtraArgs[$flag];
	}
	elsif ($flag !~ s/^-u//) {
	    push (@argv, $flag);
	}
	else {
	    while ($flag) {
		if ($flag =~ s/^o//) {$output = 1;}
		elsif ($flag =~ s/^g//) {$newstatus = 0;}
		elsif ($flag =~ s/^b//) {$newstatus = 2;}
		elsif ($flag =~ s/^[nu]//) {$newstatus = 4;}
		elsif ($flag =~ s/^C//) {$ctc = 1;}
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
			    mkdir "$WORKDIR/$curcat", 0770;
			    chmod 0770, "$WORKDIR/$curcat";
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
		    if ($#newargs < 0) {die $usage;}
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

    &make;

    chdir $WORKDIR;

    foreach $name (@names) {
	if ($DAEMON eq "IAC") {
	    $lang = "c";
	}
	else {
	    $lang = "c++";
	}
	($status, $args, $categories, $comment) = split(/\t/, $tests{$name});
	if ($newstatus >= 0) {
	    $status = $newstatus + ($status & 1);
	}
	if ($#newargs >= 0) {
	    $args = join(" ", @newargs);
	}
	if ($output) {
	    if (!-e $lang) {
		mkdir $lang, 0770;
		chmod 0770, $lang;
	    }
	    chdir "$WORKDIR/$lang";
	    $status &= 6;
	    ($status, $message) = &run(1, $name, $status, $args, split(/:/, $categories));
	    `rm -f asncc_useful.$sourcesuf 2>&1`;
	    `rm -f univ.ph 2>&1`;
	    chdir $WORKDIR;
	    print "$name: $message\n" if $message;

		;#
		;# Remove the output files if they exist.
		;#
	    `rm -fr $outputdir/$name/$lang 2>&1`;
	    if (!-e "$outputdir/$name") {
		mkdir "$outputdir/$name", 0770;
		chmod 0770, "$outputdir/$name";
	    }
	    `mv -fr $lang $outputdir/$name 2>&1`;
	    if (chdir "$outputdir/$name/$lang") {
		@dirlist = <*>;
		foreach $dir (@dirlist) {
		    chmod 0770, $dir;
	        }
	    }
	}
	if ($ctc) {
	    print STDERR "Changing comment for test case '$name'\n";
	    print STDERR "Old comment: $comment\n";
	    print STDERR "New comment: ";
	    $newcomment = <STDIN>;
	    chop $newcomment;
	    if ($newcomment) {
		$comment = $newcomment;
	    }
	}
	foreach $newcat (@newcategories) {
	    if ($categories !~ /(.|:)$newcat($|:)/) {
		$categories .= ":$newcat";
		system "cp " . (split(/:/, $categories))[0] . "/$name.$sourcesuf $newcat/$name.$sourcesuf";
	    }
	}
	foreach $oldcat (@oldcategories) {
	    $categories =~ s/(^|:)$oldcat//;
	    unlink "$oldcat/$name.$sourcesuf";
	}
	$categories =~ s/^:*//;
	$tests{$name} = "$status\t$args\t$categories\t$comment";
    }
    if (!$WINDOWS) {
	system "rm -f $lockfilename";
    }
}
elsif ($command eq "test") {
	;#
	;# Test whether output of some test cases has changed
	;# Standard args plus:
	;# -m send mail and update status in file
	;# -aasn1 use the listed asn1 instead of one in newest; incompatible with -m
	;# -d copy the diff output for changed files into this directory
	;# -o# use the #th alternate Output directory and asn1 arguments
	;#
    if (!$WINDOWS) {
	@program_list=($testdaemon, cppmake);
	foreach $program (@program_list) {
	    &is_locked($program);
	}
	$pid=$$;
	$username=$ENV{'USER'} || "crond";
	$hostname=&get_hname;
	$lockfilename=$utildir.'/'.$testdaemon.'run.lock';
	open(LOCKFILE, ">$lockfilename") || die "Error creating lock file $lockfilename.";
	print(LOCKFILE $pid, ' ', $username, ' ', $hostname);
	close(LOCKFILE); 
    }

    local($broken);
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
	    $ASN1 = $flag;
	    $asn1spec = 1;
	}
	elsif ($flag =~ s/^-o//) {
	    die "-o index must not be greater than $#alternateOutputDirs\n" if $flag > $#alternateOutputDirs;
	    die "-o index must be 0 or greater.\n" if $flag < 0;
	    $outputdir = $alternateOutputDirs[$flag];
	    $extraargs = $alternateExtraArgs[$flag];
	}
	else {
	    die $usage;
	}
    }

    $asn1spec && $mail && die "Can't send mail and specify asn1.\n";

    &make;

    chdir $WORKDIR;

    $SIG{'INT'} = 'neFarrer';
    $SIG{'TERM'} = 'neFarrer';

    unlink "DIFF_OUT$$"; # We should never need to do this
    while (($name = shift @names) && !$broken) {
	if ($DAEMON eq "IAC") {
	    $lang = "c";
	}
	else {
	    $lang = "c++";
	}
	if (!-e $lang) {
	    mkdir $lang, 0770;
	    chmod 0770, $lang;
	}
	chdir "$WORKDIR/$lang";
	($status, $args, $cats) = split(/\t/, $tests{$name});
	($m, $message) = &run(0, $name, $status, $args, split(/:/, $cats));

	system ">DIFF_OUT$$";
	if ($DAEMON eq "IAC") {
	    $DIF = "c.dif";
	    &diff("DIFF_OUT$$", "$name", "$outputdir/$name/c/", ".c.err", ".ph");
	}
	else {
	    $DIF = "cpp.dif";
	    &diff("DIFF_OUT$$", "$name", "$outputdir/$name/c++/", ".cpp.err");
	}
	chmod 0440, "DIFF_OUT$$";
	unlink "$olddir/$name.$DIF" if ($copydiff);
	if (system("cmp -s DIFF_OUT$$ ../$outputdir/$name/$lang/$name.$DIF")) {
	    push(@failednames, $message? "$name ($message)": $name);
	    warn $! if ($copydiff && system("cp DIFF_OUT$$ $olddir/$name.$DIF"));
	    if ($mail) {
		if ((!-e "DIFF_OUT$$") || (-z "DIFF_OUT$$")) {
		    $status &= ~1;
		}
		else {
		    $status |= 1;
		}
		$tests{$name} = $status . substr($tests{$name}, 1, length($tests{$name}) - 1);
		unlink "../$outputdir/$name/$lang/$name.$DIF";
		`mv -f DIFF_OUT$$ ../$outputdir/$name/$lang/$name.$DIF`;
	    }
	}
	unlink "DIFF_OUT$$";
	chdir $WORKDIR;
	`rm -fr $lang 2>&1`;
    }
    &showTimes($broken? "Broken at '$broken'": 'Time');
    if ($#failednames >= 0) {
	if (!$mail) {
	    print join(" changed\n", sort(@failednames)) . " changed\n";
	}
	else {
	    &sendmail("The state of the test cases has changed!",
		"The test cases changed are:\n\n" . join("\n", sort(@failednames)), @iacmaillist);
	}
    }
    elsif ($mail) {
	&sendmail("The state of the test cases has not changed.", "No changes.", @iacmaillist);
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
    if (!$WINDOWS) {
	system "rm -f $lockfilename";
    }
}
elsif ($command eq "extract" ||
		$command =~ m/^gett?$/ || $command =~ m/^retrieve?$/o) {
	;#
	;# Extracts some test cases.  Uses standard args.
	;#
    @names = &parseargs;
    die $usage if $#ARGV >= 0;
    $lang = $DAEMON eq "IAC"? "c": "c++";
    foreach $name (@names) {
	mkdir "$name", 0770;
	`cp -fr $WORKDIR/$outputdir/$name/$lang $name/ 2>&1`;
	($status, $args) = split(/\t/, $tests{$name});
	@files = &filesrefed(split(" ", $args));
	while ($file = shift(@files)) {
	    if ($cat = (split(/\t/, $tests{$file}))[2]) {
		($cat) = split(/:/, $cat);
		system "cp $WORKDIR/$cat/$file.$sourcesuf $name/$lang/";
	    }
	}
	system "cp $WORKDIR/asncc_useful.$sourcesuf $name/$lang/";
	system "cp $WORKDIR/univ.ph $name/$lang/";
    }
}
elsif ($command eq "rename") {
	;#
	;# Rename an existing test case
	;# format: ctest rename oldname newname
	;#
    local($km, @found);

    ($oldname = shift @ARGV) || die $usage;
    ($newname = shift @ARGV) || die $usage;
    chdir $WORKDIR;
    if (!defined($info = $tests{$oldname})) {
	die "Test case '$oldname' does not exist.\n";
    }
    if ($tests{$newname}) {
	push (found, $newname);
    }
#    elsif ($newname =~ /......./) {
#	$km = $&;
#	@found = grep(/^$km/i && $_ ne $oldname, keys tests);
#    }
    else {
	@found = grep(/^$newname$/i && $_ ne $oldname, keys tests);
    }
    die "Test case '" . join("', '", @found) . "' already there\n" if (@found);
  
    die "$outputdir name not changed (mv $?)\n" if
	-e "$outputdir/$oldname" &&
	system "mv -f $outputdir/$oldname $outputdir/$newname";

    ($status, $args, $categories, $comment) = split(/\t/, $info);
    $args =~ s/$oldname/$newname/;
    @categories = split(/:/, $categories);
    foreach $curcat (@categories) {
	rename "$curcat/$oldname.$sourcesuf", "$curcat/$newname.$sourcesuf";
    }
    $tests{$newname} = join("\t", $status, $args, $categories, $comment); 
    delete $tests{$oldname};
}
elsif ($command eq "run") {
	;#
	;# Runs a single test case in the current directory
	;# format: ctest run [-a asn1] name [args...]
	;# -a specifies which copy of asn1 to use
	;#
    ($name = shift @ARGV) || (die $usage);
    if ($name =~ s/^-a//) {
	$ASN1 = $name || ($ASN1 = shift @ARGV) || (die $usage);
	($name = shift @ARGV) || (die $usage);
    }
    else {
	&make;
    }
    @args = @ARGV;
    die "No $name.$sourcesuf found.\n" if !-e "$name.$sourcesuf";
    push(@args, $name) if -e "$name.$sourcesuf";
    if ($message = &run_test(1, $ASN1, $name, @args)) {
	print $message . "\n";
    }
}
elsif ($command eq "clean") {
	;#
	;# Cleans up from a run in the current directory
	;# Calling sequence: ctest clean test_name...
	;#
    foreach $name (@ARGV) {
	`rm -fr $name 2>&1`;
    }
}
else {
    @names = &parseargs;
    die $usage if $#ARGV >= 0;
    foreach $name (@names) {
	$categories = (split(/\t/, $tests{$name}))[2];
	$category = (split(/:/, $categories))[0];
	push (@newnames, "$WORKDIR/$category/$name.$sourcesuf");
    }
    system "$command @newnames";
}
dbmclose(tests);


;#
;# Parse command line options to find the subset of files referred to
;# Formats:
;#   name:...:name	Any one of the names specified (may be only one)
;#   -ccat:...:cat	Any one of the categories specified (may be only one)
;#   -g			Files that once worked
;#   -b			Files known to fail
;#   -u			Files with unknown status
;#   -w			Files that produce same output as checked in
;#   -f			Files that produce different output
;#   -s(0|1|2|3|4|5)*	All files with the specified status (0=works,1=worked,2=fails,3=failed,4=unknown,5=was unknown)
;#   -pprefix		All files that begin with prefix
;#
;# If several of these are specified, the intersection is returned.  If none are
;# specified, the whole thing is returned.  Unrecognized arguments are left in
;# @ARGV.  Asks for confirmation if entire suite specified and stdin is a terminal.
;#
sub parseargs
{

    local(@files, @newfiles, @argv, $curarg, $curfile, $foundspec);
    local($modified) = 0;
    

;	# Search for a name specifier
    foreach $curarg (@ARGV) {
	if ($curarg !~ /^-/) {
	    push(@files, split(/:/, $curarg));
	    $modified = $foundspec = 1;
	}
    }
    if ($foundspec) {
	@files = &verifyfiles(@files);
    }
    else {
	@files = keys %tests;		# No name specifier found
    }
    foreach $curarg (@ARGV) {
	if (!$modified) {
	    $modified = -1;
	}
	elsif ($modified == -1) {
	    $modified = 1;
	}
	if ($curarg eq "-g") {
	    @files = grep(substr($tests{$_}, 0, 1) & 6 == 0, @files);
	}
	elsif ($curarg eq "-b") {
	    @files = grep(substr($tests{$_}, 0, 1) & 6 == 2, @files);
	}
	elsif ($curarg eq "-u") {
	    @files = grep(substr($tests{$_}, 0, 1) & 6 == 4, @files);
	}
	elsif ($curarg eq "-w") {
	    @files = grep(!(substr($tests{$_}, 0, 1) & 1), @files);
	}
	elsif ($curarg eq "-f") {
	    @files = grep(substr($tests{$_}, 0, 1) & 1, @files);
	}
	elsif ($curarg =~ s/^-s//) {
	    @files = grep(($status = substr($tests{$_}, 0, 1),
					$curarg =~ /$status/), @files);
	}
	elsif ($curarg =~ s/^-p//) {
	    @files = grep(/^$curarg/, @files);
	}
	elsif ($curarg =~ s/^-c//) {
	    @cattest = split(/:/, $curarg);
	    while ($curfile = shift(@files)) {
		($s, $a, $cats) = split(/\t/, $tests{$curfile});
		foreach $curcat (@cattest) {
		    if ($cats =~ /$curcat/) {
			push(@newfiles, $curfile);
			last;
		    }
		}
	    }
	    @files = @newfiles;
	}
	elsif ($curarg =~ /^-/) {
	    push(@argv, $curarg);
	    $modified = 0 if $modified == -1;
	}
    }
    if (!$modified && $tty) {
	print STDERR "Run on whole test set? ";
	if (!&get_y_or_n) {
	    die "Aborted.\n";
	}
    }
    @ARGV = @argv;
    @files;
}


;#
;# Parses options to asn1 to find all files referred to.  Assumes no -c, -h,
;# -l, or -m.  All output files should be produced by our automatic runs.
;#
sub filesrefed
{

    local(@temp) = @_;
    local(@files, $cur);
    

    while ($cur = shift(@temp)) {
	push(@files, $cur) if $cur !~ /^-/;
    }
    @files;
}


;#
;# Sends message (the first arg) to the users listed in the remainder of args.
;#
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
From <$DAEMON>
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


;#
;# Gets an answer to a yes or no question.
;#
sub get_y_or_n
{

    local ($val) = -1;


    do {
	$ans = <STDIN>;
	if ($ans =~ /^y|Y/) {
	    $val = 1;
	}
	elsif ($ans =~ /^n|N/) {
	    $val = 0;
	}
	else {
	    print STDERR "Please answer 'y' or 'n'.\n";
	}
    } while $val < 0;
    $val;
}


;#
;# Links in appropriate files and runs a test case.  Takes name, status,
;# args, and categories of test to run.  Returns updated status of test case.
;#
sub run
{

    local ($compile, $name, $status, $args, $cat) = @_;
    local ($file, $curcat, @files, $lang);
    

    foreach $file (@files = &filesrefed(split(/ /, $args))) { #for each file in args
	if ($file eq $name) {
	    $curcat = $cat;
	}
	elsif (!defined($tests{$file})) {
	    next;
	}
	else {
	    ($curcat) = split(/:/, (split(/\t/, $tests{$file}))[2]);
	}
	$lang = $DAEMON eq "IAC"? "c": "c++";
	$symlink_exists = (eval 'symlink("","");', $@ eq '');
	if ($symlink_exists) {
	    `cp -f $WORKDIR/$curcat/$file.$sourcesuf $WORKDIR/$lang/$file.$sourcesuf 2>&1`;
	    `cp -f $WORKDIR/asncc_useful.$sourcesuf $WORKDIR/$lang/ 2>&1`;
	    `cp -f $WORKDIR/univ.ph $WORKDIR/$lang/ 2>&1`;
	}
	else {
	    `cp -f $WORKDIR/$curcat/$file.$sourcesuf $WORKDIR/$lang/$file.$sourcesuf 2>&1`;
	    `cp -f $WORKDIR/asncc_useful.$sourcesuf $WORKDIR/$lang/ 2>&1`;
	    `cp -f $WORKDIR/univ.ph $WORKDIR/$lang/ 2>&1`;
	}
    }
    if ($message = &run_test($compile, $ASN1, $name, split(/ /, $args))) {
	$status |= 1;
	@failures = () if $compile;
    }
    if ($DAEMON eq "IAC") {
	system "touch $name.c.dif";
	&cmd("chmod 0440", "$name", "", ".c.err", ".c.dif", ".ph");
    }
    else {
	system "touch $name.cpp.dif";
	&cmd("chmod 0440", "$name", "", ".cpp.err", ".cpp.dif");
    }
    foreach $file (@files) {		;#for each file in arguments
	if ($file ne $name && !defined($tests{$file})) {
	    next;
	}
	unlink "$file.$sourcesuf";
    }
    ($status, $message);
}


sub make
{
	;#
	;# Do a build...
	;#
    system "cd $ITS_ROOT; bw32 $build" unless $build eq '-n';
}


sub verifyfiles
{

	;#
	;# Make sure given files exist.
	;#
    local($curfile, @returnfiles);


    foreach $curfile (@_) {
	if (!defined($tests{$curfile})) {
	    print STDERR "Test case '$curfile' does not exist.\n";
	}
	else {
	    push(@returnfiles, $curfile);
	}
    }
    @returnfiles;
}


;#
;# Write the difference (into first argument) of second & third argument
;# with each suffix in following list.
;#
sub diff
{

    local($difference, $orig, $final, @suffixes) = @_;
    local ($suffix, $status, $cmp, $elfyl, $name, @filelist, $nline);


    $nline = "";
    foreach $suffix (@suffixes) {
	if (-e "$orig$suffix") {
	    $elfyl = "$WORKDIR/$final" . "$orig$suffix";
	    if (-e $elfyl) {
		system "cmp -s $orig$suffix $elfyl";
		$cmp = $?;
	    }
	    else {
		system "touch $elfyl";
		$cmp = 2;
	    }
	    if ($cmp) {
		`echo "$nline" >>$difference 2>&1`;
		`echo "DOING \\"diff\\" on $orig$suffix...\n" >>$difference 2>&1`;
		$nline = "\n";
		system "$DIFF $orig$suffix $elfyl >>$difference 2>&1";
	    }
	    $status |= $?;
	}
    }
    @filelist = <*.cpp *.h *.ph *.c>;
    foreach $file (@filelist) {
	if ($file eq "univ.ph" || $file eq "UNIV.ph") {
	    next;
	}
	$elfyl = "$WORKDIR/$final" . "$file";
	system "cmp -s $file$suffix $elfyl";
	$cmp = $?;
	if ($cmp) {
	    `echo "" >>$difference 2>&1` if $nline;
	    `echo "DOING \\"diff\\" on $file...\n" >>$difference 2>&1`;
	    $nline = "yes";
	    system "$DIFF $file $elfyl >>$difference 2>&1";
	}
	$status |= $?;
    }
    $status;
}


;#
;# Do a given command (first arg) on second & third arg with each suffix in 
;# list that follows.
;#
sub cmd
{

    local($prog, $orig, $final, @suffixes) = @_;
    local ($suffix, $status, $cmp);


    if (length($final) > 0) {
	foreach $suffix (@suffixes) {
	    $cmp = 0;
	    if ($prog eq "cp") {
		system "$prog $orig$suffix $final$suffix" if -e "$orig$suffix";
		$status |= $?;
	    }
	    else {
		system "$prog $orig$suffix $final" if -e "$orig$suffix";
		$status |= $?;
	    }
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


;#
;# Validate name for suitability across all platforms.
;#
sub verifyName
{

    local($name,$which) = @_;


	;#
	;# Check that name includes only digits and letters.
	;#
    if ($name !~ /^[0-9a-z_]*$/) {
	die "$which may include only lowercase letters and digits.\n";
    }
;	# In a case of lengthy name, inform user that it will be truncated
;#    if ($tty) {
;#	# This is more funny than if (length($name) > 7) {}
;#    	if ( $name !~ /^.{1,7}$/ ) {
;#	    printf STDERR "$which is too long (>7 chars). OK to truncate?   ";
;#	    if (!&get_y_or_n) { die "Aborted.\n"; }
;#	}
;#    }
}	


sub run_test
{

    local($compile, $ASN1, $name, @args) = @_;
    local($status, $tmpfile, @lstmod, $cmp, $object);
    local(@failures, $newargs, $firstChar);


    $newargs = join(" ", grep(/^$name/, @args));
    if ($newargs) {
	$newargs = "";
	foreach $arg (@args) {
	    $arg =~ tr/A-Z/a-z/;
	    ($firstChar = $arg) =~ s/(.).*/$1/;
	    if (index($arg, $name) >= 0) {
		next;
	    }
	    $newargs = $newargs eq ""? $newargs . $arg: $newargs . " " . $arg;
	}
	$status = &run_tests($ASN1, $name, $newargs);
    }
    else {
	$status = &run_tests($ASN1, $name, join(" ", @args));
    }
    if ($status) {
	if ($command eq "update" || $command eq "create") {
	    push (@failures, "$name.$sourcesuf");
	}
    }
    $tmpfile = "$TMP/$name.$$.err";
    if ($compile) {
	open(TEST, ">>$tmpfile");
	print TEST "$nline";
	print TEST "TESTING $name.$sourcesuf...\n\n";
	close(TEST);

	if ($DAEMON eq "IAC") {
	    `cat $name.c.err >>$tmpfile 2>&1`;
	    open(TEST, ">>$tmpfile");
	    print TEST "\nTESTING ALL C-FILES...\n\n";
	    close(TEST);
	    @filelist = <*.c>;
	    foreach $filename (@filelist) {
		open(TEST, ">>$tmpfile");
		print TEST "\nCOMMAND LINE FOR $filename:\n$CC -c $C_OPTIONS $filename\n\n";
		close(TEST);
		system "$CC -c $C_OPTIONS $filename>>$tmpfile 2>&1";
		if ($? >> 8) {
		    push(@failures, "$filename");
		}
		$filename =~ s@\.c@@;		# remove the .cpp
		`rm -f $filename.obj $filename.o 2>&1`;
	    }
	}
	else {
	    `cat $name.cpp.err >>$tmpfile 2>&1`;
	    open(TEST, ">>$tmpfile");
	    print TEST "\nTESTING ALL C++-FILES...\n\n";
	    close(TEST);
	    @filelist = <*.cpp>;
	    foreach $filename (@filelist) {
		open(TEST, ">>$tmpfile");
		print TEST "\nCOMMAND LINE FOR $filename:\n$CC -c $CPP_OPTIONS $filename\n\n";
		close(TEST);
		system "$CC -c $CPP_OPTIONS $filename>>$tmpfile 2>&1";
		if ($? >> 8) {
		    push (@failures, "$filename");
		}
		$filename =~ s@\.cpp@@;		# remove the .cpp
		`rm -f $filename.obj $filename.o 2>&1`;
	    }
	}
    }
    elsif ($keep_executable) {
	@filelist = <*.cpp *.h *.ph *.c *.err>;
	foreach $file (@filelist) {
	    `rm -f $olddir/$file 2>&1`;
	    `cp -f $file $olddir/ >>$tmpfile 2>&1`;
	}
    }
    `chmod ug+w $tmpfile 2>&1`;
    if ($#failures >= 0) {
	print "The following files failed: " . join(", ", @failures) . " (see $tmpfile)\n";
    }
    elsif (-s "$tmpfile" && @lstmod) {
	print "$name : " . join(", ", @lstmod) . " failed (see $tmpfile)\n";
    }
    else {
	unlink "$tmpfile";
	0;
    }
}


sub run_tests
{

    local ($ASN1, $name, $args) = @_;
    local($status, $rcode, $cline);


    $rcode = 0;
    if ($DAEMON eq "IAC") {
	print "Doing ASN.1/C test for $name...\n";
	$cline = "$ASN1 -A -a -f $name.$sourcesuf $args $extraargs";
	open(TEST, ">$name.c.err");
	print TEST "COMMAND LINE:\n$cline\n";
	close(TEST);
	$status = $rcode = system "$cline >>$name.c.err 2>&1";
    }
    else {
	print "Doing ASN.1/C++ test for $name...\n";
	$cline = "$ASN1 $name.$sourcesuf $args $extraargs -cpp -u asncc_useful.$sourcesuf";
	open(TEST, ">$name.cpp.err");
	print TEST "COMMAND LINE:\n$cline\n";
	close(TEST);
	$status = $rcode = system "$cline >>$name.cpp.err 2>&1";
    }
    if ($status) {
	$rcode = $status;
    }
    $rcode;
}


sub is_locked
{
    local($lockname)=@_;
    $lockfilename=$utildir.'/'.$lockname.'run.lock';
    if (open(LOCKFILE, "$lockfilename")) {
	($pid, $username, $hostname)=split(' ', <LOCKFILE>);
	$cur_host=&get_hname;
	if ($hostname."\n" eq $cur_host) {
	    open(PS_RESULT, "ps -e|grep $pid|");#tries to find PID of specified program
	    split(' ', <PS_RESULT>);
	    close(PS_RESULT);
	    if($pid eq @_[0]) {
		$is_locked=true;
		die "Can't run $testdaemon right now since $lockname is currently being run by $username.\n";
	    } else {
		close(LOCKFILE);
		system "rm -f $lockfilename";
		$is_locked=false;
	    }
	} else {
	    die "Can't run $testdaemon right now since $lockname is currently being run on $hostname by $username.\n";
	}
    } else {
	$is_locked=false;
    }
    $is_locked;
}


sub get_hname
{
    open(HNAME, "hostname|");
    $get_hname=<HNAME>;
    close(HNAME); 
    $get_hname;
}


chdir $CURDIR;
close(LOCK);
`rm -f $WORKDIR/$testdaemon.lock 2>&1`;

