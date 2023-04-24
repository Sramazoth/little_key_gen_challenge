/*
==========================================
 Title:  Little program to reverse
 Author: Pouet Pouet
 Date:   11 Mars 2023
==========================================
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <regex.h>
#include <time.h>
#include <stdlib.h>

int SIZE_KEY = 14;
unsigned char* azertyuiop = "æìüþ÷ðØÝÐÅ¾¶¦£©"; // hehe bait :>

char* BANNER[] = {
"\033[1;31m______\033[0m                    ",
"\033[1;31m| ___ \\\033[0m                   ",
"\033[1;31m| |_/ /\033[0m                   ",
"\033[1;31m|  __/\033[0m                    ",
"\033[1;31m| |\033[0m                       ",
"\033[1;31m\\_|\033[0m                       ",

"\033[1;32m______\033[0m                     ",
"\033[1;32m| ___ \\\033[0m                   ",
"\033[1;32m| |_/ /\033[1;31m__\033[0m                 ",
"\033[1;32m|  __/\033[1;31m _ \\\033[0m                ",
"\033[1;32m| |\033[1;31m | (_) |\033[0m               ",
"\033[1;32m\\_|\033[1;31m  \\___/\033[0m                ",

"\033[1;33m______\033[0m                     ",
"\033[1;33m| ___ \\\033[0m                   ",
"\033[1;33m| |_/ /\033[1;32m__\033[1;31m  _   _\033[0m          ",
"\033[1;33m|  __/\033[1;32m _ \\\033[1;31m| | | |\033[0m         ",
"\033[1;33m| |\033[1;32m | (_) |\033[1;31m |_| |\033[0m         ",
"\033[1;33m\\_|\033[1;32m  \\___/\033[1;31m \\__,_|\033[0m         ",

"\033[1;34m______\033[0m                     ",
"\033[1;34m| ___ \\\033[0m                   ",
"\033[1;34m| |_/ /\033[1;33m__\033[1;32m  _   _\033[1;31m  ___\033[0m     ",
"\033[1;34m|  __/\033[1;33m _ \\\033[1;32m| | | |\033[1;31m/ _ \\\033[0m    ",
"\033[1;34m| |\033[1;33m | (_) |\033[1;32m |_| |\033[1;31m  __/\033[0m    ",
"\033[1;34m\\_|\033[1;33m  \\___/\033[1;32m \\__,_|\033[1;31m\\___|\033[0m    ",

"\033[1;35m______\033[0m                \033[1;31m_\033[0m   ",
"\033[1;35m| ___ \\\033[0m              \033[1;31m| |\033[0m  ",
"\033[1;35m| |_/ /\033[1;34m__\033[1;33m  _   _\033[1;32m  ___\033[1;31m| |_\033[0m ",
"\033[1;35m|  __/\033[1;34m _ \\\033[1;33m| | | |\033[1;32m/ _ \\\033[1;31m __|\033[0m",
"\033[1;35m| |\033[1;34m | (_) |\033[1;33m |_| |\033[1;32m  __/\033[1;31m |_\033[0m ",
"\033[1;35m\\_|\033[1;34m  \\___/\033[1;33m \\__,_|\033[1;32m\\___|\033[1;31m\\__|\033[0m"
};

/*
 * Match string against the extended regular expression in
 * pattern, treating errors as no match.
 *
 * Return 1 for match, 0 for no match.
 * (merci internet)
 */
int regex_match(const char *string, char *pattern)
{
    int    status;
    regex_t    re;

    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
        return(0);
    }
    status = regexec(&re, string, (size_t) 0, NULL, 0);
    regfree(&re);
    if (status != 0) {
        return(0);
    }
    return(1);
}

/*
 * Explicit.
 * Tout ce passe ici.
 */
int est_ce_une_bonne_cle(char* input_string)
{
    // example key : nnnnlllnnnnlll where n is a number and l a letter
    // step 1 : length
    if (strlen(input_string) != SIZE_KEY) return 1;
    // step 2 : check format number/letter
    if (regex_match(input_string, "[0-9]{4}[a-z]{3}[0-9]{4}[a-z0-9]{3}") == 0) return 2;
    // step 4 : first part [0:3] is actual year (system)
    char input_year[5];
    memcpy( input_year, &input_string[0], 4 );
    input_year[4] = '\0';
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char date[5];
    sprintf(date, "%d", tm.tm_year + 1900);
    date[4] = '\0';
    if (strcmp(date,input_year) != 0) return 3;
    // free(&input_year);
    // step 5 : second part [4:6] must have 'k' 'c' and 'o', whatever the order
    char input_second_part[4];
    memcpy( input_second_part, &input_string[4], 3 );
    if (strchr(input_second_part, 'k') == 0 || strchr(input_second_part, 'c') == 0 || strchr(input_second_part, 'o') == 0) return 4;
    // step 6 : third part [7:10] is divisible by 13 and different from 0, ex: 0026 or 0143 or 1300
    char input_third_part[5];
    memcpy( input_third_part, &input_string[7], 4 );
    int int_third_part = atoi(input_third_part);
    if (int_third_part % 13 != 0 || int_third_part == 0) return 5;
    // step 7 : fourth part [11:13] is cheksum in hexa
    char input_fourth_part[4];
    memcpy( input_fourth_part, &input_string[11], 3 );
    int basic_sum = 0;
    for (int i = 0; i < SIZE_KEY; i++)
    {
        basic_sum += input_string[i];
    }
    int checksum = (int)strtol(input_fourth_part, NULL, 16);
    if (basic_sum != checksum) return 6;
    return 0;
}

