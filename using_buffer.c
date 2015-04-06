/* INFO ************************************************************************
**                                                                            **
**                                    pypp                                    **
**                                    ====                                    **
**                                                                            **
**              Advanced C PreProcessor with the Power of Python              **
**                       Version: 0.1.0.210 (20150406)                        **
**                            File: using_buffer.c                            **
**                                                                            **
**      For more information about the project, visit <http://pypp.io>.       **
**                       Copyright (C) 2015 Peter Varo                        **
**                                                                            **
**  This program is free software: you can redistribute it and/or modify it   **
**   under the terms of the GNU General Public License as published by the    **
**       Free Software Foundation, either version 3 of the License, or        **
**                    (at your option) any later version.                     **
**                                                                            **
**    This program is distributed in the hope that it will be useful, but     **
**         WITHOUT ANY WARRANTY; without even the implied warranty of         **
**            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.            **
**            See the GNU General Public License for more details.            **
**                                                                            **
**     You should have received a copy of the GNU General Public License      **
**     along with this program, most likely a file in the root directory,     **
**        called 'LICENSE'. If not, see <http://www.gnu.org/licenses>.        **
**                                                                            **
************************************************************************ INFO */

/* pypp

MyType = pypp.template['MyType']
my_type_ull = MyType(subtype=('unsigned long long', 'ull'))

pypp.generate_file(my_type_ull.header)
pypp.generate_file(my_type_ull.source)

pypp.include(my_type_ull.header.file_name) */


