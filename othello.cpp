#include<bits/stdc++.h>

#include <stdlib.h>

#include<chrono>

using namespace std;

int board[ 8 ][ 8 ],countBlack = 0,countwhite = 0;

typedef pair< int, int >pii;

pair<int, int> imposible;

set< pii > blackMoves;

set< pii > whilekMoves;

int maxPrft = 0,tempMax = 0;

set< pii > :: iterator it;

vector< pii >v[ 2 ];

vector< pii >storeUpdate;

vector< pii >tempStore;

vector< pii >storeWhiteUpdate;

vector< int > profit;

int X[ 8 ] ={ -1, 0, 1, -1, 1, -1, 0, 1};

int Y[ 8 ] ={ -1, -1, -1, 0, 0, 1, 1, 1};

void displayBoard();

void delay(int n)
{
    using namespace std::this_thread; // sleep_for, sleep_until

    using namespace std::chrono; // nanoseconds, system_clock, seconds

    sleep_for(nanoseconds(10));

    sleep_until(system_clock::now() + seconds(n));
}


void ifUpdatePossible(pii p,int directionInx, int diskcolour){

    if(p.first + X[ directionInx ] < 0 || p.first + X[ directionInx ] > 7 || p.second + Y[ directionInx ]  < 0 || p.second + Y[ directionInx ]  > 7){

        tempStore.clear();

        return ;

    }

    else if( board[ p.first + X[ directionInx ] ][ p.second + Y[ directionInx ] ] == -1 ){

        tempStore.clear();

        return ;

    }

    else if( board[ p.first + X[ directionInx ] ][ p.second + Y[ directionInx ] ] != diskcolour ) {

            tempStore.push_back( make_pair( p.first + X[ directionInx ], p.second + Y[ directionInx ] ) );

            ifUpdatePossible(make_pair(p.first + X[ directionInx ], p.second + Y[ directionInx ]),directionInx, diskcolour);

            return;

    }

    else if(board[ p.first + X[ directionInx ] ][ p.second + Y[ directionInx ] ] == diskcolour ){

        storeUpdate.push_back( make_pair( p.first + X[ directionInx ], p.second + Y[ directionInx ] ) );

        for(int i = 0; i < tempStore.size(); i++ ) storeUpdate.push_back(tempStore[ i ]);

        tempStore.clear();

        return ;

    }

    else{

        //storeUpdate.push_back( make_pair( p.first + X[ directionInx ], p.second + Y[ directionInx ] ) );

        tempStore.clear();

        return ;

    }

}

void initiateWhitekUpdate(pii p){



   // cout << p.first + 1 << " " <<p.second + 1<<endl;

    //board[ p.first ][ p.second ] = 1;

    for( int i = 0; i < 8; i++ ){

        ifUpdatePossible(p, i, 1);

       // tempMax += storeUpdate.size();

    }

   // cout<<storeUpdate.size()<<" "<<tempMax<<endl;

    if( storeUpdate.size() > maxPrft ){

        storeWhiteUpdate.clear();

        storeWhiteUpdate.push_back(p);

        maxPrft = storeUpdate.size();

        //profit.push_back( storeUpdate.size() );

        //tempMax = 0;

        //cout << p.first + 1 << " " <<p.second + 1<<endl;

        for( int i = 0; i < storeUpdate.size(); i++ ){

            storeWhiteUpdate.push_back(storeUpdate[ i ] );

        }

    }


    tempStore.clear();

    storeUpdate.clear();

}

void updateBoard( int inputMove){

    it = blackMoves.begin();

    for( int i = 1; i < inputMove; i++) it++;

    pair< int, int >p;

    p = *it;

    board[ p.first ][ p.second ] = 0;

    for( int i = 0; i < 8; i++ ){

        ifUpdatePossible(p, i, 0);

    }

    for( int i = 0; i < storeUpdate.size(); i++ ){

        board[ storeUpdate[ i ].first ][ storeUpdate[ i ].second ] = 0;

    }

    tempStore.clear();

    storeUpdate.clear();

    displayBoard();

}

void chooseMoves( ){

    cout << "Choose any move " << endl;

    int inputMove;

    cin >> inputMove;

    updateBoard( inputMove );

}

void showBackMoves(){

    if( blackMoves.size() == 0) cout<<" white win "<<endl;

    else{

        cout<< "Your Possible Moves Are" << endl;

        int i = 1;

        for(it = blackMoves.begin(); it != blackMoves.end(); it++, i++) {

                pii p = *it;

                cout << i << ". "<< p.first + 1 << "," <<p.second + 1<<endl;

        }

        chooseMoves();

    }

}

