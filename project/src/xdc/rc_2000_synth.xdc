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



create_clock -period 10.000 -name diff_clk [get_pins diffclk_ibuf/O]
create_clock -period 4.000 -name ip_clk [get_pins user/ip_clk_gen/CLK_OUT1]


