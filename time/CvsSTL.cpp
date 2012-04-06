#include <iostream>
#include <string>
#include <sys/time.h>
#include "msr.h"

using namespace std;

//=================================================
int main()
{
#define PRINT(x, y)     cout << "Test#" << x << " [" << y << "] \t: " << \
"\tAverage time = " << (time_end - time_start) / TOTAL_Iterations << " cycles" << endl
#define PRINTS(x, y)    PRINT(x, y) << endl

//=======================
const int       TOTAL_Tests = 5;
const int       TOTAL_Iterations = 1000;
const int       C_ARRAY_size = 7;
//===========
long long        time_start;
long long       time_end;
//===========

char c1 [C_ARRAY_size] = "CCC111";
char c0 [C_ARRAY_size * TOTAL_Iterations + 1];

string s0;
string s1 = "SSS111";
//===============
        //======================

        for (int theTest = 1; theTest <= TOTAL_Tests; theTest++)
        {
                //=======================
                cout << endl << "\t" << "##### Test#" << theTest << "#####" << endl;

                //======= strcpy ================
                rdtscll(time_start);
                for (int theIteration = 1; theIteration <= TOTAL_Iterations; theIteration++)
                {
                        strcpy (c0, c1);
                } // for (theIteration = 1; theIteration <= TOTAL_Iterations; theIteration++)
                rdtscll(time_end);
                PRINT (theTest, "strcpy()\t");
                //===============================
                //======= operator= ================
                rdtscll(time_start);
                for (int theIteration = 1; theIteration <= TOTAL_Iterations; theIteration++)
                {
                        s0 = s1;
                } // for (theIteration = 1; theIteration <= TOTAL_Iterations; theIteration++)
                rdtscll(time_end);
                PRINTS (theTest, "STL : operator=");
                //===============================

                //======= strcat ================
                strcpy (c0, "");
                rdtscll(time_start);
                for (int theIteration = 1; theIteration <= TOTAL_Iterations; theIteration++)
                {
                        strcat (c0, c1);
                } // for (theIteration = 1; theIteration <= TOTAL_Iterations; theIteration++)
                rdtscll(time_end);
                PRINT (theTest, "strcat()\t");
                //===============================
                //======= operator+= ================
                s0 = string ();

                rdtscll(time_start);
                for (int theIteration = 1; theIteration <= TOTAL_Iterations; theIteration++)
                {
                        s0 += s1;
                } // for (theIteration = 1; theIteration <= TOTAL_Iterations; theIteration++)
                rdtscll(time_end);
                PRINTS (theTest, "STL : operator+=");
                //===============================

                //======= strcmp ================
                strcpy (c0, "");
                rdtscll(time_start);
                for (int theIteration = 1; theIteration <= TOTAL_Iterations; theIteration++)
                {
                        strcmp (c0, c1);
                } // for (theIteration = 1; theIteration <= TOTAL_Iterations; theIteration++)
                rdtscll(time_end);
                PRINT (theTest, "strcmp()\t");
                //===============================
                //======= operator== ================
                s0 = string ();

                rdtscll(time_start);
                for (int theIteration = 1; theIteration <= TOTAL_Iterations; theIteration++)
                {
                        s0 == s1;
                } // for (theIteration = 1; theIteration <= TOTAL_Iterations; theIteration++)
                rdtscll(time_end);
                PRINTS (theTest, "STL : operator==");
                //===============================


                //======= strlen ================
                rdtscll(time_start);
                for (int theIteration = 1; theIteration <= TOTAL_Iterations; theIteration++)
                {
                        strlen (c0);
                } // for (theIteration = 1; theIteration <= TOTAL_Iterations; theIteration++)
                rdtscll(time_end);
                PRINT (theTest, "strlen()\t");
                //===============================
                //======= size () ================
                rdtscll(time_start);
                for (int theIteration = 1; theIteration <= TOTAL_Iterations; theIteration++)
                {
                        s0.size ();
                } // for (theIteration = 1; theIteration <= TOTAL_Iterations; theIteration++)
                rdtscll(time_end);
                PRINTS (theTest, "STL : size ()\t");
                //===============================

                //======= malloc ================
                rdtscll(time_start);
                for (int theIteration = 1; theIteration <= TOTAL_Iterations; theIteration++)
                {
                        free ((char *) malloc (4));
                } // for (theIteration = 1; theIteration <= TOTAL_Iterations; theIteration++)
                rdtscll(time_end);
                PRINT (theTest, "malloc&free\t");
                //===============================
                //======= new&delete ================
                rdtscll(time_start);
                for (int theIteration = 1; theIteration <= TOTAL_Iterations; theIteration++)
                {
                        string ("ABCD");
                } // for (theIteration = 1; theIteration <= TOTAL_Iterations; theIteration++)
                rdtscll(time_end);
                PRINTS (theTest, "STL : new&delete");
                //===============================

        } // for (theTest = 1; theTest <= TOTAL_Tests; theTest++)
        //======================
        return 0;

} 
