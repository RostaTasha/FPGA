	Based on 
		rc_pcie_base_2000_6 and
		Xilinx Vivado Hierarchical Design Tutorial UG946 (v2014.1)
	
	Master Block Version = 8

	
	
	Assemble instructions:
		1. Files needed for project:
			./Checkpoint/rosta_route_design.dcp 
				- rosta_pcie implemented with fixed place and route results 
			./Sources/cores/ - cores from IP Catalog. Only xci files are needed - other files may be deleted
			./Sources/hdl/ - vhdl and verilog files - place user files under ./Sources/hdl/user
			./Sources/prj/ - prj files need for synthesis. 
				After placing user files into ./Sources/hdl/user modify ./Sources/prj/top.prj file
			./Sources/xdc/ - constraints files. Normally user should not modify these files. 
			
			./Tcl - folder containing tcl scripts
		
		2.  If rosta_pcie is already implemented (rosta_route_design.dcp is saved in ./Checkpoint) then user should do the following:
		
			- place hdl files under ./Sources/hdl/user
			- modify ./Sources/prj/top.prj file
			- modify design.tcl
				set run.topSynth   1
				set run.oocSynth   0
				set run.tdImpl     0
				set run.oocImpl    0
				set run.topImpl    1
				set run.flatImpl   0
				
			- run 
				vivado -mode batch -source design.tcl -notrace
			
			- after implementation is completed open last DCP
				vivado ./Implement/rc_pcie_base_2000_9/rc_pcie_base_2000_9_route_design.dcp
				
			- generate bitstream
				write_bitstream rc_pcie_base_2000_9.bit
				
		3.  If no rosta_pcie implementation results are available 			
				AND There is NO need to modify rosta_pcie PBLOCK constraints

			- place hdl files under ./Sources/hdl/user
			- modify ./Sources/prj/top.prj file
			- modify design.tcl
				set run.topSynth   1
				set run.oocSynth   1
				set run.tdImpl     0		ZERO here
				set run.oocImpl    1
				set run.topImpl    1
				set run.flatImpl   0		
				
			- run 
				vivado -mode batch -source design.tcl -notrace
			
			- after implementation is completed open last DCP
				vivado ./Implement/rc_pcie_base_2000_9/rc_pcie_base_2000_9_route_design.dcp
				
			- generate bitstream
				write_bitstream rc_pcie_base_2000_9.bit


		3.  If no rosta_pcie implementation results are available 			
				AND you have to modify rosta_pcie PBLOCK constraints

			- get new constraints from project mode flat implementaion
			- modify ./Sources/xdc/rc_2000_top_flpn.xdc
			- place hdl files under ./Sources/hdl/user
			- modify ./Sources/prj/top.prj file
			- modify design.tcl
				set run.topSynth   1
				set run.oocSynth   1
				set run.tdImpl     1
				set run.oocImpl    1
				set run.topImpl    1
				set run.flatImpl   0		
				
			- run 
				vivado -mode batch -source design.tcl -notrace
			
			- after implementation is completed open last DCP
				vivado ./Implement/rc_pcie_base_2000_9/rc_pcie_base_2000_9_route_design.dcp
				
			- generate bitstream
				write_bitstream rc_pcie_base_2000_9.bit				