#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int convertCSVtoBinaryND(char* csvFile, char* binaryFile)
{
    FILE* fd = NULL;
    //ouverture du fichier CSV
    fd = fopen(csvFile, "r");
    if (fd == NULL)
    {
        printf("\nErreur : impossible d'ouvrir le ficier d'entrée");
        return -1;
    }

    char buffer[60000];
    
    //Calcul size of file
    fseek(fd, 0L, SEEK_END);
    int sz = ftell(fd) + 1;

    /* Seek to the beginning of the file */
    fseek(fd, 0, SEEK_SET);
    //Lecture de tout le fichier
    fread(buffer, sz, sizeof(char), fd);

    fclose(fd);

    char delimitors[] = ";\r\n";
    //Parcours du fichier avec recherche du séparateur ';'
    char* strToken = strtok(buffer, delimitors);
    if (strToken == NULL)
    {
        printf("Erreur : aucun token trouvé");
        return -2;

    }

    FILE* fs = NULL;
    fs = fopen(binaryFile, "wb");
    if (fs == NULL)
    {
        printf("\nErreur : impossible d'ouvrir le ficier de sortie");
        return -3;
    }

    char val[60000];
    int index = 0;
    while (strToken != NULL) {
        //printf("%s\n", strToken);
        // On demande le token suivant.
        

        if (strToken != NULL)
        {
             //convertion en bianire
           val[index] = atoi(strToken);
           printf("\nIndex : %d, Valeur : 0x%2x", index, val[index]);
           index++;
        }

        //Next
        strToken = strtok(NULL, delimitors);
    }
    fwrite(val, sizeof(char), index, fs);
    fclose(fs);

    return 0;
}

int main() {
    char csvFile[]  = "320x80_ImageTestDeadPixelPcba_1_255.csv";
    char binaryFile []  = "output.bin";

   //convertCSVtoBinary(csvFile, binaryFile);
    convertCSVtoBinaryND(csvFile, binaryFile);

    return 0;
}