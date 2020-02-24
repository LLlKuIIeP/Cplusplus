#!bin/bash
doxygen -g Doxyfile
sed -f command_sed_doxygen Doxyfile > Doxyfile.new
doxygen Doxyfile.new
