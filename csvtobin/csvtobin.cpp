#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <dirent.h>
#include <stdio.h>
#include <cstring>
#include <string.h>

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
    int sz = ftell(fd);

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
    while (strToken  != NULL) {
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

    fwrite(val, sizeof(char), index-1, fs);

    fclose(fs);

    return 0;
}

int main() {
    string csvFiles[50];
    string csvFiles_output[50];
    int i = 0;
    string csv_extension = ".csv";
    string bin_extension = ".bin";

    DIR* di;
    char* ptr1, *ptr2;
    int retn;
    struct dirent* dir;
    di = opendir("."); //specify the directory name
    if (di)
    {
        while ((dir = readdir(di)) != NULL)
        {
            ptr1 = strtok(dir->d_name, ".");
            ptr2 = strtok(NULL, ".");
            if (ptr2 != NULL)
            {
                retn = strcmp(ptr2, "csv");
                if (retn == 0)
                {
                    csvFiles[i] = ptr1+ csv_extension;
                    csvFiles_output[i] = ptr1 + bin_extension;
                }
            }
            i++;
        }
        closedir(di);
    }
    for (int i = 0; i < 32; i++) {
        csvFiles[i] = csvFiles[i + 2];
        std::cout << csvFiles[i] << "\n";
    }

    for (int j = 0; j < 32; j++)
    {
        string temp_str = csvFiles[j];
        string temp_str_out = csvFiles_output[j];

        
        //Converting String to char
        int length = temp_str.length();
        char* char_array = new char[length + 1];
        strcpy(char_array, temp_str.c_str());

        length = temp_str_out.length();
        char* char_array_output = new char[length + 1];
        strcpy(char_array_output, temp_str_out.c_str());
        //remove(char_array_output);


        convertCSVtoBinaryND(char_array, char_array_output);
    }
    return 0;
}
