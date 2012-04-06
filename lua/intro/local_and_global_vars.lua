x=5					-- Global Variable
do					-- Start of a block 1
	local x=x			-- Local Variable
	print (x)			-- Prints 5
	x=x+2				-- Modifies local x
	print (x)			-- Prints 7
	do				-- Start of block 2
		local x=x+4		-- Yet another local x :)
		print (x)		-- prints 11
	end				-- End of block 2
	print (x)			-- Prints 7
end					-- End of block 1
print (x)				-- Prints 5, global variable 
