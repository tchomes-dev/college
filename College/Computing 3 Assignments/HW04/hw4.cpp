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
    /// <summary>
    /// Reads a barcode and translates it into a zip code
    /// </summary>
    /// <param name="barCode"></param>
    /// <returns>A (integer) zip code that is equivalent to the inputted bar code</returns>
    int convertToZip(string barCode) {
        int result = 0;
        string r = "";
        if (initialErrorCheck(barCode) == false) {
            for (int i = 1; i + 5 < barCode.length(); i += 5) {
                int index = 0;
                int oneCounter = 0;
                int value = 0;

                for (int j = i; (j < i + 5) && (i + 5 < barCode.length()); j++) {
                    //checks if the barcode has any values that aren't '1' or '0'
                    if (barCode[j] != '1' && barCode[j] != '0') {
                        cout << "WRONG BARCODE::CAN ONLY CONTAIN '0' and '1'" << endl;
                    } 
                    //checks if in a segment of 5 theres more than 2 '1's 
                    if (oneCounter > 2) {
                        cout << "TOO MANY 1's IN A BLOCK OF 5" << endl;
                    }
                    //-------------------------
                    //Checks the value at barcode[i] and depending on the index in a subsegment of 5 
                    //the if conditionals will either add a '1' or '0'
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
                //if the resulting value is 11 then it will add a '0'
                if (value == 11) {
                    r += "0";
                }
                else {
                    r += to_string(value);
                }
            }
        }
        else {
            return 0;
        }
        return result = stoi(r);
    }
    /// <summary>
    /// Reads a zip code and translates it into a bar code
    /// </summary>
    /// <param name="zipCode"></param>
    /// <returns>A (string) bar code that is equivalent to the inputted zip code</returns>
    string convertToBar(int zipCode) {
        int index = 4;
        int zip[5] = { 0,0,0,0,0 };
        //puts zipcode into an array
        while (zipCode) {
            zip[index--] = zipCode % 10;
            zipCode /= 10;
        }

        string result = "1";
        //goes through the array
        for (int i = 0; i < 5; i++) {
            int value = 0;
            int oneCounter = 0;
            if (zip[i] == 0) {
                result += "11000";
            } else {
                //checks if zip[i] is >= 7 and one counter is < 2
                if (7 <= zip[i] && oneCounter < 2) {
                    value += 7;
                    result += "1";
                    oneCounter++;
                }
                else {
                    result += "0";
                }
                //checks if current value + 4 is <= zip[i] and adds a '1' or '0' to the barcode respectively
                if (4 + value <= zip[i] && oneCounter < 2) {
                    value += 4;
                    result += "1";
                    oneCounter++;
                }
                else {
                    result += "0";
                }
                //checks if current value + 2 is <= zip[i] and adds a '1' or '0' to the barcode respectively
                if (2 + value <= zip[i] && oneCounter < 2) {
                    value += 2;
                    result += "1";
                    oneCounter++;
                }
                else {
                    result += "0";
                }
                //checks if current value + 1 is <= zip[i] and adds a '1' or '0' to the barcode respectively
                if (1 + value <= zip[i] && oneCounter < 2) {
                    value++;
                    result += "1";
                    oneCounter++;
                }
                else {
                    result += "0";
                }
                //checks if there needs to be a '1' or '0' added to a segment of 5
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
    
    /// <summary>
    /// checks if the first or last numbers are incorrect
    /// </summary>
    /// <param name="barCode"></param>
    /// <returns>Either true or false if the bar code has a bad start/end number</returns>
    bool initialErrorCheck(string barCode) {
        if (barCode[0] != '1' || barCode[barCode.length() - 1] != '1') {
            cout << "WRONG BARCODE::WRONG START/END CHARACTER" << endl;
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