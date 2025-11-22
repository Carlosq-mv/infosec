#include <iostream>
#include <cassert>

using namespace std;

int maj(int a, int b, int c);
void shift(vector<uint8_t> &register_, uint8_t feedback_bit);
vector<uint8_t> parse_binary_str(const string &register_);
string print_register(const vector<uint8_t> &register_);

int main()
{
    // get register X, Y & Z from user
    string reg_x, reg_y, reg_z;
    cout << "Input a 19 bit binary string for Register X: ";
    cin >> reg_x;
    assert(reg_x.size() == 19);

    cout << "Input a 22 bit binary string for Register Y: ";
    cin >> reg_y;
    assert(reg_y.size() == 22);

    cout << "Input a 23 bit binary string for Register Z: ";
    cin >> reg_z;
    assert(reg_z.size() == 23);

    // 1. Create Registers
    vector<uint8_t> register_x = parse_binary_str(reg_x); // size 19
    vector<uint8_t> register_y = parse_binary_str(reg_y); // size 22
    vector<uint8_t> register_z = parse_binary_str(reg_z); // size 23

    // vector<uint8_t> register_x = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};             // size 19
    // vector<uint8_t> register_y = {1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1};    // size 22
    // vector<uint8_t> register_z = {1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0}; // size 23

    vector<uint8_t> key_stream;

    while (key_stream.size() < 32)
    {
        // 2. Get the 'special bits'
        uint8_t bit_8_x = register_x[8];
        uint8_t bit_10_y = register_y[10];
        uint8_t bit_10_z = register_z[10];

        // 3. Calculate the majority between the special bits
        int m = maj(bit_8_x, bit_10_y, bit_10_z);

        // 4. Shift register
        if (bit_8_x == m)
        {
            // Calculate feedback bit
            uint8_t feedback_bit = (register_x[13] ^ register_x[16] ^ register_x[17] ^ register_x[18]) & 1;

            // Shift register
            shift(register_x, feedback_bit);
        }

        if (bit_10_y == m)
        {
            // Calculate feedback bit
            uint8_t feedback_bit = (register_y[20] ^ register_y[21]) & 1;

            // shift register
            shift(register_y, feedback_bit);
        }

        if (bit_10_z == m)
        {
            // Calculate feedback bit
            uint8_t feedback_bit = (register_z[7] ^ register_z[20] ^ register_z[21] ^ register_z[22]) & 1;

            // shift register
            shift(register_z, feedback_bit);
        }

        // 5. Calculate bit for key stream
        uint8_t key_bit = (register_x[18] ^ register_y[21] ^ register_z[22]) & 1;
        key_stream.push_back(key_bit);
    }
    // 6. Display the keysteam
    cout << "Computed Key Stream: ";
    for (const int &key_bit : key_stream)
    {
        cout << key_bit;
    }

    // Display contents of every register
    cout << "\nContents of every register: \n";

    cout << "Register X: " << print_register(register_x) << endl;
    cout << "Register Y: " << print_register(register_y) << endl;
    cout << "Register Z: " << print_register(register_z) << endl;

    return 0;
}

int maj(int a, int b, int c)
{
    // From: https://stackoverflow.com/questions/29892243/majority-function-in-c-using-3-uint8-t
    return (a & b) | (b & c) | (c & a);
}

void shift(vector<uint8_t> &register_, uint8_t feedback_bit)
{
    for (int i = register_.size() - 1; i > 0; i--)
    {
        register_[i] = register_[i - 1];
    }

    register_[0] = feedback_bit;
}

vector<uint8_t> parse_binary_str(const string &register_)
{
    vector<uint8_t> vec;
    for (const char &ch : register_)
    {
        assert(ch == '1' || ch == '0');
        vec.push_back(ch - '0');
    }
    return vec;
}

string print_register(const vector<uint8_t> &register_)
{
    string res;
    for (const int &bit : register_)
    {
        res += bit + '0';
    }
    return res;
}