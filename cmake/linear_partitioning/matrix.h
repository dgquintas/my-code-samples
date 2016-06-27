#include <vector>
#include <sstream>

template <typename T>
class Matrix {
   public:
    Matrix(const int rows, const int cols);
    Matrix(const int rows, const int cols, const T& init);
    Matrix(const Matrix<T>& other);

    const T& operator()(const int i, const int j) const;
    T& operator()(const int i, const int j);

    T* data() { return data_.data(); }
    const T* data() const { return data_.data(); }

    int nrows() { return rows_; }
    int ncols() { return cols_; }
    std::string ToString() const;

   private:
    Matrix& operator=(const Matrix<T>& rhs);

    const int rows_;
    const int cols_;
    std::vector<T> data_;
};

template <typename T>
Matrix<T>::Matrix(const int rows, const int cols)
    : rows_(rows), cols_(cols), data_(rows * cols) {}

template <typename T>
Matrix<T>::Matrix(const int rows, const int cols, const T& init)
    : rows_(rows), cols_(cols), data_(rows * cols, init) {}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other)
    : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {}

template <typename T>
const T& Matrix<T>::operator()(const int i, const int j) const {
    return data_.at(i * cols_ + j);
}

template <typename T>
T& Matrix<T>::operator()(const int i, const int j) {
    return data_.at(i * cols_ + j);
}

template <typename T>
std::string Matrix<T>::ToString() const {
    std::ostringstream oss;
    for (int i = 0; i < rows_; ++i) {
        oss << '[';
        for (int j = 0; j < cols_; ++j) {
            oss << '\t' << this->operator()(i,j);
            if (j + 1 < cols_) oss << " ";
        }
        oss << "]\n";
    }
    return oss.str();
}


