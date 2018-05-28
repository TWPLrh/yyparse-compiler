/*

 * Your parser just need to match the if... else if ... grammar.
 * Don't need to operate the correct result after parsing.
 * In the other hand, we don't consider the "x" value in this input case.
 */
var x int = 10

if (x < 10) {
    x++
} else if(x == 10) {
    x--
} else if(x == 9) {
	if (x > 1){

	}

	else if( x== 10){

	}

	else{
    x = 20
	}
} else {
    x = 0
}
