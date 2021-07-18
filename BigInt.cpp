#include<iostream>
#include<string>
#include<algorithm>
#include<bits/stdc++.h>
using namespace std;

class BigInt{
public:
    string s;
    int neg;
    
    //defining a constructors for string input
    BigInt(string a=""){
        s="";

        if(a[0]=='-')neg=1;//checking neg -100 100 +100
        else neg=0;
        
        int p=0;
        if(a[p]=='+' || a[p]=='-')p++;//eliminating the sign term from the string
        long long n=a.size();
        while(a[p]=='0' and p<n-1)p++;
        while(p<n)s+=a[p++];
        if(s=="0")neg=0;
    }

    //defining constructor for integer input
    BigInt(long long a){
        if(a>=0)this->neg=0;
        else{
            this->neg=1;
            a*=-1;
        }

        s="";
        if(a==0)s+='0';
        while(a>0){//appending all the digits to the end
            int dig=a%10;
            a=a/10;
            s+=('0'+dig);
        }

        reverse(s.begin(),s.end());
    }

    //Converting the big int to string according to sign
    string to_String(){
        string ans="";
        if(this->neg)ans+='-';
        return ans+this->s;
    }

    //Performing the addition of two Big integers
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
    // Coparing Big int and string
    bool operator>(string a){
        if(a.size()!=this->s.size())return this->s.size()>a.size();
        else return this->s>a;
    }

    //Logical less than operator
    bool operator<(BigInt a){
        if(this->neg==a.neg){//Both have same sign
            if(a.neg) return (*this > a.s);//both are negative the one with greater abs is lesser
            else return *this < a.s;// both are positive the one with greater abs is greater
        }else{
            return this->neg==1;
        }
    }

    bool operator>(BigInt a){
        if(this->neg==a.neg){//Both have same sign
            if(a.neg) return (*this < a.s);//both are negative the one with lesser abs is greater
            else return *this > a.s;// both are positive 
        }else{
            return this->neg==0;
        }
    }
    bool operator>=(BigInt a){
        return (*this > a or *this==a);
    }
    bool operator<=(BigInt a){
        return (*this < a or *this==a);
    }

    friend ostream &operator<<(ostream &os,BigInt a){
        //The print operator
        string ans=a.to_String();//converting the big int according to sign
        os<<ans;
        return os;
    }

    //Binary Addition operator
    BigInt operator+(BigInt a){
        int sign2=a.neg;
        BigInt res=*this;
        int sign1=res.neg;
        if(sign1==sign2){//comparing both their signs if same then 
            res.s=add(res.s,a.s);//sign remains same just add the absolute value
        }else{
            if(res.abs()<a.abs())swap(res,a);//otherwise subtract the smaller absolute value from the greater one
            res.s=sub(res.s,a.s);
        }
        if(res.abs().s=="0")res.neg=0;
        return res;
    }

    //Genersting thr value of expression -x
    BigInt operator-(){
        if(this->s!="0")this->neg=1-this->neg;//Changing the sign
        return *this;
    }

    //Binary minus operator for two Big integers
    BigInt operator-(BigInt a){
        a=-a;
        BigInt res=*this+a;//then adding them
        return res;
    }

    //recursive code for Karatsuba multiply(a.s,this->s);
    string multiply(string lhs, string rhs) {
        int length = max(lhs.size(), rhs.size());

        while (lhs.size() < length)lhs.insert(0,"0");
        while (rhs.size() < length)rhs.insert(0,"0");

        if (length == 1)return to_string((lhs[0]-'0')*(rhs[0]-'0'));//base case

        string lhs0 = lhs.substr(0,length/2);
        string lhs1 = lhs.substr(length/2,length-length/2);
        string rhs0 = rhs.substr(0,length/2);
        string rhs1 = rhs.substr(length/2,length-length/2);
        
        string p0 = multiply(lhs0,rhs0);
        string p1 = multiply(lhs1,rhs1);
        string p2 = multiply(add(lhs0,lhs1),add(rhs0,rhs1));
        string p3 = sub(p2,add(p0,p1));

        for (int i = 0; i < 2*(length-length/2); i++)
            p0.append("0");
        for (int i = 0; i < length-length/2; i++)
            p3.append("0");
            
        string result = add(add(p0,p1),p3);
        return result.erase(0, min(result.find_first_not_of('0'), result.size()-1));
    }

