#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

using namespace std;

class Student {
    friend class findStudent;
public:
    Student();
    Student(const Student&);
    Student(char*, char*, char*, char*, char*, char*, char*, char*, char*, char*);

    void set(char *);
    void get();
    void show();
    ~Student();

protected:
    char *Name;
    char *Surname;
    char *Patronymic;
    char *Day;
    char *Mount;
    char *Year;
    char *Address;
    char *Phone;
    char *Faculty;
    char *Course;

private:
    int strLen(char*);
    char* copy(char*, const char*);
};

Student::Student() :Name(0),
                    Surname(0),
                    Patronymic(0),
                    Day(0),
                    Mount(0),
                    Year(0),
                    Address(0),
                    Phone(0),
                    Faculty(0),
                    Course(0) {
}

Student::Student(const Student &arg) {

    Name = new char[strLen(arg.Name)];
    copy(Name, arg.Name);

    Surname = new char[strLen(arg.Surname)];
    copy(Name, arg.Surname);

    Patronymic = new char[strLen(arg.Patronymic)];
    copy(Name, arg.Patronymic);

    Day = new char[strLen(arg.Day)];
    copy(Name, arg.Day);

    Mount = new char[strLen(arg.Mount)];
    copy(Name, arg.Mount);

    Year = new char[strLen(arg.Year)];
    copy(Name, arg.Year);

    Address = new char[strLen(arg.Address)];
    copy(Name, arg.Address);

    Phone = new char[strLen(arg.Phone)];
    copy(Name, arg.Phone);

    Faculty = new char[strLen(arg.Faculty)];
    copy(Name, arg.Faculty);

    Course = new char[strLen(arg.Course)];
    copy(Name, arg.Course);
}

Student::Student(char *nam, char *sur, char *pat, char *d, char *m, char *y, char *add, char *ph, char *fac, char *cor) {

    Name = new char[strLen(nam)];
    copy(Name, nam);

    Surname = new char[strLen(sur)];
    copy(Name, sur);

    Patronymic = new char[strLen(pat)];
    copy(Name, pat);

    Day = new char[strLen(d)];
    copy(Name, d);

    Mount = new char[strLen(m)];
    copy(Name, m);

    Year = new char[strLen(y)];
    copy(Name, y);

    Address = new char[strLen(add)];
    copy(Name, add);

    Phone = new char[strLen(ph)];
    copy(Name, ph);

    Faculty = new char[strLen(fac)];
    copy(Name, fac);

    Course = new char[strLen(cor)];
    copy(Name, cor);
}

int Student::strLen(char *str) {
int i = 0;
while(*str) {
    i++;
    str++;
}
return i;
}

char* Student::copy(char *str1, const char *str2) {
    char *tmp = str1;
    while(*tmp++ = *str2++);
    return str1;
}


Student::~Student() {
delete[] Name;
delete[] Surname;
delete[] Patronymic;
delete[] Day;
delete[] Mount;
delete[] Year;
delete[] Address;
delete[] Phone;
delete[] Faculty;
delete[] Course;
}

