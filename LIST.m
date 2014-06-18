#include<stdio.h>
#include<stdlib.h>

#define DEFINE_ZED_TYPE(type_) typedef type_ ZED##type_;typedef type_ * type_##P;typedef type_##P ZED##type_##P;static type_##P type_##ArrayNew(ulonglong size){return (type_##P)malloc(size*sizeof(type_));}static type_ type_##ArrayRef(ulonglong index,type_##P array){return array[index-1];}static type_##P type_##ArraySet(ulonglong index,type_ value,type_##P array){array[index-1]=value;return array;}

typedef unsigned char uchar;
typedef unsigned long long ulonglong;
DEFINE_ZED_TYPE(uchar)
DEFINE_ZED_TYPE(ulonglong)
typedef uchar u;
typedef ucharP p;

ulonglong extent1(ulonglong character){return character-'0';}

ulonglong extent2(ulonglong index,p list,ulonglong value){if(list[index]==')'){return value;}else{return extent2(index+1,list,extent1(list[index])+value*10);}}

ulonglong extent(p list){return extent2(1,list,0);}

ulonglong selfExtent1(ulonglong extent,ulonglong length,ulonglong magnitude){if(extent<magnitude){return length;}else{return selfExtent1(extent,length+1,magnitude*10);}}

ulonglong selfExtent(ulonglong extent){return selfExtent1(extent,3,10);}

p copy1(p list,p temp,ulonglong length){if(length==0){return temp;}else{temp[length-1]=list[length-1];return copy1(list,temp,length-1);}}

p copy(p list){ulonglong newExtent=extent(list);ulonglong newSelfExtent=selfExtent(newExtent);ulonglong length=newExtent+newSelfExtent;p temp=(p)malloc(length*sizeof(u));return copy1(list,temp,length);}

void display1(ulonglong index,ulonglong end,p list){if(index<end){printf("%c",list[index]);display1(index+1,end,list);}}

void display(p list){ulonglong ext=extent(list);ulonglong start=selfExtent(ext);ulonglong end=start+ext;display1(start,end,list);}

void line(){printf("\n");}

void displayLine(p list){display(list);printf("\n");}

ulonglong stringLength1(char* string,ulonglong index){if(string[index]==0){return index;}else{return stringLength1(string,index+1);}}

ulonglong stringLength(char* string){return stringLength1(string,0);}

char* stringReverse(char* str){ulonglong i;ulonglong j=stringLength(str)-1;ulonglong k=j/2;char temp;for(i=0;i<=k;i++){temp=str[j];str[j]=str[i];str[i]=temp;j--;}return str;}

char* stringCopy1(ulonglong index,char* str1,char* str2){if(str1[index]==0){str2[index]=0;return str2;}else{str2[index]=str1[index];return stringCopy1(index+1,str1,str2);}}

char* stringCopy(char* str){char* copy=(char*)malloc((1+stringLength(str))*sizeof(char));return stringCopy1(0,str,copy);}

p n1(char* string,p list,ulonglong left,ulonglong right,ulonglong extent){list[0]='(';list[left-1]=')';ulonglong i;for(i=left-2;i>0;--i){list[i]=(u)extent%10+'0';extent/=10;}for(i=left;i<right;++i){list[i]=(u)string[i-left];}return list;}

p n(char* string){ulonglong x=stringLength(string);ulonglong s=selfExtent(x);ulonglong t=s+x;return n1(string,ucharArrayNew(t),s,t,x);}

p push1(p one,p two,p three,ulonglong left,ulonglong middle,ulonglong right,ulonglong total){three[0]='(';three[left-1]=')';ulonglong i;for(i=left-2;i>0;--i){three[i]=total%10+'0';total/=10;}for(i=left;i<middle;++i){three[i]=one[i-left];}for(i=middle;i<right;++i){three[i]=two[i-middle];}return three;}

p push(p one,p two){ulonglong x1=extent(one);ulonglong x2=extent(two);ulonglong s1=selfExtent(x1);ulonglong s2=selfExtent(x2);ulonglong t1=s1+x1;ulonglong x3=t1+s2+x2;ulonglong s3=selfExtent(x3);ulonglong x4=s3+x3;return push1(one,two,ucharArrayNew(x4),s3,s3+t1,x4,x3);}

p top(p list){ulonglong x=extent(list);ulonglong s=selfExtent(x);return copy(list+s);}

p pop(p list){ulonglong x=extent(list);ulonglong s=selfExtent(x);ulonglong tx=extent(list+s);ulonglong ts=selfExtent(tx);return copy(list+s+ts+tx);}

int main(){

p number1=n("1234512345123451234512345123451234512345123451234512345");
p number2=copy(number1);

displayLine(number1);
free(number1);
displayLine(number2);
free(number2);
line();

p word1=n("alphabet");
p word2=copy(word1);
free(word1);
displayLine(word2);
free(word2);
line();

displayLine(n("return square(L)number(R);"));
line();
p pair1=push(n("abc"),n("123"));
p pair2=copy(pair1);
displayLine(top(pop(push(pair1,push(pair2,pair2)))));

return 0;
}
