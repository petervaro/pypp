http://www.pypp.io

`pypp`: Python PreProcessor
===========================

`pypp` (pronounced as *pipe*) is an advanced C preprocessor, which is trying to
be as simple and minimalistic as it possibly can, without sacrificing usability
and functionality.

The goal was not to invent and implement yet another preprocessor, with its own
syntax and quirks, but to use the full power of an existing dynamic language
such as python, which is well maintained and tested and makes it very easy to
read and write code in it.

Of course, this also means that sometimes one has to write a bit more code than
one would do with the standard CPP, because let's face it, one is writing a
normal python script hidden between the lines of the C code.

However this makes it possible to have no limits of what one can do with the
source code. (Define new syntax, generate source based on templates, analyse
code, even make decisions based on a JSON response of a server, etc.)

So `pypp` is pretty small, includes only a handul of predefined functions and
classes which one can use and extend based on one's needs.

Dependencies
============

- Python 3 (3.4+ preferred)
- A proper C compiler (at least C99 support)
- A nice build-manager (Make/CMake/SCons/Waf/Tup/etc.)
- Being an advanced "user" of both languages



Overview
========

First steps
-----------

The power of `pypp` comes from the fact, that it is using regular C comments to
"hide" the python snippets between the lines, so that one can write valid C code
without any extra/unnecessary overwhelmed syntax.

However this "clean" solution also means that people, who may not know a
project's folder/file structure well enough, may want to compile these "special"
files before they were preprocessed by `pypp`.

Well, one cannot be cautious enough, therefore `pypp` introduced a special and
short expression, which should be included at the beginning of each file which
needs to be preprocessed by `pypp`:

    #error PYPP

What is so special about this? Isn't this the regular and standard way, to
inform the CPP that it should throw an error during translation? Well, this
expression will be recognised and removed by `pypp` during the preprocessing.

To make it more meaningful, one can add a python comment inside a `pypp` comment
to inform the user why this error is there -- which will be evaluated and then
removed from the processed source as well:

    // pypp # This file needs to be preprocessed by `pypp`
    #error PYPP



Syntax
------

Since C99 the C language has two types of comments: the single-liner, and the
block comment. `pypp` can use both of course. To make it easier to distinguish
between the regular C comments and the special `pypp` ones, one has to add the
short `pypp` tag after the starting comment symbols, like so:

    // A regular C comment, which will be included in the preprocessed source

    // pypp print('This comment is a `pypp` comment, which will be evaluated')

    /* This one here is a regular
       C block comment, which will be
       included into the preprocessed source */

    /* pypp # On the other hand, this comment will be evaluated by `pypp` as well
       from math import pi

       print('The value of PI is:', pi) */

Unlike C, Python is an identation based language, therefore it is highly
recommended, to start the `pypp` tagged comments in the first column of each
line, which will represent the "global" scope.

One can write the first line after the tag, followed by at least one whitespace
character, because `pypp` will remove the whitespaces between the tag and the
first non-whitespace character, which also means, that the first line will be
treated as the "global" scope indentation if there is anything between the tag
and the newline character.



Evaluation units
----------------

Each file, and inside a file each comment processed separately. What does this
mean? Well, first of all, it means, that all values reset before processing
each file, so it is not possible to effect one file from another, and
accidentaly overwrite a value which is expected to be different in the other
file. However there is one exception from that which is the `pypp.user_value`.
(For more information about that, scroll down a bit.)

The aim of the separation of the comments is to protect the C code blocks
between the `pypp` tagged comments. One can think of a comment as a function,
which encapsulates and structures code. These comment-blocks are called
*evaluation units*.

The one-liner comment is a single-statement evaluation unit, while the block
comment is a multi-statement evaluation unit. However, there is one clever
exception to merge one or more evaluation units into a single code block, and
execute it as one, and that is using EOL or EOF (end-of-line or end-of-file).

The following example, will demonstrate, how to pass a small piece of code as
a string argument to a function which will process it, and then prints the
result of it:

    /* pypp
    from re import sub

    def mixed_camel_to_under(string):
        print(sub(r'([A-Z]+)', r'_\1', string).lower())

    mixed_camel_to_under(""" */

    static const char *longAndComplexVariableName;

    // pypp """)

And this will print the following to the console:

    static const char *long_and_complex_variable_name;

This technique can be used to merge even more than one evaluation units, so
one can pass as many positional or keyword based arguments as one likes, or
simply just process and concatenate them.



The `pypp.include` function
---------------------------

So far, we could only evaluate snippets inside the `pypp` tagged commets without
any effects on the output file (other than the side-effect that all evaluated
comments were removed).

`pypp` has an `include` function, which will write to the output file. One can
think of it, as the `return` keyword of a function: once it has been called,
nothing else in the comment will be evaluated further:

    // pypp print('First this line will evaluate')

    /* pypp
       print('Then this one here')

       # Let's insert a macro definition here:
       pypp.include('#define EMPTY_MACRO\n')

       print('This line will never evaluate') */

    // pypp print('This is the last line which will be evaluated')

The function can also take as many arguments as one likes. In the following
example `pypp` will generate 10 indexed variable:

    /* pypp
    variables = []
    for i in range(10):
        variables.append(""" */
    static int variable{INDEX};
    /* pypp
    """.format(INDEX=i))
    pypp.include(*variables) */



The `pypp.user_value` object
----------------------------



The `pypp.Template` class
-------------------------

    => pypp_templates folder



The `pypp.ast` module
---------------------

*WORK IN PROGRESS...*

The next major release of `pypp` will support hygienic preprocessing because it
will work on the level of the abstract syntax tree. This will make it more safe
to use and capable of more advanced operations.



The `pypp` CLI
--------------

    $ pypp -h

    -h
    --help
        Prints this text

    -v
    --version
        Prints the version number

    -d <folder>
    --dir <folder>
        Add directory which contains files needs to be preprocessed

    -f <file>
    --file <file>
        Add file which needs to be preprocessed

    -T <folder>
    --tempdir <folder>
        Add template directory

    -t <file>
    --tempfile <file>
        Add template file

    -o <folder>
    --output <folder>
        Output directory

Example:

    $ pypp -o src -t ~/temps/buff.c -T temps -f main.c -f m/calc.c -d api



LICENSE
=======

Copyright (C) 2015 Peter Varo

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program, most likely a file in the root directory, called 'LICENSE'.
If not, see <http://www.gnu.org/licenses>.
