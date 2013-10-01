#Chunktional

Chunktional is a collection of macros that can make functional style programming in C convenient.

##Abstract Data Types

Uisng the `datatype(dataname, ...)`, `datatypedefine(dataname, option)`, and `datatypeend` macros, you can create Haskell style abstract data types.

Haskell Example:

	datatype Maybe = None | Just x

	x = None
	y = Just 10

Chunktional Example:

	datatype(MaybeInt, NoneInt, JustInt);
	datatypeempty(MaybeInt, NoneInt);
	datatypedefine(MaybeInt, JustInt, {int number;});

	int main() {
		MaybeInt *x = mkdatatype(NoneInt);
	    MaybeInt *y = mkdatatype(JustInt, 10);

		free(x);
		free(y);

		return 0;
	}

##Pattern Matching

Using the `caseof(value)`, `endcaseof`, `where(value, option, result)`, and `endwhere` macros, you can create a kind of case-of statement for use with the abstract data types.

Haskell Example:

	f :: Maybe Int -> Int
	f m = case m of
			None -> 0
			Just x -> x

Chunktional Example:

	int f(MaybeInt *m) {
		caseof(m)
	        where(JustInt, j) printf("%d\n", j->number);
	        whereatom(NoneInt) printf("hello\n");
	    endcaseof;
	}
