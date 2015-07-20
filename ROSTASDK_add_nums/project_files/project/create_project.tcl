

set part "xc7v2000tfhg1761-1"
set project_name "rc_pcie_base_2000_11"
set top_entity	$project_name

set orgDir ".."
set srcDir	"$orgDir/src"

if {[file exists $srcDir]} {
   set srcDir [file normalize $srcDir]
   puts "Source Dir:\t $srcDir"
} else {
   error "ERROR: No valid location found for required Src Dir"
}


# create source files list
set src_files [list \
 "$srcDir/cores/fifo_to_user_ip/fifo_to_user_ip.xci"\
 "$srcDir/cores/fifo_from_user_ip/fifo_from_user_ip.xci"\
 "$srcDir/hdl/base/rr_arbiter.vhd"\
 "$srcDir/hdl/base/reg_synch.vhd"\
 "$srcDir/cores/tx_fifo/tx_fifo.xci"\
 "$srcDir/cores/rx_fifo/rx_fifo.xci"\
 "$srcDir/cores/ep_tx_fifo/ep_tx_fifo.xci"\
 "$srcDir/cores/ep_rx_fifo/ep_rx_fifo.xci"\
 "$srcDir/cores/fifo_1k_32/fifo_1k_32.xci"\
 "$srcDir/cores/cmd_fifo/cmd_fifo.xci"\
 "$srcDir/cores/axis_cc_buf/axis_cc_buf.xci"\
 "$srcDir/hdl/base/pcie_64b_master_ea.vhd"\
 "$srcDir/hdl/base/pcie_app_7x.vhd"\
 "$srcDir/hdl/base/pcie_7x_0_pipe_clock.v"\
 "$srcDir/cores/pcie_7x_0/pcie_7x_0.xci"\
 "$srcDir/cores/clk_wiz/clk_wiz.xci"\
 "$srcDir/cores/s6_v7/s6_v7.xci"\
 "$srcDir/cores/v7_s6/v7_s6.xci"\
 "$srcDir/hdl/user/user_ip.vhd"\
 "$srcDir/hdl/base/base_ip.vhd"\
 "$srcDir/hdl/base/cbus.vhd"\
 "$srcDir/hdl/rc_2000_top.vhd"\
]

# create xdc files list
set xdc_files [list \
	"$srcDir/xdc/rc_2000_top.xdc"\
]



# Create project
create_project -force $project_name 

# Set the directory path for the new project
set proj_dir [get_property directory [current_project]]

# Set project properties
set obj [get_projects $project_name]
set_property "default_lib" "xil_defaultlib" $obj
set_property "part" $part $obj
set_property "simulator_language" "Mixed" $obj

# Create 'sources_1' fileset (if not found)
if {[string equal [get_filesets -quiet sources_1] ""]} {
  create_fileset -srcset sources_1
}

# Set 'sources_1' fileset object
set file_set [get_filesets sources_1]
add_files -norecurse -fileset $file_set $src_files


foreach file $src_files {
	puts -nonewline "$file"
	if [regexp {.*\.vhd$} $file tmp ] {
	
		puts "\t\t is VHD file"
		set file_obj [get_files -of_objects $file_set [list "*$file"]]
		set_property "file_type" "VHDL" $file_obj
	
	} elseif [regexp {.*\.v$} $file tmp ] {
		puts "\t\t is Verilog file"
	} elseif [regexp {.*\.xci$} $file tmp ] {
	
		puts "\t\t is XCI file"
		set file_obj [get_files -of_objects $file_set [list "*$file"]]
		set_property "generate_synth_checkpoint" "0" $file_obj
	
	}
}
set_property "top" $top_entity $file_set


# Create 'constrs_1' fileset (if not found)
if {[string equal [get_filesets -quiet constrs_1] ""]} {
  create_fileset -constrset constrs_1
}


# Set 'constrs_1' fileset object
set file_set [get_filesets constrs_1]
add_files -norecurse -fileset $file_set $xdc_files

foreach file $xdc_files {
	puts "$file"
	set file_obj [get_files -of_objects $file_set [list "*$file"]]
	set_property "file_type" "XDC" $file_obj	
}


# Create 'synth_1' run (if not found)
if {[string equal [get_runs -quiet synth_1] ""]} {
  create_run -name synth_1 -part $part -flow {Vivado Synthesis 2014} -strategy "Vivado Synthesis Defaults" -constrset constrs_1
} else {
  set_property strategy "Vivado Synthesis Defaults" [get_runs synth_1]
  set_property flow "Vivado Synthesis 2014" [get_runs synth_1]
}

# keep hierachy
set_property STEPS.SYNTH_DESIGN.ARGS.FLATTEN_HIERARCHY none [get_runs synth_1]
set obj [get_runs synth_1]
set_property "part" $part $obj

# set the current synth run
current_run -synthesis [get_runs synth_1]

# Create 'impl_1' run (if not found)
if {[string equal [get_runs -quiet impl_1] ""]} {
  create_run -name impl_1 -part $part -flow {Vivado Implementation 2014} -strategy "Vivado Implementation Defaults" -constrset constrs_1 -parent_run synth_1
} else {
  set_property strategy "Vivado Implementation Defaults" [get_runs impl_1]
  set_property flow "Vivado Implementation 2014" [get_runs impl_1]
}
set obj [get_runs impl_1]
set_property "part" $part $obj

# set the current impl run
current_run -implementation [get_runs impl_1]

puts "INFO: Project created: $project_name"
