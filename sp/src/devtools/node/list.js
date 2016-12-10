var srcDir = "../../"
var target = srcDir + "game/server/server.vcxproj.filters"

var fs = require('fs')
var util = require('util')
var xml = require('xml2js')


var proj = fs.readFileSync(target)

var files = {}

function include(list) {
	for (let f of list) {
		files[f.Filter].push(f.$.Include)
	}
}

var out = ""

xml.parseString(proj, function (err, res) {
	console.dir(res, {colors: true, depth: 3})
	for (let g of res.Project.ItemGroup[0].Filter) {
		//console.log(g.$.Include)
		files[g.$.Include] = []
	}
	
	include (res.Project.ItemGroup[1].Library)
	include (res.Project.ItemGroup[2].ClInclude)
	include (res.Project.ItemGroup[3].ClCompile)
	//include (res.Project.ItemGroup[4].CustomBuild)
	
	for (let g of res.Project.ItemGroup[0].Filter) {
		files[g.$.Include].sort()
	}
	
	fs.writeFileSync("out.json", JSON.stringify(files, null, '\t'), {flags: 'w+'})
	//console.dir(files, {colors: true, depth: null})
})
