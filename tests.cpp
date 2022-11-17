// tests.cpp
// Seyfal Sultanov
// Mac OS Monterey 12.2.1 (21D62)
// VS Code Version: 1.72.2 (Universal)
// CS 251 - Data Structures
// Program 5 - mymap
// Prof. Adam Koehler

//~ test suite for mymap

#include <gtest/gtest.h>
#include "mymap.h"
#include "myrandom.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <map>

//!!! SSULTA24 IS ME

// ssulta24
// default constructor Test and size Test
TEST(mymap, defaultConstructor)
{

    // create a mymap
    mymap<int, int> m;

    // check if the size is 0
    EXPECT_EQ(m.Size(), 0);
}

// ssulta24
// put Test and size Test
TEST(mymap, put)
{

    // create a mymap
    mymap<int, int> m;

    // put a key value pair
    int arr[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) 
    {
        m.put(arr[i], arr[i]);
    }
    EXPECT_EQ(m.Size(), 3);
}

// ssulta24
// get Test
TEST(mymap, get)
{

    // create a mymap
    mymap<int, int> m;

    // put a key value pair
    int arr[] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
    {
        m.put(arr[i], arr[i]);
    }
    // get the value of the key
    EXPECT_EQ(m.get(1), 1);
    EXPECT_EQ(m.get(2), 2);
    EXPECT_EQ(m.get(3), 3);
    EXPECT_EQ(m.get(4), 0);
}

// ssulta24
// contains Test
TEST(mymap, containsKey)
{

    // create a mymap
    mymap<int, int> m;
 
    int arr[] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
    {
        m.put(arr[i], arr[i]);
    }
    // check if the key is in the map
    EXPECT_EQ(m.contains(1), true);
    EXPECT_EQ(m.contains(2), true);
    EXPECT_EQ(m.contains(3), true);
    EXPECT_EQ(m.contains(4), false);
}

// ssulta24
// toString Test
TEST(mymap, tostr)
{

    // create a mymap
    mymap<int, int> m;

    int arr[] = {3, 2, 1};
    for (int i = 0; i < 3; i++)
    {
        m.put(arr[i], arr[i]);
    }
    string ans = "key: 1 value: 1\nkey: 2 value: 2\nkey: 3 value: 3\n";
    // check if the string is correct
    EXPECT_EQ(ans, m.toString());
}

// ssulta24
// operator[] Test
TEST(mymap, operator)
{

    // create a mymap
    mymap<int, int> m;

    int arr[] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
    {
        m.put(arr[i], arr[i]);
    }
    // check if the operator works
    EXPECT_EQ(m[1], 1);
    EXPECT_EQ(m[2], 2);
    EXPECT_EQ(m[3], 3);
    EXPECT_EQ(m[4], 0);
}

// ssulta24
// stress test combining all the tests above
TEST(mymap, stressTest)
{

    // create a mymap
    mymap<int, int> m;

    vector<int> arr;

    for (int i = 0; i < 10000; i++)
    {   
        // generate a random number
        int num = randomInteger(0, 10000);
        // append num to arr
        arr.push_back(num);
        // put the key value pair
        m.put(i, num);
    }

    for (int i = 0; i < 10000; i++)
    {
        // check if the key is in the map
        EXPECT_EQ(m[i], arr[i]);
    }

    for (int i = 0; i < 10000; i++)
    {
        // check if the key is in the map
        EXPECT_EQ(m.contains(i), true);
    }

    for (int i = 0; i < 10000; i++)
    {
        // check if the key is in the map
        EXPECT_EQ(m.get(i), arr[i]);
    }

    EXPECT_EQ(m.Size(), 10000);
}

// ssulta24
// clear Test
TEST(mymap, clear)
{

    // create a mymap
    mymap<int, int> m;

    int arr[] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
    {
        m.put(arr[i], arr[i]);
    }
    // clear the map
    m.clear();
    // check if the size is 0
    EXPECT_EQ(m.Size(), 0);
}

// ssulta24
// clear stress test
TEST(mymap, clearStressTest)
{

    // create a mymap
    mymap<int, int> m;

    for (int i = 0; i < 10000; i++)
    {
        int num = randomInteger(0, 10000);
        m.put(i, num);
    }
    // clear the map
    m.clear();
    // check if the size is 0
    EXPECT_EQ(m.Size(), 0);
}

