# don't use base block name here because we already apply these constraints to base

set_false_path -to [get_pins pipe_clock_i/pclk_i1_bufgctrl.pclk_i1/S*]
set_false_path -from [get_pins {app/master/UserControlReg_c_reg[24]/C}]
set_false_path -from [get_pins user_reset_q_reg/C]


create_clock -period 4.000 -name ip_clk.ip_clk [get_ports {ip_clk}] -waveform {0.000 4.000}
create_clock -period 10.000 -name pcie_clk [get_pins refclk_ibuf/O]
create_clock -period 10.000 -name clk100 [get_ports cbus_clk]


set_clock_groups -name asynch_clk_pcie_ip -asynchronous 		\
	-group [get_clocks -include_generated_clocks pcie_clk] 		\
	-group [get_clocks -include_generated_clocks {ip_clk.ip_clk}]

set_clock_groups -name asynch_clk_pcie_100 -asynchronous 		\
	-group [get_clocks -include_generated_clocks pcie_clk] 		\
	-group [get_clocks -include_generated_clocks clk100]
	
set_clock_groups -name asynch_clk_100_ip -asynchronous 		\
	-group [get_clocks -include_generated_clocks clk100] 		\
	-group [get_clocks -include_generated_clocks {ip_clk.ip_clk}]


