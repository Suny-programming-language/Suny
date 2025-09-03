#ifndef SVM_H
#define SVM_H

#include "scompile.h"
#include "sframe.h"
#include "suny.h"
#include "sobj.h"
#include "sfunc.h"
#include "sstr.h"
#include "sinitialize.h"
#include "seval.h"
#include "sclass.h"
#include "sbool.h"

#include <math.h>

char* print_op(char c);

byte_t
get_next_code
(struct Sframe *frame);

byte_t
jump_to(struct Sframe *frame, int address);

struct Sframe *
Svm_run_program
(struct Sframe *frame);

struct Sframe *
Svm_evalutate_PUSH_FLOAT
(struct Sframe *frame);

struct Sframe *
Svm_evalutate_LOAD_GLOBAL
(struct Sframe *frame);

struct Sframe *
Svm_evalutate_STORE_GLOBAL
(struct Sframe *frame);

struct Sframe *
Svm_evaluate_MAKE_FUNCTION
(struct Sframe *frame);

struct Sframe *
Svm_evaluate_FUNCTION_CALL
(struct Sframe *frame);

struct Sframe *
Svm_evaluate_PRINT
(struct Sframe *frame);

struct Sframe *
Svm_evaluate_PUSH_STRING
(struct Sframe *frame);

struct Sframe *
Svm_evaluate_POP_JUMP_IF_FALSE
(struct Sframe *frame);

struct Sframe *
Svm_evaluate_JUMP_TO
(struct Sframe *frame);

struct Sframe *
Svm_evaluate_BUILD_LIST
(struct Sframe *frame);

struct Sframe *
Svm_evaluate_LOAD_ITEM
(struct Sframe *frame);

struct Sframe *
Svm_evaluate_STORE_ITEM
(struct Sframe *frame);

struct Sframe *
Svm_evaluate_LEN_OF
(struct Sframe *frame);

struct Sframe *
Svm_evaluate_LOAD_TRUE
(struct Sframe *frame);

struct Sframe *
Svm_evaluate_LOAD_FALSE
(struct Sframe *frame);

struct Sframe *
Svm_evaluate_LOAD_LOCAL
(struct Sframe *frame);

struct Sframe *
Svm_evaluate_STORE_LOCAL
(struct Sframe *frame);

struct Sframe *
Svm_evaluate_CLASS_BEGIN
(struct Sframe *frame);

struct Sframe*
Svm_evaluate_NOT_LOG
(struct Sframe *frame);

struct Sframe*
Svm_evaluate_AND_LOG
(struct Sframe *frame);

struct Sframe*
Svm_evaluate_OR_LOG
(struct Sframe *frame);

struct Sframe *
Svm_evalutate_BINARY_OPER
(struct Sframe *frame, byte_t op);

struct Sframe *
Svm_run_call_context
(struct Scall_context *context);

#endif // SVM_H