/*
 * We check the value which depends on your symbol table dump function.
 * Your symbol table needs to record the scope depth.
 */

var x int = 5
{
	var x int = 7
	x = x + 7
	{
		var x float32 = 16
		x += 16.16
		{
			var x float32 = 17
			x = x + 17
			println(x)
		}
	}
}
