#include <iostream>

class C {
	public:
		template<typename T>
		C(T arg) {
			std::cout << "arg: " << arg << std::endl;
		}
};

int main() {
	C c(1);
	C d("lol");
	return 0;
}
