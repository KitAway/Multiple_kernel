open_project -reset prj_RNG_
set_top generationRN

add_files -tb  main_RNG.cpp
add_files RNG.cpp

open_solution -reset original

set_part xc7vx690tffg1157-2
create_clock -period 4.81ns -name default

csynth_design
exit


