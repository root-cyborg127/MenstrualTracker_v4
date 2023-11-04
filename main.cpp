
#include <iostream>
using namespace std;

struct Date {
    int day;
    int month;
    int year;
    Date* next;
};

class MenstrualCycleTracker {
private:
    int cycleLength;
    int menstrualLength;
    Date lastPeriod;

public:
    MenstrualCycleTracker() {
        cycleLength = 0;
        menstrualLength = 0;
        lastPeriod.next = nullptr;
    }

    void setCycleLength(int length) {
        cycleLength = length;
    }

    void setMenstrualLength(int length) {
        menstrualLength = length;
    }

    void setLastPeriodDate(int day, int month, int year) {
        lastPeriod.day = day;
        lastPeriod.month = month;
        lastPeriod.year = year;
    }

    void calculateDates(int numFuturePeriods) {
        Date* nextPeriodStart = &lastPeriod;
        for (int i = 0; i < numFuturePeriods; i++) {
            Date* newNode = new Date;
            newNode->day = nextPeriodStart->day + cycleLength;
            newNode->month = nextPeriodStart->month;
            newNode->year = nextPeriodStart->year;

            if (newNode->day > 31) {
                newNode->month += 1;
                newNode->day -= 31;
            }

            newNode->next = nullptr;

            nextPeriodStart->next = newNode;
            nextPeriodStart = newNode;
        }
    }

    void displayDates() {
        Date* current = &lastPeriod;
        cout<<  "Your future menstrual and ovulation dates are:\n";

        while (current != nullptr) {
            Date periodStart = *current;
            Date periodEnd = periodStart;
            periodEnd.day += menstrualLength;

            if (periodEnd.day > 31) {
                periodEnd.month += 1;
                periodEnd.day -= 31;
            }

            Date ovulationStart = periodStart;
            ovulationStart.day += 10;

            if (ovulationStart.day > 31) {
                ovulationStart.month += 1;
                ovulationStart.day -= 31;
            }

            Date ovulationEnd = ovulationStart;
            ovulationEnd.day += 6;

            if (ovulationEnd.day > 31) {
                ovulationEnd.month += 1;
                ovulationEnd.day -= 31;
            }

            cout<<  "----------------------------------------\n";
            cout<<  "Period Start: " << periodStart.day << "-" << periodStart.month << "-" << periodStart.year << endl;
            cout<<  "Period End  : " << periodEnd.day << "-" << periodEnd.month << "-" << periodEnd.year << endl;
            cout<<  "Ovulation Start: " << ovulationStart.day << "-" << ovulationStart.month << "-" << ovulationStart.year << endl;
            cout<<  "Ovulation End  : " << ovulationEnd.day << "-" << ovulationEnd.month << "-" << ovulationEnd.year << endl;
            cout<<  "----------------------------------------\n\n";

            current = current->next;
        }
    }

    bool isDateInPeriod(int day, int month, int year) {
    Date* current = &lastPeriod;
    while (current != nullptr) {
        Date periodStart = *current;
        Date periodEnd = periodStart;
        periodEnd.day += menstrualLength;

        if (periodEnd.day > 31) {
            periodEnd.month += 1;
            periodEnd.day -= 31;
        }

        if (year > periodStart.year || (year == periodStart.year && month > periodStart.month) || 
           (year == periodStart.year && month == periodStart.month && day >= periodStart.day)) {
            // Check if the date falls between periodStart and periodEnd
            if (year < periodEnd.year || (year == periodEnd.year && month < periodEnd.month) || 
               (year == periodEnd.year && month == periodEnd.month && day <= periodEnd.day)) {
                return true;
            }
        }
        
        current = current->next;
    }
    return false;
}


    void deleteDates() {
        Date* current = &lastPeriod;
        while (current != nullptr) {
            Date* temp = current;
            current = current->next;
            delete temp;
        }
        lastPeriod.next = nullptr;
    }
    
     void note(){

    cout<<  "\n\nAsk your doctor about any concerns or questions you may have about your menstrual experience for best results.\n";
    cout<<  "For more information, visit WomensHealth.gov or GirlsHealth.gov for more facts about menstruation.\n";
	}
};

int main() {
    MenstrualCycleTracker tracker;

    int cycleLength;
    int menstrualLength;
    int day, month, year;
    int numFuturePeriods;
    
    	
//BANNER 
	
cout<<"\t    __  __________   _________________  __  _____    __       __________  ___   ________ __ __________ \n\t   /  |/  / ____/ | / / ___/_  __/ __ \/ / / /   |  / /      /_  __/ __ \/   | / ____/ //_// ____/ __ \ \n\t  / /|_/ / __/ /  |/ /\__ \ / / / /_/ / / / / /| | / /     / / / /_/ / /| |/ /   / ,<  / __/ / /_/ / \n\t / /  / / /___/ /|  /___/ // / / _, _/ /_/ / ___ |/ /___     / / / _, _/ ___ / /___/ /| |/ /___/ _, _/ \n\t/_/  /_/_____/_/ |_//____//_/ /_/ |_|\____/_/  |_/_____/    /_/ /_/ |_/_/  |_\____/_/ |_/_____/_/ |_|  \n \t\n";
                                                                                                      
cout<<"\t\t\t\t\t v1.0\t\tDEVELOPED BY : VISHWAJITH SHAIJUKUMAR \n\n\n\n\n";




    cout<<  "CYCLE TRACKER Step 1: CYCLE LENGTH\n";
    cout<<  "Please enter the number of days your previous cycle lasted: ";
    cin>> cycleLength;
    tracker.setCycleLength(cycleLength);
    cout<<  endl;

    cout<<  "CYCLE TRACKER Step 2: PERIOD LENGTH\n";
    cout<<  "Please enter the number of days your menstrual period lasts: ";
    cin>> menstrualLength;
    tracker.setMenstrualLength(menstrualLength);
    cout<<  endl;

    cout<<  "CYCLE TRACKER Step 3: WHEN DID YOUR LAST PERIOD START? (dd mm yyyy)\n";
    cin>> day >> month >> year;
    tracker.setLastPeriodDate(day, month, year);
    cout<<  endl;

    cout<<  "CYCLE TRACKER Step 4: NUMBER OF FUTURE PERIODS TO CALCULATE\n";
    cout<<  "Please enter the number of future menstruation dates to calculate: ";
    cin>> numFuturePeriods;
    tracker.calculateDates(numFuturePeriods);

    cout<<  endl;

    tracker.displayDates();

    int checkDay, checkMonth, checkYear;
    cout<<  "Enter a date to check if it's in your future periods (dd mm yyyy): ";
    cin>> checkDay >> checkMonth >> checkYear;
    
    if (tracker.isDateInPeriod(checkDay, checkMonth, checkYear)) {
        cout<<  "Yes, this date is in your future periods.\n";
         tracker.note();
    } else {
        cout<<  "No, this date is not in your future periods.\n";
         tracker.note();
    }

    tracker.deleteDates();
   
    return 0;
}
