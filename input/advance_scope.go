/*
 * We check the value which depends on your symbol table dump function.
 * Your symbol table needs to record the scope depth.
 */
var x float32 = 87

{
	var x int = 5
	x++
	println(x)
	{
		var x int = 3
		x++
	}
}

println(x)

{
	x++
	println(x)
	{
		var x int = 17
		var b float32 = 21.21

		x += b + 17.17
		b += x + 26.56
	
		{
			var x float32 = 87.87
			x++
			println(x /= 7)
		}
	}
}

println(x)

