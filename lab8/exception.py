import sys

class InputException(Exception):
    pass 

def input_num(number):
    if number < 0 or number > 10:
        raise InputException("Input not between 1 and 10")

    # do some stuff if number is between 0 and 10 
    print("Your number, {}, is between 0 and 10".format(number))

try:
    input_num(25)
    raise TypeError()
    print("No problems here!")
except InputException as e:
    print("This exception only runs if the error is type InputException: ", e, file=sys.stderr)
    sys.exit(-1)
except:
    print("This catches all other errors.", file=sys.stderr)
    sys.exit(-1) 
finally:
    print("After everything in the try or exceptions has run, then this runs.")
    
print("I'm the rest of the program.")
