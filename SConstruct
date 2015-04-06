## INFO ########################################################################
##                                                                            ##
##                                    pypp                                    ##
##                                    ====                                    ##
##                                                                            ##
##              Advanced C PreProcessor with the Power of Python              ##
##                       Version: 0.1.0.210 (20150406)                        ##
##                              File: SConstruct                              ##
##                                                                            ##
##      For more information about the project, visit <http://pypp.io>.       ##
##                       Copyright (C) 2015 Peter Varo                        ##
##                                                                            ##
##  This program is free software: you can redistribute it and/or modify it   ##
##   under the terms of the GNU General Public License as published by the    ##
##       Free Software Foundation, either version 3 of the License, or        ##
##                    (at your option) any later version.                     ##
##                                                                            ##
##    This program is distributed in the hope that it will be useful, but     ##
##         WITHOUT ANY WARRANTY; without even the implied warranty of         ##
##            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.            ##
##            See the GNU General Public License for more details.            ##
##                                                                            ##
##     You should have received a copy of the GNU General Public License      ##
##     along with this program, most likely a file in the root directory,     ##
##        called 'LICENSE'. If not, see <http://www.gnu.org/licenses>.        ##
##                                                                            ##
######################################################################## INFO ##

# Indicate the beginning of building
print '{:#^80}'.format(' SCONS BUILD ')

# Import python modules
from os import path

# Config variables
gcc        = 'gcc'
clang      = 'clang'
input_dir  = '.'
output_dir = 'build'
target     = 'test'
source     = ['test-target.c']

# C Compiler
CC = clang

# C Compiler Flags
CCFLAGS = ['v',
           'g',
           'O3',
           'Wall',
           'Wextra',
           'pedantic',
           'std=c11',]

# GCC Specific Compiler Flags
GCCFLAGS = ['fdiagnostics-color=always']

# CLANG Specific Compiler Flags
CLANGFLAGS = ['fcolor-diagnostics',
              'fmacro-backtrace-limit=0']

# Add compiler specific flags
CCFLAGS.extend(GCCFLAGS if CC == gcc else CLANGFLAGS if CC == clang else [])

# C Pre-Processor Path (Include)
CPPPATH = ['.']

# Library paths
LIBPATH = ['/usr/lib',
           '/usr/local/lib']

# Libraries
LIBS = []

# Create environment
environment = Environment(CC=CC,
                          CCFLAGS=['-' + flag for flag in CCFLAGS],
                          CPPPATH=CPPPATH,
                          LIBPATH=LIBPATH,
                          LIBS=LIBS,)

# Specify output directory
environment.VariantDir(variant_dir=output_dir,
                       src_dir=input_dir)

# Create program
environment.Program(target=target,
                    source=[path.join(output_dir, file) for file in source])
