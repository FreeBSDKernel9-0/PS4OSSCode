use File::Copy::Recursive qw(dircopy);
use File::Copy;
use File::Path;


sub initializeOrbis($)
{
    my ($jsc_console_root) = @_;

    $ENV{"ORBIS_JSC_APPHOME"} = "" . $jsc_console_root; # set APP_HOME to jsc_console_root
    $ENV{"ORBIS_JSC_HOSTAPP"} = "."; # set HOST_APP to sunspider test directory

    return "../../Tools/Scripts/sony/orbisrun-jsc.sh";
}

sub initializeVita($)
{
    my ($jsc_console_root) = @_;

    $ENV{"PSP2_JSC_APPHOME"} = "" . $jsc_console_root; # set APP_HOME to jsc_console_root
    $ENV{"PSP2_JSC_HOSTAPP"} = "."; # set HOST_APP to sunspider test directory

    return "../../Tools/Scripts/sony/psp2run-jsc.sh";
}

1;