void Student::set(char *sentence) {
    int i, j, k;
    i = j = k = 0;
    for(i = 0; sentence[i] != '\0'; i++) {

        if(isspace(sentence[i])) {
            sentence[i] = ' ';
        }
        switch(sentence[i]) {
        case '.': case ',':
            sentence[i] = ' ';
            break;
        default:
            break;
        }
    }

//*********NAME********************
    for(i = 0; sentence[i] != ' '; i++) {}

    Name = new char[i + 1];
    for(k = 0; k < i; k++) {
        Name[k] = sentence[k];
        sentence[k] = ' ';
    }
    Name[k] = '\0';
    sentence[k] = ' ';
    //cout << "Name: " << Name << endl;


//*********SURNAME********************
    while(sentence[i] == ' ') {
        i++;
    }
    k = i;
    while(sentence[i] != ' ') {
        i++;
    }

    Surname = new char[i - k + 1];
    for(j = 0; j < i - k; j++) {
        Surname[j] = sentence[k + j];
        sentence[k + j] = ' ';
    }
    Surname[j] = '\0';
    sentence[k + j] = ' ';
    //cout << "Surname: " << Surname << endl;

//*********PATRONYMIC********************
    while(sentence[i] == ' ') {
        i++;
    }
    k = i;
    while(sentence[i] != ' ') {
        i++;
    }

    Patronymic = new char[i - k + 1];
    for(j = 0; j < i - k; j++) {
        Patronymic[j] = sentence[k + j];
        sentence[k + j] = ' ';
    }
    Patronymic[j] = '\0';
    sentence[k + j] = ' ';
    //cout << "Patronymic: " << Patronymic << endl;

//*********DATE********************
    while(sentence[i] == ' ') {
        i++;
    }
    k = i;
    while(sentence[i] != ' ') {
        i++;
    }

    Day = new char[i - k + 1];
    for(j = 0; j < i - k; j++) {
        Day[j] = sentence[k + j];
        sentence[k + j] = ' ';
    }
    Day[j] = '\0';
    sentence[k + j] = ' ';
    //cout << "day: " << day << endl;
    //Day = atoi(day);
    //delete[] day;
    //cout << "Day: " << Day << endl;

    while(sentence[i] == ' ') {
        i++;
    }
    k = i;
    while(sentence[i] != ' ') {
        i++;
    }

    Mount = new char[i - k + 1];
    for(j = 0; j < i - k; j++) {
        Mount[j] = sentence[k + j];
        sentence[k + j] = ' ';
    }
    Mount[j] = '\0';
    sentence[k + j] = ' ';
    //cout << "day: " << day << endl;
    //Mount = atoi(mount);
    //delete[] mount;
    //cout << "Mount: " << Mount << endl;


    while(sentence[i] == ' ') {
        i++;
    }
    k = i;
    while(sentence[i] != ' ') {
        i++;
    }

    Year = new char[i - k + 1];
    for(j = 0; j < i - k; j++) {
        Year[j] = sentence[k + j];
        sentence[k + j] = ' ';
    }
    Year[j] = '\0';
    sentence[k + j] = ' ';
    //cout << "day: " << day << endl;
    //Year = atoi(year);
    //delete[] year;
    //cout << "Year: " << Year << endl;

//*********CITY********************
    while(sentence[i] == ' ') {
        i++;
    }
    k = i;
    while(sentence[i] != ' ') {
        i++;
    }

    Address = new char[i - k + 1];
    for(j = 0; j < i - k; j++) {
        Address[j] = sentence[k + j];
        sentence[k + j] = ' ';
    }
    Address[j] = '\0';
    sentence[k + j] = ' ';
    //cout << "Address: " << Address << endl;

//*********PHONE********************
    while(sentence[i] == ' ') {
        i++;
    }
    k = i;
    while(sentence[i] != ' ') {
        i++;
    }

    Phone = new char[i - k + 1];
    for(j = 0; j < i - k; j++) {
        Phone[j] = sentence[k + j];
        sentence[k + j] = ' ';
    }
    Phone[j] = '\0';
    sentence[k + j] = ' ';
    //Phone = atoi(phone);
    //delete[] phone;
    //cout << "Phone: " << Phone << endl;

//*********FACULTY********************
    while(sentence[i] == ' ') {
        i++;
    }
    k = i;
    while(sentence[i] != ' ') {
        i++;
    }

    Faculty = new char[i - k + 1];
    for(j = 0; j < i - k; j++) {
        Faculty[j] = sentence[k + j];
        sentence[k + j] = ' ';
    }
    Faculty[j] = '\0';
    sentence[k + j] = ' ';
    //cout << "Faculty: " << Faculty << endl;

//*********COURSE********************
    while(sentence[i] == ' ') {
        i++;
    }
    k = i;
    while(sentence[i] != ' ') {
        i++;
    }

    Course = new char[i - k + 1];
    for(j = 0; j < i - k; j++) {
        Course[j] = sentence[k + j];
        sentence[k + j] = ' ';
    }
    Course[j] = '\0';
    sentence[k + j] = ' ';
    //Course = atoi(course);
    //delete[] course;
    //cout << "Course: " << Course << endl;
}

void Student::get() {
cout << Name << ", "
        << Surname << ", "
        << Patronymic << ", "
        << Day << "."
        << Mount << "."
        << Year << ", "
        << Address << ", "
        << Phone << ", "
        << Faculty << ", "
        << Course;
}

void Student::show() {
    cout << "Name: " << Name << endl;
    cout << "Surname: " << Surname << endl;
    cout << "Patronymic: " << Patronymic << endl;
    cout << "Day: " << Day << endl;
    cout << "Mount: " << Mount << endl;
    cout << "Year: " << Year << endl;
    cout << "Address: " << Address << endl;
    cout << "Phone: " << Phone << endl;
    cout << "Faculty: " << Faculty << endl;
    cout << "Course: " << Course << endl << endl;
}


class findStudent {
public:
    void find(char*, Student*, int);
};


