// see "constructor.js"
var Quo = function(str){
    this.status = str;
};
Quo.prototype.get_status = function(){
    return this.status;
};

// a simple vanila object with a "status" attribute
var statusObject = {
    status: 'alrighty!'
};

// we are applying the "get_status" method to an arbitrary
// instance, provided that this instance has all the
// attributes the applied method needs. 
var status = Quo.prototype.get_status.apply(statusObject);
print(status);