// ssulta24
// toString stress test
TEST(mymap, toStringStressTest)
{

    // create a mymap
    mymap<int, int> m;

    for (int i = 0; i < 10000; i++)
    {   
        // generate a random number
        int num = randomInteger(0, 10000);
        // put the key value pair
        m.put(i, num);
    }

    string ans = "";
    for (int i = 0; i < 10000; i++)
    {
        // append the string
        ans += "key: " + to_string(i) + " value: " + to_string(m.get(i)) + "\n";
    }

    // check if the string is correct
    EXPECT_EQ(ans, m.toString());
}

// ssulta24
// operator[] stress test
TEST(mymap, operatorStressTest)
{

    // create a mymap
    mymap<int, int> m;

    for (int i = 0; i < 10000; i++)
    {   
        // generate a random number
        int num = randomInteger(0, 10000);  
        // put the key value pair
        m.put(i, num);
    }

    for (int i = 0; i < 10000; i++)
    {
        // check if the operator works
        EXPECT_EQ(m[i], m.get(i));
    }
}

// ssulta24
// put stress test
TEST(mymap, putStressTest)
{

    // create a mymap
    mymap<int, int> m;

    // put a key value pair
    for (int i = 0; i < 10000; i++)
    {
        // generate a random number
        int num = randomInteger(0, 10000);
        m.put(i, num);
    }

    for (int i = 0; i < 10000; i++)
    {
        // check if the key is in the map
        EXPECT_EQ(m.get(i), m[i]);
    }
}

// ssulta24
// contains stress test
TEST(mymap, containsStressTest)
{

    // create a mymap
    mymap<int, int> m;

    for (int i = 0; i < 10000; i++)
    {
        // generate a random number
        int num = randomInteger(0, 10000);
        m.put(i, num);
    }

    for (int i = 0; i < 10000; i++)
    {   
        // check if the key is in the map
        EXPECT_EQ(m.contains(i), true);
    }
}

// ssulta24
// get stress test
TEST(mymap, getStressTest)
{

    // create a mymap
    mymap<int, int> m;

    for (int i = 0; i < 10000; i++)
    {
        // generate a random number
        int num = randomInteger(0, 10000);
        m.put(i, num);
    }

    for (int i = 0; i < 10000; i++)
    {
        // check if the key is in the map
        EXPECT_EQ(m.get(i), m[i]);
    }
}

// ssulta24
// other mymap constructor test
TEST(mymap, otherConstructor)
{

    // create a mymap
    mymap<int, int> m;

    int arr[] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
    {
        m.put(arr[i], arr[i]);
    }

    // create a new mymap
    mymap<int, int> m2(m);

    // check the sizes of the two maps
    EXPECT_EQ(m.Size(), 3);
    EXPECT_EQ(m2.Size(), 3);
    EXPECT_EQ(m.Size(), m2.Size());

    for (int i = 0; i < 3; i++)
    {
        // check if the key is in the map
        EXPECT_EQ(m2[i], m[i]);
    }
}

// ssulta24
// other mymap constructor stress test
TEST(mymap, otherConstructorStressTest)
{

    // create a mymap
    mymap<int, int> m;

    for (int i = 0; i < 10000; i++)
    {
        // generate a random number
        int num = randomInteger(0, 10000);
        m.put(i, num);
    }

    // create a new mymap
    mymap<int, int> m2(m);

    for (int i = 0; i < 10000; i++)
    {   
        // check if the key is in the map
        EXPECT_EQ(m2[i], m[i]);
    }
}

// ssulta24
// copy operator test
TEST(mymap, copyOperator)
{

    // create a mymap
    mymap<int, int> m;

    int arr[] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
    {
        m.put(arr[i], arr[i]);
    }

    mymap<int, int> m2; // create a new mymap
    m2 = m; // copy the map

    for (int i = 0; i < 3; i++)
    {
        EXPECT_EQ(m2[i], m[i]);
    }
}

// ssulta24
// copy operator stress test
TEST(mymap, copyOperatorStressTest)
{

    // create a mymap
    mymap<int, int> m;

    for (int i = 0; i < 10000; i++)
    {
        int num = randomInteger(0, 10000);
        m.put(i, num);
    }

    mymap<int, int> m2;
    m2 = m;

    for (int i = 0; i < 10000; i++)
    {
        EXPECT_EQ(m2[i], m[i]);
    }
}

