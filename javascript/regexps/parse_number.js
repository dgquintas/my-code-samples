var parse_number = /^-?\d+(?:\.\d*)?(?:e[+\-]?\d+)?$/i;

var test = function(num) {
    print(parse_number.test(num));
};

test('1'); 
test('number'); 
test('98.6'); 
test('132.21.86.100'); 
test('123.45E-67'); 
test('123.45D-67');
