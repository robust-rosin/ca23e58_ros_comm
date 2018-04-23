#include <boost/thread/thread.hpp>
#include <gtest/gtest.h>

#include "ros/topic_manager.h"

class Test_ca23e58
{
public:
    Test_ca23e58();
    void thread1();
    void thread2();

    int result1_;
    int result2_;
};

Test_ca23e58::Test_ca23e58()
: result1_(0),
  result2_(0)
{}

void Test_ca23e58::thread1()
{
    result1_ = rosin_robust::flag_value();
}

void Test_ca23e58::thread2()
{
    result2_ = rosin_robust::flag_value();
}

bool testDCLP()
{
    Test_ca23e58 tester;
    boost::thread thread1 = boost::thread(&Test_ca23e58::thread1, &tester);
    boost::thread thread2 = boost::thread(&Test_ca23e58::thread2, &tester);
    thread1.join();
    thread2.join();
    return tester.result1_ == tester.result2_;
}

TEST(TestSuite, doubleCheckedLocking)
{
    EXPECT_TRUE(testDCLP());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
