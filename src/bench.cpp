// #include <iostream>
// #include <chrono>
// #include <random>
// #include "Table.h"

// using namespace std;
// using namespace std::chrono;

// int main() {
//     cout << "===== MiniDB Benchmark =====" << endl;

//     // Create a table with id + age
//     Table users("users", {"id", "age"});
    
//     // Generate random ages between 18 and 60
//     random_device rd;
//     mt19937 gen(rd());
//     uniform_int_distribution<> dist(18, 60);

//     int N = 10000;
//     cout << "Inserting " << N << " records..." << endl;

//     auto start = high_resolution_clock::now();
//     for (int i = 1; i <= N; i++) {
//         users.insert({to_string(i), to_string(dist(gen))});
//     }
//     auto end = high_resolution_clock::now();
//     cout << "Insertion time: " 
//          << duration_cast<milliseconds>(end - start).count() << " ms\n";

//     // Range query (ages 25–30)
//     cout << "\nRunning range query (age 25–30)" << endl;

//     // Linear scan
//     // Linear scan
// start = high_resolution_clock::now();
// int countLinear = 0;
// for (auto &row : users.getAllRecords()) {
//     int age = stoi(row.values[1]);  // col0 = id, col1 = age
//     if (age >= 25 && age <= 30) countLinear++;
// }
// end = high_resolution_clock::now();


//     // Indexed scan (B+Tree)
//     start = high_resolution_clock::now();
//     vector<Record> indexed = users.rangeQuery("age", 25, 30);
//     end = high_resolution_clock::now();
//     cout << "B+Tree scan found " << indexed.size()
//          << " records in "
//          << duration_cast<milliseconds>(end - start).count() << " ms\n";

//     cout << "===== Benchmark Complete =====" << endl;
//     return 0;
// }
