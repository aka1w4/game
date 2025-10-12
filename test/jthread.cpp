#include <iostream>
#include <thread>
#include <chrono>

void worker(std::stop_token st) {
    int i = 0;
    while (!st.stop_requested()) { // berhenti kalau diminta stop
        std::cout << "Worker loop " << i++ << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << "Worker berhenti\n";
}

int main() {
    std::jthread t(worker);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "Meminta worker berhenti...\n";
    t.request_stop(); // kasih sinyal stop ke worker

    // otomatis join di destructor
    return 0;
}
