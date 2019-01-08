# Errors Handled in uvroff_class.py #

1. Check for bad input files and outputs error message.
2. Check for invalid formatting commands that are not a number -displays the invalid number and specifies error.
3. Check .LM command if it has negative value and changes to 0 if it is -displays error.
4. Check .LS command, if it is greater than 2 set it to 2, if it is less than 0 set it to 0.

Files to test:

1. e_in01.txt
	- tests valid file input
	- does not do any formatting because it does not contain .txt extension
	- Gives an AttributeError
	- Giving a filename that does not exist will give IOError
2. e_in02.txt
	- tests values that are not numbers
	- will not do any formatting if values invalid, output the text as is
	- Gives a ValueError
3. e_in03.txt
	- tests .LM, .LS to be negative and .LS to be greater than 2
	- Does formatting with .LM, .LS to 0 if negative and .LS 2 if higher than 2
	- Output to stderr
4. e_in04.txt
	- tests non-valid value after .FT command
	- will retain original value and format properly
	- no error because .FT is neither "on" or "off"
