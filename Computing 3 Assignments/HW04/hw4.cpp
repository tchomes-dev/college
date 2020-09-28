#include <iostream>
#include <string>
using namespace std;

class ZipCode {
public:
    ZipCode(int zipCode) {
        this->zipCode = zipCode;
    }
    ZipCode(string barCode) {
        this->barCode = barCode;
    }
    int getZipCode() {
        return zipCode;
    }
    string getBarCode() {
        return barCode;
    }
private:
    int zipCode = 0;
    string barCode = "";
    const char code[5] = {'7', '4', '2', '1', '0'};


};

int main(int argc, char * argv[]) {
    ZipCode zip(99504),
    zip2("100101010011100001100110001"),
    zip3(12345),
    zip4(67890);
    
    cout << zip.getZipCode() << "'s bar code is '"
    << zip.getBarCode() << "'" << endl;
    cout << zip2.getZipCode() << "'s bar code is '"
    << zip2.getBarCode() << "'" << endl;
    cout << zip3.getZipCode() << "'s bar code is '"
    << zip3.getBarCode() << "'" << endl;
    cout << zip4.getZipCode() << "'s bar code is '"
    << zip4.getBarCode() << "'" << endl;
    
    cout << endl;
    
    // Test a range of values by first constructing a zip code
    // with an integer, then retrieving the bar code and using
    // that to construct another ZipCode.
    int zip_int = 0;
    for (int i = 0; i < 25; i++)
    {
        // Make an aribrary 5-digit zip code integer, and use it
        // to construct a ZipCode
        int five_digit_zip = (zip_int * zip_int) % 100000;
        ZipCode z1(five_digit_zip);
        
        // Construct a second ZipCode from the first's bar code
        string z1_barcode = z1.getBarCode();
        ZipCode z2(z1_barcode);
        
        cout.width(3);
        cout << (i + 1) << ": ";
        cout.width(5);
        cout << z2.getZipCode() << " has code '"
        << z1_barcode << "'";
        
        if ((z1_barcode == z2.getBarCode()) &&
            (z1.getZipCode() == z2.getZipCode()) &&
            (z2.getZipCode() == five_digit_zip))
        {
            cout << " [OK]" << endl;
        }
        else
        {
            cout << " [ERR]" << endl;
        }
        
        // Increment the test value arbitrarily
        zip_int += (233 + zip_int % 7);
    }
    cout << endl;
    
    // Test some error conditions. This test assumes that
    // ZipCode will simply set its value to a flag that indicates
    // an error, and will not exit the program.
    int BAD_ZIP_COUNT = 2;
    string bad_zips[][2] = {
        { "100101010011100001100110000", "bad start/end character" },
        { "100101010011100001100110021", "bad digit" },
    };
    for (int i = 0; i < BAD_ZIP_COUNT; i++)
    {
        cout << "Testing: " << bad_zips[i][1] << " " << bad_zips[i][0] << endl;
        ZipCode test(bad_zips[i][0]);
        cout << endl;
    }
    
    cout << "Enter a character to quit." << endl;
    char c;
    cin >> c;
    return 0;
}