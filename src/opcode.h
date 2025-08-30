#ifndef OPCODE_H
#define OPCODE_H

#define PUSH_FLOAT '\x01'

#define BINARY_ADD '\x02'
#define BINARY_SUB '\x03'
#define BINARY_MUL '\x04'
#define BINARY_DIV '\x05'

#define PRINT '\x06'
#define POP_TOP '\x07'

#define LOAD_GLOBAL '\x08'
#define STORE_GLOBAL '\x09'

#define PROGRAM_START '\x10'
#define PROGRAM_END '\x11'

#define BINARY_BIGGER '\x12'
#define BINARY_SMALLER '\x13'
#define BINARY_EQUAL '\x14'
#define BINARY_BIGGER_EQUAL '\x15'
#define BINARY_SMALLER_EQUAL '\x16'
#define BINARY_NOT_EQUAL '\x17'

#define MAKE_FUNCTION '\x18'
#define END_FUNCTION '\x19'

#define FUNCTION_CALL '\x20'

#define RETURN_TOP '\x21'

#define PUSH_STRING '\x22'

#define PUSH_TRUE '\x23'
#define PUSH_FALSE '\x24'

#define JUMP_TO '\x27'
#define ADD_LABEL '\x28'

#define POP_JUMP_IF_TRUE '\x25'
#define POP_JUMP_IF_FALSE '\x26'

#define JUMP_IF_TOP_IS_TRUE '\x27'
#define JUMP_IF_TOP_IS_FALSE '\x28'

#define JUMP_FORWARD '\x29'
#define JUMP_BACKWARD '\x30'

#define SKIP_TO_INDEX '\x31'

#define EXIT_PROGRAM '\x32'
#define STOP_PROGRAM '\x33'

#define LOAD_ITEM '\x34'
#define STORE_ITEM '\x35'

#define BUILD_LIST '\x36'

#define LEN_OF '\x37'

#endif 