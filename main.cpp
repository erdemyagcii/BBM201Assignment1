#include <iostream>
#include <fstream>
#include<sstream>
using namespace std;

int main(int argc, char** argv) {


    string arr1[2];
    istringstream ss(argv[1]);
    string del1;
    int i = 0;
    while(getline(ss, del1, 'x')) {
        arr1[i] = del1;
        i++;
    }

    int mapMatrix_X = atoi(arr1[1].c_str());
    int mapMatrix_Y = atoi(arr1[0].c_str());

    int keyMatrixDegree = atoi(argv[2]);
    string mapFilePath = argv[3];
    string keyFilePath = argv[4];
    string outputFilePath = argv[5];

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int** mapMatrix = new int*[mapMatrix_Y];// Bu ifadeyi anlamadım
    for(int i = 0; i < mapMatrix_Y; i++){
        mapMatrix[i] = new int[mapMatrix_X];
    }

    ifstream readMap(mapFilePath);//artık dosyaoku nesnesi cin yerine kullanilabilir.

    string line;
    int startingX = 0;
    int startingY = 0;
    while(getline(readMap, line)){

        string arr[mapMatrix_X];
        istringstream ss(line);
        string del;
        int i = 0;
        while(getline(ss, del, ' ')) {
            arr[i] = del;
            i++;
        }

        for(int i = 0; i < mapMatrix_X; i++){
            mapMatrix[startingY][startingX] = atoi( arr[i].c_str() );
            startingX++;
        }
        startingX = 0;
        startingY += 1;
    }

    readMap.close();

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int** keyMatrix = new int*[keyMatrixDegree];// Bu ifadeyi anlamadım
    for(int i = 0; i < keyMatrixDegree; i++){
        keyMatrix[i] = new int[keyMatrixDegree];
    }

    ifstream readKey(keyFilePath);

    startingX = 0;
    startingY = 0;
    line = "";
    while(getline(readKey, line)){

        string arr2[keyMatrixDegree];
        istringstream ss(line);
        string del2;
        int i = 0;
        while(getline(ss, del2, ' ')) {
            arr2[i] = del2;
            i++;
        }

        for(int i = 0; i < keyMatrixDegree; i++){
            keyMatrix[startingY][startingX] = atoi( arr2[i].c_str() );
            startingX++;
        }
        startingX = 0;
        startingY += 1;
    }

    readKey.close();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int x = keyMatrixDegree/2;
    int y = keyMatrixDegree/2;
    int lowerBound = keyMatrixDegree/2;//aşağı merkez sınır
    int upperBoundX = (mapMatrix_X - 1) - lowerBound;//sağ merkez sınır
    int upperBoundY = (mapMatrix_Y - 1) - lowerBound;//sol merkez sınır
    int result = 0;
    int wbw;
    int di = 0;
    int dj = 0;


    ofstream  dosyaYaz(outputFilePath);
    while(true) {
        result = 0;
        for (int i = y - (keyMatrixDegree / 2); i < (y + (keyMatrixDegree / 2) + 1); i++) {
            for (int j = x - (keyMatrixDegree / 2); j < (x + (keyMatrixDegree / 2) + 1); j++) {
                result = result + (mapMatrix[i][j] * keyMatrix[i - di][j - dj]);
                wbw = result;
            }
        }
        dosyaYaz << y << "," << x << ":" << wbw << endl;
        result = result % 5;

        if(result < 0)
            result += 5;

        else if(result == 1){
            //direction = up;
            if(y - keyMatrixDegree >= lowerBound){
                y -= keyMatrixDegree;
                di -= keyMatrixDegree;
            }
            else{
                y += keyMatrixDegree;
                di += keyMatrixDegree;
            }
        }

        else if(result == 2){
            //direction = down;
            if(y + keyMatrixDegree <= upperBoundY){
                y+=keyMatrixDegree;
                di+=keyMatrixDegree;
            }
            else{
                y-=keyMatrixDegree;
                di-=keyMatrixDegree;
            }
        }

        else if(result == 3){
            //direction = right;
            if(x + keyMatrixDegree <= upperBoundX){
                x+=keyMatrixDegree;
                dj+=keyMatrixDegree;
            }
            else{
                x-=keyMatrixDegree;
                dj-=keyMatrixDegree;
            }
        }

        else if(result == 4){
            //direction = left;
            if(x - keyMatrixDegree >= lowerBound){
                x-=keyMatrixDegree;
                dj-=keyMatrixDegree;
            }
            else{
                x+=keyMatrixDegree;
                dj+=keyMatrixDegree;
            }
        }

        else if(result == 0)
            break;

    }
    dosyaYaz.close();

    return 0;
}


