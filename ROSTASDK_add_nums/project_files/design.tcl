###############################################################
###   Tcl Variables
###############################################################
#set tclParams [list <param1> <value> <param2> <value> ... <paramN> <value>]
set tclParams [list place.closeImportedSites  1 \
                    hd.StrictContainRouting   1 \
              ]

#Define location for "Tcl" directory. Defaults to "./Tcl"
set tclHome "./tcl"
if {[file exists $tclHome]} {
   set tclDir $tclHome
} elseif {[file exists "./Tcl"]} {
   set tclDir  "./Tcl"
} else {
   error "ERROR: No valid location found for required Tcl scripts. Set \$tclDir in design.tcl to a valid location."
}

###############################################################
### Part Variables - Define Device, Package, Speedgrade 
###############################################################
set device       "xc7v2000t"
set package      "fhg1761"
set speed        "-1"
set part         $device$package$speed

###############################################################
###  Setup Variables
###############################################################

set project_name "rc_pcie_base_2000_10"


set systemTime [clock seconds]

puts ""
puts "The date is: [clock format $systemTime -format %D]"
puts "The time is: [clock format $systemTime -format %H:%M:%S]"
puts ""



####flow control
set run.topSynth   1
set run.oocSynth   1
set run.tdImpl     1
set run.oocImpl    1
set run.topImpl    1
set run.flatImpl   0

set write_bit		1 

puts "Implementing project $project_name" 
puts ""
puts "Working dir = [pwd]"
puts ""
puts "topSynth = ${run.topSynth}"
puts "oocSynth = ${run.oocSynth}"
puts "tdImpl = ${run.tdImpl}"
puts "oocImpl = ${run.oocImpl}"
puts "topImpl = ${run.topImpl}"
puts "flatImpl = ${run.flatImpl}"
puts "write_bit = $write_bit"


####Report and DCP controls - values: 0-required min; 1-few extra; 2-all
set verbose      1
set dcpLevel     1

####Output Directories
set synthDir  "./Synth"
set implDir   "./Implement"
set dcpDir    "./Checkpoint"

####Input Directories
set srcDir     "./src"
set rtlDir     "$srcDir/hdl"
set prjDir     "$srcDir/prj"
set xdcDir     "$srcDir/xdc"
set coreDir    "$srcDir/cores"
set netlistDir "$srcDir/netlist"

####Source required Tcl Procs
source $tclDir/design_utils.tcl
source $tclDir/synth_utils.tcl
source $tclDir/impl_utils.tcl
source $tclDir/hd_floorplan_utils.tcl

###############################################################
### Top Definition
###############################################################
set top $project_name
add_module $top
set_attribute module $top    top_level     1
set_attribute module $top    prj           $prjDir/top.prj
set_attribute module $top    ip            [list $coreDir/clk_wiz/clk_wiz.xci]
set_attribute module $top	 synthXDC	   [list $xdcDir/rc_2000_synth.xdc]

set_attribute module $top    synth         ${run.topSynth}

add_implementation $top
set_attribute impl $top      top      		$top     
set_attribute impl $top      implXDC       [list 	$xdcDir/rc_2000_top.xdc]
set_attribute impl $top      impl          ${run.topImpl}
set_attribute impl $top      hd.impl       1

####################################################################
### OOC Module Definition and OOC Implementation for each instance
####################################################################
set module1 "base_ip"
add_module $module1
set_attribute module $module1 prj          		$prjDir/$module1.prj
set_attribute module $module1 ip            	[list 	$coreDir/fifo_1k_32/fifo_1k_32.xci	\
														$coreDir/cmd_fifo/cmd_fifo.xci		\
														$coreDir/s6_v7/s6_v7.xci		\
														$coreDir/v7_s6/v7_s6.xci		\
														$coreDir/fifo_from_user_ip/fifo_from_user_ip.xci		\
														$coreDir/fifo_to_user_ip/fifo_to_user_ip.xci		\
														$coreDir/pcie_7x_0/pcie_7x_0.xci		\
														$coreDir/rx_fifo/rx_fifo.xci		\
														$coreDir/tx_fifo/tx_fifo.xci		\
														$coreDir/ep_rx_fifo/ep_rx_fifo.xci		\
														$coreDir/ep_tx_fifo/ep_tx_fifo.xci		\
														$coreDir/axis_cc_buf/axis_cc_buf.xci		\
												]
set_attribute module $module1 synthXDC	   		[list $xdcDir/base_ip_synth.xdc]												
set_attribute module $module1 synth        		${run.oocSynth}

set instance "base"
add_ooc_implementation $instance
set_attribute ooc $instance   module       		$module1
set_attribute ooc $instance   inst         		$instance
set_attribute ooc $instance   hierInst     		$instance
set_attribute ooc $instance   implXDC      		[list $xdcDir/${instance}_phys.xdc         \
                                                 $xdcDir/${instance}_ooc_timing.xdc   \
                                                 $xdcDir/${instance}_ooc_budget.xdc   \
                                                 $xdcDir/${instance}_ooc_optimize.xdc \
												] 
set_attribute ooc $instance   impl         		 ${run.oocImpl}
set_attribute ooc $instance   preservation 		routing



####################################################################
### Create TopDown implementation run 
####################################################################
set module1File "$synthDir/$module1/${module1}_synth.dcp"

add_implementation TopDown
set_attribute impl TopDown      top          $top
set_attribute impl TopDown      implXDC      [list 	$xdcDir/rc_2000_top.xdc		\
													$xdcDir/rc_2000_top_flpn.xdc		\
											 ] 											
set_attribute impl TopDown      td.impl      1
set_attribute impl TopDown      cores        [list $module1File                          \
                                                   [get_attribute module $top cores]     \
                                                   [get_attribute module $module1 cores] \
                                             ] 
set_attribute impl TopDown      impl         ${run.tdImpl}
set_attribute impl TopDown      route        0

####################################################################
### Create Flat implementation run 
####################################################################
add_implementation Flat
set_attribute impl Flat         top          $top
set_attribute impl Flat         implXDC      [list $xdcDir/${top}_flpn.xdc] 
set_attribute impl Flat         cores        [list $module1File                          \
                                                   [get_attribute module $top cores]     \
                                                   [get_attribute module $module1 cores] \
                                             ] 
set_attribute impl Flat         impl         ${run.flatImpl}

########################################################################
### Task / flow portion
########################################################################


# Enable max multithreading
set_param general.maxThreads 8

# Build the designs
source $tclDir/run.tcl

if { ${write_bit} } {
	open_checkpoint ./Implement/${project_name}/${project_name}_route_design.dcp
	write_bitstream -force ${project_name}.bit
	
	puts ""
	puts ""
	puts ""
	puts ""
	puts "********************************************************************************************"
	puts ""
	puts "Finished implementing project $project_name started at [clock format $systemTime -format %H:%M:%S]"
	
	start_gui
}

