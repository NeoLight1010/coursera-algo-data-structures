#include <iostream>
#include <cassert>

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}

int fibonacci_sum_fast(long long n) {
    n = n % 60; // Pisano period of 10 is 60.
    if (n <= 1)
        return n;

    int previous = 0;
    int current = 1;

    for (int i=2; i < n + 1; i++) {
        int temp_current = current;
        current = (previous + current + 1) % 10;
        previous = temp_current;
    }

    return current;
}

void test_solution(int n_tests = 50, int max_n = 70) {
    std::cout << "- " << 3 << ": " << fibonacci_sum_fast(3) << std::endl;
    assert(fibonacci_sum_fast(3) == 4);
    
    std::cout << "- " << 100 << ": " << fibonacci_sum_fast(100) << std::endl;
    assert(fibonacci_sum_fast(100) == 5);

    // Stress test
    for (int i=0; i < n_tests; i++) {
        int rand_n = rand() % max_n + 1;

        int naive_sol = fibonacci_sum_naive(rand_n);
        int fast_sol = fibonacci_sum_fast(rand_n);

        std::cout << "- " << rand_n << ": " << naive_sol << " " << fast_sol << std::endl;
        assert(naive_sol == fast_sol);
    }

    std::cout << "Test ended successfully";
}

int main() {
    long long n = 0;
    std::cin >> n;
    
    // std::cout << fibonacci_sum_naive(n);
    // test_solution();
    std::cout << fibonacci_sum_fast(n);

    return 0;
}
