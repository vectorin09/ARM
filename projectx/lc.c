// ip1="hello" ip2="1234567" vice versa ips output="h1e2l3l4o567"
#include<stdio.h>
#include<string.h>
int main()
{
	char string1[]="123456";
	char string2[]="hello";int i;int great;
	int len=strlen(string1);
	int len2=strlen(string2);
	if(len>len2) great=len;else great=len2;
	for(i=0;i<great;i++)
	{
		if(string1[i]||string2[i]) printf("%c%c",string1[i],string2[i]);
		else if(string1[i]) string2[i];
		else string2[i];
	}
	
}	
