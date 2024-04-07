
#include <memory>
#include <cstdint>

using namespace std;

class Test {
public:

    Test(unique_ptr<uint8_t[]> &data) {
        bytes = std::move(data);
    }

    ~Test() {}

private:
    unique_ptr<uint8_t[]> bytes;
};

int main() {
    std::unique_ptr<uint8_t[]> data = std::make_unique<uint8_t[]>(10);
    std::shared_ptr<Test> foo = std::make_shared<Test>(data);
    return 0;
}