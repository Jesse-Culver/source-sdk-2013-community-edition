-------------------------------------------------------------------

-- Quick Script to Make .VPC files
-- change parameters here

local projectDir = "game/server"

local macros =
{
	SRCDIR = "../..",
	GAMENAME = "sdk2013ce",
}

local includes =
{
	"$SRCDIR/game/server/server_base.vpc",
	"$SRCDIR/game/shared/shared_sdk2013CE.vpc",
}

local config =
{
	Compiler =
	{
		AdditionalIncludeDirectories =
		"$BASE;$SRCDIR/game/shared/hl2;$SRCDIR/game/shared/episodic;./hl2;./episodic;$SRCDIR/game/shared/$GAMENAME;$SRCDIR/game/server/$GAMENAME",
		PreprocessorDefinitions = "$BASE;HL2_DLL;HL2_EPISODIC;USES_SAVERESTORE;SDK2013CE;GLOWS_ENABLE"
	}
}

-- file names all use Lua patterns (very similar to regular expressions)
-- (See: https://www.lua.org/pil/20.2.html)
--
-- all paths are relative to the current directory

local projects = {
	["Server (SDK2013CE)"] = {
		["Source Files"] = {
				"^[^/]+%.cpp",
				"^[^/]+%.h",
				["HL2 DLL"] = {
					"hl2/..-%.cpp",
					"hl2/..-%.h"
				}
		}
	}
}

-------------------------------------------------------------------


local output = ""

local file = io.open(projectDir .. '/out.vpc', 'a')

local indentLevel = 0;
function puts(s)
	for i = 0, indentLevel - 1 do
		file:write('\t')
	end
	file:write(s..'\n')
end

function startBlock()
	puts('{')
	indentLevel = indentLevel + 1;
end

function endBlock()
	indentLevel = indentLevel - 1;
	puts('}')
end


-------------------------------------------------------------------

for k,v in pairs(macros) do puts("$Macro "..k..'\t"'..v..'"') end
for i = 1, #includes do puts('$Include "'..includes[i]..'"') end


function recursiveVPCWrite(t)
	startBlock()
	
	for k,v in pairs(t) do
		if type(v) == 'table' then
			puts('$'..k)
			recursiveVPCWrite(v)
		else
			puts('$'..k..'\t"'..v..'"')
		end
	end
	
	endBlock()
end
puts("$Configuration")
recursiveVPCWrite(config)

-------------------------------------------------------------------

function getdir(dir)
	local t = {}
	
	local files = io.popen('dir "'..dir..'" /b /a-d'):lines()
	local folders = io.popen('dir "'..dir..'" /b /ad'):lines()
	
	for f in files do
		if f ~= nil then
			t[#t + 1] = f
		end
	end
	
	for f in folders do
		local dirFiles = getdir(dir..'/'..f)
		for df = 1, #dirFiles do
			local name = dirFiles[df]
			t[#t + 1] = f..'/'..name
		end
	end
	
	return t
	
end

local files = getdir(projectDir)
--for i = 1, #files do print(files[i]) end


function getMatch(pattern)
	
	local matches = {}
	
	for i = 0, #files do
		if files[i] ~= nil then
			local m = string.match(files[i], pattern)
			if m then
				matches[#matches + 1] = files[i]
				
				files[i] = nil
			end
		end
	end
	
	return matches
	
end

function VPCDir(t)
	

	startBlock()
	for k,v in pairs(t) do
		if type(v) == 'table' then
			puts('$Folder "'..k..'"')
			VPCDir(v)
		else
			--puts('$File\t"'..v..'"')
			
			local matches = getMatch(v)
			if matches then
				for i = 1, #matches do
					puts('$File\t"'..matches[i]..'"')
				end
			end
		end
	end
	endBlock()
end


for k,v in pairs(projects) do
	puts('$Project "'..k..'"')
	VPCDir(v)
end
