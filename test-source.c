/* INFO ************************************************************************
**                                                                            **
**                                    pypp                                    **
**                                    ====                                    **
**                                                                            **
**              Advanced C PreProcessor with the Power of Python              **
**                       Version: 0.1.0.210 (20150406)                        **
**                            File: test-source.c                             **
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

// pypp # Warn the user: this file has to be preprocessed
#error PYPP

#include <stdlib.h> /*
    const : EXIT_SUCCESS
            EXIT_FAILURE
*/

/* pypp ########################################################################

def some_func(value1, value2):
    print(value1, 'and', value2)

############################################################################# */


/*----------------------------------------------------------------------------*/
static void
test_func1(void)
{

/* pypp
T = 'MyBuffer_int'
pypp.include(""" */

    TYPE buffer;

    NEW(&buffer, 10);

    PUSH(&buffer, 12);
    PUSH(&buffer, 59);
    PUSH(&buffer, 66);
    PUSH(&buffer, 37);

    DEL(&buffer);

/* pypp
""".replace('TYPE', T          )
   .replace('NEW' , T + '_new' )
   .replace('PUSH', T + '_push')
   .replace('DEL' , T + '_del' )) */
}

// pypp some_func(value2="""
static const char *value2 = "this has to be second";
// pypp """, value1="""
static const char *value1 = "this has to be first";
// pypp """)

/* pypp print(' */ static int = 12; /* pypp ') */


/*----------------------------------------------------------------------------*/
/* pypp
variables = []
for i in range(10):
    variables.append(""" */
static int variable{INDEX};
/* pypp
""".format(INDEX=i))
pypp.include(*variables) */


/*----------------------------------------------------------------------------*/
static void
test_func2(void)
{

// pypp pypp.include("""

    Type buffer;

    buffer.init(10);

    buffer.push(12);
    buffer.push(59);
    buffer.push(66);
    buffer.push(37);

    buffer.del();

/* pypp
""".replace('Type'        , 'MyBuffer_int'                    )
   .replace('buffer.init(', 'MyBuffer_int_new'  + '(&buffer, ')
   .replace('buffer.push(', 'MyBuffer_int_push' + '(&buffer, ')
   .replace('buffer.del(' , 'MyBuffer_int_del'  + '(&buffer'  )) */
}
