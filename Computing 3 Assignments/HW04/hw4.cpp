/***********************************************
Author: <Tony Choma>
Date: <9-28-2020>
Purpose: <Zip code and bar code interpreter>
Sources of Help: <N/A>
Time Spent: <5 hours>
***********************************************/
#include <iostream>
#include <string>
using namespace std;

class ZipCode {
public:
    ZipCode(int zipCode) {
        this->zipCode = zipCode;
        this->barCode = convertToBar(zipCode);
    }
    ZipCode(string barCode) {
        this->barCode = barCode;
        this->zipCode = convertToZip(barCode);
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
    
    int convertToZip(string barCode) {
        int result = 0;
        string r = "";
        if (initialErrorCheck(barCode) == false) {
            for (int i = 1; i + 5 < barCode.length(); i += 5) {
                int index = 0;
                int oneCounter = 0;
                int value = 0;

                for (int j = i; (j < i + 5) && (i + 5 < barCode.length() - 2); j++) {
                    if (barCode[j] != '1' && barCode[j] != '0') {
                        cout << "ERROR::WRONG BARCODE::CAN ONLY CONTAIN '0' and '1'" << endl;
                    } 
                    if (oneCounter > 2) {
                        cout << "ERROR::TOO MANY 1's IN A BLOCK OF 5" << endl;
                    }
                    if (index == 0) {
                        if (barCode[j] == '1') {
                            oneCounter++;
                            value += 7;
                        }
                    } else if (index == 1) {
                        if (barCode[j] == '1') {
                            oneCounter++;
                            value += 4;
                        }
                    } else if (index == 2) {
                        if (barCode[j] == '1') {
                            oneCounter++;
                            value += 2;
                        }
                    } else if (index == 3) {
                        if (barCode[j] == '1') {
                            oneCounter++;
                            value++;
                        }
                    } else if (index == 4) {
                        if (barCode[j] == '1') {
                            oneCounter++;
                        }
                    }
                    index++;
                }
                if (value == 11) {
                    r += "0";
                }
                else {
                    r += to_string(value);
                }
            }
        }
        cout << r << endl;
        return result = stoi(r);
    }

    string convertToBar(int zipCode) {
        int index = 0;
        int zip[5] = { 0,0,0,0,0 };
        while (zipCode) {
            zip[index++] = zipCode % 10;
            zipCode /= 10;
        }

        string result = "1";
        int value = 0;
        for (int i = 0; i < 5; i++) {
            int oneCounter = 0;
            if (zip[i] == 0) {
                result += "11000";
            } else {
                if (7 <= zip[i] && oneCounter < 2) {
                    value += 7;
                    result += "1";
                    oneCounter++;
                }
                else {
                    result += "0";
                }
                if (4 + value <= zip[i] && oneCounter < 2) {
                    value += 4;
                    result += "1";
                    oneCounter++;
                }
                else {
                    result += "0";
                }
                if (2 + value <= zip[i] && oneCounter < 2) {
                    value += 2;
                    result += "1";
                    oneCounter++;
                }
                else {
                    result += "0";
                }
                if (1 + value <= zip[i] && oneCounter < 2) {
                    value++;
                    result += "1";
                    oneCounter++;
                }
                else {
                    result += "0";
                }
                if (value <= zip[i] && oneCounter < 2) {
                    result += "1";
                    oneCounter++;
                }
                else {
                    result += "0";
                }
            }
        }
        return result += "1";
    }

    bool initialErrorCheck(string barCode) {
        cout << barCode.length();
        cout << barCode[0] << barCode[barCode.length() - 1];
        if (barCode[0] != '1' || barCode[barCode.length() - 1] != '1') {
            cout << "ERROR::WRONG BARCODE::WRONG START/END CHARACTER" << endl;
            return true;
        } 
        return false;
    }
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

/*
Computing III -- COMP.2010 Honor Statement
The practice of good ethical behavior is essential for maintaining
good order in the classroom, providing an enriching learning
experience for students, and as training as a practicing computing
professional upon graduation. This practice is manifested in the
University’s Academic Integrity policy. Students are expected to
strictly avoid academic dishonesty and adhere to the Academic
Integrity policy as outlined in the course catalog. Violations will
be dealt with as outlined therein.
All programming assignments in this class are to be done by the
student alone. No outside help is permitted except the instructor and
approved tutors.
I certify that the work submitted with this assignment is mine and was
generated in a manner consistent with this document, the course
academic policy on the course website on Blackboard, and the UMass
Lowell academic code.
Date: 9-28-2020
Name: Tony Choma
*/