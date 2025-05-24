#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int curr = 0;
char str[100];

void invalid() {
	printf("~~~~~~ERROR~~~~~~\n");
	exit(0);
}

void valid() {
	printf("~~~~~~SUCCESS!~~~~~~\n");
	exit(0);
}

void S();
void L();
void Ldash();

void S() {
	if(str[curr] == '('){
		curr++;
		L();
		if(str[curr] == ')'){
			curr++;
			return;
		}
		else{
			invalid();
		}
	}
	else if (str[curr] == 'a'){
		curr++;
		return;
	}
	else{
		invalid();
	}
}

void L() {
	S();
	Lprime();
}

void Lprime() {
	if(str[curr] == ','){
		curr++;
		S();
		Lprime();
	}
	return;
}

int main() {
	printf("Enter String: ");
	scanf("%s", str);
	S();
	if(str[curr] == '$')
		valid();
	else
		invalid();
}
