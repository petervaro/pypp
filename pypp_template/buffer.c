/* INFO ************************************************************************
**                                                                            **
**                                    pypp                                    **
**                                    ====                                    **
**                                                                            **
**              Advanced C PreProcessor with the Power of Python              **
**                       Version: 0.1.0.210 (20150406)                        **
**                        File: pypp_template/buffer.c                        **
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

/* For safety reasons: warn the user, that this file has to be preprocessed */
#error PYPP

/* pypp ########################################################################

class MyType(pypp.Template):

    base_type = 'MyType'

    def __init__(self, memtype, subtype, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self.c_type, self.str_type = subtype
        self.type_name = '{.base_type}_{.str_type}'.format(self)

############################################################################# */


// pypp MyType.generic.append("""
#include <stddef.h> /*
    type  : size_t
*/
// pypp """, header=True)


// pypp MyType.base.append('', typedef="""
typedef struct
{
    size_t     size;
    size_t     index;
    {.c_type} *data;

} {.type_name}_{.str_type};
// pypp """)


// pypp MyType.generic.append("""
static variable;
// pypp """)


// pypp MyType.methods.append('new', declaration="""
static bool
{.type_name}_{.str_type}_new()
// pypp """, definition="""
{

}
// pypp """)


// pypp MyType.methods.append('del', declaration="""
static void
{.type_name}_{.str_type}_del()
// pypp """, definition="""
{

}
// pypp """)


// pypp MyType.methods.append('push', declaration="""
static bool
{.type_name}_{.str_type}_push()
// pypp """, definition="""
{

}
// pypp """)


// pypp MyType.methods.append('repr', declaration="""
static void
{.type_name}_{.str_type}_repr()
// pypp """, definition="""
{

}
// pypp """)

// pypp pypp.templates['MyType'] = MyType