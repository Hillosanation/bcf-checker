const { encoder, Field } = require('tetris-fumen');
const fs = require('fs');

function CombineFields(FieldA, FieldB) {
    if (FieldA.length != FieldB.length) throw "Size of fields are not equal.";
    newField = ""
    Array.from(FieldA).forEach((item, index) => {
        if (FieldB[index] == "1") {
            newField += "1"
        } else {
            newField += item
        }
    });
    return newField
}

function IndexesToField(Indexes) {
    var newField = "0000000000000000000000000000000000000000"; //assumes 4x10 field
    for (let i = 0; i < Indexes.length; i++) {
        newField = CombineFields(newField, FieldPermutations[Indexes[i]]);
    }
    return newField;
}

//###

var FieldPermutations = []
{
    let data = fs.readFileSync('field_permutations.txt', 'utf8').toString().split(/\r?\n/);
    for (let i = 0; i < data.length/6; i++) {
        let field = "";
        for (let j = 1; j < 5; j++) {
            field += data[6*i+j];
        }
        FieldPermutations.push(field);
    }
}
function CreateFumen(fieldString) {
    let page = [];
    page.push({
        field: Field.create(fieldString),
    })
    return encoder.encode(page);
}
{
    let indexes = []
    let ReplaceTetromino = process.argv[2]
    process.argv.slice(3).forEach((item, index, arr) => {
        indexes.push(parseInt(item));
    })
    let fieldString = IndexesToField(indexes).replace(/0/g, "_").replace(/1/g, ReplaceTetromino)
    
    console.log(CreateFumen(fieldString));
}
// console.log(IndexesToField([378, 11, 121]))