/*
 * Explicit. 
 */
void uncipher_file(char* filename)
{
    FILE *fps, *fpt;
    unsigned char ch;
    fps = fopen(filename, "rb");
    if(fps == NULL)
    {
        printf("Can't open file \033[1m%s\033[0m.\n", filename);
        return;
    }

    strcat(filename, ".c");

    fpt = fopen(filename, "wb");
    if(fpt == NULL)
    {
        printf("Can't create an output file, verify permission.\n");
        return;
    }
    
    int cpt = 0;
    ch = fgetc(fps);
    int value;
    while(ch != 255)
    {
        value = ch - azertyuiop[cpt % strlen(azertyuiop)];
        // Attention, ce qui suit n'est pas très joli :|
        if (value < 0) ch = value + 254;
        else if (value > 254) ch = value - 254;
        else ch = value;
        fputc(ch, fpt);
        ch = fgetc(fps);
        cpt += 1;
    }
    fclose(fps);
    fclose(fpt);
    printf("Done unciphering, output: \033[32m%s\033[0m\n", filename);
}

/*
 * Banner at start. 
 */
void jacky_tunning_banniere()
{
    int cpt_1 = 0;
    int cpt_2 = 0;
    while (cpt_1 < 5)
    {   
        printf("\e[1;1H\e[2J");
        cpt_2 = 0;
        while (cpt_2 < 6)
        {
            printf("%s\n", BANNER[cpt_1 * 6 + cpt_2]);
            cpt_2 += 1;
        }
        usleep(70000);
        cpt_1 += 1;
    }
}

/*
 * Explicit. 
 */
int main(int argc, char *argv[], char **envp)
{
    bool display_the_banner = true;
    bool debug_mode = false;
    bool jesuisbloque_mode = false;
    char filename[128];
    bool filename_defined = false;
    if (argc != 1) 
    {
        for (int i = 1; i < argc; ++i)
        {
            if (strcmp(argv[i], "-s") == 0)
            {
                display_the_banner = false;
            }
            else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0 
                || strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0)
            {
                debug_mode = true;
            }
            else if (strcmp(argv[i], "--gbesoindeplusdaide") == 0 || strcmp(argv[i], "--oskur") == 0)
            {
                jesuisbloque_mode = true;
            }
            else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0)
            {
                if (i+1 < argc) {
                    filename_defined = true;
                    strcpy( filename, argv[i+1] );
                    i++;
                }
            }
        }
    }
    if (display_the_banner)
    {
        jacky_tunning_banniere();
        printf("(rajouter '-s' pour skipper la bannière à la prochaine exécution)\n");        
    }
    printf("J'ai perdu le code source ¯\\_(ツ)_/¯, mais en me donnant la bonne clé ");
    printf("je pourrai sans doute le retrouver.\n");
    printf("Clé pour obtenir mon secret: ");
    char cle[64];
    fgets(cle, 64, stdin);
    cle[strcspn(cle, "\r\n")] = 0;
    int valid_key = est_ce_une_bonne_cle(cle);
    if (valid_key != 0)
    {
        printf("'%s' n'est malheuresement pas une clé valide :/\n", &cle);
        if (debug_mode)
        {
            printf("DEBUG: step \033[1m%i\033[0m of key verification reached but not validated.\n", valid_key);
        }
        if (jesuisbloque_mode)
        {
            switch (valid_key)
            {
                case 1:
                    printf("ALAIDE: Problème sur le format.\n");
                    break;
                case 2:
                    printf("ALAIDE: Toujours un problème de format mais on se rapproche.\n");
                    break;
                case 3:
                    printf("ALAIDE: Niquel pour le format, maintenant il faut un peu de connaissances en librairies c, indice: \033[1m<time.h>\033[0m.\n");
                    break;
                case 4:
                    printf("ALAIDE: Retour au primaire.\n");
                    break;
                case 5:
                    printf("ALAIDE: Retour au collège (je crois).\n");
                    break;
                case 6:
                    printf("ALAIDE: Retour au primaire le retour (en vrai c'est pas hyper simple, il va falloir vous aider d'un programme).\n");
                    break;
                default:
                    printf("ALAIDE: Je vois pas comment on peut arriver ici sans Buffer overflow ?\n"); 
            }
        }
        return -1;
    }
    if (!filename_defined) {
        printf("Bravo ! Vous avez trouvé une clé valide, il ne vous reste plus qu'à dé\033[1mcrypter\033[0m (\033[1;31m“ψ(｀∇´)ψ\033[0m) le fichier avec : \033[0;35m-f [file]\033[0m.\n");
        return 0;
    }
    uncipher_file(filename);
    return 0;
}