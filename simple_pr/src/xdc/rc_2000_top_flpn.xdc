

create_pblock pblock_base
add_cells_to_pblock [get_pblocks pblock_base] [get_cells -quiet [list base]]
resize_pblock [get_pblocks pblock_base] -add {SLICE_X490Y300:SLICE_X517Y399}
resize_pblock [get_pblocks pblock_base] -add {DSP48_X8Y120:DSP48_X8Y159}
resize_pblock [get_pblocks pblock_base] -add {RAMB18_X9Y120:RAMB18_X10Y159}
resize_pblock [get_pblocks pblock_base] -add {RAMB36_X9Y60:RAMB36_X10Y79}
set_property CONTAIN_ROUTING true [get_pblocks pblock_base]
set_property HD.PARTPIN_RANGE {SLICE_X490Y300:SLICE_X491Y399} [get_pins base/*] 