    BigInt operator*(BigInt a){
        int sign1=a.neg;
        int sign2=this->neg;
        string multiplication_value=multiply(a.s,this->s);
        BigInt res(multiplication_value);
        res.neg=1;
        if(sign1==sign2)res.neg=0;
        return res;
    }

    BigInt operator/(BigInt x)
    {
        BigInt temp(0), res;
 
        for (int a = 0; a < this->s.size(); a++)
            res.s += "0";//initializing res with "00000.."

        int newSign = 1;
        if(x.neg==this->neg)newSign=0;//assigning the sign of resultant num
        x=x.abs();
        BigInt y=*this;
        y=y.abs();//making both of them positive
        for (int a = 0; a<y.s.size(); a++) {
            temp=temp*BigInt(10);//current part we are considering
            temp = temp + BigInt(y.s.substr(a, 1));
            while (!(temp < x)) {
                temp = temp - x;
                res.s[a]++;
            }
        }
        res=BigInt(res.s);
        res.neg=(res.s=="0")?0:newSign;
        return res;
    }

    BigInt operator%(BigInt a){
        BigInt res=(*this/a);
       // cout<<a<<" "<<res<<endl;
        if(a.neg !=this->neg)return (a*res).abs()-(*(this)).abs();
        return *this-(a*res);
    }
    
};

//Finding GCD using euclidean algorithm
BigInt gcd(BigInt a,BigInt b){
    if(b==BigInt(0))return a;
    return gcd(b,a%b);
}
void intTest(long long x, long long y)
{
    BigInt A(x), B(y);

    // cout << x << " + " << y << " = " << A + B << "\n";
    assert((A + B)== BigInt(x + y));

   //  cout << x << " - " << y << " = " << A - B << "\n";
    assert((A - B)== BigInt(x - y));

     //cout << x << " * " << y << " = " << (A * B)<<"\n";
     assert((A * B)== BigInt(x * y));

   //  cout << x << " / " << y << " = " << A / B <<" "<<BigInt(x*y)<< "\n";
    if(y!=0) assert((A / B)== BigInt(x / y));

   //  cout << x << " % " << y << " = " << A % B << "\n";
    assert((A % B)== BigInt(x % y));

    // cout << x << " == " << y << " = " << (A == B) << "\n";
    assert((A == B) == (x == y));

    // cout << x << " < " << y << " = " << (A < B) << "\n";
    assert((A < B) == (x < y));

    // cout << x << " > " << y << " = " << (A > B) << "\n";
    assert((A > B) == (x > y));

    // cout << x << " <= " << y << " = " << (A <= B) << "\n";
    assert((A <= B) == (x <= y));

    // cout << x << " >= " << y << " = " << (A >= B) << "\n";
    assert((A >= B) == (x >= y));
    
    cout<<gcd(A,B)<<endl;
    assert(gcd(A,B)==__gcd(x,y));
}
int main(){
 
    // intTest(10, 15);
    // intTest(15, 100);
    // intTest(1, 1);
    // intTest(-1, -1);
    // intTest(1, -1);
    // intTest(-1, 1);
    // intTest(-1, 2);
    // intTest(0, 1);
    // intTest(10000099, 99999);
    // intTest(-999999999, -333333333);
    string a="",b="";
    for(int i=1;i<=10000;i++)a+='9',b+='4';
    cout<<(BigInt(a)*BigInt(b));

}