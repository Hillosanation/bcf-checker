const yargs = require('yargs')(process.argv.slice(2));
const fs = require('fs');
const path = require('path');
const {decoder, encoder, Field} = require('tetris-fumen');
const Hashmap = require('hashmap');

const argv = yargs
  .option({
    'so': {
        alias: 'single-output',
        default: false,
        describe: 'Option to only add one glued fumen per fumen inputted. Useful for cover in sfinder.',
        type: 'boolean',
    },
    's': {
        alias: 'silence',
        default: false,
        describe: 'Does not report when multiple fumens were available.',
        type: 'boolean',
    },
    'fu': {
        alias: 'fumen',
        default: '',
        describe: 'The input to be glued. If multiple fumens are to be glued, then put them in a space-separated string.',
        type: 'string',
    },
    'fp': {
        alias: 'file-path',
        default: '',
        type: 'string',
        describe: 'File path for the newline-separated fumens. This overrides --fu.',
    },
    'op': {
        alias: 'output-path',
        default: '',
        type: 'string',
        describe: 'File path for the output file.'
    },
  })
  .check((argv, options) => {
    const filePaths = argv
    if ((filePaths.fu == '') && (filePaths.fp == '')) {
      throw new Error("Neither fp nor fu was provided.");
    } else {
      return true; // tell Yargs that the arguments passed the check
    }
  })
  .hide('version')
  .help()
  .alias('help', 'h').argv;

var fumenCodes = [];
if (argv.fp != "") {
    const data = fs.readFileSync(argv.fp, "utf8");
    fumenCodes = data.split('\r\n'); //suck it, unix users //maybe "\r?\n"?
    // console.log(fumenCodes);
} else {
    fumenCodes = argv.fu.split(" ");
}

const rowLen = 10;

const pieceMappings = new Hashmap();
pieceMappings.set("T", [
    [[0, -1], [0, 0], [-1, -1], [1, -1]],
    [[0, -1], [0, 0], [-1, -1], [0, -2]],
    [[1, 0], [0, 0], [2, 0], [1, -1]],
    [[0, -1], [0, 0], [1, -1], [0, -2]]
    ])
pieceMappings.set("I", [
    [[1, 0], [0, 0], [2, 0], [3, 0]],
    [[0, -2], [0, 0], [0, -1], [0, -3]]
    ])
pieceMappings.set("L", [
    [[-1, -1], [0, 0], [-2, -1], [0, -1]],
    [[1, -1], [0, 0], [1, 0], [1, -2]],
    [[1, 0], [0, 0], [2, 0], [0, -1]],
    [[0, -1], [0, 0], [0, -2], [1, -2]]
    ])
pieceMappings.set("J", [
    [[1, -1], [0, 0], [0, -1], [2, -1]],
    [[0, -1], [0, 0], [-1, -2], [0, -2]],
    [[1, 0], [0, 0], [2, 0], [2, -1]],
    [[0, -1], [0, 0], [1, 0], [0, -2]]
    ])
pieceMappings.set("S", [
    [[0, -1], [0, 0], [1, 0], [-1, -1]],
    [[1, -1], [0, 0], [0, -1], [1, -2]]
    ])
pieceMappings.set("Z", [
    [[1, -1], [0, 0], [1, 0], [2, -1]],
    [[0, -1], [0, 0], [-1, -1], [-1, -2]]
    ])
pieceMappings.set("O", [
    [[0, -1], [0, 0], [1, 0], [1, -1]]
    ])

const rotationDict = new Hashmap();
rotationDict.set(0, "spawn");
rotationDict.set(1, "left");
rotationDict.set(2, "reverse");
rotationDict.set(3, "right");