pii isMovePosible( pii p, int directionInx,int diskColour,int count_){

   // cout << p.first + 1 << " " <<p.second + 1<<X[ directionInx ] <<Y[ directionInx ]<<"     "<<count_ <<endl;

    if( p.first + X[ directionInx ] < 0 || p.first + X[ directionInx ] > 7 || p.second + Y[ directionInx ]  < 0 || p.second + Y[ directionInx ]  > 7 ) return make_pair( -100, -100 );

    else if( board[ p.first + X[ directionInx ] ][ p.second + Y[ directionInx ] ] == -1 && count_ <= 0)  return make_pair( -100, -100 );

    else if( board[ p.first + X[ directionInx ] ][ p.second + Y[ directionInx ] ] == diskColour) return make_pair( -100, -100 );

    else if( board[ p.first + X[ directionInx ] ][ p.second + Y[ directionInx ] ] == -1 && count_ > 0) {

       // cout << p.first + X[ directionInx ] << " " <<p.second + Y[ directionInx ]<<endl;

        int x, y;

        x = p.first + X[ directionInx ];

        y = p.second + Y[ directionInx ];

        //if ( tempMax < count_ ) tempMax = count_;

        return make_pair( x , y );

    }

    else if( board[ p.first + X[ directionInx ] ][ p.second + Y[ directionInx ] ] != diskColour ) {
            pair<int , int> temp;

            temp = make_pair( ( p.first + X[ directionInx ] ),( p.second + Y[ directionInx ]  ) );

            temp = isMovePosible( temp , directionInx, diskColour ,count_+ 1);

            return temp;

           // cout<<directionInx<<endl;

    }

}

void findBlackMoves(){

    pair< int, int >p;

    pair< int, int >p1;

    for(int i = 0; i < v[ 0 ].size(); i++){

        p = v[ 0 ][ i ];

        //cout << p.first + 1 << " " <<p.second + 1<<endl;

        for(int j = 0; j < 8; j++){

            p1 = isMovePosible( p, j, 0, 0);

            if(p1.first >= 0) blackMoves.insert(p1);

        }

    }

    showBackMoves();

}

void findWhiteMove(){

   // int count_ = 0;

   maxPrft = 0;

    pair< int, int >p;

    pair< int, int >p1;

   // pair< int, int >p2;

    for(int i = 0; i < v[ 1 ].size(); i++){

        p = v[ 1 ][ i ];

        //cout << p.first + 1 << " " <<p.second + 1<<endl;

        for(int j = 0; j < 8; j++){

            p1 = isMovePosible( p, j, 1 ,0);

            if(p1.first >= 0) whilekMoves.insert(p1);

        }

    }

    for( it = whilekMoves.begin(); it != whilekMoves.end(); it++){

        //cout << it.first + 1 << " " <<it.second + 1<<endl;

        tempMax = 0;

        initiateWhitekUpdate(*it);

    }

    for(int i = 0; i < storeWhiteUpdate.size(); i++){

        board[ storeWhiteUpdate[ i ].first ][ storeWhiteUpdate[ i ].second ] = 1 ;

    }

//    for(int i = 0; i < profit.size(); i++)  cout<<profit[i]<<" ";
//
//    cout<<endl;

    displayBoard();


}


void setBoard(){

    for(int i = 0; i < 8; i++){

        for(int j = 0; j < 8; j++) board[ i ][ j ] = -1;
    }

    board[ 3 ][ 3 ] = board[ 4 ][ 4 ] = 1;

    board[ 4 ][ 3 ] = board[ 3 ][ 4 ] = 0;

    v[ 1 ].push_back( make_pair( 3, 3) );

    v[ 1 ].push_back( make_pair( 4, 4) );

    v[ 0 ].push_back( make_pair( 3, 4) );

    v[ 0 ].push_back( make_pair( 4, 3) );


}

void displayBoard(){

   if (system("CLS")) system("clear");

    cout << "   1  2  3  4  5  6  7  8 " << endl;

    for(int i = 0; i < 8; i++){

        cout << "  ------------------------" << endl;

        cout << i + 1 << " ";

        for(int j = 0; j < 8; j++){

            cout << "|";

            if( board[ i ][ j ] == -1)  cout << " ";

            if( board[ i ][ j ] == 1)  cout << "W";

            if( board[ i ][ j ] == 0)  cout << "B";

            if( j == 7) cout << "|";

            else cout << " ";

        }

        cout <<endl;

    }
    cout << "  ------------------------" << endl;

    countBlack = countwhite = 0;

    v[0].clear();

    v[1].clear();

    blackMoves.clear();

    for(int i = 0; i < 8; i++ ){

        for(int j = 0; j < 8; j++){

            //cout<<board[ i ][ j ]<<" ";

            if(board[ i ][ j ] == 1 ){

                countwhite++;

                v[ 1 ].push_back(make_pair( i, j) );


            }


            else if(board[ i ][ j ] == 0 ){

                countBlack++;

                v[ 0 ].push_back(make_pair( i, j) );

            }

        }

        //cout<<endl;

    }

    cout<< "Count of White = "<< countwhite <<endl;

    cout<< "Count of Black = "<< countBlack <<endl;



}

int main(){

    setBoard();

    displayBoard();

    while( countwhite + countBlack < 64){

        findBlackMoves();

        delay( 5 );

        cout<< "white move processing..........."<<endl;

        findWhiteMove();


    }

    if( countBlack == 0 )   cout<<" White win " <<endl;

    else if( countwhite == 0 )   cout<<" black win " <<endl;

    else if( countwhite == countBlack )   cout<<" White win " <<endl;

    else if( countwhite > countBlack )   cout<<" White win " <<endl;





}

