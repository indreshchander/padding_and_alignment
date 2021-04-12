#include <iostream> 
#include <fstream> 
#include <cstring> 
 
struct SimpleStruct { 
    int i; 
    double d; 
}; 
 
int main() { 
    const SimpleStruct s{1337, 42.0}; 
    std::cout << sizeof(SimpleStruct) << std::endl; 
     
    { // Write as-is (with padding) 
    std::ofstream ofs{"out_padded.bin", std::ios::binary}; 
    ofs.write(reinterpret_cast<const char*>(&s), sizeof(s)); 
    } 
 
    { // Write per-field (more compact, no padding) 
    std::ofstream ofs{"out_compact.bin", std::ios::binary}; 
    ofs.write(reinterpret_cast<const char*>(&s.i), sizeof(s.i)); 
    ofs.write(reinterpret_cast<const char*>(&s.d), sizeof(s.d)); 
    } 
     
 
    { // Read as-is (with padding) 
    SimpleStruct s2; 
    std::memset(&s2,0, sizeof(s2)); 
         
    std::ifstream ifs{"out_padded.bin", std::ios::binary}; 
    ifs.read(reinterpret_cast<char*>(&s2), sizeof(SimpleStruct)); 
         
    std::cout << "Read: i=" << s2.i << " d=" << s2.d << std::endl; 
    } 
         
    { // Read per-field (more compact, no padding) 
    SimpleStruct s2; 
    std::memset(&s2,0, sizeof(s2)); 
    std::ifstream ifs{"out_compact.bin", std::ios::binary}; 
    ifs.read(reinterpret_cast<char*>(&s2.i), sizeof(SimpleStruct::i)); 
    ifs.read(reinterpret_cast<char*>(&s2.d), sizeof(SimpleStruct::d)); 
 
    // Don't do: 
    // ifs.read(reinterpret_cast<char*>(&s2) + sizeof(SimpleStruct::i),  
    //          sizeof(SimpleStruct::d)); 
    // Because this will not be correctly aligned 
 
    std::cout << "Read: i=" << s2.i << " d=" << s2.d << std::endl; 
    } 
     
    return 0; 
} 
