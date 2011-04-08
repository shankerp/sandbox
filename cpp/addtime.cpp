#include <iostream>

using namespace std;

class mytime
{
    int hours;
    int minutes;
    public:
    void gettime(int h, int m) {
        hours = h;
        minutes = m;
    }
    void puttime(void) {
        cout << hours << " hours and ";
        cout << minutes << " minutes" << "\n";
    }
    void sum(mytime, mytime);
};

void mytime::sum(mytime t1, mytime t2)
{
    minutes = t1.minutes + t2.minutes;
    hours = minutes/60;
    minutes = minutes%60;
    hours = hours + t1.hours + t2.hours;
}

int main()
{
    mytime t1, t2, t3;

    t1.gettime(2, 45);
    t2.gettime(3, 30);
    t3.sum(t1, t2);

    cout << "t1 = "; t1.puttime();
    cout << "t2 = "; t2.puttime();
    cout << "t3 = "; t3.puttime();
}
