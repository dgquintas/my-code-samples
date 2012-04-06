-- File sqr.lua
function sqr(x)
  return x*x
end

print("Sqr calculator")

--[[
Bla bla bla. Que funcion tiene
este tipo de comentarios?
mmm quizas es ser multilinea XD
--]]
print("Enter a number :")
n = io.read("*number")
print(sqr(n))
