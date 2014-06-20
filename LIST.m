#include<stdio.h>
#include<stdlib.h>

#define DEFINE_ZED_TYPE(type_) typedef type_ ZED##type_;typedef type_ * type_##P;typedef type_##P ZED##type_##P;static type_##P type_##ArrayNew(ull size){return (type_##P)malloc(size*sizeof(type_));}static type_ type_##ArrayRef(ull index,type_##P array){return array[index-1];}static type_##P type_##ArraySet(ull index,type_ value,type_##P array){array[index-1]=value;return array;}

typedef unsigned char u;
typedef unsigned long long ull;
DEFINE_ZED_TYPE(u)
DEFINE_ZED_TYPE(uP)
DEFINE_ZED_TYPE(ull)
typedef uP p;
typedef uPP pp;

ull extent1(ull character){return character-'0';}

ull extent2(ull index,p list,ull value){if(list[index]==')'){return value;}else{return extent2(index+1,list,extent1(list[index])+value*10);}}

ull extent(p list){return extent2(1,list,0);}

ull selfExtent1(ull extent,ull length,ull magnitude){if(extent<magnitude){return length;}else{return selfExtent1(extent,length+1,magnitude*10);}}

ull selfExtent(ull extent){return selfExtent1(extent,3,10);}

p copy1(p list,p temp,ull length){if(length==0){return temp;}else{temp[length-1]=list[length-1];return copy1(list,temp,length-1);}}

p copy(p list){ull newExtent=extent(list);ull newSelfExtent=selfExtent(newExtent);ull length=newExtent+newSelfExtent;p temp=(p)malloc(length*sizeof(u));return copy1(list,temp,length);}

void display1(ull index,ull end,p list){if(index<end){printf("%c",list[index]);display1(index+1,end,list);}}

void display(p list){ull ext=extent(list);ull start=selfExtent(ext);ull end=start+ext;display1(start,end,list);}

void line(){printf("\n");}

void displayLine(p list){display(list);printf("\n");}

ull stringLength1(char* string,ull index){if(string[index]==0){return index;}else{return stringLength1(string,index+1);}}

ull stringLength(char* string){return stringLength1(string,0);}

ull garbageListLength1(pp garbage,ull index){if(garbage[index]==0){return index;}else{return garbageListLength1(garbage,index+1);}}

ull garbageListLength(pp garbage){return garbageListLength1(garbage,0);}

pp garbageListNew(){pp garbage=uPArrayNew(1024);garbage=garbage+1023;garbage[0]=0;return garbage;}

p n1(char* string,p list,ull left,ull right,ull extent){list[0]='(';list[left-1]=')';ull i;for(i=left-2;i>0;--i){list[i]=(u)extent%10+'0';extent/=10;}for(i=left;i<right;++i){list[i]=(u)string[i-left];}return list;}

p n(char* string){ull x=stringLength(string);ull s=selfExtent(x);ull t=s+x;return n1(string,uArrayNew(t),s,t,x);}

p push1(p one,p two,p three,ull left,ull middle,ull right,ull total){three[0]='(';three[left-1]=')';ull i;for(i=left-2;i>0;--i){three[i]=total%10+'0';total/=10;}for(i=left;i<middle;++i){three[i]=one[i-left];}for(i=middle;i<right;++i){three[i]=two[i-middle];}return three;}

p push(p one,p two){ull x1=extent(one);ull x2=extent(two);ull s1=selfExtent(x1);ull s2=selfExtent(x2);ull t1=s1+x1;ull x3=t1+s2+x2;ull s3=selfExtent(x3);ull x4=s3+x3;return push1(one,two,uArrayNew(x4),s3,s3+t1,x4,x3);}

p top(p list){ull x=extent(list);ull s=selfExtent(x);return copy(list+s);}

p pop(p list){ull x=extent(list);ull s=selfExtent(x);ull tx=extent(list+s);ull ts=selfExtent(tx);return copy(list+s+ts+tx);}

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

printf("\n%llu\n",garbageListLength(garbageListNew()));

return 0;
}
