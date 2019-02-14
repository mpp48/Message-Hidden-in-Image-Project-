//Author: Mark P.
//Last Updated: 2/9/19
//Version 1.0
#include <string>
#include <bitset>
#include <iostream>
#include <sstream>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp> 

using namespace std;
using namespace cv;



string strToBinary(string s)
{
	string bString = "";
	for (char& c : s) {
		bString += bitset<8>(c).to_string();
	}
	return bString;
}

string binaryToStr(string d) {
	stringstream sstream(d);
	string output;

	while (sstream.good()) {
		bitset<8> bits;
		sstream >> bits;
		char c = char(bits.to_ulong());
		output += c;
	}

	return output;
}



int main()
{

	string ans;
	string ans2;
	string s;
	string d;

	Mat image1, image2;

	cout << "encode or decode an image" << endl;
	cin >> ans;

	if (ans == "encode") {
		//encode
				
		//Read the image
		image1 = imread("C:\\Users\\Mark\\Pictures\\blue.png");


		if (!image1.data) {
			cout << "No image exists" << endl;
		}
		else {
			cout << "Image is good to go" << endl;
		}

		//convert string to binary
		cout << "What is your message to be encoded:" << endl;
		cin >> s;
		string str = strToBinary(s);
		int len = str.length();
		cout << str << endl;
		cout << len << endl;

		for (int a = 0; a < 1; a++) {
			int i = 0;
			
			if (i == 1) {
				break;
			}
			else {
				for (int b = 0; b < len; b++) {

					if (str[b] == '0' ) {
						image1.at<Vec3b>(a, b)[0] = 255;
						image1.at<Vec3b>(a, b)[1] = 255;
						image1.at<Vec3b>(a, b)[2] = 255;
					}
					else  {
						image1.at<Vec3b>(a, b)[0] = 0;
						image1.at<Vec3b>(a, b)[1] = 0;
						image1.at<Vec3b>(a, b)[2] = 0;
					}
					i++;
				}
			}
		}


		imwrite("C:\\Users\\Mark\\Pictures\\blue_mod.png", image1);
		//image2 = imread("C:\\Users\\Mark\\Pictures\\blue_mod.png");

		namedWindow("Modified Image");
		imshow("Modified Image", image1); 
		waitKey(5000);


	}

	else if (ans == "decode") {
		//decode
		//Read the image
		image2 = imread("C:\\Users\\Mark\\Pictures\\blue_mod.png");
		if (!image2.data) {
			cout << "No image exists" << endl;
		}
		else {
			cout << "Image is good to go" << endl;
		}
		// Read for specfic colors that translate into either 1s or 0s and translate that back into a string
		for (int y = 0; y < image2.rows; y++) {
			int i = 0;
			if (i == 1) {
				break;
			}
			else {
				for (int x = 0; x < image2.cols; x++) {
					Vec3b color = image2.at<Vec3b>(Point(x, y));

					if (color[0] == 255 && color[1] == 255 && color[2] == 255){
						d += '0';
					}
					else if (color[0] == 0 && color[1] == 0 && color[2] == 0) {
						d += '1';
					}
				}
			}
		}

		cout << binaryToStr(d) << endl;
	}
	return 0;
}
