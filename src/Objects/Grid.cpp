#include "Grid.h"

int Grid::getInvCount() const {
    std::vector<int> arr(N * N);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            arr[i * N + j] = grid[i][j];
    int inv_count = 0;
    for (int i = 0; i < N * N - 1; i++) {
        for (int j = i + 1; j < N * N; j++) {
            if (arr[j] && arr[i] && arr[i] > arr[j])
                inv_count++;
        }
    }
    return inv_count;
}

int Grid::findXPosition() const {
    for (int i = N - 1; i >= 0; i--)
        for (int j = N - 1; j >= 0; j--)
            if (grid[i][j] == 0)
                return N - i;
    return -1;
}

bool Grid::isSolvable() const {
    const int invCount = getInvCount();
    if (grid.size() & 1)
        return !(invCount & 1);
    else {
        if (const int pos = findXPosition(); pos & 1)
            return !(invCount & 1);
        else
            return invCount & 1;
    }
}

void Grid::fillGrid() {
    std::vector<int> flat;
    flat.reserve(N * N);

    for (const auto& row : grid)
        for (int val : row)
            flat.push_back(val);

    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

    do {
        std::ranges::shuffle(flat, rng);

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                grid[i][j] = flat[i * N + j];

    } while (!isSolvable());
}

void Grid::printGrid() const {
    int sp = 3;
    if (N >= 10)
        sp = 5;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0)
                std::cout << std::setw(sp) << "00" << " ";
            else
                std::cout << std::setw(sp) << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int Grid::size() const {
    return N;
}

int Grid::area() const {
    return N * N;
}

std::array<std::array<int, 4>, 4>& Grid::get() {
    return grid;
}

int Grid::get(const int i, const int j) const {
    return grid[i][j];
}

Grid::Grid() {
    N = grid.size();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = i * N + j;
        }
    }
    std::ranges::copy(grid, win.begin());
    fillGrid();
}
