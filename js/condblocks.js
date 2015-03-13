var predicate = true;
if(predicate) {} else {};   // conditional blocks

var value=10, match1=10;
switch(value) {             // switch .. case
    case match1: 'codeblock'; break;
    case match2: 'codeblock'; break;
    default: 'codeblock';
}

try {                       // try .. catch .. finally
    if (a < 0) throw 'badnum';
    if (a== 0) throw 'zero';
} catch(e) {
    switch(err) {
        case 'badnum': num = -num; break;
        case 'zero': num = 1; break;
    }
} finally {
    console.log('Execute this in any case');
}

true ? 'it was true' : 'it was false'   // ternary conditional operatory
