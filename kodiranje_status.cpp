#include<string>
#include<iostream>
#include<math.h>
using namespace std;

string packet(double X_kor, double Y_kor, int code){
	string binary="";
	
	X_kor>=0? binary.append("0"): binary.append("1");
	X_kor=fabs(X_kor);
	cout<<X_kor<<endl;
	int rem=0;
	
	for(int i=7;i>=0;i--){
		rem=(int)X_kor/(int)(pow(2,i));
		X_kor-=rem*pow(2,i);
		cout<<rem<<endl;
		
		rem>0? binary.append("1"): binary.append("0");
	}
	cout<<endl;
	rem=0;
	for(int i=-1;i>=-27;i--){
		rem=X_kor/(pow(2,i));
		X_kor-=rem*pow(2,i);
		cout<<rem<<endl;
		
		rem>0? binary.append("1"): binary.append("0");
	}
	
	cout<<binary<<endl;
	return binary;
}

int main(){
	double X_kor=179.12345678;
	double Y_kor= 89.12345678;
	int code=3;  // [0 15]  4bita
	packet(X_kor, Y_kor, code);
	
}


