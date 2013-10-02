#include "chunktional.h"
#include <stdio.h>

datatype(MaybeInt, NoneInt, JustInt);
datatypeatom(MaybeInt, NoneInt);
datatypedefine(MaybeInt, JustInt, {int number;});

void f(MaybeInt *m) {
    caseof(m)
        where(JustInt, j) printf("%d\n", j->number);
        whereatom(NoneInt) printf("hello\n");
    endcaseof;
}

int num(MaybeInt *m) {
    caseof(m)
        whereatom(NoneInt) return 0;
        where(JustInt, j) return j->number;
    endcaseof;
    return 0; // we unfortunately need a dummy return value to avoid a compiler warning
}

closure(static inline int, lambda, {MaybeInt *x; MaybeInt *y;}, int multiplier) {
    return (num(closure.x) + num(closure.y)) * multiplier;
}

int main() {
    MaybeInt *x = mkdatatype(NoneInt);
    MaybeInt *y = mkdatatype(JustInt, 10);

    f(x);
    f(y);

    MaybeInt *m = mkdatatype(JustInt, call(lambda, {x, y}, 10));
    f(m);

    free(x);
    free(y);
    free(m);

    return 0;
}
