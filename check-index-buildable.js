const fs = require('fs');
const { exit } = require('process');

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

function isTouchingGround(fieldString) {
    return fieldString.slice(30).search("1") != -1
}

function isPieceSupported(field, combinedField) {
    if (field.length != combinedField.length) throw "Size of fields are not equal.";
    for (let i = 0; i < field.length; i++) {
        if ((field[i] == "1") & (combinedField[i] == "1")) return true;
    }
    return false;
}

function RemoveFromField(originalField, removeField) {
    // console.log(originalField, removeField)
    if (originalField.length != removeField.length) throw "Size of fields are not equal.";
    output = "";
    for (let i = 0; i < originalField.length; i++) {
        if (removeField[i] == "1") {
            output += "0";
        } else {
            output += originalField[i];
        }
    }
    // console.log(output)
    return output;
}

function isAllPiecesSupported(separatedFields, combinedField) {
    combinedField += "1111111111";
    separatedFields.forEach((item, index, arr) => {
        arr[index] = RemoveFromField("0000000000" + item, item + "0000000000");
    })
    // console.log(separatedFields, combinedField)
    for (let i = 0; i < separatedFields.length; i++) {
        if (!isPieceSupported(separatedFields[i], combinedField)) return false;
    }
    return true;
}

{
    let indexes = []
    process.argv.slice(2).forEach((item, index, arr) => {
        indexes.push(parseInt(item));
    })
    let combinedField = IndexesToField(indexes)
    if ((combinedField.match(/1/g) || []).length != 4 * indexes.length) { //all pieces do not intersect
        console.log(false)
        exit(0);
    }
    
    let separatedFields = []
    indexes.forEach((item)=> {
        separatedFields.push(IndexesToField([item]))
    })
    //isTouchingGround(combinedField)
    console.log(isAllPiecesSupported(separatedFields, combinedField))
}
// console.log(IndexesToField([378, 11, 121]))

