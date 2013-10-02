#Chunktional

Chunktional is a collection of macros that can make functional style programming in C convenient.

##Abstract Data Types

Uisng the `datatype(dataname, ...)`, `datatypeatom(dataname, option)`, and `datatypedefine(dataname, option, structure)` macros, you can create Haskell style abstract data types.

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

Using the `caseof(value)`, `endcaseof`, `where(option, result)`, `whereatom(option)`, and `otherwise` macros, you can create a kind of case-of statement for use with the abstract data types.

Haskell Example:

	f :: Maybe Int -> Int
	f m = case m of
			None -> 0
			Just x -> x

Chunktional Example:

	int f(MaybeInt *m) {
		caseof(m)
	        whereatom(NoneInt) return 0;
	        where(JustInt, j) return j->number;
	    endcaseof;
	    return 0; // we unfortunately need a dummy return value to avoid a compiler warning
	}

##Closures

Using the `closure(type, fn, context, ...)` and `call(fn, context, ...)` macros, you can create a kind of closure over desired values for functions. This can be useful to easily create context for function calls.

Haskell Example:

	f :: Int -> Int
	f x = fhelper 5
		where fhelper y = x + y

Chunktional Example:

	closure(int, fhelper, {int x;}, int y) {
		return closure.x + y;
	}

	int f(int x) {
		return call(fhelper, {x}, 5);
	}