void findStudent::find(char *str1, Student *st, int num) {
    int i, j, k, n, e, r;
    int *mas = new int[num];
    i = 0;
    while(str1[i] == ' ') {
        i++;
    }
    k = i;
    while(str1[i] != ',') {
        i++;
    }

    char *faculty = new char[i - k + 1];
    for(j = 0; j < i - k; j++) {
        faculty[j] = str1[k + j];
        str1[k + j] = ' ';
    }
    faculty[j] = '\0';
    str1[k + j] = ' ';
    //cout << "faculty: " << faculty << endl;


    while(str1[i] == ' ') {
        i++;
    }
    k = i;
    while(str1[i] != ',') {
        i++;
    }
//for(n = 0; n < M; n++) {
    char *course = new char[i - k + 1];
    for(j = 0; j < i - k; j++) {
        course[j] = str1[k + j];
        str1[k + j] = ' ';
    }
    course[j] = '\0';
    str1[k + j] = ' ';
    //cour = atoi(course);
    //cout << "course: " << course << endl;

    while(str1[i] == ' ') {
        i++;
    }
    k = i;
    while(str1[i] != '\0') {
        i++;
    }

    char *year = new char[i - k + 1];
    for(j = 0; j < i - k; j++) {
        year[j] = str1[k + j];
        str1[k + j] = ' ';
    }
    year[j] = '\0';
    str1[k + j] = '\0';
    //yyyy = atoi(year);
    //cout << "year: " << year << endl;

e = 0;
r = 0;
for(n = 0; n < num; n++) {
    mas[n] = -1;
}

for(n = 0; n < num; n++) {
    if(strlen(st[n].Faculty) == strlen(faculty)) {
        if(!strcmp((st[n].Faculty), faculty)) {
            mas[e] = n;
            e++;
            r++;
        }
    }
}


for(n = 0; n < num; n++) {
    if(mas[n] >= 0 && r == 1){
        st[mas[n]].get();
        cout << ". ";
    }

    if(mas[n] >= 0 && r > 1){
        st[mas[n]].get();
        cout << "; ";
        r--;
    }
}


e = 0;
r = 0;
for(n = 0; n < num; n++) {
    mas[n] = -1;
}

for(n = 0; n < num; n++) {
    if(atoi(st[n].Course) == atoi(course)) {
        mas[e] = n;
        e++;
        r++;
    }
}

for(n = 0; n < num; n++) {
    if(mas[n] >= 0 && r == 1){
        st[mas[n]].get();
        cout << ". ";
    }

    if(mas[n] >= 0 && r > 1){
        st[mas[n]].get();
        cout << "; ";
        r--;
    }
}

e = 0;
r = 0;
for(n = 0; n < num; n++) {
    mas[n] = -1;
}

for(n = 0; n < num; n++) {
    if(atoi(st[n].Year) > atoi(year)) {
        mas[e] = n;
        e++;
        r++;
    }
}

for(n = 0; n < num; n++) {
    if(mas[n] >= 0 && r == 1){
        st[mas[n]].get();
        cout << ".";
    }

    if(mas[n] >= 0 && r > 1){
        st[mas[n]].get();
        cout << "; ";
        r--;
    }
}

delete[] mas;
delete[] faculty;
delete[] course;
delete[] year;
}


int main()
{
    int i, count, m, j;
    char c;
    char *str1 = new char;

    count = 0;
    for(i = 2; scanf("%c", &c) != EOF; i++) {
        char *str2 = new char[i];
        strcpy(str2, str1);
        str2[i - 2] = c;
        str2[i - 1] = '\0';
        delete[] str1;
        //cout << "delete[] str1: " << str1 << endl;
        str1 = str2;
        if(c == '.') {
            count++;
        }
        //cout << "str1 = str2: " << str1 << endl;
    }
    //cout << "count: " << count << endl;
    //cout << "str1: " << str1 << endl;
    //cout << "str2: " << str2 << endl;
if(count/3 > 0) {
    int num = 0;//count/3;
    m = 0;
    Student *st = new Student[count/3];
    for(i = 1; str1[i] != 0; i++) {
        if(str1[i - 1] == '.' && str1[i] ==' ') {
            char *sentence = new char[i - m];

            for(j = 0; j < i - m; j++) {
                sentence[j] = str1[m + j];
                str1[m + j] = ' ';
            }
            sentence[j] = '\0';
            m = i + 1;
            //cout << "sentence: " << sentence << endl;
            st[num].set(sentence);
            //st[num].show();
            //st[num].get();
            num++;
            //st[]set(sentence) f(sentence, st);
            //cout << "f(sentence, st): " << sentence << endl << endl;
            delete[] sentence;
            //cout << "delete[] sentence: " << sentence << endl;
        }
    }

    findStudent *find = new findStudent;
    find->find(str1, st, num);
    delete find;
//    delete[] st;
}
    //cout << "str1: " << str1 << endl;
    //cout << "Hello world!" << endl;
    delete[] str1;
    return 0;
}