// ssulta24
// toVector test
TEST(mymap, toVector1)
{

    // create a mymap
    mymap<int, int> m;
    vector<pair<int, int>> ans;

    int arr[] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
    {
        m.put(arr[i], arr[i]); // put the key value pair
        ans.push_back(make_pair(arr[i], arr[i])); // put the key value pair in the vector
    }
    sort(ans.begin(), ans.end()); // sort the vector

    vector<pair<int, int>> v = m.toVector(); // create a vector from the map
 
    EXPECT_EQ(ans, v); // check if the vectors are equal
}

// ssulta24
// toVector stress test
TEST(mymap, toVectorStressTest)
{

    // create a mymap
    mymap<int, int> m; // create a mymap
    vector<pair<int, int>> ans;  // create a vector

    for (int i = 0; i < 10000; i++)
    {
        int num = randomInteger(0, 10000); // generate a random number
        m.put(i, num); // put the key value pair
        ans.push_back(make_pair(i, num)); // put the key value pair in the vector
    }
    sort(ans.begin(), ans.end()); // sort the vector

    vector<pair<int, int>> v = m.toVector(); // create a vector from the map

    EXPECT_EQ(ans, v); // check if the vectors are equal
}

// netid: rshah268
// Copy and Clear Stress Test
TEST(mymap, Copy)
{

    // Create two mymaps m1 and m2
    mymap<int, int> m1;
    mymap<int, int> m2;
    int n = 10000;

    for (int i = 0; i < n; i++)
    {

        // Generate two random numbers
        int key = randomInteger(0, 100000);
        int val = randomInteger(0, 100000);

        // Insert them in map1
        m1.put(key, val);

        // Insert different elements in map2
        if (i % 2)
        {
            m2.put(val, key);
        }
    }

    // At this point they must be unequal
    ASSERT_NE(m1.Size(), m2.Size());

    // Set map2 equals to map1
    m2 = m1;

    // Both should be the same size and contain the same elements
    ASSERT_EQ(m1.Size(), m2.Size());
    ASSERT_EQ(m1.toString(), m2.toString());

    // Clear map1
    m1.clear();

    // Now they are unequal again
    ASSERT_NE(m1.Size(), m2.Size());
    // Map1 must be empty
    ASSERT_EQ(m1.Size(), 0);
}

// netid: tkoope2
// Copy Operator test <int, int>
TEST(Operator, IICopyP)
{
    mymap<int, int> m;
    mymap<int, int> m2;

    // Populate 1 and 2
    int key, value, high, low, modOp;
    int arrSize = rand() % 100;

    string mOriginal, m2Original;

    // Populate m
    high = 500;
    low = 1;
    modOp = (high - (low + 1)) + low;
    for (int i = 0; i < arrSize; i++)
    {
        key = rand() % modOp;
        value = rand() % modOp;
        m.put(key, value);
    }

    // Populate m2
    high = 1000;
    low = 500;
    modOp = (high - (low + 1)) + low;
    for (int i = 0; i < arrSize; i++)
    {
        key = rand() % modOp;
        value = rand() % modOp;
        m2.put(key, value);
    }

    m = m2;

    EXPECT_EQ(m.Size(), m2.Size()) << "IIEquals; size difference\n";
    EXPECT_NE(mOriginal, m.toString()) << "m should not still equal original\n";
    EXPECT_EQ(m2.toString(), m.toString()) << "toString() !=\n"
                                           << "M:\n"
                                           << m.toString() << "\nM2:\n"
                                           << m2.toString() << endl;
    ;
}

// tkoope2
// Copy Constructor
TEST(copyConstructor, IIConCopy)
{
    mymap<int, int> m;
    map<int, int> correct;
    vector<int> keys;
    int key;
    int val;
    int arrSize = 15;
    int high = 500, low = 0;
    int modOp = (high - (low + 1)) + low;

    // Populate
    for (int i = 0; i < arrSize; i++)
    {
        key = rand() % modOp;
        val = rand() % modOp;

        keys.push_back(key);

        m.put(key, val);
        correct[key] = val;
    }

    EXPECT_EQ(m.Size(), correct.size()) << "mymap != map\n";

    mymap<int, int> m2 = m;
    EXPECT_EQ(m.toString(), m2.toString()) << "Copy operator formating off\n";
    EXPECT_EQ(m2.Size(), correct.size()) << "M2's size does not match correct's\n";

    // Both have the same return value on keys
    int compA;
    int compB;
    for (auto &k : keys)
    {
        compA = m2[k];
        compB = correct[k];
        EXPECT_EQ(compA, compB) << compA << " != " << compB << "\t Incorrect Copy Constructor\n";
    }
}

