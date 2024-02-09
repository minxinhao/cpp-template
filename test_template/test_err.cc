#include <iostream>
#include <system_error>

int main() {
    std::error_code ec = std::make_error_code(std::errc{});
    
    if (!ec) {
        std::cout << "No error" << std::endl;
    } else {
        std::cout << "Error: " << ec.message() << std::endl;
    }
    
    return 0;
}