#include<iostream>
#include<string>
#include<algorithm>
#include<bits/stdc++.h>
using namespace std;

class BigInt{
public:
	string s;
	int neg;

	BigInt(string a=""){
		s="";

		if(a[0]=='-')neg=1;//checking neg -100 100 +100
		else neg=0;
		
		int p=0;
		if(a[p]=='+' || a[p]=='-')p++;//eliminating the sign term from the string
		long long n=a.size();
        while(a[p]=='0' and p<n-1)p++;
		while(p<n)s+=a[p++];
	}
	BigInt(long long a){
		if(a>=0)this->neg=0;
		else{
			this->neg=1;
			a*=-1;
		}

		s="";
		if(a==0)s+='0';
		while(a>0){
			int dig=a%10;
			a=a/10;
			s+=('0'+dig);
		}
		reverse(s.begin(),s.end());
	}
	string to_String(){
		string ans="";
		if(this->neg)ans+='-';
		return ans+this->s;
	}
    string add(string a,string b){
    	int n1=a.size();
    	int n2=b.size();
    	int i=n1-1;
    	int j=n2-1;
    	string ans="";
    	int carry=0;
    	while(i>=0 && j>=0){
             int d1=a[i]-'0';
             int d2=b[j]-'0';
             int tot=d1+d2+carry;
             ans+=('0'+(tot%10));
             carry=tot/10;
             i--,j--;
    	}
    	while(i>=0){
    		int d1=a[i]-'0';
            int tot=d1+carry;
            carry=tot/10;
            ans+=('0'+(tot%10));
            i--;
    	}
    	while(j>=0){
    		int d1=b[j]-'0';
            int tot=d1+carry;
            carry=tot/10;
            ans+=('0'+(tot%10));
            j--;
    	}
    	if(carry>0)ans+=(carry+'0');
    	reverse(ans.begin(),ans.end());
    	return ans;
    }
    string sub(string a,string b){
       int n1=a.size();
       int n2=b.size();
       int i=n1-1;
       int j=n2-1;
       string ans="";
       int carry=0;
       while(i>=0 && j>=0){
          int d1=a[i]-'0'+carry;
          int d2=b[j]-'0';
          if(d1<d2){
          	ans+=(10+d1-d2+'0');
          	carry=-1;
          }else{
          	ans+=(d1-d2+'0');
          	carry=0;
          }
          i--;
          j--;
       }
       while(i>=0){
          int d1=a[i]-'0'+carry;
       	  if(d1<0){
       	  	ans+=(10+d1+'0');
       	  	carry=-1;
       	  }else{
       	  	ans+=(d1+'0');
            carry=0;
          }
          i--;
       }
       reverse(ans.begin(),ans.end());
       i=0;
       while(i+1<(long long)ans.size() and ans[i]=='0')i++;
       return ans.substr(i);
    }
    void swap(BigInt &a,BigInt &b){
    	BigInt temp=a;
    	a=b;
    	b=temp;
    }
	void operator=(string a){
		BigInt temp(a);
		*this=temp;
	}
	void operator=(long long a){
		BigInt temp(a);
		*this=temp;
	}
	bool operator==(BigInt a){
		return (this->neg==a.neg and this->s==a.s);
	}
	BigInt abs(){
		BigInt res=*this;
		res.neg=0;
		return res;
	}
	bool operator<(string a){
		if(a.size()!=this->s.size())return this->s.size()<a.size();
		else return this->s<a;
	}
	bool operator>(string a){
		if(a.size()!=this->s.size())return this->s.size()>a.size();
        else return this->s>a;
	}
	bool operator<(BigInt a){
        if(this->neg==a.neg){
        	if(a.neg) return (*this > a.s);
        	else return *this < a.s;
        }else{
        	return this->neg==0;
        }
	}
	friend ostream &operator<<(ostream &os,BigInt a){
		string ans=a.to_String();
		os<<ans;
		return os;
	}
	BigInt operator+(BigInt a){
        int sign2=a.neg;
        BigInt res=*this;
        int sign1=res.neg;
        if(sign1==sign2){
        	res.s=add(res.s,a.s);
        }else{
            if(res.abs()<a.abs())swap(res,a);
            res.s=sub(res.s,a.s);
        }
        if(res.abs().s=="0")res.neg=0;
        return res;
	}
	BigInt operator-(BigInt a){
		a.neg=1-a.neg;
		BigInt res=*this+a;
		return res;
	}
};
int main(){
    // for(int i=1;i<1000;i++){
    // 	for(int j=0;j<=10;j++){
    // 		BigInt a=i;
    // 		BigInt b=j;
    // 		if((to_string(i+j)==(a+b).to_String()))continue;
    // 	    else cout<<i<<" "<<j<<" "<<a<<" "<<b<<" "<<a-b<<endl;
    // 	}
    // }
    string a,b;
    cin>>a>>b;
    BigInt s1=a;
    BigInt s2=b;
    cout<<s1+s2<<" "<<s1-s2<<endl;
}