// netid: msiddi73
// Testing Put with random int key (Testing Size and toString)
TEST(Put, randomIntInt)
{

    map<int, int> m;
    mymap<int, int> mymap;
    stringstream s;

    int randomKey = 0;
    int randomValue = 0;
    int randomSize = 0;
    string test;

    for (int i = 0; i < 35; i++)
    {

        test = "";
        s.str("");

        randomSize = randomInteger(1, 50);

        for (int p = 0; p < randomSize; p++)
        {

            randomKey = randomInteger(0, 100);
            randomValue = randomInteger(0, 100);

            m[randomKey] = randomValue;
            mymap.put(randomKey, randomValue);
        }

        for (auto const &x : m)
        {
            s << "key: " << x.first << " value: " << x.second << "\n";
        }

        test = mymap.toString();

        ASSERT_EQ(mymap.Size(), m.size());
        ASSERT_EQ(test, s.str());

        mymap.clear();
        m.clear();
    }
}

// netid: msiddi73
// Testing put with random char key (Testing Size and toString)
TEST(Put, randomCharInt)
{

    map<char, int> m;
    mymap<char, int> mymap;
    stringstream s;

    char randomKey = 0;
    int randomValue = 0;
    int randomSize = 0;
    string test;

    for (int i = 0; i < 35; i++)
    {

        test = "";
        s.str("");

        randomSize = randomInteger(1, 50);

        for (int p = 0; p < randomSize; p++)
        {

            randomKey = randomInteger(65, 90); // get uppercase characthers
            randomValue = randomInteger(0, 100);

            m[randomKey] = randomValue;
            mymap.put(randomKey, randomValue);
        }

        for (auto const &x : m)
        {
            s << "key: " << x.first << " value: " << x.second << "\n";
        }

        test = mymap.toString();

        ASSERT_EQ(mymap.Size(), m.size());
        ASSERT_EQ(test, s.str());

        mymap.clear();
        m.clear();
    }
}

// netid: lsasu2
// Test for operator[] on already balanced tree.
TEST(mymap, operatorBrackets)
{
    mymap<int, string> test;
    map<int, string> omap;
    int n = 10;
    int arr[] = {40, 25, 60, 18, 35, 80, 30, 38, 50, 70};

    for (int i = 0; i < n; i++)
    {
        string value = "MAX: " + to_string(randomInteger(0, 40));
        test.put(arr[i], value);
        omap.emplace(arr[i], value);
    }
    for (int i = 0; i < n; i++)
    {
        ASSERT_EQ(test[arr[i]], omap[arr[i]]);
    }

    // Value not in map
    for (int i = 0; i < n; i++)
    {
        ASSERT_EQ(test[i * 1000], "");
        ASSERT_EQ(test.Size(), n + i + 1);
    }

    // Duplicate values
    for (int i = 0; i < n; i++)
    {
        string value = "MAX: " + to_string(randomInteger(0, 40));
        test.put(arr[i], value);
        omap[arr[i]] = value;
    }
    for (int i = 0; i < n; i++)
    {
        ASSERT_EQ(test[arr[i]], omap[arr[i]]);
    }
}

// from pdf document provided, Adam Koehler
// Final Test
TEST(final, FinalTest)
{
    mymap<int, int> mapMine;
    map<int, int> mapSol;
    int n = 1000000;
    for (int i = 1; i <= n; i++)
    {
        int key = randomInteger(0, 10000);
        int val = randomInteger(0, 10000);
        mapMine.put(key, val);
        mapSol[key] = val;
    }
    EXPECT_EQ(mapMine.Size(), mapSol.size());
    stringstream solution("");
    for (auto e : mapSol)
    {
        solution << "key: " << e.first << " value: " << e.second << endl;
        EXPECT_TRUE(mapMine.contains(e.first));
        EXPECT_EQ(mapMine.get(e.first), e.second);
    }
    EXPECT_EQ(mapMine.toString(), solution.str());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    // run toVector test
    return RUN_ALL_TESTS();
}