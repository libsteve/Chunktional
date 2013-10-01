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

int main() {
    MaybeInt *x = mkdatatype(NoneInt);
    MaybeInt *y = mkdatatype(JustInt, 10);

    f(x);
    f(y);

    free(x);
    free(y);

    return 0;
}
