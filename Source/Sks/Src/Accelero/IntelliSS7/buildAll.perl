use Cwd;
use Win32;

$BUILD_ORDER_FILE       = "build.ord";
$BUILD_OUTPUT_FILE      = "build.out";
$SUBSYSTEM_TARGETS_FILE = "build.targets";


$buildSubsystemOnly      = 0;
$buildEntityOnly         = 0;
$subsystemPrefix         = "";
$entityPrefix            = "";
$startingSubsystemPrefix = "";
$buildFlag               = "debug";


#
# getArguments
#
#   Purpose:
#       Get the command line arguments and store the results in
#       global variables.
#
#   Usage:
#       build [-s] [-u] [-f <debug | release | all>] [-x <subsystemPrefix>]
#             [-e <subsystemPrefix>] [<entity>]
#
#       where -s just build the subsystem and not it's dependencies
#       the default is to build all dependencies and then the subsystem.
#
#       where -u just build the entity and not it's dependencies
#       the default is to build all dependencies and then the entity
#
#       where -f allows the user to specify the build flag.  Recognized
#       flags are 'debug' to just build subsytem softeare, 'release' to just
#       build release software, and 'all' to build both debug and release.
#
#       where -x is the subsystem to start from when building dependent
#       subsystems up to the desired subsystem.
#
#       where -e <subsystemPrefix> is the prefix of the subsystem to build to,
#       or none to build all remaining subsystems.
#
#       where <entity> is the protocol module to build, or common, tools.
#
sub printUsage
{
    printf "perl build.perl [-s] [-u] [-f <debug | release | all>]\n";
    printf "        [-x <subsystemPrefix>] [-e <subsystemPrefix>] [<entity>]\n";
}

