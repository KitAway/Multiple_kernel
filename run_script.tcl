

open_project -reset prj_hestonEuro
set_top hestonEuro

add_files barrierData.cpp
add_files hestonEuro.cpp
add_files -tb  main_tb.cpp
add_files RNG.cpp
add_files stockData.cpp
add_files volatilityData.cpp

open_solution -reset original

set_part xc7vx690tffg1157-2
create_clock -period 4.81ns -name default

csynth_design
export_design -format ip_catalog
exit

