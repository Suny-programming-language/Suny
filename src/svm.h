#ifndef SVM_H
#define SVM_H

#include "scompile.h"
#include "sframe.h"
#include "suny.h"
#include "sobj.h"
#include "stype.h"
#include "sfunc.h"
#include "sinitialize.h"

#include <math.h>

byte_t
get_next_code
(struct Sframe *frame);

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
Svm_evalutate_BINARY_OPER
(struct Sframe *frame, byte_t op);

struct Sframe *
Svm_run_call_context
(struct Scall_context *context);

struct Sframe *
Svm_evaluate_MAKE_FUNCTION
(struct Sframe *frame);

struct Sframe *
Svm_evaluate_FUNCTION_CALL
(struct Sframe *frame);

struct Sframe *
Svm_evaluate_PRINT
(struct Sframe *frame);

#endif // SVM_H