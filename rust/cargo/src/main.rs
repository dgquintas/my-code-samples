fn main() {
    hello("mundo");
    let (x,y) = (1i, 2i);
    let z: int = 5;
    let mut m;
    m = 10i;
    println!("x = {}; y = {}; z = {}, m = {}", x, y, z, m);
    m = 100i;
    println!("x = {}; y = {}; z = {}, m = {}", x, y, z, m);

    print_number(f());

    tuples();
    {
        let (x,y) = next_two(5);
        println!("x, y = {}, {}", x,y);
    }

    structs();
    enums();
    match_();

    for x in range(0i, 10i) {
        println!("{:d}", x);
    }
    println!("");

    let mut x = 5u;
    let mut done = false;
    while !done {
        x += x - 3;
        println!("{}", x);
        if x % 5 == 0 { done = true; }
    }
    println!("");

    x = 5u;
    loop {  // while true
        x += x -3;
        println!("{}", x);
        if x % 5 == 0 { break; }
    }

}

/// `hello` is a function that prints a greeting bla bla.
///
/// #Arguments
///
/// * `name` - The name.
///
/// # Example
///
/// ```rust
/// let name = "Steve";
/// hello(name); // prints bla bla
/// ```
fn hello(name: &str) {
    println!("hola {}!", name);
}

fn f() -> int {
    let x = 5i;
    let y = if x == 5i { 10i } else { 15i };
    y  // same as "return y;"
}

fn print_number(x: int) {
    println!("x is: {}", x);
}


fn tuples() {
    let x: (int, &str) = (1, "hello"); // let x = (1i, "hello");
    let (a,b) = x;
    println!("a = {}, b = {}", a, b);

    let mut k;
    let l = (2i, 3i);
    k = l;
    println!("k = {}", k);
}

fn next_two(x:int) -> (int, int) { (x+1, x+2) }

fn structs() {
    struct Point {
        x: int,
        y: int,
    }

    let origin = Point { x: 0i, y: 0i };
    println!("The origin is at ({}, {})", origin.x, origin.y);

    let mut mpoint = Point { x: 0, y: 0 };
    mpoint.x = 5;

    println!("The point is at ({}, {})", mpoint.x, mpoint.y);

    // newtypes (~ typedef)
    struct Inches(int);
    let length = Inches(10);
    let Inches(integer_length) = length;
    println!("length is {} inches. Fuck inches though.", integer_length);
}

fn enums() {
    enum OptionalInt {
        Value(int),
        Missing,
    }

    let x = Value(5);
    let y = Missing;

    match x {
        Value(n) => println!("x is {:d}", n),
        Missing  => println!("x is missing!"),
    }

    match y {
        Value(n) => println!("y is {:d}", n),
        Missing  => println!("y is missing!"),
    }
}

fn match_() {
    let x = 5i;

    match x {
        1 => println!("one"),
        2 => println!("two"),
        3 => println!("three"),
        4 => println!("four"),
        5 => println!("five"),
        _ => println!("wooot"),
    }
}