sub getArguments
{
    my $haveEnt = 0;

    if ($#_ == -1)
    {
        printUsage();
        exit 1;
    }

    while ($#_ >= 0)
    {
        for ($_[0])
        { 
            /-s/ and do 
            {
                $buildSubsystemOnly = 1;
                shift;
                last;
            };

            /-u/ and do 
            {
                $buildEntityOnly = 1;
                shift;
                last;
            };

            /-f/ and do 
            {                           
                if ($#_ >= 1)
                {
                    if ($_[1] ne "debug" && $_[1] ne "release" &&
                        $_[1] ne "all")
                    {
                        printf "ERROR, build flag '%s' is not valid.\n", $_[1];
                        printUsage();
                        exit 1;
                    }

                    $buildFlag = $_[1];
                    shift;  
                    shift;
                    last;
                }
                else
                {
                    print "ERROR: Missing build flag\n";
                    printUsage();
                    exit 1;
                }
            };

            /-x/ and do 
            {
                if ($#_ >= 1)
                {
                    $startingSubsystemPrefix = $_[1];
                    shift;  
                    shift;
                    last;
                }
                else
                {
                    print "ERROR: Missing <subsystemPrefix>\n";
                    printUsage();
                    exit 1;
                }
            };

            /-e/ and do
            {
                if ($#_ >= 1)
                {
                    $subsystemPrefix = $_[1];
                    shift;  
                    shift;
                    last;
                }
                else
                {
                    print "ERROR: Missing <subsystem>\n";
                    printUsage();
                    exit 1;
                }
            };

            'DEFAULT' and do 
            {   
                if ($#_ == 0)
                {
                    $entityPrefix = $_[0];
                    shift;
                    last;
                }
                else
                {
                    printf "ERROR: Incorrect number of parameters %d.\n$USAGE",
                           $#_;
                    exit 1;
                }
            };               
        } 
    }
}


#
# displayWarnings
#
#   Purpose:
#       Display all warning messages found in the output file.
#
#   Input Parameters:
#       fileName - Name of the output file.
#
#   Return Value:
#       Number of warnings found.
#
sub displayWarnings
{
    # Check for proper input
    if ($#_ != 0)
    {
        print "ERROR: Usage: displayWarnings <fileName>\n";
        return 1;
    }    
    my $fileName = $_[0];

    # Return 0 warnings if file exists and is empty
    if (-z $fileName)
    {
        return 0;
    }

    # Read the contents of the output file
    $result = open( filehandle, $fileName );
    if ($result == undef)
    {
        printf "ERROR: Unable to open file %s\n", $fileName;
        return 1;
    }

    my $bytesRead = read filehandle, $buildOutput, 100000;
    if ($bytesRead <= 0)
    {
        printf "ERROR: Unable to read file %s\n", $fileName;
        return 1;
    }

    close filehandle;

    my @buildOutput = split /\n/, $buildOutput;
    my @warnings = grep / warning/, @buildOutput;

    my $index = 0;
    while ($index <= $#warnings)
    {
        printf "%s\n", $warnings[$index++];
    }
    
    return $#warnings;
}


#
# checkForErrors
#
#   Purpose:
#       Check a specified output file for errors.
#
#   Input Parameters:
#       fileName - Name of the output file.
#
#   Return Value:
#       Number of errors found.
#
sub checkForErrors
{
    # Check for proper input
    if ($#_ != 0)
    {
        print "ERROR: Usage: checkForErrors <fileName>\n";
        return 1;
    }    
    my $fileName = $_[0];

    # Return 0 errors if file exists and is empty
    if (-z $fileName)
    {
        return 0;
    }

    # Read the contents of the output file
    my $result = open( filehandle, $fileName );
    if ($result == undef)
    {
        printf "ERROR: Unable to open file %s\n", $fileName;
        return 1;
    }

    my $bytesRead = read filehandle, $buildOutput, 100000;
    if ($bytesRead <= 0)
    {
        printf "ERROR: Unable to read file %s\n", $fileName;
        return 1;
    }

    close filehandle;

    my @buildOutput = split /\n/, $buildOutput;
        my @errors = grep / error/, @buildOutput;

        return $#errors + 1;
}


    
    
    
#
# buildTarget
#
#   Purpose:
#       Build a target within a subsystem.
#
#   Input Parameters:
#       subsystemDir - Directory name of the subsystem under the src directory.
#
#   Return Value:
#       1 if successful, 0 otherwise.
#
sub buildTarget
{
    # Check for proper input
        if ($#_ != 3)
        {
            print "ERROR: Usage: buildTarget <targetName> <path to makefile> <makefile> <configuration>\n";
            return 0;
        }
        my $target         = $_[0];
        my $pathToMakefile = $_[1];
        my $makefileName   = $_[2];
        my $configuration  = $_[3];

    # Change directory to where the makefile is located
        my $subsystemDir = GetCwd();
        
    # Build the subsystem    
        printf "\n======== %s : %s ========\n", $target, $configuration;
        printf "Building %s ...\n", $makefileName;
        if (system( "nmake /nologo /s /f $makefileName CFG=$configuration > $BUILD_OUTPUT_FILE" ))
        {
            system( "type $BUILD_OUTPUT_FILE" );
            return 0;
        }

    # Check the build output for errors
        print "Checking output file for errors ...\n";
        if ($numberOfErrors = checkForErrors( $BUILD_OUTPUT_FILE ))
        {
            system( "type $BUILD_OUTPUT_FILE" );
            printf "%d errors found.\n", $numberOfErrors;
            return 0;
        }

    # Display warnings (if any)
        displayWarnings $BUILD_OUTPUT_FILE;

    # Change directory back to the subsystem directory
    chdir "$subsystemDir";

    return 1;
}


#
# buildSubsystem
#
#   Purpose:
#       Build a subsystem.
#
#   Input Parameters:
#       subsystemDir - Directory name of the subsystem under the src directory.
#
#   Return Value:
#       1 if successful, 0 otherwise.
#
sub buildSubsystem
{
    # Check for proper input
    if ($#_ != 0)
    {
        print "ERROR: Usage: buildSubsystem <subsystemDir>\n";
        return 0;
    }    
    my $subsystemDir = $_[0];
    
    # Change directory to the subsystem directory
    my $rootDirectory = GetCwd();
    my $result = chdir "src/$subsystemDir";
    if (! $result)
    {
        my $result = chdir "src";
        if (! $result)
        {
            printf "ERROR: Unable to access directory src/%s or src\n",
                   $subsystemDir;
            return 0;
        }
    }

    # Read in the build.order file for the subsystem
    # The build.order file must be of the format:
    # <directory to makefile> <makefile name> <configuration> <build flag>
    $result = open( filehandle, $SUBSYSTEM_TARGETS_FILE );
    if ($result == undef)
    {
        printf "ERROR: Unable to open file %s\n", $SUBSYSTEM_TARGETS_FILE;
        return 0;
    }

    my $bytesRead = read filehandle, $buildTargets, 100000;
    if ($bytesRead <= 0)
    {
        printf "ERROR: Unable to read file %s\n", $SUBSYSTEM_TARGETS_FILE;
        return 0;
    }

    close filehandle;
    my @buildTargets = split /\n/, $buildTargets;
    
    # Build all of the desired targets in the build.order file
    my $targetIndex = 0;
    while ($targetIndex <= $#buildTargets)
    {
        my @targetEntry = split /\s+/, $buildTargets[$targetIndex], 4;
        if ($buildFlag eq "all" || $buildFlag eq $targetEntry[2])
        {
            $result = buildTarget( $subsystemDir, $targetEntry[0],
                                   $targetEntry[1], $targetEntry[3] );
            if ($result != 1)
            {
                printf "ERROR: buildTarget failed for target '%s'\n",
                       $targetEntry[3];
                return 0;
            }
        }
        ++$targetIndex;
    }

    # Change back to the original working directory
    chdir "$rootDirectory";

    return 1;
}


#
# buildOneSub
#
#   Purpose:
#       Build the specified subsystem.  Make sure all dependencies
#       are build before the subsystem is built.
#
#   Input Parameters:
#       subsystemPrefix - Prefix identifying the substem.  Must be
#                         the same as the directory name of the subsystem
#                         under the src directory.
#
#   Return Value:
#       1 if successful, 0 otherwise.
#
sub buildEntity
{
    # Check for proper input
    if ($#_ != 0)
    {
        print "ERROR: Usage: buildSubsystem <subsystemDir>\n";
        return 0;
    }    
    my $subsystemDir = $_[0];
    
    # Change directory to the subsystem directory
    my $rootDirectory = GetCwd();
    my $result = chdir "$subsystemDir";
    if (! $result)
    {
        printf "ERROR: Unable to access directory src/%s or src\n",
               $subsystemDir;
        return 0;
    }

    # Read the contents of the build order file into an array
    my $result = open( filehandle, $BUILD_ORDER_FILE );
    if ($result == undef)
    {
        printf "ERROR: Unable to open file %s\n", $BUILD_ORDER_FILE;
        return 0;
    }

    my $bytesRead = read filehandle, $buildOrder, 100000;
    if ($bytesRead <= 0)
    {
        printf "ERROR: Unable to read file %s\n", $BUILD_ORDER_FILE;
        return 0;
    }

    close filehandle;
    my @buildOrder = split /\n/, $buildOrder;

    # Verify the desired entry exists in the build order file
    my $index;
    for ($index = 0; $index <= $#buildOrder; $index++)
    {
        if ($subsystemPrefix eq $buildOrder[$index])
        {
            goto found;
        }
    }

    if ($index > $#buildOrder)
    {
        printf "Attempting to build entire subsystem\n";

        $index = $#buildOrder;
        $subsystemPrefix = $buildOrder[$index];
    }


    # Build dependencies if desired.
    found:
    if (! $buildSubsystemOnly)
    {
        my $buildIndex = 0;

        # Advance buildIndex to index of starting subsystem if a
        # starting subsystem was specified.
        if ($startingSubsystemPrefix ne "")
        {
            while ($buildIndex <= $#buildOrder &&
                   $startingSubsystemPrefix ne $buildOrder[$buildIndex])
            {
                ++$buildIndex;
            }
            if ($buildIndex > $#buildOrder)
            {
                printf "ERROR: %s is an invalid starting subsystem prefix.\n",
                        $startingSubsystemPrefix;
                return 0;
            }
        }

        while ($subsystemPrefix ne $buildOrder[$buildIndex])
        {
            $result = buildSubsystem( $buildOrder[$buildIndex] );
            if (! $result)
            {
                printf "ERROR: build failed for subsystem %s.\n",
                       $buildOrder[$buildIndex];
                return 0;
            }
            ++$buildIndex;
        }
    }

    # Build specified subsystem
    $result = buildSubsystem( $subsystemPrefix );
    if (! $result)
    {
        printf "ERROR: build failed for subsytem %s.\n", $subsystemPrefix;
        return 0;
    }

    # Change back to the original working directory
    chdir "$rootDirectory";

    return 1;
}

#
# buildAll
#
#   Purpose:
#       Build the specified subsystem.  Make sure all dependencies
#       are build before the subsystem is built.
#
#   Input Parameters:
#       subsystemPrefix - Prefix identifying the substem.  Must be
#                         the same as the directory name of the subsystem
#                         under the src directory.
#
#   Return Value:
#       1 if successful, 0 otherwise.
#
sub buildAll
{
    # Parse the command line arguments
    getArguments( @ARGV );

    # Read the contents of the build order file into an array
    my $result = open( filehandle, $BUILD_ORDER_FILE );
    if ($result == undef)
    {
        printf "ERROR: Unable to open file %s\n", $BUILD_ORDER_FILE;
        return 0;
    }

    my $bytesRead = read filehandle, $entityOrder, 100000;
    if ($bytesRead <= 0)
    {
        printf "ERROR: Unable to read file %s\n", $BUILD_ORDER_FILE;
        return 0;
    }

    close filehandle;
    my @entityOrder = split /\n/, $entityOrder;

    # Verify the desired entry exists in the build order file
    my $index;
    for ($index = 0; $index <= $#entityOrder; $index++)
    {
        if ($entityPrefix eq $entityOrder[$index])
        {
            goto found;
        }
    }

    if ($index > $#entityOrder)
    {
        printf "Attempting to build all entities\n";

        $index = $#entityOrder;
        $entityPrefix = $entityOrder[$index];
    }


    # Build dependencies if desired.
    found:
    if (!$buildEntityOnly)
    {
        while ($entityPrefix ne $entityOrder[$entityIndex])
        {
            $result = buildEntity( $entityOrder[$entityIndex] );
            if (! $result)
            {
                printf "ERROR: build failed for entity %s.\n",
                       $entityOrder[$entityIndex];
                return 0;
            }
            ++$entityIndex;
        }
    }

    # Build specified entity
    $result = buildEntity( $entityPrefix );
    if (! $result)
    {
        printf "ERROR: build failed for subsytem %s.\n", $entityPrefix;
        return 0;
    }

    return 1;
}

#
# MAIN
#
my $result = buildAll( @ARGV );
if ($result)
{
    print "\nBuild Complete.\n";
}
else
{
    print "\nBUILD FAILED!!!\n";
}
