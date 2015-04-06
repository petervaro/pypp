## INFO ########################################################################
##                                                                            ##
##                                    pypp                                    ##
##                                    ====                                    ##
##                                                                            ##
##              Advanced C PreProcessor with the Power of Python              ##
##                       Version: 0.1.0.210 (20150406)                        ##
##                               File: pypp.py                                ##
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

# Import python modules
from sys import stderr
from io import SEEK_SET
from re import compile, match, sub, finditer, MULTILINE, DOTALL, VERBOSE

# Import user modules
import public_pypp


# Module level constants
#------------------------------------------------------------------------------#
PROMPT = '(pypp)'
EOL_EOF  = compile(r'^EO(L|F)')
ERROR    = compile(r'^\s*#\s*error\s+PYPP\s*$', flags=MULTILINE)
COMMENTS = compile(r"""
    (
        # Single line comments:
        //\s*pypp\s*(?P<line>.+?)$
        |
        # Multi line comments:
        /\*\s*pypp\s*(?P<block>.+?)\*/
    )
""", flags=MULTILINE | DOTALL | VERBOSE)



#------------------------------------------------------------------------------#
def on_error(target, exception, code_buffer):
    # Inform the user about the problem
    print('{} The following exception occured '
          'in these lines:'.format(PROMPT),
          code_buffer,
          sep='\n\n',
          end='\n\n',
          file=stderr)
    # Make sure the generated file cannot be used as a C file
    target.seek(SEEK_SET)
    target.write('#error "Invalid `pypp` output, '
                 'see console for furhter info"')
    target.truncate()
    # And re-raise the caught exception
    # TODO: set proper line and column numbers as well, as file name
    raise exception



#------------------------------------------------------------------------------#
def generate_output(source, target):
    # Read file, and remove pypp-safety-errors
    source = sub(ERROR, '', source.read())

    # Reading states
    environment_globals = {'pypp': public_pypp}
    environment_locals  = {}
    inside_expression   = False
    exec_buffer         = ''
    prev_buffer         = ''
    curr_index          = 0

    # Process the whole text
    for catch in finditer(COMMENTS, source):
        # Get indicies
        start_index, end_index = catch.span()
        # Get the next python snippet
        curr_buffer = catch.group('line') or catch.group('block')

        # If the last evaluation was failed, because EOF
        if inside_expression:
            # Step at the index
            prev_buffer += source[curr_index:start_index]
            # Update index
            curr_index = end_index
            # Try to exit from the expression
            inside_expression = False

        # Try to run the interpreter
        try:
            # Execute code in the buffers
            exec_buffer = prev_buffer + curr_buffer
            exec(exec_buffer, environment_globals, environment_locals)
            # Empty previous-code-buffer
            prev_buffer = ''
        # If code-buffer contained invalid code
        except SyntaxError as exception:
            # If error is not end-of-file or end-of-line
            if not match(EOL_EOF, str(exception)):
                # Propagate error to user and clean up
                on_error(target, exception, exec_buffer)
            # If error was about unended expression
            prev_buffer += curr_buffer
            inside_expression = True
        # If `pypp.include` function was called
        except public_pypp.IncludeSnippet as include:
            # Write all values stored in the exception
            for string in include.strings:
                target.write(string)
            # Clear buffer
            prev_buffer = ''
        # If some other exception happened
        except Exception as exception:
            # Propagate error to user and clean up
            on_error(target, exception, exec_buffer)

        # Write
        target.write(source[curr_index:start_index])
        curr_index = end_index

    # Write what's left from the source to the target
    target.write(source[curr_index:])



#------------------------------------------------------------------------------#
def main():
    # Open output file
    with open('test-target.c', 'w', encoding="utf-8") as target:
        # Open input file:
        with open('test-source.c', encoding="utf-8") as source:
            # If source supports random access
            if source.seekable():
                generate_output(source, target)
            # If not, create a seekable-proxy
            else:
                generate_output(FileObjectProxy(source.read()), target)



#------------------------------------------------------------------------------#
if __name__ == '__main__':
    main()
