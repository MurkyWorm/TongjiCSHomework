######################################################################
#
# File name : DIV_tb_simulate.do
# Created on: Sun Apr 02 16:34:23 +0800 2023
#
# Auto generated by Vivado for 'behavioral' simulation
#
######################################################################
vsim -voptargs="+acc" -L unisims_ver -L unimacro_ver -L secureip -L xil_defaultlib -lib xil_defaultlib xil_defaultlib.DIV_tb xil_defaultlib.glbl

do {DIV_tb_wave.do}

view wave
view structure
view signals

do {DIV_tb.udo}

run 1000ns
