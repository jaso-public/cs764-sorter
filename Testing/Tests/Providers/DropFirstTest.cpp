#include <cassert>

void testDropWithCount10() {
    auto records = generateInOrder(10);
    ArrayProvider generator("name", records);
    Witness lower(&generator);
    DropFirst dropper(&lower);
    for (int i = 0; i < 9; i++){
        shared_ptr<Record> ptr = dropper.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record>  ptr = dropper.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

void testDropWithCount20() {
    auto records = generateInOrder(20);
    ArrayProvider generator("name", records);
    Witness lower(&generator);
    DropFirst dropper(&lower);
    for (int i = 0; i < 19; i++){
        shared_ptr<Record>  ptr = dropper.next();
        assert("Next should have existed" && ptr != nullptr );
    }
    shared_ptr<Record> ptr = dropper.next();
    assert("Next should have given a null pointer" && ptr == nullptr );
}

int main(){
    testDropWithCount10();
    testDropWithCount20();
}