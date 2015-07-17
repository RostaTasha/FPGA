
###############################################################################
# Timing Constraints
###############################################################################

#
# Timing requirements and related constraints.
#

create_clock -period 10.000 -name pcie_clk [get_pins base/refclk_ibuf/O]
create_clock -period 10.000 -name diff_clk [get_pins diffclk_ibuf/O]
create_clock -period 10.000 -name clk100 [get_ports clk100]


set_clock_groups -name asynch_clk_pcie_diff -asynchronous 		\
	-group [get_clocks -include_generated_clocks pcie_clk] 		\
	-group [get_clocks -include_generated_clocks diff_clk]

set_clock_groups -name asynch_clk_pcie_100 -asynchronous 		\
	-group [get_clocks -include_generated_clocks pcie_clk] 		\
	-group [get_clocks -include_generated_clocks clk100]
	
set_clock_groups -name asynch_clk_100_diff -asynchronous 		\
	-group [get_clocks -include_generated_clocks clk100] 		\
	-group [get_clocks -include_generated_clocks diff_clk]

	
	
set_false_path -to [get_pins base/pipe_clock_i/pclk_i1_bufgctrl.pclk_i1/S*]

create_clock -period 4.000 -name ip_clk [get_pins user/ip_clk_gen/CLK_OUT1]
create_clock -period 40.000 -name cbus_uclk [get_pins base/cntl/uclk_bufg/O]



###############################################################################
# pcie ref_clk
###############################################################################
set_property LOC IBUFDS_GTE2_X0Y15 [get_cells base/refclk_ibuf]

set_property LOC BUFGCTRL_X0Y68 [get_cells base/pipe_clock_i/txoutclk_i.txoutclk_i]
set_property LOC BUFGCTRL_X0Y66 [get_cells base/pipe_clock_i/pclk_i1_bufgctrl.pclk_i1]
set_property LOC BUFGCTRL_X0Y65 [get_cells base/pipe_clock_i/userclk1_i1.usrclk1_i1]
set_property LOC BUFGCTRL_X0Y67 [get_cells base/pipe_clock_i/dclk_i_bufg.dclk_i]

set_property LOC MMCME2_ADV_X0Y7 [get_cells base/pipe_clock_i/mmcm_i]



###############################################################################
# GTXE2
###############################################################################
set_property LOC GTXE2_COMMON_X0Y7 [get_cells base/pcie_7x_0_i/inst/inst/gt_top_i/pipe_wrapper_i/pipe_lane[0].pipe_quad.gt_common_enabled.gt_common_int.gt_common_i/qpll_wrapper_i/gtx_common.gtxe2_common_i]
set_property LOC GTXE2_CHANNEL_X0Y31 [get_cells base/pcie_7x_0_i/inst/inst/gt_top_i/pipe_wrapper_i/pipe_lane[0].gt_wrapper_i/gtx_channel.gtxe2_channel_i]
set_property LOC GTXE2_CHANNEL_X0Y30 [get_cells base/pcie_7x_0_i/inst/inst/gt_top_i/pipe_wrapper_i/pipe_lane[1].gt_wrapper_i/gtx_channel.gtxe2_channel_i]
set_property LOC GTXE2_CHANNEL_X0Y29 [get_cells base/pcie_7x_0_i/inst/inst/gt_top_i/pipe_wrapper_i/pipe_lane[2].gt_wrapper_i/gtx_channel.gtxe2_channel_i]
set_property LOC GTXE2_CHANNEL_X0Y28 [get_cells base/pcie_7x_0_i/inst/inst/gt_top_i/pipe_wrapper_i/pipe_lane[3].gt_wrapper_i/gtx_channel.gtxe2_channel_i]




###############################################################################
# diff ref_clk
###############################################################################
set_property LOC IBUFDS_GTE2_X0Y9 [get_cells diffclk_ibuf]

set_property LOC BUFGCTRL_X0Y32 [get_cells user/ip_clk_gen/inst/clkout1_buf]
set_property LOC MMCME2_ADV_X1Y4 [get_cells user/ip_clk_gen/inst/mmcm_adv_inst]



###############################################################################
# local clock 100 MHz
###############################################################################
set_property LOC BUFGCTRL_X0Y37 [get_cells base/cntl/cbusclk_bufg]
set_property LOC BUFGCTRL_X0Y71 [get_cells base/cntl/uclk_bufg]



