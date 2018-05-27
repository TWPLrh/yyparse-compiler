/*
 * We check the value which depends on your symbol table dump function.
 * Your symbol table needs to record the scope depth.
 */
var x int = 10

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
		{
			var x float32 = 87.87
			x++
		}
	}
}

println(x)

