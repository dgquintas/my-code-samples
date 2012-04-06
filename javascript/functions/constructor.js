var Quo = function(str){
    this.status = str;
};

// Give all instances of Quo a public
// method called "get_status"
Quo.prototype.get_status = function(){
    return this.status;
};

// instantiate
var myQuo = new Quo("hola");

print(myQuo.get_status());
