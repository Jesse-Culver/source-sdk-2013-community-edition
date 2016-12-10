//////////////////////////////////////////////////////////////////-

// Quick Script to Make .VPC files
// change parameters here

/* var macros =
{
	SRCDIR: "../..",
	GAMENAME: "sdk2013ce"
}

var includes =
[
	"$SRCDIR/game/server/server_base.vpc",
	"$SRCDIR/game/shared/shared_sdk2013CE.vpc",
] */

var list = require("./out.json")
var project = "Server (SDK2013CE)"

//////////////////////////////////////////////////////////////////-

const fs = require('fs')

var file = {}
file.text = ""
file.write = function(s) {this.text += s}

var indentLevel = 0;
function puts(s) {
	for (let i = 0; i < indentLevel; i++) {
		file.write('\t')
	}
	file.write(s + '\n')
}

function startBlock() {
	puts('{')
	indentLevel++;
}

function endBlock() {
	indentLevel--;
	puts('}\n')
}


//////////////////////////////////////////////////////////////////-

//for (let k in macros) { puts("$Macro " + k + '\t"' + macros[k] + '"') }
//for (let i of includes) { puts('$Include "' + i + '"') }

puts('$Project "' + project + '"')
startBlock()
for (let dir in list) {
	puts('$Folder "' + dir + '"')
	startBlock()
	for (let f of list[dir]) {
		f = f.replace("..\\..", "$SRCDIR")
		puts('$File\t"' + f + '"')
	}
	endBlock()
}
endBlock()




fs.writeFileSync("out.vpc", file.text)
