#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>

using namespace std;

int column=0,row=0;
int i=0, start, counter = 0, neighbor[4], next;
char dummy,x;
double rmat[100][100];
double qmat[100][100];

int random_move (int start){

    srand(time(NULL));
    int poss_move = 0;
    counter = 0;
    for(i=0;i<column;i++){
        if(rmat[start][i] == 0 || rmat[start][i] == 100 ){
            neighbor[counter]=i;
            counter++;
        }
    }

    poss_move=rand()% counter;
    int dondur = neighbor[poss_move];
    return dondur;
}

int find_all_moves (int start){

    int counter=0;
    for(i=0;i<column;i++){
        if(rmat[start][i] == 0 || rmat[start][i] == 100 ){
            neighbor[counter]=i;
            counter++;
        }
    }
    return counter;
}

int find_big (int next){
    int big = 0, i, road_count;
    bool flag=false;

    road_count = find_all_moves(next);

    for(i=0;i<road_count;i++){
        if(big<qmat[next][neighbor[i]]){
            big=neighbor[i];
            flag = true;
        }
    }
    i=big;
    if(flag==false){
        i=random_move(next);
    }
    return i;
}

void find_path(int reserve_start,int target){
    int path[40]={0},k=0,l,i=0,hold;
    int reserve_column = column;
    bool flag=true;

    ofstream pathW ("path.txt",ios::out);
    pathW << reserve_start << " ";
    k=reserve_start;
    while(flag==true && target!=k){
        flag=false;

        for(l=0;l<reserve_column;l++){
            if(qmat[k][l]>path[i]){
                path[i]=qmat[k][l];
                //path[i]=(k)*(column)+l;
                flag=true;
                hold=l;
            }
        }
        if(flag==true){
                reserve_start=hold;
                path[i]=hold;
                i++;
        }
        k=reserve_start;
    }

    for(k=0;k<i;k++){
        pathW << path[k] << " ";
    }
}

void create_labyrinth(int row, int column){

        int gd = DETECT, gm, v, w, color, angle = 0;
        struct arccoordstype h, p;
        initwindow(600,600,"Labyrinth");
        setbkcolor(RGB(255,225,200));
        cleardevice();
        delay(2000);
        v = mousex();
        w = mousey();


}

int main()
{
    int iteration, reserve_start, number=0, target, temp_number, hold_row, hold_column;

    cout << "Labirent Boyutunu Giriniz (m,n):  ";
    cin >> row >> dummy >> column;
    cout << endl << endl;

    while(column<1){
        cout << "Lutfen Gecerli Bir Deger Giriniz (m,n):  ";
        cin >> row >> dummy >> column;
        cout << endl << endl;
    }

    hold_row=row;
    hold_column=column;

    cout << "Baslanacak Kareyi Giriniz: ";
    cin >> start;

    start = start - 1;
    cout<< endl;

    reserve_start = start;

    cout << "Hedef Kareyi Giriniz (m,n): ";

    cin >> target;

    target = target -1;

    cout<<endl;

    cout << "Iterasyon Sayisini Giriniz: ";

    cin >> iteration;

    column*=column;
    row*=row;

    srand(time(NULL));
    double lambda = 0.8;

    int k,l;
    for(k=0;k<row;k++){
        for(l=0;l<column;l++){
            rmat[k][l]=-1;
        }
    }

    for(k=0;k<row;k++){
        for(l=0;l<column;l++){
            qmat[k][l]=0;
        }
    }

    ifstream read("komsu.txt", ios::app);


    while(!read.eof()){

        read>>x;

        temp_number = x - 48;
        if(x!=',' && x!=';'){
        number = number * 10 + temp_number;
        continue;
        }
        if(x==','){
            if(number==target){
                rmat[i][number]=100;
            }
            else{
                rmat[i][number]=0;
            }
            number=0;
        }

        if(x==';'){
            if(number==target){
                rmat[i][number]=100;
            }
            else{
                rmat[i][number]=0;
            }
            i++;
            number=0;
        }

    }

    ofstream writeR("outR.txt", ios::out);

    for(k=0;k<row;k++){
        for(l=0;l<column;l++){
            writeR<<rmat[k][l]<<" ";
        }
        writeR<<endl;
    }

    for(k=0;k<row;k++){
        for(l=0;l<column;l++){
            cout<<rmat[k][l]<<" ";
        }
        cout<<endl;
    }



    for(k=0; k<iteration; k++){

        srand(time(NULL));
        start=rand()%(hold_column*hold_row);
        next = random_move(start);
        int qbig = find_big(next);
        qmat[start][next] = rmat [start][next]  + lambda * qmat[next][qbig];
        while(start!=target){
            srand(time(NULL));
            start = next;
            next = random_move(start);
            qbig = find_big(next);
            qmat[start][next] = rmat [start][next]  + lambda * qmat[next][qbig];
            cout<< start;
        }
    }




    ofstream writeQ("outQ.txt", ios::out);

    for(k=0;k<row;k++){
        for(l=0;l<column;l++){
            writeQ<<qmat[k][l]<<" ";
        }
        writeQ<<endl;
    }

    find_path(reserve_start,target);

   // create_labyrinth();

    return 0;
}
