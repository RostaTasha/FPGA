# Urock TCL script for cleaning src folder of FPGA projects

# for now only /src/cores is cleaned
# depends on ./src/prj/xci.prj file

set tclDir [pwd]

set srcDir     [file normalize "$tclDir/../src"]
set coreDir    "$srcDir/cores"
set prjDir     "$srcDir/prj"

# get a list of xci files from file
set xci_file "$prjDir/xci.prj"
set xci_file_list [list]
if [catch {set f_id [open $xci_file r]} msg] {
	puts "Failed to open xci.prj, error = $msg"
	exit
}

while {[gets $f_id line] >= 0} {
	# skip comment lines starting with "#" character
	if {[regexp {^#.*} $line tmp ] == 0} {
		lappend xci_file_list $line
	}
}

close $f_id



foreach core $xci_file_list {

    foreach filename [glob -nocomplain "$coreDir/$core/*"] {
	
		if [regexp {\.xci$} $filename tmp] {
			puts "$filename is XCI"
		} else {
			set ret_val [file delete -force $filename]
			puts "Deleting $filename: $ret_val"
		}
     
    }  
}