###############################################################################
#
# SYS reset (input) signal.
#
set_property IOSTANDARD LVCMOS18 [get_ports sys_rst_n]
set_property PULLUP true [get_ports sys_rst_n]
set_property PACKAGE_PIN AL36 [get_ports sys_rst_n]
set_false_path -from [get_ports sys_rst_n]

###############################################################################
# Physical Constraints
###############################################################################
#
# SYS clock 100 MHz (input) signal.
#
set_property PACKAGE_PIN G9 [get_ports sys_clk_n]

set_property PACKAGE_PIN F4 [get_ports {pci_exp_txp[0]}]

set_property PACKAGE_PIN G2 [get_ports {pci_exp_txp[1]}]

set_property PACKAGE_PIN H4 [get_ports {pci_exp_txp[2]}]

set_property PACKAGE_PIN J2 [get_ports {pci_exp_txp[3]}]



# Diff Clock
set_property PACKAGE_PIN AB7 [get_ports aclk_n]

# Local Clock
set_property IOSTANDARD LVCMOS18 [get_ports clk100]
set_property PACKAGE_PIN AK34 [get_ports clk100]

# Command
set_property IOSTANDARD LVCMOS18 [get_ports strtcmd]
set_property PACKAGE_PIN AM34 [get_ports strtcmd]

# ID
set_property IOSTANDARD LVCMOS18 [get_ports {id[0]}]
set_property IOSTANDARD LVCMOS18 [get_ports {id[1]}]
set_property PACKAGE_PIN AH34 [get_ports {id[0]}]
set_property PACKAGE_PIN AJ35 [get_ports {id[1]}]

# Command
set_property IOSTANDARD LVCMOS18 [get_ports dval]
set_property PACKAGE_PIN AM31 [get_ports dval]
set_property PULLUP true [get_ports dval]
set_property SLEW FAST [get_ports dval]

set_property IOSTANDARD LVCMOS18 [get_ports {command[0]}]
set_property IOSTANDARD LVCMOS18 [get_ports {command[1]}]
set_property IOSTANDARD LVCMOS18 [get_ports {command[2]}]
set_property IOSTANDARD LVCMOS18 [get_ports {command[3]}]
set_property IOSTANDARD LVCMOS18 [get_ports {command[4]}]
set_property IOSTANDARD LVCMOS18 [get_ports {command[5]}]
set_property IOSTANDARD LVCMOS18 [get_ports {command[6]}]
set_property IOSTANDARD LVCMOS18 [get_ports {command[7]}]

set_property PACKAGE_PIN AM36 [get_ports {command[0]}]
set_property PACKAGE_PIN AN36 [get_ports {command[1]}]
set_property PACKAGE_PIN AJ36 [get_ports {command[2]}]
set_property PACKAGE_PIN AJ37 [get_ports {command[3]}]
set_property PACKAGE_PIN AK37 [get_ports {command[4]}]
set_property PACKAGE_PIN AL37 [get_ports {command[5]}]
set_property PACKAGE_PIN AN35 [get_ports {command[6]}]
set_property PACKAGE_PIN AP35 [get_ports {command[7]}]


###############################################################################
# Rosta Constraints
###############################################################################

set_property IO_BUFFER_TYPE none [get_ports sys_clk_p]
set_property IO_BUFFER_TYPE none [get_ports sys_clk_n]
set_property IO_BUFFER_TYPE none [get_ports pci_exp_txp[*]]
set_property IO_BUFFER_TYPE none [get_ports pci_exp_txn[*]]
set_property IO_BUFFER_TYPE none [get_ports pci_exp_rxp[*]]
set_property IO_BUFFER_TYPE none [get_ports pci_exp_rxn[*]]

set_property IO_BUFFER_TYPE none [get_ports id[*]]
set_property IO_BUFFER_TYPE none [get_ports strtcmd]
set_property IO_BUFFER_TYPE none [get_ports clk100]
set_property IO_BUFFER_TYPE none [get_ports dval]
set_property IO_BUFFER_TYPE none [get_ports command[*]]



###############################################################################
# User Physical Constraints
###############################################################################

# User FALSE PATH
set_false_path -from [get_pins {base/app/master/UserControlReg_c_reg[24]/C}]


# Set FALSE PATH clocks
set_false_path -from [get_clocks clk100] -to [get_clocks ip_clk]

set_false_path -from [get_pins base/app/master/ep_tx_error_reg/C]

###############################################################################
# End
###############################################################################

set_property BITSTREAM.GENERAL.COMPRESS true [current_design]


