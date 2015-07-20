#---------------------------------------
# Create Clock Constraints - base 
#---------------------------------------
create_clock -period 10.000 -name clk100.cbus_clk [get_ports {cbus_clk}] -waveform {0.000 5.000}
create_clock -period 4.000 -name ip_clk.ip_clk [get_ports {ip_clk}] -waveform {0.000 2.000}
set_property HD.CLK_SRC BUFGCTRL_X0Y32 [get_ports {ip_clk}]
set_system_jitter 0.0
set_clock_latency -source -max 3.451 [get_clocks {clk100.cbus_clk}]
set_clock_latency -source -min 3.113 [get_clocks {clk100.cbus_clk}]
set_clock_uncertainty 0.035 [get_clocks {clk100.cbus_clk}]
set_clock_latency -source -max 0.33799999999999997 [get_clocks {ip_clk.ip_clk}]
set_clock_latency -source -min 0.0 [get_clocks {ip_clk.ip_clk}]
set_clock_uncertainty 0.035 [get_clocks {ip_clk.ip_clk}]
set_clock_groups -asynchronous -group [get_clocks {clk100.cbus_clk}] -group [get_clocks {ip_clk.ip_clk}]
