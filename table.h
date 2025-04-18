#ifndef TABLE_H
#define TABLE_H

#include<fstream>
#include<iostream>
#include<math.h>
#include<conio.h>
using namespace std;

//extern int MAXX = 800, MAXY = 600;
//extern int ROW;
//extern int COLUMN;
//extern int SOP = 0;
//extern int NOV;
//extern int side=64;
//extern bool MapCorner = false;

class Table {
protected:

    ///------------------------------------------------------------------------------------------------------------------------------

    struct MapTable {
        int i; int j;
        int iSize;int jSize;
        MapTable *next;
    }*MTptr, *MTtop, *MTprev, *MTnext, *MTcur;

    //Creates a new Node and assigns it THE information
    MapTable *CreateEntry(int i, int j, int iSize, int jSize);

    //Adds the entry to the Table
    void pushEntry(MapTable *np);
    ///------------------------------------------------------------------------------------------------------------------------------
    struct coOrdinates {
        int i;
        int j;
        bool status;
        coOrdinates *next;
    }*COptr, *COtop, *COptr2, *COtop2, *COptr3;

    //Creates a new Node and assigns it THE information
    coOrdinates *emergeCoOrdinate(int i, int j, bool status = false);

    //Adds the entry to the Table
    void insertCoOrdinate(coOrdinates *np);
    //truncates the entire co-ordinate list
    void deleteCoOrdinateList(coOrdinates *top);
    //Creates a new Node and assigns it THE information
    coOrdinates *emergeCoOrdinate2(int i, int j, bool status = false);

    //Adds the entry to the Table
    void insertCoOrdinate2(coOrdinates *np);
    ///------------------------------------------------------------------------------------------------------------------------------

    struct FringeMapTable {
        int i1; int j1;
        int iSize;int jSize;
        int i2; int j2;

        FringeMapTable *next;
    }*FTptr, *FTtop, *FHTtop, *FTprev, *FTnext, *FTcur;

    FringeMapTable *CreateEntry(int i1, int j1, int i2, int j2, int iSize, int jSize);

    void pushEntry(FringeMapTable *np);
    void pushHEntry(FringeMapTable *np);

};
#endif // TABLE_H
