#include "KeyTest.h"

void KeyTest::testCompareWithNotEqualKeys() {
    Key key1(10, 1);
    Key key2(8, 2);
    assert("1 should have been returned" && key1.compareTo(key2) == 1);
    assert("-1 should have been returned" && key2.compareTo(key1) == -1);
}


void KeyTest::testCompareWithEqualKeys() {
    Key key1(10, 2);
    Key key2(10, 1);
    assert("1 should have been returned" && key1.compareTo(key2) == 1);
    assert("-1 should have been returned" && key2.compareTo(key1) == -1);
}

void KeyTest::testCompareWithSameKey() {
    Key key1(10, 2);
    assert("1 should have been returned" && key1.compareTo(key1) == 0);
}

int main(){
    KeyTest test;
    test.testCompareWithNotEqualKeys();
    test.testCompareWithNotEqualKeys();
}