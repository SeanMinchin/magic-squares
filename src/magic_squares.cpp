#include "magic_squares.hpp"
#include "matrix.hpp"
#include <limits>

// checks if input is odd integer between 3 and 15
bool InputManager::IsValid(int size) {
    return size >= 3 && size <= 15 && size % 2 != 0;
}

int InputManager::DefineSquareMatrixSize() {
    int size;
    while((std::cout << "Enter the size of the magic square: " && !(std::cin >> size)) || !IsValid(size)) {
        std::cout << "Error: enter an odd integer between 3 and 15 inclusive\n" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return size;
}

MagicSquare::MagicSquare(int size) : magic_square(Matrix<int>(size)), kSize(size), magic_square_count(0) {}

const int& MagicSquare::size() const {
    return kSize;
}

// rotate each edge of the matrix
void MagicSquare::Rotate() {
    auto** temp = new int*[kSize];
    for(int i = 0; i < kSize; ++i) {
        temp[i] = new int[kSize];
    }

    for(int i = 0; i < kSize; ++i) {
        for(int j = 0; j < kSize; ++j) {
            temp[i][j] = magic_square.value(kSize - 1 - j, i);
        }
    }
    magic_square.set_matrix(temp);
}

// reflect the matrix across its right vertical edge
void MagicSquare::Reflect() {
    auto** temp = new int*[kSize];
    for(int i = 0; i < kSize; ++i) {
        temp[i] = new int[kSize];
    }

    for(int i = 0; i < kSize; ++i) {
        for(int j = 0; j < kSize; ++j) {
            temp[i][j] = magic_square.value(i, kSize - 1 - j);
        }
    }
    magic_square.set_matrix(temp);
}

// turn matrix into magic square via the Siamese method
void MagicSquare::ApplySiameseMethod() {
    magic_square.Fill(0);
    for(int i = 0; i < kSize; ++i) {
        for(int j = 0; j < kSize; ++j) {
            magic_square.set_value((kSize * (((i + j + 1 + (kSize / 2)) % kSize)) + ((i + (2 * j) + 1) % kSize) + 1), i, j);
        }
    }
}

// turn matrix into magic square via the Torus method
// https://www.quora.com/How-can-I-create-a-magic-square-1
void MagicSquare::ApplyTorusMethod() {
    magic_square.Fill(0);
    const int kMid = (kSize - 1) / 2;
    int row;
    int column;
    for(int i = 0; i < kSize; ++i) {
        for(int j = 0; j < kSize; ++j) {
            row = (((i + j - kMid) % kSize) + kSize) % kSize;
            column = (((i - j + kMid) % kSize) + kSize) % kSize;
            magic_square.set_value(i * kSize + j + 1, row, column);
        }
    }
}

void MagicSquare::Print() {
    std::cout << "Magic square #" << magic_square_count << " is:" << '\n' << std::endl;
    for(int i = 0; i < kSize; ++i) {
        for(int j = 0; j < kSize; ++j) {
            // align whitespace to produce even-looking matrix when printed
            if(magic_square.value(i, j) < 100) {
                std::cout << ' ';
            }
            if(magic_square.value(i, j) < 10) {
                std::cout << ' ';
            }
            std::cout << magic_square.value(i, j) << ' ';
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void MagicSquare::CheckSums() {
    std::string row_sum_display = "Checking the sum of every row:      ";
    std::string column_sum_display = "Checking the sum of every column:   ";
    std::string diagonal_sum_display = "Checking the sum of every diagonal: ";
    int current_row_sum, current_column_sum, diagonal_sum_left = 0, diagonal_sum_right = 0;

    for(int i = 0; i < kSize; ++i) {
        current_column_sum = 0;
        current_row_sum = 0;
        diagonal_sum_left += magic_square.value(i, i);
        diagonal_sum_right += magic_square.value(i, kSize - 1 - i);
        for(int j = 0; j < kSize; ++j) {
            current_column_sum += magic_square.value(j, i);
            current_row_sum += magic_square.value(i, j);
        }
        row_sum_display += std::to_string(current_row_sum) + " ";
        column_sum_display += std::to_string(current_column_sum) + " ";
    }
    diagonal_sum_display += std::to_string(diagonal_sum_left) + " " + std::to_string(diagonal_sum_right);

    std::cout << row_sum_display.append("\n") << column_sum_display.append("\n") << diagonal_sum_display.append("\n") << std::endl;
}

void MagicSquare::DisplayData() {
    ++magic_square_count;
    Print();
    CheckSums();
}

int main() {
    MagicSquare magic_square(InputManager::DefineSquareMatrixSize());
    std::cout << std::endl;

    // square 1
    magic_square.ApplySiameseMethod();
    magic_square.DisplayData();

    // square 2
    magic_square.Reflect();
    magic_square.DisplayData();

    // square 3
    magic_square.Rotate();
    magic_square.DisplayData();

    // square 4
    magic_square.Reflect();
    magic_square.DisplayData();

    // square 5
    magic_square.Rotate();
    magic_square.DisplayData();

    // square 6
    magic_square.Reflect();
    magic_square.DisplayData();

    // square 7
    magic_square.Rotate();
    magic_square.DisplayData();

    // square 8
    magic_square.Reflect();
    magic_square.DisplayData();

    // 3x3 magic squares only have 8 unique variations
    if(magic_square.size() != 3) {
        // square 9
        magic_square.ApplyTorusMethod();
        magic_square.DisplayData();

        // square 10
        magic_square.Reflect();
        magic_square.DisplayData();
    }
}
