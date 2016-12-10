-- for n in pairs(_G) do print (n) end

function tryCall(name)
	print("Calling " .. name)
	print(type(_G[name]))
end