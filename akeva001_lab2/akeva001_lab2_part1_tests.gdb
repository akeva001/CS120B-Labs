# Test file for Lab2_introToAVR


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
test "PINA: 0x00, PINB: 0x00 => PORTC: 0"
# Set inputs
setPINA 0x00
setPINB 0x00
# Continue for several ticks
continue 2
# Set expect values
expectPORTC 0
# Check pass/fail
checkResult

# Add tests below

# ------------------------------- Incorrect Cases
test "PINA: 0x42 => PORTB: 0x00"
setPINA 0x42
continue 5
expectPORTB 0x00
checkResult

test "PINA: 0x12 => PORTB: 0x00"
setPINA 0x12
continue 5
expectPORTB 0x00
checkResult

test "PINA: 0x15 => PORTB: 0x00"
setPINA 0x15
continue 5
expectPORTB 0x00
checkResult

test "PINA: 0xA9 => PORTB: 0x00"
setPINA 0xA9
continue 5
expectPORTB 0x00
checkResult

test "PINA: 0x9F => PORTB: 0x00"
setPINA 0x9F
continue 5
expectPORTB 0x00
checkResult

test "PINA: 0xFF => PORTB: 0x00"
setPINA 0xFF
continue 5
expectPORTB 0x00
checkResult

test "PINA: 0xDA => PORTB: 0x00"
setPINA 0xDA
continue 5
expectPORTB 0x00
checkResult

test "PINA: 0x43 => PORTB: 0x00"
setPINA 0x43
continue 5
expectPORTB 0x00
checkResult

test "PINA: 0x9F => PORTB: 0x00 => PINA: 0x32 => PORTB: 0x00"
setPINA 0x9F
continue 5
expectPORTB 0x00
continue 5
setPINA 0x32
continue 5
expectPORTB 0x00
checkResult



# ------------------------------- Correct Cases
test "PINA: 0x03 => PORTB: 0x01"
setPINA 0x03
continue 5
expectPORTB 0x01
checkResult

test "PINA: 0x03 => PORTB: 0x01"
setPINA 0x03
continue 5
expectPORTB 0x01
checkResult

test "PINA: 0x13 => PORTB: 0x00"
setPINA 0x13
continue 5
expectPORTB 0x01
checkResult

test "PINA: 0x23 => PORTB: 0x00"
setPINA 0x23
continue 5
expectPORTB 0x01
checkResult

test "PINA: 0x33 => PORTB: 0x00"
setPINA 0x33
continue 5
expectPORTB 0x01
checkResult

test "PINA: 0x43 => PORTB: 0x00"
setPINA 0x43
continue 5
expectPORTB 0x01
checkResult

test "PINA: 0x53 => PORTB: 0x00"
setPINA 0x53
continue 5
expectPORTB 0x01
checkResult

test "PINA: 0xD3 => PORTB: 0x00"
setPINA 0xD3
continue 5
expectPORTB 0x01
checkResult

test "PINA: 0xC3 => PORTB: 0x00"
setPINA 0xC3
continue 5
expectPORTB 0x01
checkResult





# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
