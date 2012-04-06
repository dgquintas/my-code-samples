var sum = function() {
    var i, sum = 0;
    for(i=0; i < arguments.length; i++){
        sum += arguments[i];
    }
    return sum;
};

print(sum(4,8,15,16, 23, 42)); // 108
