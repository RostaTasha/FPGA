# Note: run "source sourceme" before make

# Note: add further C++ source-files here (after t_calculator.cpp)
a.out: t_calculator.cpp obj_dir/Vcalculator.h
	g++ -std=c++0x -g -Iobj_dir -I$(VERILATOR_ROOT)/include t_calculator.cpp obj_dir/Vcalculator__ALL.a $(VERILATOR_ROOT)/include/verilated.cpp $(VERILATOR_ROOT)/include/verilated_vcd_c.cpp

# Note: add further verilog source-files here (after calculator.sv)
obj_dir/Vcalculator.h: calculator.sv add.sv sub.sv mul.sv arbiter.sv arbiter_engine.sv
	$(VERILATOR_ROOT)/verilator_bin -Wall --cc calculator.sv add.sv sub.sv mul.sv arbiter.sv arbiter_engine.sv --trace --x-assign 0
	cd obj_dir && make -f Vcalculator.mk

clean:
	rm -rf obj_dir a.out simx.vcd
