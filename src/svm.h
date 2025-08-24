#ifndef SVM_H
#define SVM_H

#include "scompile.h"
#include "sframe.h"
#include "suny.h"
#include "sobj.h"

byte_t
get_next_code
(struct Sframe *frame);

struct Sframe *
Svm_run_program(struct Sframe *frame);

#endif // SVM_H