function checkRotation(x, y, field, piecesArr){
    const piece = field.at(x, y);

    const rotationStates = pieceMappings.get(piece);

    let found = false;

    for(let state = 0; state < rotationStates.length; state++){
        let minoPositions = [];
        let newPiecesArr = piecesArr.slice();
        for(let pos of rotationStates[state]){
            let posX = x + pos[0];
            let posY = y + pos[1];

            // checks for position is in bounds
            if(posX < 0 || posX >= rowLen){
                break;
            }
            if(posY < 0){
                break;
            }

            if(field.at(posX, posY) == piece){
                minoPositions.push([posX, posY]);
            }
            else{
                break;
            }
        }
        // if there's 4 minos
        if(minoPositions.length == 4){
            // a rotation is found
            found = true;

            // a rotation that works
            let operPiece = {
                type: piece,
                rotation: rotationDict.get(state),
                x: minoPositions[0][0],
                y: minoPositions[0][1]
            }
            newPiecesArr.push(operPiece)

            let newField = field.copy()
            for(let pos of minoPositions){
                let posX = pos[0];
                let posY = pos[1];
                // change the field to be the piece to be replaced by gray
                newField.set(posX, posY, "X");
            }
            newField = removeLineClears(newField);

            const height = newField.str().split("\n").length - 1;

            let oldLen = allPiecesArr.length;

            let possPiecesArr = scanField(0, height, newField, newPiecesArr)
            
            // if the field doesn't have any more pieces it's good
            if(checkFieldEmpty(newField)){
                allPiecesArr.push(possPiecesArr);
            } else if(oldLen == allPiecesArr.length){
                // the piece didn't result into a correct glued fumen
                found = false;
            }
        }
    }
    return found
}

function scanField(x, y, field, piecesArr){
    var newX = x;
    for(let newY = y; newY >= 0; newY--){
        for(; newX < rowLen; newX++){
            // if it is a piece
            if(field.at(newX, newY) != "X" && field.at(newX, newY) != "_"){
                if(checkRotation(newX, newY, field, piecesArr)){
                    // a rotation works for the piece so just end the function as the scan finished
                    return null;
                }
                // skips this one that meets no rotation as it might be a cut piece
            }
        }
        newX = 0
    }
    return piecesArr;
}

function makeEmptyField(field, height){
    var emptyField = field.copy();
    for(let y = height-1; y >= 0; y--){
        for(let x = 0; x < rowLen; x++){
            let piece = emptyField.at(x, y);
            if(piece.match(/[TILJSZO]/)){
                emptyField.set(x, y, "_");
            }
        }
    }
    return emptyField;
}

function removeLineClears(field){
    var lines = field.str().split("\n");
    for(let i = lines.length-1; i >= 0; i--){
        if(lines[i].match(/X{10}/)){
            lines.splice(i, 1);
        }
    }
    const newField = Field.create(lines.slice(0, -1).join(""), lines[-1]);
    return newField;
}

function checkFieldEmpty(field){
    let lines = field.str().split("\n").slice(0, -1);
    for(let line of lines){
        if(line.match(/.*[TILJSZO].*/)){
            return false;
        }
    }
    return true;
}

// console.log(fumenCodes.length);
var allPiecesArr = [];
var allFumens = [];
var fumenIssues = 0;
for(let code of fumenCodes){
    // console.log("\"" + code + "\"")
    if (code == "") continue;
    let inputPages = decoder.decode(code);
    for(let pageNum = 0; pageNum < inputPages.length; pageNum++){
        let field = inputPages[pageNum].field;
        field = removeLineClears(field);
        const height = field.str().split("\n").length - 1;
        let emptyField = makeEmptyField(field, height);
        allPiecesArr = []

        scanField(0, height - 1, field, []);
        
        if(allPiecesArr.length == 0){
            console.log(code + " couldn't be glued");
            fumenIssues++;
        }
        
        let convertedFumens = [];
        
        for(let piecesArr of allPiecesArr){
            let pages = [];
            pages.push({
                field: emptyField,
                operation: piecesArr[0]
            })
            for(let i = 1; i < piecesArr.length; i++){
                pages.push({
                    operation: piecesArr[i]
                })
            }
            let pieceFumen = encoder.encode(pages);
            convertedFumens.push(pieceFumen);
        }

        if(allPiecesArr.length > 1){
            // multiple outputs warning
            if (argv.so) {
                if (!argv.s) console.log(code + " led to " + allPiecesArr.length + " outputs, inserting only 1: " + convertedFumens[0]);
                convertedFumens = [convertedFumens[0]];
            }
            else {
                if (!argv.s) console.log(code + " led to " + allPiecesArr.length + " outputs: " + convertedFumens.join(" ")); //only outputs ones converted from current fumen
            }
        }
        allFumens.push(...convertedFumens)
    }
    // console.log(allFumens.length)
}
if(fumenIssues != 0){
    console.log("Warning: " + fumenIssues + " fumens couldn't be glued");
}

Output = allFumens.join("\n");

if (argv.op != '') {
    fs.writeFile(argv.op, Output, (err) => {
    if (err)
      console.log(err);
    else {
      console.log("File written successfully to " + argv.op + "\n");
    }
    });
} else {
    console.log(Output);
}