## INFO ########################################################################
##                                                                            ##
##                                    pypp                                    ##
##                                    ====                                    ##
##                                                                            ##
##              Advanced C PreProcessor with the Power of Python              ##
##                       Version: 0.1.0.210 (20150406)                        ##
##                            File: public_pypp.py                            ##
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

#------------------------------------------------------------------------------#
class IncludeSnippet(Exception):

    def __init__(self, strings, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.strings = strings


#------------------------------------------------------------------------------#
class User:

    @property
    def value(self):
        try:
            return self._value
        except AttributeError:
            raise AttributeError("'value' has not been set for the User-object")
    @value.setter
    def value(self, data):
        self._value = data


#------------------------------------------------------------------------------#
def include(*strings, header=False):
    raise IncludeSnippet(strings)



# class Element:

#     @classmethod
#     def append(cls, value):
#         try:
#             cls.elements.append(value)
#         except AttributeError:
#             cls.elements = [value]


# class Template:

#     generic = Element
#     base    = Element
#     methods = Element

#     def __init__(self):
#         pass



# class This(Template):
#     pass



# class That(Template):
#     pass



# This.base.append(12)

# this = This()
# that = That()

# print(this.base)