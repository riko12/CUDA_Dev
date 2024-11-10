// main.cpp
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

// Declare the CUDA function
extern "C" bool cuda_vector_add(const float* h_a, const float* h_b, float* h_c, int n);

// CPU version for comparison
void cpu_vector_add(const float* a, const float* b, float* c, int n) {
    for (int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    const int N = 1000000; // Vector size
    
    // Allocate and initialize host vectors
    std::vector<float> h_a(N);
    std::vector<float> h_b(N);
    std::vector<float> h_c(N);     // CUDA result
    std::vector<float> h_c_cpu(N); // CPU result for verification

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-100.0f, 100.0f);

    // Fill input vectors with random numbers
    for (int i = 0; i < N; i++) {
        h_a[i] = dis(gen);
        h_b[i] = dis(gen);
    }

    // Run CPU version and measure time
    auto cpu_start = std::chrono::high_resolution_clock::now();
    cpu_vector_add(h_a.data(), h_b.data(), h_c_cpu.data(), N);
    auto cpu_end = std::chrono::high_resolution_clock::now();
    auto cpu_duration = std::chrono::duration_cast<std::chrono::microseconds>(cpu_end - cpu_start);

    // Run CUDA version and measure time
    auto gpu_start = std::chrono::high_resolution_clock::now();
    bool success = cuda_vector_add(h_a.data(), h_b.data(), h_c.data(), N);
    auto gpu_end = std::chrono::high_resolution_clock::now();
    auto gpu_duration = std::chrono::duration_cast<std::chrono::microseconds>(gpu_end - gpu_start);

    if (!success) {
        std::cerr << "CUDA vector addition failed!" << std::endl;
        return 1;
    }

    // Verify results
    bool correct = true;
    for (int i = 0; i < N; i++) {
        if (std::abs(h_c[i] - h_c_cpu[i]) > 1e-5) {
            correct = false;
            std::cerr << "Mismatch at position " << i << ": GPU=" << h_c[i] 
                      << ", CPU=" << h_c_cpu[i] << std::endl;
            break;
        }
    }

    // Print results
    std::cout << "Vector addition of " << N << " elements\n";
    std::cout << "CPU time: " << cpu_duration.count() << " microseconds\n";
    std::cout << "GPU time: " << gpu_duration.count() << " microseconds\n";
    std::cout << "Results are " << (correct ? "correct" : "incorrect") << std::endl;

    return 0;
}