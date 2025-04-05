// matrix - считывается из файла csv (delimetr=,)
// значения из матрицы хранятся в шаблонном векторе

// пусть есть бызовый класс Matrix, в нем определены операции сравнения, проверка на соответствие измерений, транспонирование, возведение в степень, ранг матрицы, арифметические операции

// !SquareMatrix - наследуется от Matrix, нужно реализовать поиск обратной матрицы и поиск определителя

// Вроде все


#include <iostream>
#include <vector>

template<typename T>
class Matrix {
public:
    Matrix() = default;
    Matrix(const matrix& data);
    explicit Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    explicit Matrix(Matrix&& other);
    Matrix& operator=(Matrix&& other);
    virtual ~Matrix() = default;
    auto rows() const;
    auto cols() const;
    auto operator<=>(const Matrix& other) const;
    bool operator==(const Matrix& other) const = default;
    void transpose();
    void pow();
    auto getRank() const;
    const void operator+=(const Matrix& obj);
    const void operator-=(const Matrix& obj);
    const void operator*=(const Matrix& obj);
    const void operator/=(const Matrix& obj);
    friend Matrix operator+(const Matrix& robj, const Matrix& lobj);
    friend Matrix operator-(const Matrix& robj, const Matrix& lobj);
    friend Matrix operator*(const Matrix& robj, const Matrix& lobj);
    friend Matrix operator/(const Matrix& robj, const Matrix& lobj);
    friend std::ostream& operator<<(std::ostream& out, Matrix& obj); //< не обязательно
protected:
    using matrix = std::vector<std::vector<T>>;
    matrix _data;
    unsigned rows = 0;
    unsigned cols = 0;
}

Matrix operator+(const Matrix& robj, const Matrix& lobj);
Matrix operator-(const Matrix& robj, const Matrix& lobj);
Matrix operator*(const Matrix& robj, const Matrix& lobj);
Matrix operator/(const Matrix& robj, const Matrix& lobj);
std::ostream& operator<<(std::ostream& out, Matrix& obj);
